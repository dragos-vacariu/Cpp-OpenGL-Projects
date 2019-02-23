// License work1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SDL.h>
#include <glew.h>
#include <iostream>
#include <SDL_ttf.h>
#define GLEW_STATIC

using namespace std;

//Prototyping the functions:
int Control (void);
SDL_Texture* SurfaceToTexture( SDL_Surface* surf, SDL_Renderer* renderer);
int CountLetters(string Message);

//Some global variables called in multiple functions:
SDL_Rect solidRect;

int _tmain(int argc, _TCHAR* argv[])
{
	//The size of the window:
	struct WindowSize{
			int x;
			int y;
		};
	struct WindowSize windowSize;
	windowSize.x=500;
	windowSize.y=500;

	SDL_Init(SDL_INIT_EVERYTHING); //SDL function to initialize everything;
	//Creating all the variables.
    SDL_Window* window;
	TTF_Font* font;
	string fontName = "arial.ttf"; //this variable will hold the filepath of the font file.
	//The message for the text:
	string Message = "This is a message";
	const int FontSize = 30;

	//Set the color of the text to white.
	SDL_Color textColor = { 255, 0, 255, 255 }; // color for the text
	
	SDL_Texture* solidTexture;
	SDL_Rect windowRect = { windowSize.x, windowSize.y };
	
	//Preparing window:
	window=SDL_CreateWindow("My Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y, SDL_WINDOW_OPENGL); //SDL function to create a window;
	if ( window == nullptr )
    {
        cout << "Failed to create window : " << SDL_GetError();
		int a;
		cin >> a;
        return -1;
    }
	//Preparing the renderer:
	SDL_Renderer* renderer;
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	if ( renderer == nullptr )
    {
        cout << "Failed to create renderer : " << SDL_GetError();
		int a;
		cin >> a;
        return -1;
    }
	SDL_RenderSetLogicalSize( renderer, windowSize.x, windowSize.y); //size of the renderer;
    // Set color of renderer to red
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 ); //set a drawing color for the specified renderer(in first argument)
	
	//Preparing the font:
	if ( TTF_Init() == -1 ) //if the initialization fails;
    {
        cout << " Failed to initialize TTF : " << SDL_GetError() << std::endl;
		int a;
		cin >> a;
        return -1;
    }
	font = TTF_OpenFont( fontName.c_str(), FontSize ); //open font with size 90
	if ( font == nullptr ) // if the font is not found;
    {
        cout << " Failed to load font : " << SDL_GetError() << endl;
		int a;
		cin >> a;
        return -1;
    }

	//Create a GL Context on that window
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	//GLenum error will store the value returned by glewInit();
	GLenum error = glewInit();
	//Set double buffering for my GL Context
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//if value stored in "error" is not GLEW_OK, then it was an error.
    if (error != GLEW_OK)
    {
            std::cout << "Glew Error: " << glewGetErrorString(error) << std::endl;
			int a;
		    cin >> a;
    }
	//Creating text textures:
	SDL_Surface* solid = TTF_RenderText_Solid( font, Message.c_str(), textColor ); //creating a surface with the text from Message string.
    //Converting surface to texture;
	solidTexture = SurfaceToTexture( solid , renderer); //first type
	//Placing the texture in the renderer;
    SDL_QueryTexture( solidTexture, NULL, NULL, &solidRect.w, &solidRect.h );
	//Setting the position of the text message inside the renderer:
    solidRect.x = 10; //the text will be placed starting from this value on x axis;
	//and it will end at solidRect.w (which tells the exact width of the text message)
    solidRect.y = 40; //this text will be places starting from this value on y axis;
	//and it will have a height of solidRect.h so it will end at solidRect.y + solidRect.h; on y axis.

	glClearColor(0.0f,0.0f,0.0f,1.0f);

	//Let it loop until the end.
	while(Control()==0)
	{
		//Set background window color to black.
		//glClear(GL_COLOR_BUFFER_BIT);
		//Using the renderer
		SDL_RenderClear( renderer ); //create a renderer
		SDL_RenderCopy( renderer, solidTexture, nullptr, &solidRect );
		SDL_RenderPresent( renderer); //use this renderer
		//SDL_GL_SwapWindow(window);
	}
	//Wait a button press and then quit.
	int a;
	cin >> a;
	return 0;
}

int Control ()
{
	//If there is an event, then it will be stored in this variable by SDL.
	SDL_Event a;
	while(SDL_PollEvent(&a)) //if there is an event set
        {
        if(a.type==SDL_KEYDOWN )//verify if at the event is any key pressed
            switch(a.key.keysym.sym) // if the key was pressed, verify which key that was
            {
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
				//cout << "Mouse.x = " << a.motion.x << "   solidRect.x = "<< solidRect.x << "   > or < " << solidRect.w << endl;
				//cout << "Mouse.y = " << a.motion.y << "   solidRect.h = " << solidRect.h << "  > or < " << solidRect.y << endl << endl << endl;
					if(a.motion.x > solidRect.x && a.motion.x < solidRect.w &&
						a.motion.y > solidRect.y && a.motion.y < solidRect.y+solidRect.h)
				{
					cout << "You are hovering over the message." << endl;
					break;
				}
			}
			//if the cursor has moved:
			case SDL_MOUSEMOTION:
			{
				if(a.motion.x > solidRect.x && a.motion.x < solidRect.w &&
						a.motion.y > solidRect.y && a.motion.y < solidRect.y+solidRect.h)
				{
					//I will change the color here:
					//SDL_Color textColor = { 255, 255, 0, 255 };

					break;
				}
			}
			default:{
				break;
				}
		}
	}
	return 0;
}
SDL_Texture* SurfaceToTexture( SDL_Surface* surf, SDL_Renderer* renderer) //Function;
{
    SDL_Texture* text; //create SDL texture

	//Converting surface to texture;
    text = SDL_CreateTextureFromSurface( renderer, surf );

	//Clear the surface;
    SDL_FreeSurface( surf ); //delete the surface;

    return text;
}