#include "p34class.h"

p34class::p34class()
{
}

p34class::~p34class()
{
}

unsigned int p34class::loadtexture(const char* filename)
{
    SDL_Surface* image=SDL_LoadBMP(filename);
    if(image==nullptr)
    {
        cout << "The file: " << filename << " could not be loaded!" << endl;
        return 0;
    }
    unsigned int id;
    glGenTextures(1,&id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(image);
    return id;
}

SDL_Window* p34class::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project34", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,600, SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    context=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "Ërror initializing glew!" << endl;
        return nullptr;
    }
    return window;
}

void p34class::draw()
{
    SDL_Window* openwindow = init();
    if(openwindow==nullptr)
    {
        cerr << "Failed to initialize!" << endl;
        return;
    }
    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);

    int showInTenSeconds=0;
    unsigned int texture;

    glViewport(0,0, 800,600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 800, -10, 600, -200, 600);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat rectanglebox[]
    {
      200,100,0,
      400,100,0,
      400,500,0,
      200,500,0,

      200,100,-100,
      400,100,-100,
      400,500,-100,
      200,500,-100,

      200,100,0,
      400,100,0,
      400,100,-100,
      200,100,-100,

      200,500,0,
      400,500,0,
      400,500,-100,
      200,500,-100,

      200,100,0,
      200,100,-100,
      200,500,-100,
      200,500,0,

      400,100,0,
      400,100,-100,
      400,500,-100,
      400,500,0

    };
    glEnable(GL_TEXTURE_2D);
    texture=loadtexture("7.bmp");
    while(1)
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);

        glTranslatef(1.0,-1.0,1.0); //move the rotating image around
        glRotatef(1,1.0,1.0,0.0); //rotate the image.

        glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0); //set texture corner coordinate
        glNormal3f(0.0,0.0,1.0);
        glVertex3f(200,200, 0);
        glTexCoord2f(0.0,0.0), //set the texture corner coordinate
        glVertex3f(200,400, 0);
        glTexCoord2f(1.0,0.0); //set the texture corner coordinate
        glVertex3f(400,400, 0);
        glTexCoord2f(1.0,1.0); //set the texture corner coordinate
        glVertex3f(400,200, 0);

        glTexCoord2f(0.0,1.0); //set texture corner coordinate
        glNormal3f(-1.0,0.0,0.0);
        glVertex3f(200,200, 0);
        glTexCoord2f(0.0,0.0), //set the texture corner coordinate
        glVertex3f(200,400, 0);
        glTexCoord2f(1.0,0.0); //set the texture corner coordinate
        glVertex3f(200,400, -200);
        glTexCoord2f(1.0,1.0); //set the texture corner coordinate
        glVertex3f(200,200, -200);

        glTexCoord2f(0.0,1.0); //set texture corner coordinate
        glNormal3f(0.0,0.0,-1.0);
        glVertex3f(200,200, -200);
        glTexCoord2f(0.0,0.0), //set the texture corner coordinate
        glVertex3f(200,400, -200);
        glTexCoord2f(1.0,0.0); //set the texture corner coordinate
        glVertex3f(400,400, -200);
        glTexCoord2f(1.0,1.0); //set the texture corner coordinate
        glVertex3f(400,200, -200);

        glTexCoord2f(0.0,1.0); //set texture corner coordinate
        glNormal3f(1.0,0.0,0.0);
        glVertex3f(400,200, 0);
        glTexCoord2f(0.0,0.0), //set the texture corner coordinate
        glVertex3f(400,400, 0);
        glTexCoord2f(1.0,0.0); //set the texture corner coordinate
        glVertex3f(400,400, -200);
        glTexCoord2f(1.0,1.0); //set the texture corner coordinate
        glVertex3f(400,200, -200);

        glTexCoord2f(0.0,1.0); //set texture corner coordinate
        glNormal3f(0.0,1.0,0.0);
        glVertex3f(200,400, 0);
        glTexCoord2f(0.0,0.0), //set the texture corner coordinate
        glVertex3f(200,400, -200);
        glTexCoord2f(1.0,0.0); //set the texture corner coordinate
        glVertex3f(400,400, -200);
        glTexCoord2f(1.0,1.0); //set the texture corner coordinate
        glVertex3f(400,400, 0);

        glTexCoord2f(0.0,1.0); //set texture corner coordinate
        glNormal3f(0.0,-1.0, 0.0);
        glVertex3f(200,200, 0);
        glTexCoord2f(0.0,0.0), //set the texture corner coordinate
        glVertex3f(200,200, -200);
        glTexCoord2f(1.0,0.0); //set the texture corner coordinate
        glVertex3f(400,200, -200);
        glTexCoord2f(1.0,1.0); //set the texture corner coordinate
        glVertex3f(400,200, 0);
        glEnd();


        calculatefps(showInTenSeconds);
        if(showInTenSeconds==10) //order is important;
        {
            showInTenSeconds=0;
        }

        input();
        SDL_GL_SwapWindow(openwindow);
        SDL_Delay(30);
        showInTenSeconds++;
    }
}
void p34class::input()
{
    SDL_Event a;
    while(SDL_PollEvent(&a))
    {
        switch(a.type)
        {
            case SDL_QUIT:
            {
                SDL_Quit();
                exit(1);
            }
        }
    }
}
void p34class::calculatefps(int looper)
{
    static const int samples=10; //size of array
    static float frametimes[samples]; //store in this array the frametime
    static float prevticks=SDL_GetTicks();// store the time from the beginning of the program;
    static int currentframe=0; //this is initialized only once, and then it keeps the previous value;

    float currenticks=SDL_GetTicks(); //store the time from the beginning of the program, this is executed each function call;

    frametime = currenticks-prevticks; //first time this will be zero;
    frametimes[currentframe%samples]=frametime; //store the frame time in the array (circle storage);
    prevticks=currenticks; //prevticks gets the value of currentticks;

    int counter; // simple counter

    if(currentframe<samples)
    {
        counter=currentframe;
    }
    else
    {
        counter=samples;
    }

    float frametimeavg=0;

    for(int i=0;i<counter; i++)
    {
        frametimeavg+=frametimes[i]; //get the sum of the entire array into frametimeavg
    }

    frametimeavg/=counter; //compute the average frame;

    if(frametimeavg>0) //if the average is not zero
    {
        fps=1000.0/frametimeavg; //compute the fps;
    }
    else
    {
        fps = 60; //fake a value
    }

    if(looper==10) //display this one once in ten calls;
    {
        cout << fps << endl;
    }
    currentframe++; //get to the next frame;
}
