// License work4, animation using sprites
//

#include "StdAfx.h"
#include <custom/SDL.h>
#include <custom/glew.h>
#include <iostream>
#include <custom/SOIL.h>
#include <fstream>
#include <string>
#define GLEW_STATIC

using namespace std;

int Control (struct ElementCoordinates *menuNewGame);
bool IsHeroKicking, IsHeroFighting=false;
GLuint Load_Texture(const char* filename);
GLuint Install_Shaders() ;
float getH(int number);
float getV(int number);
GLuint HeroStanding(GLuint HeroMotions[], int &frameNumber);
GLuint HeroKicking(GLuint HeroMotions[], int &frameNumber);
GLuint HeroFighting(GLuint HeroMotions[], int &frameNumber);

struct ElementCoordinates{
			float xLeft;
			float xRight;
			float yBottom;
			float yTop;
	} ElemCoord;
int screen_Heigth = 500;
int screen_Width = 500;
bool selected = false;
GLuint texture_NewGameBlue[32]; 
int frameIndex=0;

int _tmain(int argc, _TCHAR* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING); //SDL function to initialize everything;
	SDL_Window* window;
	window=SDL_CreateWindow("My Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_Heigth, screen_Width, SDL_WINDOW_OPENGL); //SDL function to create a window;
	if ( window == nullptr )
    {
        cout << "Failed to create window : " << SDL_GetError();
		int a;
		cin >> a;
        return -1;
    }
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK)
    {
            std::cout << "Glew Error: " << glewGetErrorString(error) << std::endl;
			int a;
		    cin >> a;
    }
	struct ElementCoordinates menuNewGame;
	menuNewGame.xRight=0.2f;
	menuNewGame.xLeft=-0.2f;
	menuNewGame.yTop=0.7f;
	menuNewGame.yBottom=-0.3f;

	    float vertices[] = {
        // positions                               // colors          //Texcoords
         menuNewGame.xRight,  menuNewGame.yTop,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // Top-left
         menuNewGame.xRight, menuNewGame.yBottom,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // Top-right
        menuNewGame.xLeft, menuNewGame.yBottom,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // Bottom-right
        menuNewGame.xLeft,  menuNewGame.yTop,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // Bottom-left
    };
	
	//Set the window background to black color.
	glClearColor(1.0f,0.0f,0.0f,1.0f);
	//Starting the shader program;
	GLuint shaderProgram=Install_Shaders();
	glUseProgram(shaderProgram);
	//Variable to store the texture:
	//glActiveTexture(GL_TEXTURE1); //THIS STATEMENT WILL MAKE YOUR TEXTURE INVISIBLE
	texture_NewGameBlue[0] = Load_Texture("./separated sprites/extracolors versions/FRAME001.png");
	texture_NewGameBlue[1] = Load_Texture("./separated sprites/extracolors versions/FRAME002.png");
	texture_NewGameBlue[2] = Load_Texture("./separated sprites/extracolors versions/FRAME003.png");
	texture_NewGameBlue[3] = Load_Texture("./separated sprites/extracolors versions/FRAME004.png");
	texture_NewGameBlue[4] = Load_Texture("./separated sprites/extracolors versions/FRAME005.png");
	texture_NewGameBlue[5] = Load_Texture("./separated sprites/extracolors versions/FRAME006.png");
	texture_NewGameBlue[6] = Load_Texture("./separated sprites/extracolors versions/FRAME007.png");
	texture_NewGameBlue[7] = Load_Texture("./separated sprites/extracolors versions/FRAME008.png");
	texture_NewGameBlue[8] = Load_Texture("./separated sprites/extracolors versions/FRAME009.png");
	texture_NewGameBlue[9] = Load_Texture("./separated sprites/extracolors versions/FRAME010.png");
	texture_NewGameBlue[10] = Load_Texture("./separated sprites/extracolors versions/FRAME011.png");
	texture_NewGameBlue[11] = Load_Texture("./separated sprites/extracolors versions/FRAME012.png");
	texture_NewGameBlue[12] = Load_Texture("./separated sprites/extracolors versions/KICKA01.png");
	texture_NewGameBlue[13] = Load_Texture("./separated sprites/extracolors versions/KICKA02.png");
	texture_NewGameBlue[14] = Load_Texture("./separated sprites/extracolors versions/KICKA03.png");
	texture_NewGameBlue[15] = Load_Texture("./separated sprites/extracolors versions/KICKA04.png");
	texture_NewGameBlue[16] = Load_Texture("./separated sprites/extracolors versions/KICKA05.png");
	texture_NewGameBlue[17] = Load_Texture("./separated sprites/extracolors versions/KICKA06.png");
	texture_NewGameBlue[18] = Load_Texture("./separated sprites/extracolors versions/KICKA07.png");
	texture_NewGameBlue[19] = Load_Texture("./separated sprites/extracolors versions/KICKA08.png");
	texture_NewGameBlue[20] = Load_Texture("./separated sprites/extracolors versions/KICKA09.png");
	texture_NewGameBlue[21] = Load_Texture("./separated sprites/extracolors versions/KICKA10.png");
	texture_NewGameBlue[22] = Load_Texture("./separated sprites/extracolors versions/KICKA11.png");
	texture_NewGameBlue[23] = Load_Texture("./separated sprites/extracolors versions/KICKA12.png");
	texture_NewGameBlue[24] = Load_Texture("./separated sprites/regular/KICKB1.png");
	texture_NewGameBlue[25] = Load_Texture("./separated sprites/regular/KICKB2.png");
	texture_NewGameBlue[26] = Load_Texture("./separated sprites/regular/KICKB3.png");
	texture_NewGameBlue[27] = Load_Texture("./separated sprites/regular/KICKB4.png");
	texture_NewGameBlue[28] = Load_Texture("./separated sprites/regular/KICKB5.png");
	texture_NewGameBlue[29] = Load_Texture("./separated sprites/regular/KICKB6.png");
	texture_NewGameBlue[30] = Load_Texture("./separated sprites/regular/KICKB6.png");
	texture_NewGameBlue[31] = Load_Texture("./separated sprites/regular/KICKB6.png");
	glUniform1i(glGetUniformLocation(shaderProgram, "texKitten"), 0);
	//GLuint texture_NewGameRed =  Load_Texture("newgamered.png");
	
	// Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
	// Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// Detailing each data that the buffer contains
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
	
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	//last parameter of glVertexAttribPointer "const GLvoid * pointer" will fit the texture into the quad. Its purpose is to specify an 
	//offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the 
	//GL_ARRAY_BUFFER target. The initial value is 0.

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	//last parameter of glVertexAttribPointer "const GLvoid * pointer" will fit the texture into the quad. Its purpose is to specify an 
	//offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the 
	//GL_ARRAY_BUFFER target. The initial value is 0.

	// Create an element array
    GLuint ebo;
    glGenBuffers(1, &ebo);
	    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	while(Control(&menuNewGame)==0)
	{
		//Set background window color to black.
		glClear(GL_COLOR_BUFFER_BIT);

		//Enable Transperancy: (usually for PNG files)
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindVertexArray(vao);
		//Send the texture to VertexShader;
		if(!IsHeroKicking && !IsHeroFighting)
			glBindTexture(GL_TEXTURE_2D, HeroStanding(texture_NewGameBlue, frameIndex));
		else if(IsHeroKicking)
		{
			glBindTexture(GL_TEXTURE_2D, HeroKicking(texture_NewGameBlue, frameIndex));
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, HeroFighting(texture_NewGameBlue, frameIndex));
		}
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//Done drawing:
		SDL_GL_SwapWindow(window);
		SDL_Delay(1000/10);
	}
	return 0;
}
int Control (struct ElementCoordinates *menuNewGame)
{
	//If there is an event, then it will be stored in this variable by SDL.
	SDL_Event a;
	while(SDL_PollEvent(&a)) //if there is an event set
        {
        if(a.type==SDL_KEYDOWN )//verify if at the event is any key pressed
            switch(a.key.keysym.sym) // if the key was pressed, verify which key that was
            {
			    case SDL_QUIT:
				{
					break;
				}
				case SDLK_SPACE:
				{
					IsHeroKicking=true;
					break;
				}
				case SDLK_b:
				{
					IsHeroFighting=true;
					break;
				}
				default:
				{
					break;
				}
			}
		switch(a.type)
		{
			case SDL_QUIT: //if the window close button pressed
            {
                cout << "Close the console to quit!" << endl; //print this message in the console.
				break;
            }
			case SDL_MOUSEBUTTONDOWN:
			{
				break;
			}
			//if the cursor has moved:
			//case SDL_MOUSEMOTION:{}
			
			default:{
					break;
				}
		}
	}
	return 0;
}
GLuint Load_Texture(const char* filename)
{
    int width, height; //variables to store the height and width of the picture loaded
    unsigned char* image= SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
    if(image==nullptr)
    {
        cerr << "Failed to load the texture" << " " << filename << endl;
        return 0;
    }
    GLuint textureid;
    glGenTextures(1, &textureid);
    glBindTexture(GL_TEXTURE_2D, textureid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT );
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );
    SOIL_free_image_data(image);
    return textureid;
}
GLuint Install_Shaders() //function that install the shaders
{
	//Getting the location of the code file:
    const GLchar* vertexShaderFilePath = "vertexshader.vsh";  //this is the filepath for vertexshader
    const GLchar* fragmentShaderFilePath = "fragmentshader.fsh";  //this is the filepath for fragmentshader
	
	//Variable to store the ids of the shaders:
    GLuint vertexshaderID, fragmentshaderID; //make 2 identifiers one for each shader.

    vertexshaderID=glCreateShader(GL_VERTEX_SHADER); //create a vertex shader and store its identifier in vertexshaderID
    fragmentshaderID=glCreateShader(GL_FRAGMENT_SHADER);//create a fragment shader and store its identifier in fragmentshaderID
    
	//Open the code files:
	ifstream vertexfile; //pointer to a file;
    ifstream fragmentfile;
    string line=""; //string initialized to nothing;
    string fcontent="";
    vertexfile.open(vertexShaderFilePath); //open the file;
	//Reading line by line from the opened file:
    while(getline(vertexfile,line))
    {
        fcontent += line + "\n"; //fcontent takes every line and puts after it, a \n.
    }
    vertexfile.close(); //close the file once we're done with it;
	//Converting the string to a char array (C-style string).
    const GLchar* vertexshadercode=fcontent.c_str(); //make a new string to keep all the data into it;
    
	//  cout << vertexshadercode << endl; // This was here only for debug.
	
	//Adding the code read from the file to the shader id:
    glShaderSource(vertexshaderID,1, &vertexshadercode, nullptr);
    //IMPORTANT: the order of doing these operations is important, vertexshadercode changes it's value if its moved.

	//Preparing for the fragment shader:
    fcontent=""; //initialize the string
    line="";
    fragmentfile.open(fragmentShaderFilePath); //open the file;
    while(getline(fragmentfile, line)) //read line by line;
    {
        fcontent += line + "\n"; //get all the content line by line;
    }
    const GLchar* fragmentshadercode=fcontent.c_str(); //store the code into this string;
    fragmentfile.close(); //close the file;

   // cout << fragmentshadercode << endl; //this is here only for debug

	//Adding the code to the fragmentshaderID.
    glShaderSource(fragmentshaderID,1,&fragmentshadercode, nullptr); //get the source code to it's ID;


	//Compiling the shaders:
    glCompileShader(vertexshaderID); //compile the shader;
    GLint success=0; //this variable will check if the compilation was successful
    GLchar infolog[512]; //this variable will store the error log (in case that compilation was unsuccessful).

	//Checking if successful!
    glGetShaderiv(vertexshaderID, GL_COMPILE_STATUS, &success);
    if(!success) //check for success
    {
        cout << "Error compiling the vertex shader's code!" << endl;
        glGetShaderInfoLog(vertexshaderID, 512, 0, infolog);
        cout << infolog << endl;
    }
	
	//Do the same for the fragment shader:
    glCompileShader(fragmentshaderID); //compile the shader;

    glGetShaderiv(fragmentshaderID, GL_COMPILE_STATUS, &success);
    if(!success) //check for success;
    {
        cout << "Error compiling the fragment shader's code!" << endl;
        glGetShaderInfoLog(fragmentshaderID, 512, 0, infolog);
        cout << infolog << endl;
    }

	//If both was successful create a shader program containing these shaders:
    GLuint programID = glCreateProgram(); //create a program;

    glAttachShader(programID, vertexshaderID); //attach the shaders to it;
    glAttachShader(programID, fragmentshaderID);

    glLinkProgram(programID); //link the pieces of the program;

	//Check for errors:
    glGetProgramiv(programID,GL_LINK_STATUS, &success);
    if(!success) //check for success;
    {
        cout << "Error linking the program!" << endl;
        glGetProgramInfoLog(programID, 512, 0, infolog);
        cout << infolog << endl;
    }
	//If reached this point, the program that uses those shaders has been successful created:
    glDeleteShader(vertexshaderID); //delete shader id;
    glDeleteShader(fragmentshaderID); //delete shader id
    glUseProgram(programID); //use the program which already contains the shaders;
    return programID;
}

float getH(int number)
{
		return (number-screen_Heigth/2)/(float)(screen_Heigth/2)*(-1);
}
float getV(int number)
{
		return (number-screen_Width/2)/(float)(screen_Width/2);
}
GLuint HeroStanding(GLuint HeroMotions[], int &frameNumber)
{
	frameNumber++;
	if(frameNumber>11)
	{
		frameNumber=0;
	}
	return HeroMotions[frameNumber];
}
GLuint HeroKicking(GLuint HeroMotions[], int &frameNumber)
{
	if(frameNumber<12)
	{
		frameNumber=12;
	}
	else
	{
		frameNumber++;
	}
	if(frameNumber>23)
	{
		frameNumber=0;
		IsHeroKicking = false;
	}
	return HeroMotions[frameNumber];
}
GLuint HeroFighting(GLuint HeroMotions[], int &frameNumber)
{
	if(frameNumber<24)
	{
		frameNumber=24;
	}
	else
	{
		frameNumber++;
	}
	if(frameNumber>31)
	{
		frameNumber=0;
		IsHeroFighting = false;
	}
	return HeroMotions[frameNumber];
}