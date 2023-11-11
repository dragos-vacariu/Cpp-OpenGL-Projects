#ifndef P8CLASS_H
#define P8CLASS_H
#include <SDL.h>
#include <iostream>
#include <glew.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

using namespace std;
class p8class
{
    public:
        p8class();
        virtual ~p8class();
        GLfloat checkinput(SDL_Window* window);
        SDL_Window* init();
        void menu();
        void draw();
        void clearscreen();

    protected:

    private:
};

#endif // P8CLASS_H
