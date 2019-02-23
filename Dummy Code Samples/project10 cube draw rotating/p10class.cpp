#include "p10class.h"

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
    Xrot, Yrot=29.0f;
    SDL_Event event;
    const GLfloat rotationSpeed = 10;

    while(SDL_PollEvent(&event))
        if(event.type==SDL_KEYDOWN) // if a button is pressed
            switch(event.key.keysym.sym) //check what button is pressed;
            {
                case SDL_QUIT:
                {
                    cout << "Close the console to quit!" << endl;
                }
               /* case SDLK_LEFT: //case arrow left;
                   {
                       Xrot=Xrot-rotationSpeed;
                       cout << "The left arrow is being pressed" << endl;
                        break;
                   }
                case SDLK_RIGHT: //case arrow right;
                    {
                        Xrot=Xrot+rotationSpeed;
                        cout << "The right arrow is being pressed" << endl;
                        break;
                    }
                case SDLK_UP: // case arrow up;
                    {
                        Yrot=Yrot+rotationSpeed;
                        cout << "The up arrow is being pressed" << endl;
                        break;
                    }
                case SDLK_DOWN: // case arrow down;
                    {
                        Yrot=Yrot-rotationSpeed;
                        cout << "The down arrow is being pressed" << endl;
                        break;
                    }
                    */
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
            200, 500, -200,
            400, 500, -200,
            400, 500, 0,
            //downside face;
            200, 300, 0,
            200, 300, -200,
            400, 300, -200,
            400, 300, 0,

        };

        GLfloat color[]
        {
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
            0.0,1.0,0.0,

            1.0,1.0,0.0,
            1.0,1.0,0.0,
            1.0,1.0,0.0,
            1.0,1.0,0.0,

            1.0,0.0,1.0,
            1.0,0.0,1.0,
            1.0,0.0,1.0,
            1.0,0.0,1.0,

            0.0,1.0,1.0,
            0.0,1.0,1.0,
            0.0,1.0,1.0,
            0.0,1.0,1.0
        };
        //Translating the normalized coordinates into pixel's real coordinates
        glViewport(0, 0, 650, 650);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-25,650,-25,650,-650,650); //use this for camera view, get the image closer, or further, set the 3d field
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //the translation is done.

    while(1)//infinite loop;
    {
        glClearColor(0.01,0.01,0.01,0.0); //clear the screen each iteration.
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //fill the screen with the clear screen color.

   //     glPushMatrix(); //optional
        glTranslatef(50,50,-20); //translate the matrix for the rotation
        glRotatef(1,1.0,1.0,0.0); //make the rotation
        glTranslatef(-50,-50,20); //translate the matrix back.

       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //making the quad be empty, with GL_LINE argument.

       //THE FIRST WAY OF DRAWING, USING THE CUBE ARRAY, AND COLOR ARRAY DECLARED ABOVE:
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnable(GL_LINE_SMOOTH);

        glPopMatrix(); //optional

        glVertexPointer(3, GL_FLOAT, 0, cube);
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, color);
        glDrawArrays(GL_QUADS, 0, 24);//draw to the screen;

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);

       //THE SECOND WAY OF DRAWING, USING THE VERTEXES AND COLORS BELOW (IMMEDIAT MODE):
     /*  glBegin(GL_QUADS); //drawing starts here.

       glColor3f(1.0,0.0,0.0);
       glVertex3f(200,200,0);
       glVertex3f(200,400,0);
       glVertex3f(400,400,0);
       glVertex3f(400,200,0);

       glColor3f(0.0,1.0,0.0);
       glVertex3f(200,200,0);
       glVertex3f(200,400,0);
       glVertex3f(200,400,-200);
       glVertex3f(200,200,-200);

       glColor3f(0.0,0.0,1.0);
       glVertex3f(400,200,0);
       glVertex3f(400,200,-200);
       glVertex3f(400,400,-200);
       glVertex3f(400,400,0);

       glColor3f(1.0,1.0,0.0);
       glVertex3f(200,200,0);
       glVertex3f(400,200,0);
       glVertex3f(400,200,-200);
       glVertex3f(200,200,-200);

       glColor3f(1.0,0.0,1.0);
       glVertex3f(200,400,0);
       glVertex3f(200,400,-200);
       glVertex3f(400,400,-200);
       glVertex3f(400,400,0);

       glColor3f(0.5,0.5,0.5);
       glVertex3f(200,200,-200);
       glVertex3f(400,200,-200);
       glVertex3f(400,400,-200);
       glVertex3f(200,400,-200);

       glEnd(); //drawing ends here.
*/
       SDL_Delay(60); //small delay.

        checkinput(window); //check the input;
        SDL_GL_SwapWindow(window);// when the draw is completed, put the full image on the screen.
   }
}
