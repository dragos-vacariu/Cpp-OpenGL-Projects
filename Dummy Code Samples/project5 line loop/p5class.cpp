#include "p5class.h"

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

    GLfloat lineloop[] //drawing a table.
    {
        100, 100, 0.0,
        100, 300, 0.0,
        300, 300, 0.0,
        300, 100, 0.0,
        100, 100, 0.0,
        50, 100, 0.0,
        50, 300, 0.0,
        100, 300, 0.0,
        100, 250, 0.0,
        300, 250, 0.0,
        300, 200, 0.0,
        100, 200, 0.0,
        100, 150, 0.0,
        300, 150, 0.0,
        300, 100, 0.0
    };
    GLfloat name[] //building the letter B.
    {
        50,400,0.0,
        50,500,0.0,
        100, 450,0.0,
        50, 450, 0.0,
        100, 400, 0.0
    };
    GLfloat name2[] //building the letter L.
    {
        150,400,0.0,
        150,500,0.0,
        150, 400,0.0,
        200, 400, 0.0,
        //100, 400, 0.0
    };
    GLfloat name3[] //building the letter K.
    {
        250,400,0.0,
        250,500,0.0,
        250, 450,0.0,
        300, 500, 0.0,
        250, 450, 0.0,
        300, 400, 0.0,
        250, 450, 0.0,
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
    glEnable(GL_LINE_SMOOTH); // enable line smooth, which makes the line clearer.
    glEnable(GL_LINE_STIPPLE); //enable function for pointed line.
    glLineStipple(1,0x00FF); // making a pointed line.
    glVertexPointer(3,GL_FLOAT, 0, lineloop);
    glDrawArrays(GL_LINE_LOOP, 0, 15); // drawing Line Loop table.
    glVertexPointer(3, GL_FLOAT, 0, name);
    glDrawArrays(GL_LINE_LOOP, 0,5); // drawing Line Loop B letter.
    glVertexPointer(3, GL_FLOAT,0, name2);
    glDrawArrays(GL_LINE_LOOP,0,4); //drawing Line Loop L letter.
    glVertexPointer(3, GL_FLOAT,0, name3);
    glDrawArrays(GL_LINE_LOOP,0,7); //drawing Line Loop K letter.
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_LINE_STIPPLE);
    glDisableClientState(GL_VERTEX_ARRAY);
    SDL_GL_SwapWindow(window);
}
