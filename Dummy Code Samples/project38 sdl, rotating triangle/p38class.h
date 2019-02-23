#ifndef P38CLASS_H
#define P38CLASS_H
#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

class p38class
{
    public:
        p38class();
        virtual ~p38class();
        SDL_Window* init();
        void draw();
        void input();

    protected:

    private:
};

#endif // P38CLASS_H
