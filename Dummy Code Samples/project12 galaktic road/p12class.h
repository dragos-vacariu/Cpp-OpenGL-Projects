#ifndef P12CLASS_H
#define P12CLASS_H
#include <SDL.h>
#include <glew.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class p12class
{
    public:
        p12class();
        virtual ~p12class();
        SDL_Window* init(); //declaring the init function
        void draw(SDL_Window* window); //declaring the draw function

    protected:

    private:
};

#endif // P12CLASS_H
