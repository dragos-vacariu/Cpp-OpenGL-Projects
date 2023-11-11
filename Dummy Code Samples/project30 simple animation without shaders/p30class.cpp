#include "p30class.h"

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
    int x,y=0;
    float z=0.0f;
    bool comp=false;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project30", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
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
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50,800,-50,600,-650,650); //use this for camera view, get the image closer, or further, set the 3d field
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //the translation is done.

   glEnable(GL_LIGHTING); //enable lighting
   glEnable(GL_LIGHT0); //put this light in the world
   glLightfv(GL_LIGHT0, GL_POSITION, pos); //the light position is in the pos array.
   glLightfv(GL_LIGHT0, GL_AMBIENT, amb); //the light ambient color is in the amb array.
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diff); //the light diffuse color is in the diff array.
   glEnable(GL_COLOR_MATERIAL); //enable the color material, to enable the color for all the cube's faces...

    while(1)//infinite loop;
    {
        glClearColor(0.1,0.0,0.0,1.0); //clear the screen each iteration.

        glEnable(GL_DEPTH_TEST);   //Enable depth buffering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the screen each time.

       //THE SECOND WAY OF DRAWING, USING THE VERTEXES AND COLORS BELOW (IMMEDIAT MODE):
       glBegin(GL_QUADS); //drawing starts here.
       //front face
       glNormal3f(0.0,0.0,1.0);
       glColor3f(1.0-(z/100),1.0, 0.0+ (float(y)/100));
       glVertex3f(200+y,200+z,0);
       glVertex3f(200+y,400+z,0);
       glVertex3f(400+y,400+z,0);
       glVertex3f(400+y,200+z,0);
       glEnd(); //drawing ends here.

       glBegin(GL_TRIANGLES);
       glColor3f(1.0,0.0+(z/100),0.1+ (float(y)/100));
       glVertex3f(500+y,200+z,0);
       glVertex3f(700+y,200+z,0);
       glVertex3f(600+y,400+z,0);
       glEnd();

       glBegin(GL_TRIANGLE_FAN);
       glColor3f(1.0-(float(y)/100),0.5,0.1+(z/100));
       glVertex3f(50+y,200+z,0);
       glVertex3f(150+y,200+z,0);
       glVertex3f(100+y,500+z, 0);
       glVertex3f(120+y,550+z,0);
       glEnd();

       x++;

       if(x<50)
       {
           y++;
       }

       if(x>50&&x<100)
       {
           z++;
       }
       if(x>100&&x<150)
       {
           y--;
       }
       if(x>150&&x<200)
       {
           z--;
       }
       if(x>200)
       {
           x=0;
       }

       SDL_Delay(60); //small delay.
       checkinput(window); //check the input;
       SDL_GL_SwapWindow(window);// when the draw is completed, put the full image on the screen.
   }
}
