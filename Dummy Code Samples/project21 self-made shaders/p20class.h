#ifndef P20CLASS_H
#define P20CLASS_H
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;
class p20class
{
    public:
        p20class();
        virtual ~p20class();
        SDL_Window* init();
        void draw(SDL_Window* window);
        GLuint installshaders();
        void input();

    protected:

    private:
};

#endif // P20CLASS_H
