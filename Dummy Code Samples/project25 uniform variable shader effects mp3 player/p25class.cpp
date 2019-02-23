#include "p25class.h"

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
    float speed;
    float operation;

    glEnable(GL_DEPTH_TEST); //this will enable the depth buffer, the possibility of rendering in 3d (activates the Z coordinate),
    //and use the depths, on the screen. Example see the effects: comment the glEnable(GL_DEPTH_TEST), and
    //glClear(GL_DEPTH_BUFFER_BIT), lines to see the results.
    GLuint programID;
    programID=installshaders();
    GLfloat time=0;

    GLfloat square[] {-1.0f,1.0f,0.0f, 1.0f,1.0f,0.0f, 1.0f,-1.0f,0.0f,  -1.0f, -1.0f, 0.0f};

    GLfloat color [] {1.0,0.0,0.0 ,0.0,1.0,0.0, 0.0,0.0,1.0, 1.0,0.0,0.0};

    GLuint bufferID;
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint colorID, colorlocation;
    glGenBuffers(1, &colorID);
    colorlocation=glGetAttribLocation(programID, "color");
    glBindBuffer(GL_ARRAY_BUFFER, colorID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorlocation);
    glVertexAttribPointer(colorlocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint elements[] {0,1,2,3};
    GLuint indices;
    glGenBuffers(1,&indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    GLint timelocation = glGetUniformLocation(programID, "time"); //get uniform location.

    if(SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        cout << "Failed to open the audio file!" << endl;
    }

    while(1)
    {
        operation=rand()%2; //get random operation for the time which will be sent to fragment shader.
        speed=((rand()%6)+1)*0.02f; //getting a value for addition or subtraction...
        glUniform1f(timelocation, time); //uniform location attribute
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the depth buffer, from default values (1.0) to whatever, my
         //vertices values are.
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);

        SDL_GL_SwapWindow(window);
        input();
        if(operation == 1)
        {
            time+=speed; //use addition.
        }
        if(operation == 0)
        {
            time-=speed; //use subtraction
        }
    }
}

void p22class::input()
{
    Mix_Music* music1; //music file pointer;
    Mix_Music* music2;
    Mix_Music* music3;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096); //open all the music in this way.
    music1 = Mix_LoadMUS("1.black"); //music location;
    music2 = Mix_LoadMUS("2.black");
    music3 = Mix_LoadMUS("3.black");

    SDL_Event a;
    while(SDL_PollEvent(&a))
    {
        if(a.type==SDL_KEYDOWN)
        switch(a.key.keysym.sym)
        {
            case SDL_QUIT:
                exit(1);

            case SDLK_1:
                {
                    system("cls");
                    Mix_PlayMusic(music1,0); //play music1.
                    cout << "Playing the track NO: 1!" << endl;
                    break;
                }
            case SDLK_2:
                {
                    system("cls");
                    Mix_PlayMusic(music2,0); //play music2.
                    cout << "Playing the track NO: 2!" << endl;
                    break;
                }
            case SDLK_3:
                {
                    system("cls");
                    Mix_PlayMusic(music3,0); //play music3.
                    cout << "Playing the track NO: 3!" << endl;
                    break;
                }
            case SDLK_SPACE:
                {
                    cout << "Music is paused!" << endl;
                    Mix_PauseMusic(); //pause music.
                    break;
                }

        }
    }
}
GLuint p22class::installshaders()
{
    GLchar* vertexShaderFilePath = "vertexshader.vsh"; //path for vertexshader.
    GLchar* fragmentShaderFilePath = "fragmentshader.fsh"; //path for fragmentshader.
    GLuint vertexshaderID; //identifier for vertexshader.
    vertexshaderID = glCreateShader(GL_VERTEX_SHADER); //create a vertex shader.
    ifstream vertexfile; //file pointer for inputting (reading).
    vertexfile.open(vertexShaderFilePath); //file pointer open the file.
    if(!vertexfile.good()) //if the file is not good (opened);
    {
        cout << "Error opening the Vertex Shader File!" << endl;
        return 0; //end the function call.
    }
    string line;  //string for the line.
    string fcontent; //string for all the content of file;
    while(getline(vertexfile,line)) //get every line within the file
    {
        fcontent+=line + "\n"; //store every line in the fcontent, put "\n" at the end of each line.
    }
    const GLchar* vertexshaderCode = fcontent.c_str(); //store fcontent converted to c_str into this new char* variable.
    glShaderSource(vertexshaderID, 1, &vertexshaderCode, nullptr); //associate the vertex source code to vertexshaderID.
    glCompileShader(vertexshaderID); //compile the vertexshaderID;

    GLint compilationStatus; //variable that is used to store the compilation status
    glGetShaderiv(vertexshaderID, GL_COMPILE_STATUS, &compilationStatus); //return a value for the compilation status
    if(!compilationStatus) //if was not compiled
    {
        GLint infolenght; //create a variable to get the lenght of the error message.
        glGetShaderiv(vertexshaderID, GL_INFO_LOG_LENGTH, &infolenght); //get the lenght of the error message
        GLchar infolog[infolenght]; //create an array to store exactly the lenght of the error message
        glGetShaderInfoLog(vertexshaderID, infolenght, 0, infolog); // store the error message
        cout << infolog << endl; //print the error message.
        return 0; //end the function call.
    }
    GLuint fragmentshaderID; //create an identifier for the fragmentshader.
    fragmentshaderID=glCreateShader(GL_FRAGMENT_SHADER); //create a fragment shader
    ifstream fragmentfile; //input file pointer for the fragment shader code file.
    fragmentfile.open(fragmentShaderFilePath); //open the file pointer to read from the file
    if(!fragmentfile.good()) //if the file was not opened.
    {
        cout << "Error reading the Fragment Shader File!" << endl;
        return 0;
    }
    fcontent=""; //initialize the fcontent string.
    while(getline(fragmentfile, line)) //read line by line from the file
    {
        fcontent+=line + "\n"; //store each line into the fcontent string and add "\n" at the end of each one.
    }
    const GLchar* fragmentshaderCode = fcontent.c_str(); //store the content of fcontent converted to c_str() into this variable.
    glShaderSource(fragmentshaderID,1,&fragmentshaderCode,nullptr); //associate the code to fragmentshader.
    glCompileShader(fragmentshaderID); //compile the fragmentshader
    glGetShaderiv(fragmentshaderID, GL_COMPILE_STATUS, &compilationStatus); //get compilation status.
    if(!compilationStatus) //if was not compiled successfully
    {
        GLint infolenght2; //for infolenght
        glGetShaderiv(fragmentshaderID, GL_INFO_LOG_LENGTH, &infolenght2); //get infolenght.
        GLchar infolog2[infolenght2]; //for info log
        glGetShaderInfoLog(fragmentshaderID, infolenght2, 0, infolog2); //get info log
        cout << infolog2 << endl; //print info log
        return 0; // end the function call.
    }
    GLint programID; //create a program;
    programID=glCreateProgram();
    glAttachShader(programID, vertexshaderID); //attach shaders
    glAttachShader(programID, fragmentshaderID);
    glLinkProgram(programID); //link the program;

    glDeleteShader(vertexshaderID); //delete each shader
    glDeleteShader(fragmentshaderID);

    glUseProgram(programID); //use the program.

    return programID; //everything was successfully return the program ID for later uses.

}
