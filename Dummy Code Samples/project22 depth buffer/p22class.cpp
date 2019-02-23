#include "p22class.h"

p22class::p22class()
{
}
p22class::~p22class()
{
}
SDL_Window* p22class::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project22", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,600, SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    context=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "Glew has failed to initialize!" << endl;
        exit(1);
    }
    return window;
}
void p22class::draw(SDL_Window* window)
{
    glEnable(GL_DEPTH_TEST); //this will enable the depth buffer, the possibility of rendering in 3d (activates the Z coordinate),
    //and use the depths, on the screen. Example see the effects: comment the glEnable(GL_DEPTH_TEST), and
    //glClear(GL_DEPTH_BUFFER_BIT), lines to see the results.
    GLuint programID;
    programID=installshaders();

    GLfloat triangle[] {-0.8,-0.8,0.0, 0.8,-0.8,0.0,

    0.0,0.8,-0.5, //the blue triangle's edge.

    -0.8,0.8,0.0, 0.8,0.8,0.0, 0.0,

    -0.8,-0.1}; //the red triangle's edge.

    GLfloat color [] {1.0,0.0,0.0 ,0.0,1.0,0.0, 0.0,0.0,1.0, 1.0,0.0,0.0, 1.0,1.0,1.0, 1.0,0.0,0.0};

    GLuint bufferID;
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint colorID, colorlocation;
    glGenBuffers(1, &colorID);
    colorlocation=glGetAttribLocation(programID, "color");
    glBindBuffer(GL_ARRAY_BUFFER, colorID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorlocation);
    glVertexAttribPointer(colorlocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint elements[] {0,1,2,3,4,5};
    GLuint indices;
    glGenBuffers(1,&indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    while(1)
    {
         glClear(GL_DEPTH_BUFFER_BIT); //clear the depth buffer, from default values (1.0) to whatever, my
         //vertices values are.

       // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        SDL_GL_SwapWindow(window);
        input();
    }
}

void p22class::input()
{
    SDL_Event a;
    while(SDL_PollEvent(&a))
    {
        switch(a.type)
        {
            case SDL_QUIT:
                exit(1);
        }
    }
}

GLuint p22class::installshaders()
{
    GLchar* vertexShaderFilePath = "vertexshader.vsh";
    GLchar* fragmentShaderFilePath = "fragmentshader.fsh";
    GLuint vertexshaderID;
    vertexshaderID = glCreateShader(GL_VERTEX_SHADER);
    ifstream vertexfile;
    vertexfile.open(vertexShaderFilePath);
    if(!vertexfile.good())
    {
        cout << "Error opening the Vertex Shader File!" << endl;
        return 0;
    }
    string line;
    string fcontent;
    while(getline(vertexfile,line))
    {
        fcontent+=line + "\n";
    }
    const GLchar* vertexshaderCode = fcontent.c_str();
    glShaderSource(vertexshaderID, 1, &vertexshaderCode, nullptr);
    glCompileShader(vertexshaderID);

    GLint compilationStatus;
    glGetShaderiv(vertexshaderID, GL_COMPILE_STATUS, &compilationStatus);
    if(!compilationStatus)
    {
        GLint infolenght;
        glGetShaderiv(vertexshaderID, GL_INFO_LOG_LENGTH, &infolenght);
        GLchar infolog[infolenght];
        glGetShaderInfoLog(vertexshaderID, infolenght, 0, infolog);
        cout << infolog << endl;
        return 0;
    }
    GLuint fragmentshaderID;
    fragmentshaderID=glCreateShader(GL_FRAGMENT_SHADER);
    ifstream fragmentfile;
    fragmentfile.open(fragmentShaderFilePath);
    if(!fragmentfile.good())
    {
        cout << "Error reading the Fragment Shader File!" << endl;
        return 0;
    }
    fcontent="";
    while(getline(fragmentfile, line))
    {
        fcontent+=line + "\n";
    }
    const GLchar* fragmentshaderCode = fcontent.c_str();
    glShaderSource(fragmentshaderID,1,&fragmentshaderCode,nullptr);
    glCompileShader(fragmentshaderID);
    glGetShaderiv(fragmentshaderID, GL_COMPILE_STATUS, &compilationStatus);
    if(!compilationStatus)
    {
        GLint infolenght2;
        glGetShaderiv(fragmentshaderID, GL_INFO_LOG_LENGTH, &infolenght2);
        GLchar infolog2[infolenght2];
        glGetShaderInfoLog(fragmentshaderID, infolenght2, 0, infolog2);
        cout << infolog2 << endl;
        return 0;
    }
    GLuint programID;
    programID=glCreateProgram();
    glAttachShader(programID, vertexshaderID);
    glAttachShader(programID, fragmentshaderID);
    glLinkProgram(programID);

    glDeleteShader(vertexshaderID);
    glDeleteShader(fragmentshaderID);

    glUseProgram(programID);

    return programID;

}
