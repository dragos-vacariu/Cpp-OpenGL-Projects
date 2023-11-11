#include "p31class.h"

int n=0;
GLfloat drawing[1000];
GLenum option=0x0001;
GLfloat red = 1.0;
GLfloat green = 0.0;
GLfloat blue = 0.0;
bool cleared=false;

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
  {
        switch(event.type)
        {
            case SDL_MOUSEBUTTONUP:
            {
                drawing[n]=event.motion.x;
                drawing[n+1]=-event.motion.y+600;
                n+=2;
            }

        }
        if(event.type==SDL_KEYDOWN)
            switch(event.key.keysym.sym)
            {
                case SDLK_1:
            {
                   cout << "Lines selected!" << endl;
                   option = 0x0001;
                   n=0;
                   break;
               }
                case SDLK_2:
                {
                    cout << "Points selected!" << endl;
                    option = 0x0000;
                    n=0;
                    break;
                }
                case SDLK_3:
                {
                    cout << "Triangles selected!" << endl;
                    option = 0x0004;
                    n=0;
                    break;
                }
                case SDLK_4:
                {
                    cout << "Polygon selected!" << endl;
                    option = 0x0009;
                    n=0;
                    break;
                }
                case SDLK_5:
                 {
                    cout << "Quads selected!" << endl;
                    option = 0x0007;
                    n=0;
                    break;
                }
                  case SDLK_6:
                 {
                    cout << "Triangle Strip selected!" << endl;
                    option = 0x0005;
                    n=0;
                    break;
                }
                  case SDLK_7:
                 {
                    cout << "Line Strip selected!" << endl;
                    option = 0x0003;
                    n=0;
                    break;
                }
                case SDLK_a:
                {
                    green = 0.0;
                    blue = 0.0;
                    red=1.0;
                    break;
                }
                case SDLK_s:
                {
                    green=1.0;
                    red=0.0;
                    blue=0.0;
                    break;
                }
                case SDLK_d:
                {
                    green=0.0;
                    red=0.0;
                    blue=1.0;
                    break;
                }
                case SDLK_q:
                {
                    green=0.0;
                    red=1.0;
                    blue=1.0;
                    break;
                }
                case SDLK_w:
                {
                    green=1.0;
                    red=1.0;
                    blue=0.0;
                    break;
                }
                case SDLK_e:
                {
                    green=1.0;
                    red=1.0;
                    blue=1.0;
                    break;
                }
                case SDLK_SPACE:
                {
                    glClear(GL_COLOR_BUFFER_BIT);
                    glLoadIdentity();
                    SDL_GL_SwapWindow(window);
                    cleared=true;
                }
            }
    }

}

SDL_Window* p8class::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project31", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext glstuff;
    glstuff=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "Glew has failed to initialize!" << endl;
    }
    return window;
}

void p8class::draw()
{
    SDL_Window* window;
    window=init();
    //Translating the normalized coordinates into pixel's real coordinates
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,800,0,600,0,1); //use this for camera view, get the image closer, or further, set the 3d field
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //the translation is done.

   menu();
    while(1)//infinite loop;
    {
        if(!cleared)
       {
            glEnableClientState(GL_POINT_SIZE);
            glPointSize(20);
        //    Drawing elements:
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(2, GL_FLOAT, 0, drawing);
                glColor3f(red,green,blue);
                glDrawArrays(option, 0, n/2);
                glDisableClientState(GL_VERTEX_ARRAY);
        //     Done drawing elements
            glDisableClientState(GL_POINT_SIZE);
       }
       else if(cleared)
       {
           GLfloat drawing[1000]={0};
           cleared=false;
           n=0;
       }
       checkinput(window); //check the input;
       SDL_GL_SwapWindow(window);// when the draw is completed, put the full image on the screen.
   }
}

void p8class::menu()
{
    cout << "MENU:\n" << endl;
    cout << "Press the following keys to change the mode: " << endl;
    cout << "1. Lines\n" << "2. Points\n" << "3. Triangles\n" << "4. Polygon\n" << "5. Quads\n" << "6. Triangle Strip\n"
                    << "7. Line Strip\n" << endl;
    cout << "A. red\n" << "S. green\n" << "D. blue\n" << "W. yellow\n" << "Q. magenta\n" << "E. white\n" << endl;
}
