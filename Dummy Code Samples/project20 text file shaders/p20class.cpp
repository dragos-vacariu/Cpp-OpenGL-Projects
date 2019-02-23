#include "p20class.h"

p20class::p20class()
{
}

p20class::~p20class()
{
}
SDL_Window* p20class::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project20", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 640,480,SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    context=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "Error! Glew has failed to initialize." << endl;
    }
    return window;
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
void p20class::draw(SDL_Window* window)
{
    GLfloat triangle []
    {
        -0.2,0.2,
        0.4,0.2,
        -0.2,-0.6
    };

    GLuint triangleBufferID;//store the identifier of this buffer
    glGenBuffers(1, &triangleBufferID); //generate one buffer
    glBindBuffer(GL_ARRAY_BUFFER, triangleBufferID); //bind the buffer for GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW); //describe the data in the buffer
    glEnableVertexAttribArray(0); //enable the buffer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0); //Get the pointer for the buffer.

    //SECOND SHADER TYPE (READ FROM FILE):
    const GLchar* vertexshaderPath = "vertexshader.vsh"; //glchar pointer (like string), to get filepath of vertexshader;
    const GLchar* fragmentshaderPath = "fragmentshader.fsh"; //glchar pointer, to get filepath of fragmentshader;
    string vertexshaderSource = ""; //getting a string to store the source code of vertexshader.vsh
    string fragmentshaderSource = ""; //getting a string to store the source code of fragmentshader.fsh
    ifstream vertexfile; //getting a file pointer for vertexshader.vsh;
    ifstream fragmentfile; //getting a file pointer for fragmentshader.fsh;
    vertexfile.exceptions (ifstream::badbit); //add exceptions to the file pointer;
    fragmentfile.exceptions (ifstream::badbit); //add exceptions to the file pointer;
    try //try to do this even with badbit
    {
        vertexfile.open(vertexshaderPath); //open vertexshader.vsh
        fragmentfile.open(fragmentshaderPath); //open fragmentshader.fsh
        stringstream vfstream, ffstream; //get two stringstream object;
        vfstream << vertexfile.rdbuf(); //get the content of vertexshader.vsh into a stringstream;
        ffstream << fragmentfile.rdbuf(); //get the content of fragmentshader.fsh into a stringstream;
        vertexfile.close(); //close the file;
        fragmentfile.close(); //close the file;
        vertexshaderSource=vfstream.str(); //copy the string from stringstream into vertexshaderSource;
        fragmentshaderSource=ffstream.str(); //copy the string from stringstream into fragmentshaderSource;
    }
    catch (ifstream::failure e) //if failure caught...
    {
        cout << "Error, file is unreadable!" << endl;
    }
    const GLchar* vscode = vertexshaderSource.c_str(); //create a GLchar pointer (like a string) to store vertexshaderSource
    //converted into c_str();
    const GLchar* fscode = fragmentshaderSource.c_str(); //create a GLchar pointer (like a string) to store fragmentshaderSource
    //converted into c_str();

    //THIS PART FOR ALL WAYS:
    GLuint vertexshaderID=glCreateShader(GL_VERTEX_SHADER); //create a shader
    glShaderSource(vertexshaderID,1,&vscode,nullptr);
    glCompileShader(vertexshaderID); //compile shader;
    GLint success;
    GLchar infolog[512];
    glGetShaderiv(vertexshaderID, GL_COMPILE_STATUS, &success);
    if(!success) //check the compilation results
    {
        glGetShaderInfoLog(vertexshaderID,512,0,infolog);
        cout << "Error vertex shader's compilation failed" << endl;
        cout << infolog << endl;
    }
    GLuint fragmentshaderID=glCreateShader(GL_FRAGMENT_SHADER); //create a shader
    glShaderSource(fragmentshaderID,1,&fscode, nullptr);
    glCompileShader(fragmentshaderID); //compile shader
    glGetShaderiv(fragmentshaderID,GL_COMPILE_STATUS,&success);
    if(!success) //check the compilation results
    {
        glGetShaderInfoLog(fragmentshaderID,512,0,infolog);
        cout << "Error fragment shader's compilation failed" << endl;
        cout << infolog << endl;
    }
    GLuint programID = glCreateProgram(); //create a program;
    glAttachShader(programID, vertexshaderID); //attach vertexshader to the program;
    glAttachShader(programID, fragmentshaderID); //attach fragmentshader to the program;

    glLinkProgram(programID); //link the pieces of the program;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if(!success) //check the link status;
    {
        glGetProgramInfoLog(programID,512,0,infolog);
        cout << "Error linking the program" << endl;
        cout << infolog << endl;
    }
    glDeleteShader(vertexshaderID);
    glDeleteShader(fragmentshaderID);

    glUseProgram(programID); //use the program;
    while(1)
    {
        glDrawArrays(GL_TRIANGLES, 0, 3); //draw elements in the buffer.
        input();
        SDL_GL_SwapWindow(window);
    }

}
