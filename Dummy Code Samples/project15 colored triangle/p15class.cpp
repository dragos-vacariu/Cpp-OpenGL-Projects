#include "p15class.h"

p15class::p15class()
{
    //ctor
}

p15class::~p15class()
{
    //dtor
}
SDL_Window* p15class::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project15", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 500,500, SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    context=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "Error initializing glew!" << endl;
    }
    else
    {
        cout << "Glew has been successfully initialized!" << endl;
    }
    return window;
}
void p15class::draw(SDL_Window* window)
{
    GLfloat triangle[]
    {
      250,480,0,
      40,20,0,
      480,20,0
    };
    GLfloat color[]
    {
      255,0,0,
      0,255,0,
      0,0,255

    };
    //Translating the coordinates from normalized to pixel's
    glViewport(0,0,500,500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,500,0,500,0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    SDL_Event a;
    //the translate has been done.
    while(1)
    {
        glClear(GL_COLOR_BUFFER_BIT); //clear the screen after each iteration.
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3,GL_FLOAT,0,triangle);
        glColorPointer(3,GL_FLOAT,0,color); //without this statement, the program crashes
        //because there is no color to draw, for the triangle.
        glDrawArrays(GL_TRIANGLES, 0,9);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        SDL_GL_SwapWindow(window);

        while(SDL_PollEvent(&a))
        {
            if(a.type==SDL_KEYDOWN)
                switch(a.key.keysym.sym)
                {
                    case SDL_QUIT:
                    {
                        cout << "Close the console to quit!" << endl;
                    }
                }
        }
    }
}
