#include "p27class.h"

p8class::p8class()
{
}

p8class::~p8class()
{
}
GLfloat p8class::checkinput(SDL_Window* window)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
        switch(event.type) //check what button is pressed;
        {
            case SDL_QUIT:
            {
                SDL_Quit();
                exit(1);
            }
        }
}

void p8class::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project27", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 650, 650, SDL_WINDOW_OPENGL);
    SDL_GLContext glstuff;
    glstuff=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "Glew has failed to initialize!" << endl;
    }

    float amb [] = {0.5, 0.5, 0.5, 1.0}; //color for the ambient light
    float diff [] = {1.0, 0.6, 0.0, 1.0}; //color for the diffuse
    float pos [] = {0, 500, 0.0}; //light position

    //Translating the normalized coordinates into pixel's real coordinates
    glViewport(0, 0, 650, 650);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-250,650,-250,650,-650,650); //use this for camera view, get the image closer, or further, set the 3d field
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //the translation is done.

   glEnable(GL_LIGHTING); //enable lighting
   glEnable(GL_LIGHT0); //put this light in the world
   glLightfv(GL_LIGHT0, GL_POSITION, pos); //the light position is in the pos array.
   glLightfv(GL_LIGHT0, GL_AMBIENT, amb); //the light ambient color is in the amb array.
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diff); //the light diffuse color is in the diff array.
   glEnable(GL_COLOR_MATERIAL); //enable the color material, to enable the color for all the cube's faces...

   glEnable(GL_FOG); //enable the fog
   glFogi(GL_FOG_MODE, GL_EXP); //the fog will be linear;
   glFogf(GL_FOG_DENSITY, 0.6); //this is used for exponential fog mode;
   //glFogf(GL_FOG_START, 0.1); //at this value the object will be the most visible;
   //glFogf(GL_FOG_END, 5.0); //at this value the fog will cover the entire object.
   float fogcolor[] {0.1,0.0,0.0,1.0}; //the color for the fog.
   glFogfv(GL_FOG_COLOR, fogcolor); // set the color for the fog.

    while(1)//infinite loop;
    {
        glClearColor(0.1,0.0,0.0,1.0); //clear the screen each iteration.

        glEnable(GL_DEPTH_TEST);   //Enable depth buffering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the screen each time.

       //THE SECOND WAY OF DRAWING, USING THE VERTEXES AND COLORS BELOW (IMMEDIAT MODE):
       glBegin(GL_QUADS); //drawing starts here.

       //front face
       glNormal3f(0.0,0.0,1.0);
       glColor3f(1.0,0.0,0.0);
       glVertex3f(200,200,0);
       glVertex3f(200,400,0);
       glVertex3f(400,400,0);
       glVertex3f(400,200,0);

        //right face
        glNormal3f(-1.0,0.0,0.0);
       glColor3f(0.0,1.0,0.0);
       glVertex3f(200,200,0);
       glVertex3f(200,400,0);
       glVertex3f(200,400,-200);
       glVertex3f(200,200,-200);

       //left face
       glNormal3f(1.0,0.0,0.0);
       glColor3f(0.0,0.0,1.0);
       glVertex3f(400,200,0);
       glVertex3f(400,200,-200);
       glVertex3f(400,400,-200);
       glVertex3f(400,400,0);

       //bottom face
       glNormal3f(0.0,-1.0,0.0);
       glColor3f(1.0,1.0,1.0);
       glVertex3f(200,200,0);
       glVertex3f(400,200,0);
       glVertex3f(400,200,-200);
       glVertex3f(200,200,-200);

       //top face
       glNormal3f(0.0,1.0,0.0);
       glColor3f(1.0,0.0,1.0);
       glVertex3f(200,400,0);
       glVertex3f(200,400,-200);
       glVertex3f(400,400,-200);
       glVertex3f(400,400,0);

       //back face
       glNormal3f(0.0,0.0,-1.0);
       glColor3f(1.0,1.0,0.5);
       glVertex3f(200,200,-200);
       glVertex3f(400,200,-200);
       glVertex3f(400,400,-200);
       glVertex3f(200,400,-200);

       glEnd(); //drawing ends here.

       glRotatef(1,1.0,1.0,0.0); //make the rotation

       SDL_Delay(60); //small delay.
       checkinput(window); //check the input;
       SDL_GL_SwapWindow(window);// when the draw is completed, put the full image on the screen.
   }
}
