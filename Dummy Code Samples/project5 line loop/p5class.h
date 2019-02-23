#ifndef P5CLASS_H
#define P5CLASS_H
#include <SDL.h>
#include <glew.h>
#include <iostream>
#include <conio.h>

using namespace std;
class p5class
{
    public:
        p5class();
        virtual ~p5class();
        void pollevents();
        void openwindow();
        SDL_Window* window;

    protected:

    private:
};

#endif // P5CLASS_H
