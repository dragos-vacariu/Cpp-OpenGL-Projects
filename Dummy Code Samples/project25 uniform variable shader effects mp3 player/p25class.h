#ifndef P22CLASS_H
#define P22CLASS_H
#include <glew.h>
#include <SDL.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <SDL_mixer.h>


using namespace std;
class p22class
{
    public:
        p22class();
        virtual ~p22class();
        SDL_Window* init();
        void draw(SDL_Window* window);
        GLuint installshaders();
        void input();

    protected:

    private:
};

#endif // P22CLASS_H
