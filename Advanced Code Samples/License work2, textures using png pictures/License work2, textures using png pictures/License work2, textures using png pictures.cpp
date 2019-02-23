// License work2, textures using png pictures.cpp : Defines the entry point for the console application.
//
#include "StdAfx.h"
#include <custom/SDL.h>
#include <custom/glew.h>
#include <iostream>
#include <custom/SOIL.h>
#define GLEW_STATIC

using namespace std;

int Control (struct ElementCoordinates *menuNewGame);
GLuint Load_Texture(const char* filename);
struct ElementCoordinates{
			int xLeft;
			int xRight;
			int yBottom;
			int yTop;
	} ElemCoord;

int screen_Heigth = 500;
int screen_Width = 500;
bool selected = false;

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
	menuNewGame.xLeft=100;
	menuNewGame.xRight=400;
	menuNewGame.yTop=400;
	menuNewGame.yBottom=300;
	//translating the normalized coordinates into pixel's
    glViewport(0,0,screen_Heigth,screen_Width);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,screen_Heigth,0,screen_Width,-100,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //translating done.
	//Set the window background to black color.
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	//Variable to store the texture:
	GLuint texture_used;

	while(Control(&menuNewGame)==0)
	{
		//Set background window color to black.
		glClear(GL_COLOR_BUFFER_BIT);

		//Load the texture;
		if(selected)
		{
			texture_used=Load_Texture("newgamered.png");
		}
		else
		{
			texture_used=Load_Texture("newgameblue.png");
		}
		//Enable TEXTURING:
		glEnable(GL_TEXTURE_2D);
		//Enable Transperancy: (usually for PNG files)
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Drawing a Quad (Square) -> in immediate mode:
		glBindTexture(GL_TEXTURE_2D, texture_used);
		glBegin(GL_QUADS);
				glTexCoord2f(0.0,1.0);
				glVertex2f(menuNewGame.xLeft, menuNewGame.yBottom);
				glTexCoord2f(1.0,1.0);
				glVertex2f(menuNewGame.xRight, menuNewGame.yBottom);
				glTexCoord2f(1.0,0.0);
				glVertex2f(menuNewGame.xRight, menuNewGame.yTop);
				glTexCoord2f(0.0,0.0);
				glVertex2f(menuNewGame.xLeft, menuNewGame.yTop);
		
		glEnd();
		//Done drawing:

		SDL_GL_SwapWindow(window);
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
            }
			case SDL_MOUSEBUTTONDOWN:
			{

			}
			//if the cursor has moved:
			case SDL_MOUSEMOTION:
			{
				if(a.motion.x >= menuNewGame->xLeft && a.motion.x <= menuNewGame->xRight && (screen_Heigth-a.motion.y) <= menuNewGame->yTop
					&& (screen_Heigth-a.motion.y)  >= menuNewGame->yBottom)
					{
						selected=true;
					}
				else
					{
						selected=false;
					}
				break;
			}
			default:{
				break;
				}
		}
	}
	return 0;
}
GLuint Load_Texture(const char* filename)
{
    int width, height;
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
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );
    SOIL_free_image_data(image);
    return textureid;
}

