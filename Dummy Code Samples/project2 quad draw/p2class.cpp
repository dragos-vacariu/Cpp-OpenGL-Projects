#include "p2class.h"

p2class::p2class()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    window=SDL_CreateWindow("Project2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 700, SDL_WINDOW_OPENGL);
    if (window==nullptr)
    {
        cerr << "Could not open a window!" << endl;
    }
    SDL_GLContext context;
    context=SDL_GL_CreateContext(window);
    glewInit();
    if(glewInit()!=GLEW_OK)
    {
        cerr << "Could not initialize GLEW!" << endl;
    }
    cout << "Everything worked fine!" << endl;

    float vertices []
    {
        300, 300, 0.0,
        300, 600, 0.0,
        40, 500, 0.0,
        330, 300, 0.0
    };
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);

    glViewport(0.0f, 0.0f, 500, 700); //new view;
    glMatrixMode(GL_PROJECTION); //matrix mode;
    glLoadIdentity(); // load identity;
    glOrtho(0, 500, 0, 700, 0, 1); // orthogonal view, gives the opportunity to change the
    //normalized screen coordinates system, to classic, which uses pixels of window height, and weight;
    glMatrixMode( GL_MODELVIEW ); //matrix mode;
    glLoadIdentity();


    glVertexPointer(3,GL_FLOAT, 0, vertices );
    // 4 argumentes : number of pieces of data for every vertex(number of coordinates)
    //the type of data, float, converted into GL_FLOAT, the stride=0, and the pointer for the array, which is the index of the array.
    glDrawArrays(GL_QUADS, 0, 4);
    // 3 arguments: the type of drawing, the stride=0, and the number of vertices;


    glDisableClientState(GL_VERTEX_ARRAY);
    SDL_GL_SwapWindow(window);
    SDL_Event a;

    while(1)
        while(SDL_PollEvent(&a))
        {
            if(a.type==SDL_QUIT)
            {
                cout << "The window has been closed by the user" << endl;
                SDL_GL_DeleteContext(context);
                SDL_DestroyWindow(window);
                SDL_QUIT;
            }
        }
}

p2class::~p2class()
{
}
