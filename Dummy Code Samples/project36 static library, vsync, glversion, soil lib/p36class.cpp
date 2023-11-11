#include "p36class.h"
//The static library is project36staticlibrary, this also must be linked to the IDE.

extern "C" int returnten (); //declare an extern function
extern "C" char* strING (); //declare an extern function

p16class::p16class()
{
}
p16class::~p16class()
{
}

unsigned int p16class::loadtexture(const char* filename) //Function that will load the texture;
{
    //Use these variables to store the width and the heights of the images;
    int width, height;
    //Use the SOIL library, SOIL.h, and important: SOIL.c added to the project:
    //for the next function to work;
    unsigned char* image2 = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
    //SOIL reads all the image file formats
    if(image2==nullptr)
    {
        cout << "Image: " << filename << " has failed to load!" << endl;
        return 0;
    }
    unsigned int id; //variable to take the id of generated texture buffer;
    glGenTextures(1, &id); //generate a texture buffer;
    glBindTexture(GL_TEXTURE_2D, id); //bind the texture buffer;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2); //describe the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//set parameter 1 blurry far side
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //set parameter 2 blurry close side
    SOIL_free_image_data(image2); //delete the content of the pointer, after the texture is sent into a buffer.

    return id; //return the id of the texture;
}

SDL_Window* p16class::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project36", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    context=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "Error initializing the glew!" << endl;
    }
    else
    {
        cout << "Glew has been successfully initialized!" << endl;
    }
    return window;
}

void p16class::draw(SDL_Window* window)
{
    unsigned int texture1, texture2, texture3, texture4, texture5, texture6;
    bool closeWindow=false;
    SDL_Event a;

    //translating the coordinates.
    glViewport(0,0,640,480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10,640,-10,480,-500,500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //done translating the coordinates

    //for lighting
    GLfloat pos [] {10, 500, 0};
    GLfloat pos2 [] {650, 100, -10};

    GLfloat ambient [] {1.0,1.0,1.0,1.0};
    GLfloat ambient2 [] {0.0,1.0,0.0,1.0};

    GLfloat diffuse [] {0.0,0.0,1.0,1.0};
    GLfloat diffuse2 [] {1.0, 1.0, 0.0, 1.0};


    glEnable(GL_DEPTH_TEST); //enable the depth buffer/
    glEnable(GL_TEXTURE_2D); //enable the texture 2d
    texture1=loadtexture("8.jpg"); //get the texture into this function,
    texture2=loadtexture("2.bmp");
    texture3=loadtexture("3.bmp");
    texture4=loadtexture("4.bmp");
    texture5=loadtexture("7.bmp");
    texture6=loadtexture("6.bmp");

    cout << returnten() << endl; //call for external function, from project36staticlibrary
    cout << strING() << endl;//call for external function from project36staticlibrary

    SDL_GL_SetSwapInterval(1); //activate V-SYNC.
    cout << "Your OpenGL Version is: " << glGetString(GL_VERSION) << endl; //get the OpenGL Version.

   while(1)
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glTranslatef(1.0,-1.0,1.0); //move the rotating image around
        glRotatef(1,1.0,1.0,0.0); //rotate the image.

        glBindTexture(GL_TEXTURE_2D, texture1); //activate the texture1;

        glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0); //set texture corner coordinate
        glNormal3f(0.0,0.0,1.0);
        glVertex3f(200,200, 0);
        glTexCoord2f(0.0,0.0), //set the texture corner coordinate
        glVertex3f(200,400, 0);
        glTexCoord2f(1.0,0.0); //set the texture corner coordinate
        glVertex3f(400,400, 0);
        glTexCoord2f(1.0,1.0); //set the texture corner coordinate
        glVertex3f(400,200, 0);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture2); // activate the texture2;

        glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0); //set texture corner coordinate
        glNormal3f(-1.0,0.0,0.0);
        glVertex3f(200,200, 0);
        glTexCoord2f(0.0,0.0), //set the texture corner coordinate
        glVertex3f(200,400, 0);
        glTexCoord2f(1.0,0.0); //set the texture corner coordinate
        glVertex3f(200,400, -200);
        glTexCoord2f(1.0,1.0); //set the texture corner coordinate
        glVertex3f(200,200, -200);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture3); //activate texture3;

        glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0); //set texture corner coordinate
        glNormal3f(0.0,0.0,-1.0);
        glVertex3f(200,200, -200);
        glTexCoord2f(0.0,0.0), //set the texture corner coordinate
        glVertex3f(200,400, -200);
        glTexCoord2f(1.0,0.0); //set the texture corner coordinate
        glVertex3f(400,400, -200);
        glTexCoord2f(1.0,1.0); //set the texture corner coordinate
        glVertex3f(400,200, -200);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture4); //activate texture4;

        glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0); //set texture corner coordinate
        glNormal3f(1.0,0.0,0.0);
        glVertex3f(400,200, 0);
        glTexCoord2f(0.0,0.0), //set the texture corner coordinate
        glVertex3f(400,400, 0);
        glTexCoord2f(1.0,0.0); //set the texture corner coordinate
        glVertex3f(400,400, -200);
        glTexCoord2f(1.0,1.0); //set the texture corner coordinate
        glVertex3f(400,200, -200);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture5); //activate texture5;

        glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0); //set texture corner coordinate
        glNormal3f(0.0,1.0,0.0);
        glVertex3f(200,400, 0);
        glTexCoord2f(0.0,0.0), //set the texture corner coordinate
        glVertex3f(200,400, -200);
        glTexCoord2f(1.0,0.0); //set the texture corner coordinate
        glVertex3f(400,400, -200);
        glTexCoord2f(1.0,1.0); //set the texture corner coordinate
        glVertex3f(400,400, 0);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texture6); //activate texture6;

        glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0); //set texture corner coordinate
        glNormal3f(0.0,-1.0, 0.0);
        glVertex3f(200,200, 0);
        glTexCoord2f(0.0,0.0), //set the texture corner coordinate
        glVertex3f(200,200, -200);
        glTexCoord2f(1.0,0.0); //set the texture corner coordinate
        glVertex3f(400,200, -200);
        glTexCoord2f(1.0,1.0); //set the texture corner coordinate
        glVertex3f(400,200, 0);
        glEnd();

        SDL_Delay(50); //short delay;
        SDL_GL_SwapWindow(window);


        while(SDL_PollEvent(&a))
        {
            switch(a.type)
            {
                case SDL_QUIT:
                {
                   closeWindow=true;
                    break;
                }
            }
        }
        if(closeWindow==true)
        {
            break;
        }
    }
    SDL_DestroyWindow(window);
    cout << "Program closed!" << endl;
}

GLuint p16class::installshaders() //Function to install the shaders.
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

const GLchar* p16class::readfile(ifstream &FILE, GLchar* shaderpath) //Function that reads shaders from files.
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
void p16class::compilationErrors(GLuint shadername) //Function that check if the compilation of shaders succeeded.
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
void p16class::linkingErrors(GLuint programID) //Function that check if the Program was Linked properly.
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
