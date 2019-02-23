#ifndef P20CLASS_H
#define P20CLASS_H
#include <glew.h>
#include <SDL.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <sstream>
#include <fstream>

using namespace std;
class p20class
{
    public:
        p20class();
        virtual ~p20class();
        SDL_Window* init();
        void input();
        void draw(SDL_Window* window);

    protected:

    private:

};

#endif // P20CLASS_H
