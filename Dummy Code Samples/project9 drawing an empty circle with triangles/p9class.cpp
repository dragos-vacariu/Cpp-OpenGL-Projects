#include "p9class.h"

p8class::p8class()
{
    //ctor
}

p8class::~p8class()
{
    //dtor
}
void p8class::checkinput()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
        if(event.type==SDL_QUIT)
            cout << "Close the console to exit the program!" << endl;
}

void p8class::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project9", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 650, 650, SDL_WINDOW_OPENGL);
    SDL_GLContext glstuff;
    glstuff=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "Glew has failed to initialize!" << endl;
    }
    glClearColor(0.1,0.1,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //Put in use the pixel's coordinates as they are;
    glViewport(0, 0, 650, 650);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,650,0,650,0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //the system of coordinates is set;

    //The drawing begins here.
    GLint numberofsides=20;
    GLfloat radius = 100;

    GLint numberofvertices=numberofsides+1;
    //+1 because for 2 triangle we need 3+1 vertexes;
    GLfloat x,y,z; //coordinates of the center of the circle;
    x=200;
    y=200;
    z=0;

    GLfloat doublepi = 2.0f*M_PI; //twice the value of PI to obtain 360 degrees; for a circle;

    //One array for each of the coordinates of a vertex;
    GLfloat arrayX[numberofvertices];
    GLfloat arrayY[numberofvertices];
    GLfloat arrayZ[numberofvertices];

    //Math function;
    for(int i=0;i<numberofvertices; i++)
    {
        arrayX[i]= x + (radius * cos( i* (doublepi/numberofsides)));
        arrayY[i]= y + (radius * sin ( i* (doublepi/numberofsides)));
        arrayZ[i]= z;
    }
    //end of Math function;

    GLfloat allarrays[numberofvertices*3]; // a big array to store all the other 3 arrays above;

    //copying the other 3 arrays above, into this big array.
    for(int i=0;i<numberofvertices; i++)
    {
        allarrays[i*3]=arrayX[i];
        allarrays[(i*3)+1]=arrayY[i];
        allarrays[(i*3)+2]=arrayZ[i];
    }
    //the storage is complete;

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT, 0, allarrays);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, numberofvertices);//draw to the screen;
    glDisableClientState(GL_VERTEX_ARRAY);

    SDL_GL_SwapWindow(window);// when the draw is completed, put the full image on the screen.

    //SDL_Delay(6000); //keep the window open for 6 seconds;
   // SDL_GL_DeleteContext(glstuff); //delete the context after the delay;
   // SDL_DestroyWindow(window); //close the window;
   // SDL_QUIT; // quit SDL;
}
