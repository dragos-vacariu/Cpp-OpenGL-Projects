#include "p24class.h"

p8class::p8class()
{
    //ctor
}

p8class::~p8class()
{
    //dtor
}
GLfloat p8class::checkinput(SDL_Window* window)
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
        if(event.type==SDL_KEYDOWN) // if a button is pressed
            switch(event.key.keysym.sym) //check what button is pressed;
            {
                case SDL_QUIT:
                {
                    cout << "Close the console to quit!" << endl;
                }
                case SDLK_LEFT: //case arrow left;
                   {
                        glRotatef(1, 0.0, 1.0, 0.0); //make the rotation
                        break;
                   }
                case SDLK_RIGHT: //case arrow right;
                    {
                        glRotatef(359, 0.0, 1.0, 0.0);
                        break;
                    }
                case SDLK_UP: // case arrow up;
                    {
                        glRotatef(1 ,1.0, 0.0, 0.0);
                        break;
                    }
                case SDLK_DOWN: // case arrow down;
                    {
                        glRotatef(359, 1.0, 0.0, 0.0);
                        break;
                    }

            }
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
     GLfloat cube[]
        {
            //front face;
            200, 300, 0,
            200, 500, 0,
            400, 500, 0,
            400, 300, 0,
            //left face;
            200, 300, 0,
            200, 500, 0,
            200, 500, -200,
            200, 300, -200,
            //right face;
            400, 300, 0,
            400, 500, 0,
            400, 500, -200,
            400, 300, -200,
            //back face;
            200, 300, -200,
            200, 500, -200,
            400, 500, -200,
            400, 300, -200,
            //upside face;
            200, 500, 0,
            200, 500, 0,
            400, 500, -200,
            400, 500, -200,
            //downside face;
            200, 300, 0,
            200, 300, 0,
            400, 300, -200,
            400, 300, -200,

        };

        GLfloat color[]
        {
            1.0,0.0,0.0,
            1.0,0.0,0.0,
            1.0,0.0,0.0,
            1.0,0.0,0.0,

            1.0,0.0,0.0,
            1.0,0.0,0.0,
            1.0,0.0,0.0,
            1.0,0.0,0.0,

            1.0,0.0,0.0,
            1.0,0.0,0.0,
            1.0,0.0,0.0,
            1.0,0.0,0.0,

            1.0,0.0,0.0,
            1.0,0.0,0.0,
            1.0,0.0,0.0,
            1.0,0.0,0.0,

            0.0,0.0,1.0,
            0.0,0.0,1.0,
            0.0,0.0,1.0,
            0.0,0.0,1.0,

            0.0,1.0,0.0,
            0.0,1.0,0.0,
            0.0,1.0,0.0,
            0.0,1.0,0.0
        };
        float amb [] = {0.5, 0.5, 0.5, 1.0}; //color for the ambient light
        float diff [] = {1.0, 0.6, 0.0, 1.0}; //color for the diffuse
        float pos [] = {0, 500, 0.0}; //light position

        float amb2 [] = {0.5, 0.1, 0.0, 1.0}; //color for the ambient light
        float diff2 [] = {0.3, 3.0, 0.0, 1.0}; //color for the diffuse
        float pos2 [] = {400, 300, 0.0}; //light position

        float amb3 [] = {0.2, 0.0, 0.9, 1.0}; //color for the ambient light
        float diff3 [] = {0.5, 0.5, 0.5, 1.0}; //color for the diffuse
        float pos3 [] = {200, 300, -200}; //light position
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
       glEnable(GL_LIGHT1);
       glLightfv(GL_LIGHT1, GL_POSITION, pos2);
       glLightfv(GL_LIGHT1, GL_AMBIENT, amb2);
       glLightfv(GL_LIGHT1, GL_DIFFUSE, diff2);
       glEnable(GL_LIGHT2);
       glLightfv(GL_LIGHT2, GL_POSITION, pos3);
       glLightfv(GL_LIGHT2, GL_AMBIENT, amb3);
       glLightfv(GL_LIGHT2, GL_DIFFUSE, diff3);

    while(1)//infinite loop;
    {

        glEnable(GL_DEPTH_TEST);   //Enable depth buffering
        glClearColor(0.0,0.0,0.0,1.0); //clear the screen each iteration.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the screen each time.

    //   glPushMatrix(); //optional

       //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //making the quad be empty, with GL_LINE argument.

       //THE FIRST WAY OF DRAWING, USING THE CUBE ARRAY, AND COLOR ARRAY DECLARED ABOVE:

/*
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glPopMatrix(); //optional
        glVertexPointer(3,GL_FLOAT, 0, cube);
        glColorPointer(3,GL_FLOAT,0,color);
        glDrawArrays(GL_QUADS, 0, 24);//draw to the screen;

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
*/

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

       SDL_Delay(60); //small delay.
        checkinput(window); //check the input;
        SDL_GL_SwapWindow(window);// when the draw is completed, put the full image on the screen.
   }
}
