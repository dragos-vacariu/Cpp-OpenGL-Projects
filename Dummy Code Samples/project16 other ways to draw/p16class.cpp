#include "p16class.h"

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
    //translating the coordinates
    glViewport(0,0,640,480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,640,0,480,0,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*GLfloat triangle []
    {
        400,300,
        200,100,
        200,400
    };*/
    //done translating the coordinates
   while(1)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glTranslatef(0.0,0.0,0.0); //move the draw around the x and y axes
        //glScalef(2.0,1.0,1.0);
       // glRotatef(9.0,0.0,1.0,0.0);
        glBegin(GL_TRIANGLES); //the drawing begins here.
        glColor3f(0.2,0.1,0.0); //other way to color a draw
        glVertex2f(400,300); //vertex one with 2 float arguments
        glVertex2f(200,100); //vertex two with 2 float arguments
        glVertex2f(200,400); //vertex three with 2 float arguments
        glEnd(); // the drawing ends here.
        SDL_Delay(500);
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
    }
    SDL_DestroyWindow(window);
    cout << "Program closed!" << endl;
}
