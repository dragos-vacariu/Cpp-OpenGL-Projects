#include "p38class.h"

p38class::p38class()
{
}

p38class::~p38class()
{
}

SDL_Window* p38class::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project38", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,600, SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    context=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cout << "Glew has failed to initialize!" << endl;
        exit(1);
    }
    return window;
}
void p38class::draw()
{
    float ratio=800/600;
    SDL_Window* window=init();
    glClearColor(0.0,0.0,0.0,1.0);

    //this does not translate the coordinates but set the perspective;
    glViewport(0,0,800,600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1, 1,-1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //done setting the perspective;

    while(1)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glRotatef(1.0, 0.0, 0.0, 1.0); //simple rotation;

        glBegin(GL_TRIANGLES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(-0.8,-0.4,0); //the coordinates for the vertices are important for the perspective;
        glColor3f(1.0,1.0,0.0);
        glVertex3f(0.2,-0.4,0); //the coordinates are important;
        glColor3f(0.0,0.0,1.0);
        glVertex3f(-0.3,0.2,0); //the coordinates are important;
        glEnd();

        SDL_GL_SwapWindow(window);
        input();
        SDL_Delay(40);
    }
}

void p38class::input()
{
    SDL_Event a;
    while(SDL_PollEvent(&a))
    {
        switch(a.type)
        {
            case SDL_QUIT:
            {
                exit(1);
            }
        }
    }
}
