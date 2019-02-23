#include "p20class.h"

p20class::p20class()
{
    //ctor
}

p20class::~p20class()
{
    //dtor
}
SDL_Window* p20class::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project21", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,600, SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    context=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "GLEW has failed to initialize!" << endl;
    }
    return window;
}
void p20class::draw(SDL_Window* window)
{
    GLuint programID=installshaders();
    GLfloat triangle[]
    {
      0.2,0.2,
      0.6,0.2,
      0.4,0.5,
      -0.6,0.0,
      0.4,-0.5,
    };
    GLfloat color[]
    {
        1.0,0.0,0.0,
        0.0,1.0,0.0,
        0.0,0.0,1.0,
        0.0,1.0,1.0,
        1.0,0.0,1.0
    };
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    GLuint trianglebufferID;
    glGenBuffers(1, &trianglebufferID);
    glBindBuffer(GL_ARRAY_BUFFER, trianglebufferID);
    glBufferData(GL_ARRAY_BUFFER,sizeof(triangle), triangle, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE, 0, 0);

    GLint colorlocation;
    GLuint colorbufferID;
    glGenBuffers(1,&colorbufferID);
    colorlocation = glGetAttribLocation(programID, "color");
    glBindBuffer(GL_ARRAY_BUFFER, colorbufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorlocation);
    glVertexAttribPointer(colorlocation,3,GL_FLOAT,GL_FALSE,0,0);

    GLuint vertices[] = {0,1,2,0,3,4};
    //important to use for vertices only GLuint, and GLushort;
    GLuint indices;
    glGenBuffers(1, &indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    while(1)
    {
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, nullptr);
        SDL_GL_SwapWindow(window);
        input();
    }
}

GLuint p20class::installshaders() //function that install the shaders
{
    const GLchar* vertexShaderFilePath = "vertexshader.vsh"; //this is the filepath for vertexshader
    const GLchar* fragmentShaderFilePath = "fragmentshader.fsh"; //this is the filepath for fragmentshader

    GLuint vertexshaderID, fragmentshaderID; //make 2 identifiers one for each shader.
    vertexshaderID=glCreateShader(GL_VERTEX_SHADER); //create a vertex shader and store its identifier in vertexshaderID
    fragmentshaderID=glCreateShader(GL_FRAGMENT_SHADER);
    ifstream vertexfile; //pointer to a file;
    ifstream fragmentfile;
    string line=""; //string initialized to nothing;
    string fcontent="";
    vertexfile.open(vertexShaderFilePath); //open the file;
    while(getline(vertexfile,line)) //read line by line
    {
        fcontent += line + "\n"; //fcontent takes every line and puts after it, a \n
    }
    vertexfile.close(); //close the file once we're done with it;
    const GLchar* vertexshadercode=fcontent.c_str(); //make a new string to keep all the data into it;
    //  cout << vertexshadercode << endl;
    glShaderSource(vertexshaderID,1, &vertexshadercode, nullptr); //add the sourcecode of the shader to its ID;
    //IMPORTANT: the order of doing these operations is important, vertexshadercode changes it's value if it's moved.
    fcontent=""; //initialize the string
    line="";
    fragmentfile.open(fragmentShaderFilePath); //open the file;
    while(getline(fragmentfile, line)) //read line by line;
    {
        fcontent += line + "\n"; //get all the content line by line;
    }
    const GLchar* fragmentshadercode=fcontent.c_str(); //store the code into this string;
    fragmentfile.close(); //close the file;

   // cout << fragmentshadercode << endl;
    glShaderSource(fragmentshaderID,1,&fragmentshadercode, nullptr); //get the source code to it's ID;

    glCompileShader(vertexshaderID); //compile the shader;
    GLint success=0;
    GLchar infolog[512];
    glGetShaderiv(vertexshaderID, GL_COMPILE_STATUS, &success);
    if(!success) //check for success
    {
        cout << "Error compiling the fragment shader's code!" << endl;
        glGetShaderInfoLog(vertexshaderID, 512, 0, infolog);
        cout << infolog << endl;
    }
    glCompileShader(fragmentshaderID); //compile the shader;

    glGetShaderiv(fragmentshaderID, GL_COMPILE_STATUS, &success);
    if(!success) //check for success;
    {
        cout << "Error compiling the vertex shader's code!" << endl;
        glGetShaderInfoLog(fragmentshaderID, 512, 0, infolog);
        cout << infolog << endl;
    }
    GLuint programID = glCreateProgram(); //create a program;

    glAttachShader(programID, vertexshaderID); //attach the shaders to it;
    glAttachShader(programID, fragmentshaderID);

    glLinkProgram(programID); //link the pieces of the program;
    glGetProgramiv(programID,GL_LINK_STATUS, &success);
    if(!success) //check for success;
    {
        cout << "Error linking the program!" << endl;
        glGetProgramInfoLog(programID, 512, 0, infolog);
        cout << infolog << endl;
    }

    glDeleteShader(vertexshaderID); //delete shaders;
    glDeleteShader(fragmentshaderID);
    glUseProgram(programID); //use the program which already contains the shaders;
    return programID;
}
void p20class::input()
{
    SDL_Event a;
    while(SDL_PollEvent(&a))
        switch(a.type)
        {
            case SDL_QUIT:
                cout << "Close the console to quit!" << endl;
        }
}
