#ifndef P12CLASS_H
#define P12CLASS_H
#include <SDL.h>
#include <glew.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SOIL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

class p12class
{
    public:
        p12class();
        virtual ~p12class();
        SDL_Window* init(); //declaring the init function
        void draw(SDL_Window* window); //declaring the draw function
        GLuint loadtexture(const char* filename);
        void input();
        void resetcoords();
        void movecoords();
        void fieldrand();
        void playtrack();
        void collisiondetection();
        int isgameover(SDL_Window* window, int Score, int highscore);
        int scoreupdate(int Score, int highscore);
        void savescore();
        void distancetravel();
        void frontcollision();
        void pushup();
        void scoremultiplier();

    protected:

    private:
};

#endif // P12CLASS_H
