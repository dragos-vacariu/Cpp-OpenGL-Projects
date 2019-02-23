#include "p7class.h"

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

    GLfloat trianglestrip []
    {
      200, 100, 0,
      400, 200, 0,
      200, 300, 0,
      410, 320, 0
    };
    //converting from normalized coordinates, to pixel coordinates and changing the view
    glViewport(0, 0, 650, 650);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,650,0,650,0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //the view changing process ended here.

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, trianglestrip);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //GL_TRIAGLE_STRIP - makes possible the usage of the same vertexes for building an another triangle, with a new
    //given vertex.
    glDisableClientState(GL_VERTEX_ARRAY);

    SDL_GL_SwapWindow(window);
}
