#include "p4class.h"

p4class::p4class()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    context=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "Error initializing glew!" << endl;
    }
    else
    {
        cout << "Glew has been succesfully initialized" << endl;
    }

    //Drawing a lines;
    GLfloat drawlines[]
    {
        200, 350, 0.0,
        50, 100, 0,0,

    };

    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);

    glViewport(0.0f, 0.0f, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glLineWidth(1);
    glEnable(GL_LINE_SMOOTH); //enable Line smooth;
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1,0x0C0F); // function to draw the segments of line
    glVertexPointer(3, GL_FLOAT, 0, drawlines);
    glDrawArrays(GL_LINES, 0, 2);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_LINE_STIPPLE);

    glDisableClientState(GL_VERTEX_ARRAY);
    SDL_GL_SwapWindow(window);

    SDL_Event a;
    while(1)
        while(SDL_PollEvent(&a))
        {
            if(a.type==SDL_QUIT)
                cout << "If you want to exit, close the console!" << endl;
        }
}

p4class::~p4class()
{
    //dtor
}
