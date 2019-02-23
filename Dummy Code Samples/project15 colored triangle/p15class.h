#ifndef P15CLASS_H
#define P15CLASS_H
#include <SDL.h>
#include <glew.h>
#include <iostream>
#include <conio.h>

using namespace std;
class p15class
{
    public:
        p15class();
        virtual ~p15class();
        SDL_Window* init();
        void draw(SDL_Window* window);

    protected:

    private:
};

#endif // P15CLASS_H
