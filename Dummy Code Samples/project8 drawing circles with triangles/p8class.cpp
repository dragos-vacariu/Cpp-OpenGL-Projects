#include "p8class.h"

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

void p8class::init(GLint numberofsides, GLfloat radius)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 650, 650, SDL_WINDOW_OPENGL);
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
    glViewport(0, 0, 650,650);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,650,0,650,0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //the system of coordinates is set;


    GLint numberofvertices= numberofsides+2; //you need minimum 3 vertexes to draw a triangle.
    //numberofvertices=numberofside+2, because 1, vertext from those +2, is requiered for the center, the place
    //in which the radius will start, and 1, is required because, if you want to draw for example 2 triangles 
	//you need an extra vertex.
    
	GLfloat doublepi = 2.0f* M_PI; //M_PI is the predefined value of PI, 3.14 etc;
    //we will need 2PI, in order to draw a circle, 360 degrees;

    //Making 3 arrays to store each coordinate of the vertexes;
    GLfloat arrayX[numberofvertices];
    GLfloat arrayY[numberofvertices];
    GLfloat arrayZ[numberofvertices];

    //The position of the center;
    GLfloat x,y,z;
    x=250;
    y=250;
    z=0;

    arrayX[0]=x; //first triangle's x coordinate
    arrayY[0]=y; //first triangle's y coordinate;
    arrayZ[0]=z; //first triangle's z coordinate;

    //MATH function;
    for(int i=1; i<numberofvertices; i++)
    {
        arrayX[i]= x + (radius * cos(i* (doublepi/numberofsides) ));
        //put a vertex coordinate around the x axes, at radius distance, and cos direction;
        arrayY[i]= y + (radius * sin (i* (doublepi/numberofsides) ));
        //put a vertex coordinate around the y axes at radius distance and sin direction
        arrayZ[i]= z;
    }
    //end of MATH function;

    GLfloat allArraysInOne[numberofvertices*3];

    //putting all those 3 arrays above in one and ONLY;
    for(int i=0; i<numberofvertices; i++)
    {
        allArraysInOne[i*3]=arrayX[i]; //one at 3 times put the arrayX value into allArraysInOne;
        allArraysInOne[(i*3)+1]=arrayY[i]; //one at 3 times put the arrayY value into allArraysInOne;
        allArraysInOne[(i*3)+2]=arrayZ[i];  //one at 3 times put the arrayZ value into allArraysInOne;
    }

    //The drawing begins here.
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, allArraysInOne);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numberofvertices); //drawing the circle;

    glDisableClientState(GL_VERTEX_ARRAY);

    SDL_GL_SwapWindow(window);// when the draw is completed, put the full image on the screen.

    SDL_Delay(6000); //keep the window open for 6 seconds;
    SDL_GL_DeleteContext(glstuff); //delete the context after the delay;
    SDL_DestroyWindow(window); //close the window;
    SDL_QUIT; // quit SDL;
}
