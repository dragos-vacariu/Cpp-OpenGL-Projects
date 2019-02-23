#include "p17class.h"

p16class::p16class()
{
    //ctor
}

p16class::~p16class()
{
    //dtor
}
SDL_Window* p16class::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project16", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    context=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "Error initializing the glew!" << endl;
    }
    else
    {
        cout << "Glew has been successfully initialized!" << endl;
    }
    return window;
}

void p16class::draw(SDL_Window* window)
{
    bool closeWindow=false;
    SDL_Event a;
    int angle=1;
    //translating the coordinates
    GLfloat cube []
    {
        300,300, 0,
        300,500, 0,
        500,500, 0,
        500,300, 0,

        300,300,0,
        300,500,0,
        300,300,200,
        300,500,200,

        500,300,0,
        500,300,200,
        500,500,0,
        500,500,200,

        300,300,0,
        300,300,200,
        500,300,0,
        500,300,200,

        300,500,0,
        300,500,200,
        500,500,0,
        500,500,200,

        300,300, 200,
        300,500, 200,
        500,500, 200,
        500,300, 200
    };

    glViewport(0,0,640,480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,640,0,480,0,600);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //done translating the coordinates

   while(1)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glTranslatef(650,650,-100); //move the draw around the x and y axes
        //glScalef(2.0,1.0,1.0);
        glRotatef(angle,1.0,1.0,0.0);
        glTranslatef(-650,-650,100);
        glBegin(GL_QUADS);
        glEnable(GL_DEPTH_TEST);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(200,200, -20);
        glVertex3f(200,400, -20);
        glVertex3f(400,400, -20);
        glVertex3f(400,200, -20);
        glEnd();

        SDL_Delay(50);
        SDL_GL_SwapWindow(window);
        while(SDL_PollEvent(&a))
        {
            switch(a.type)
            {
                case SDL_QUIT:
                {
                   closeWindow=true;
                    break;
                }
            }
        }
        if(closeWindow==true)
        {
            break;
        }
 //        angle++;
    }

    SDL_DestroyWindow(window);
    cout << "Program closed!" << endl;
}
