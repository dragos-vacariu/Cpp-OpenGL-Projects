#include "p19class.h"

p19class::p19class()
{
}

p19class::~p19class()
{
}
SDL_Window* p19class:: init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project19", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    context=SDL_GL_CreateContext(window);
    glewInit();
    installshaders();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "Error initializing the glew" << endl;
    }
    return window;
}

void p19class::draw(SDL_Window* window)
{
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat verts[]
    {
        0.0f,0.0f,
        1.0f,0.0f,0.0f,
        -1.0f,-1.0f,
        1.0f,0.0f,0.0f,
        1.0f,-1.0f,
        0.0f,0.0f,1.0f,
    //    0.0f,0.0f,
        -1.0f,1.0f,
        0.0f,0.0f,1.0f,
        1.0f,1.0f,
        0.0f,0.0f,1.0f
    };

    GLuint vertexbuffer; //variable to store the identifier of the buffer

    glGenBuffers(1,&vertexbuffer); //buffer generator, (generate for me 1 buffer, put the identifier in simplebuffer variable)
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); //bind the buffer, show which type of buffer it is
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // create the buffer;
    glEnableVertexAttribArray(0); //enable this state
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*5,0); //get the pointer for the position array (in verts)
    //stride= distance in bytes between a type of information until reaches again the same type of information
    //in our case the position, the stride distance began to count at the beginning of the information, and
    //and count the size of that information also. Example: we have 2 types of informations in the array above, we have
    //position and color, the stride between position is: 2floats for the position data, and 3 floats for the color data,
    //total 5 floats.

    //THESE WORK ONLY WITH SHADERS:
    glEnableVertexAttribArray(1); //1 because it's the second array.
    glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE,sizeof(float)*5, 0); //get the pointer for the color array; (in verts)

    GLushort elements[] {0,1,2,0,3,4}; //these are the elements of the buffer.
    GLuint indexbuffer; //store the identifier of the elements buffer in this variable/
    glGenBuffers(1, &indexbuffer); //generate a buffer in indexbuffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexbuffer); //bind the buffer to GL_ELEMENT_ARRAY_BUFFER point.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,GL_STATIC_DRAW); //describe the data in the buffer/
    while(1)
    {
        //glDrawArrays(GL_TRIANGLES,0,6); //draw the buffer content.
        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_SHORT, nullptr); //this function draw the elements within the buffer.
        input();
        SDL_GL_SwapWindow(window);
    }

}

void p19class::input()
{
    SDL_Event a;
    while(SDL_PollEvent(&a))
        switch(a.type)
        {
            case SDL_QUIT:
                cout << "Close the console to quit." << endl;
        }
}

void p19class::installshaders()
{
    const GLchar* vertexshaderSource = //this is the vertex shader;
    "#version 130\n"
    "in vec2 vertexPosition;\n"
    "void main(void)\n"
    "{\n"
    "gl_Position.xy=vertexPosition;\n"
    "gl_Position.z=0.0;\n"
    "gl_Position.w=1.0;\n"
    "}\0";

    const GLchar* fragmentshaderSource = //this is the fragment shader;
    "#version 130\n"
    "out vec4 color;\n"
    "void main(void)\n"
    "{\n"
    "color=vec4(1.0,0.0,0.0,1.0);\n"
    "}\0";
    GLuint vertexshaderID = glCreateShader(GL_VERTEX_SHADER); //create a vertex shader and pass its identifier to vertexshaderID
    GLuint fragmentshaderID= glCreateShader(GL_FRAGMENT_SHADER); //create a fragment shader and pass its identifier to fragmentshaderID

    const char* aux [1]; //array of one pointers;
    aux[0]=vertexshaderSource; //use this single pointer to point to firstvertexshader;
    glShaderSource(vertexshaderID,1,aux,0); //create a shader source;
    aux[0]=fragmentshaderSource; //aux is now pointing to firstfragmentshader
    glShaderSource(fragmentshaderID,1,aux,0); //create a shader source;

    glCompileShader(vertexshaderID); //compile the shader;
    glCompileShader(fragmentshaderID); //compile the shader;

    GLint success=0;
    GLchar infolog[512]; //this will take the compilation/liking error messages/log
    glGetShaderiv(vertexshaderID, GL_COMPILE_STATUS, &success); //check the shader's integer value;
    if(success==GL_FALSE) // if compilation was not successful
    {
        glGetShaderInfoLog(vertexshaderID, 512, 0, infolog); //get the message;
        cout << "Error compiling vertex shader!" << endl;
        cout << infolog << endl;
    }

    glGetShaderiv(fragmentshaderID, GL_COMPILE_STATUS, &success); //check the shader's integer value;
    if(success==GL_FALSE) //if the compilation was not successful
    {
        glGetShaderInfoLog(fragmentshaderID, 512, 0, infolog); //get the message
        cout << "Error compiling the fragment shader!" << endl;
        cout << infolog << endl;
    }
    GLuint programID=glCreateProgram(); //create a program
    glAttachShader(programID, vertexshaderID); //attach the vertex shader to the program,
    glAttachShader(programID, fragmentshaderID); //attach the fragment shader to the program
    glLinkProgram(programID); // link the pieces of the program
    glGetProgramiv(programID, GL_LINK_STATUS, &success); //get the program's integer value;
    if(!success) // if the linking was not successful
    {
        glGetProgramInfoLog(programID, 512, 0, infolog); //get the message;
        cout << "Error linking the program!" << endl;
        cout << infolog << endl;
    }
    glDeleteShader(vertexshaderID); //the shader is now in the program, so we don't need this anymore.
    glDeleteShader(fragmentshaderID); //the shader is now in the program. so we don't need this anymore;
    glUseProgram(programID);  // use the program

}
