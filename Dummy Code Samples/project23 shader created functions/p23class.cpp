#include "p23class.h"

p23class::p23class()
{

}
p23class::~p23class()
{
}
SDL_Window* p23class::init() //function to initialize everything we need.
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project23", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,600, SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    context=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "Glew has failed to initialize!" << endl;
        return 0;
    }
    return window;
}

void p23class::draw(SDL_Window* window) //the function that does the drawing.
{
//glEnable(GL_DEPTH_TEST); //this will enable the depth buffer, the possibility of rendering in 3d (activates the Z coordinate),
    //and use the depths, on the screen. Example see the effects: comment the glEnable(GL_DEPTH_TEST), and
    //glClear(GL_DEPTH_BUFFER_BIT), lines to see the results.
    GLuint programID;
    programID=installshaders();

    GLfloat triangle[] {-0.2,0.2,0.0, 0.7,-0.2,0.0,

    0.0,0.8,0.0, //the blue triangle's edge.

    -0.8,-0.2,0.0, 0.1,-0.8,0.0, -0.5,

    -0.8,0.0}; //the red triangle's edge.

    GLfloat color [] {1.0,1.0,1.0 ,1.0,0.0,0.0, 1.0,1.0,0.0, 1.0,0.0,0.0, 1.0,1.0,1.0, 1.0,0.0,0.0};

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
      //   glClear(GL_DEPTH_BUFFER_BIT); //clear the depth buffer, from default values (1.0) to whatever, my
         //vertices values are.

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        SDL_GL_SwapWindow(window);
        input();
    }
}

void p23class::input() //Function to check the keyboard input, in this case checks only if the X button from the window
//has been pressed.
{
    SDL_Event a;
    while(SDL_PollEvent(&a))
        switch(a.type)
        {
            case SDL_QUIT:
                exit(1);
        }
}

GLuint p23class::installshaders() //Function to install the shaders.
{
    GLchar* vertexShaderFilePath = "vertexshader.vsh";
    GLchar* fragmentShaderFilePath = "fragmentshader.fsh";

    ifstream vertexfile;
    const GLchar* vertexshaderCode = readfile(vertexfile, vertexShaderFilePath);

    GLuint vertexshaderID, fragmentshaderID;

    vertexshaderID=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshaderID, 1, &vertexshaderCode, nullptr);
    glCompileShader(vertexshaderID);
    compilationErrors(vertexshaderID);

    ifstream fragmentfile;
    const GLchar* fragmentshaderCode = readfile(fragmentfile, fragmentShaderFilePath);
    fragmentshaderID=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshaderID, 1, &fragmentshaderCode, nullptr);
    glCompileShader(fragmentshaderID);
    compilationErrors(fragmentshaderID);

    GLuint programID;
    programID=glCreateProgram();
    glAttachShader(programID, vertexshaderID);
    glAttachShader(programID, fragmentshaderID);
    glLinkProgram(programID);

    linkingErrors(programID);

    glUseProgram(programID);
    return programID;
}

const GLchar* p23class::readfile(ifstream &FILE, GLchar* shaderpath) //Function that reads shaders from files.
{
    FILE.open(shaderpath);
    if(!FILE.good())
    {
        cerr << "The file could not be loaded!" << endl;
        return 0;
    }
    string line, fcontent = "";
    while(getline(FILE, line))
    {
        fcontent+=line + "\n";
    }
    const GLchar* shadercode = fcontent.c_str(); //converting to a pointer to a c_string;
    return shadercode;
}
void p23class::compilationErrors(GLuint shadername) //Function that check if the compilation of shaders succeeded.
{
    GLint success;
    glGetShaderiv(shadername, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        GLint lenght;
        glGetShaderiv(shadername, GL_INFO_LOG_LENGTH, &lenght);
        GLchar infolog[lenght];
        glGetShaderInfoLog(shadername, lenght, 0, infolog);
        cout << infolog << endl;
        exit(1);
    }
}
void p23class::linkingErrors(GLuint programID) //Function that check if the Program was Linked properly.
{
    GLint success;
    glGetShaderiv(programID, GL_LINK_STATUS, &success);
    if(!success)
    {
        GLint lenght;
        glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &lenght);
        GLchar infolog[lenght];
        glGetShaderInfoLog(programID, lenght, 0, infolog);
        cout << infolog << endl;
        exit(1);
    }
}
