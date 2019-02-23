#ifndef P19CLASS_H
#define P19CLASS_H
#include <glew.h>
#include <SDL.h>
#include <conio.h>
#include <iostream>

using namespace std;
class p19class
{
    public:
        p19class();
        virtual ~p19class();
        void draw(SDL_Window* window);
        SDL_Window* init();
        void input();
        void installshaders();

    protected:

    private:
};

#endif // P19CLASS_H
