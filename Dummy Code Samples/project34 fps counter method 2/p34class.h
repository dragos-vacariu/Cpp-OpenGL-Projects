#ifndef P34CLASS_H
#define P34CLASS_H
#include <glew.h>
#include <SDL.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>


using namespace std;

class p34class
{
    public:
        p34class();
        virtual ~p34class();
        SDL_Window* init();
        void draw();
        void input();
        void calculatefps(int looper);
        float frametime=0;
        float fps=0;
        unsigned int loadtexture(const char* filename);

    protected:

    private:
};

#endif // P34CLASS_H
