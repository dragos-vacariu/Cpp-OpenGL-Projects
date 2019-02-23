#include "p1class.h"

p1class::p1class()
{
    //ctor
}

p1class::~p1class()
{
    //dtor
}

void p1class::init()
{
    SDL_Init(SDL_INIT_EVERYTHING); // intialize sdl;
    SDL_Window* window;
    SDL_GLContext mycontext;
    window=SDL_CreateWindow("Project1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_OPENGL);
    if(window==nullptr)
    {
        cerr << "Window failed to initialize" << endl;
        exit(1);
    }

    mycontext=SDL_GL_CreateContext(window);
    glewInit(); //initialize glew;
    if(glewInit()!=GLEW_OK) //GLEW_OK=1;
    {
        cerr << "Glew failed to initialize" << endl;
        exit(1);
    }

     float vertex []
    {
        0.5, 0.0, 0.0,
        0.0, 0.5, 0.0,
        -0.5, -0.5, 0.0,
    };

    float vertex2 [] // first vectors coordinates;
    {
        1.0, 0.2, 0.0,
        0.1, -1.0, 0.0,
        -0.7, 0.8, 0.0

    };
    glClearColor(0.1, 0.0, 0.0, 0.0); // set the color for filling the screen;
    glClear(GL_COLOR_BUFFER_BIT); // fill the screen with a color;
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex); //gettint the vertex pointer;
    glVertexPointer(3, GL_FLOAT, 0, vertex2);
    glDrawArrays(GL_TRIANGLES,0,3);
    glDrawArrays(GL_TRIANGLES, 0, 3); //gl draw function;
    glDisableClientState(GL_VERTEX_ARRAY); // disable the array;
    SDL_GL_SwapWindow(window); // change the window;
    closed = checkbut();
    if(closed==true); // if the closed gets 1 value from the checkbut function;
    {
        SDL_GL_DeleteContext(mycontext); // delete the context;
        SDL_DestroyWindow(window); // destroy the window;
        SDL_QUIT; //quit sdl;
        exit(1);
    }
}

int p1class::checkbut()
{
    SDL_Event myevent;
    while(1) //infinite loop, to check any incoming events;
    {
        while(SDL_PollEvent(&myevent)) // check if there is an event;
        {
            switch(myevent.type) //convert a quantity into a value;
            {
            case SDL_KEYUP: // case that a button is released;
                 {
                    cout << "Button released" << endl;
                    return 0;
                    break;
                }
            case SDL_KEYDOWN: // case that a button is pressed;
               {
                    cout << "Button pressed!" << endl;
                    return 0;
                    break;
               }
            case SDL_QUIT: // case the window closes;
                {
                    return 1;
                }
            }
        }
    }
}
