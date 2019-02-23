/*User defined headers:*/
#include "Window.h"

//The constructor of the window.
Window::Window()
{
    //Initialize the SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    //Creating the window
    window=SDL_CreateWindow("License work", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_Width, screen_Height , SDL_WINDOW_OPENGL); //SDL function to create a window;
	if ( window == nullptr )
    {
        cout << "Failed to create window : " << SDL_GetError();
		int a;
		cin >> a;
    }
    //Creating the context for drawing in the window.
	glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK)
    {
            cout << "Glew Error: " << glewGetErrorString(error) << endl;
			int a;
		    cin >> a;
    }

    start_time = time(0);
    srand(time(0));
    the_time[0] = rand()%24;
    the_time[1] = rand()%60;
    setBackgroundTexture();
}
Window::Window(unsigned int hours, unsigned int minutes)
{
    //Initialize the SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    //Creating the window
    window=SDL_CreateWindow("License work", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_Width, screen_Height , SDL_WINDOW_OPENGL); //SDL function to create a window;
	if ( window == nullptr )
    {
        cout << "Failed to create window : " << SDL_GetError();
		int a;
		cin >> a;
    }
    //Creating the context for drawing in the window.
	glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK)
    {
            cout << "Glew Error: " << glewGetErrorString(error) << endl;
			int a;
		    cin >> a;
    }

    start_time = time(0);
    //Validating the time:
    if(hours > 23 || hours < 0) {hours = 0;}
    if(minutes > 60 || minutes < 0) {minutes = 0;}
    the_time[0] = hours;
    the_time[1] = minutes;
    setBackgroundTexture();
}

Window::~Window()
{
    //dtor
}
