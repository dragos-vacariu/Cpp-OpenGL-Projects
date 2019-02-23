#include "p3class.h"

p3class::p3class()
{
   SDL_Init(SDL_INIT_EVERYTHING);
   SDL_Window* window;
   window=SDL_CreateWindow("Project3", 250, 150, 500, 500, SDL_WINDOW_OPENGL);
   SDL_GLContext context;
   context=SDL_GL_CreateContext(window);

   glewInit();
   if(glewInit()!=GLEW_OK)
   {
       cerr << "Failed to initialize Glew" << endl;
   }
    else
       {cout << "Glew has been succesfully initialized!" << endl;}
    //Creating a dot on the center of the screen

    GLfloat drawpoint[]
   {
      200, 200, //point 1
      150, 450  //point 3
   };
   GLfloat drawpoint2[]
   {
       350, 350 //point2
   };

    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);

    glViewport(0.0f,0.0f, 500,500); //specifies the part of the window in which opengl will draw with normal pixels,
    // NOT normalized ones
    glMatrixMode(GL_PROJECTION); //this function defines the view, on the "world".
    glLoadIdentity(); //transform the given matrix into the identity matrix.
    glOrtho(0,500,0,500,0,1); //glOrtho always need to be called before the glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_MODELVIEW); //transforms the view of the object, scale, zoom... etc
    glLoadIdentity();


    glPointSize(50); //set the size of the drawing point
    glVertexPointer(2, GL_FLOAT, 0, drawpoint);
    glDrawArrays(GL_POINTS, 0, 1); //draw point 1

    glVertexPointer(2,GL_FLOAT, 0, drawpoint2);
    glDrawArrays(GL_POINTS, 0, 1); //draw point 2

    glEnable(GL_POINT_SMOOTH); //enable GL_POINT_SMOOTH which makes the point be circular;
    glVertexPointer(2, GL_FLOAT, 0, drawpoint);
    glDrawArrays(GL_POINTS, 1, 1); //draw point 3
    glDisable(GL_POINT_SMOOTH); //disable GL_POINT_SMOOTH;
    glDisableClientState(GL_VERTEX_ARRAY);

    SDL_GL_SwapWindow(window);


   SDL_Event a;
   while(1)
        while(SDL_PollEvent(&a))
            if(a.type==SDL_QUIT)
                cout << "Close the console to end up the program!" << endl;
}

p3class::~p3class()
{
    //dtor
}
