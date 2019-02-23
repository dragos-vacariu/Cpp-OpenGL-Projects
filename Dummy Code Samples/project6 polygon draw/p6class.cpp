#include "p6class.h"

p5class::p5class()
{
}

p5class::~p5class()
{
    //dtor
}

void p5class::pollevents()
{
    SDL_Event evnt;
        while(SDL_PollEvent(&evnt))
            if(evnt.type==SDL_QUIT)
                cout << "CLOSE THE CONSOLE TO END THE PROGRAM!" << endl;
}
 void p5class::openwindow()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GLContext context;
    window=SDL_CreateWindow("Project5", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 650, 650, SDL_WINDOW_OPENGL);
    context=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "ERROR, initializing the glew!" << endl;
    }

    else cout << " Glew has been initialized!" << endl;

    GLfloat polygon[]
    {
        200, 300, 0,
        400, 100, 0,
        300, 50, 0,
        450, 450, 0,
        120, 320, 0
    };
    //converting from normalized coordinates, to pixel coordinates and changing the view
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,500,0,500,0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //the view changing process ended here.

    glEnableClientState(GL_VERTEX_ARRAY);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //GL_FILL is set by default always.
    glVertexPointer(3, GL_FLOAT, 0, polygon);
    glDrawArrays(GL_POLYGON, 0, 5);
    glDisableClientState(GL_VERTEX_ARRAY);


    SDL_GL_SwapWindow(window);
}
