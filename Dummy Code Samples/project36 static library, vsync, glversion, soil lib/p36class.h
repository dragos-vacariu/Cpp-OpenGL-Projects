#ifndef P16CLASS_H
#define P16CLASS_H
#include <SDL.h>
#include <glew.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <SOIL.h>
#include <fstream>

using namespace std;
class p16class
{
    public:
        p16class();
        virtual ~p16class();
        SDL_Window* init();
        void draw(SDL_Window* window);
        unsigned int loadtexture(const char* filename);
        void linkingErrors(GLuint programID);
        void compilationErrors(GLuint shadername);
        GLuint installshaders();
        const GLchar* readfile(ifstream &FILE, GLchar* shaderpath);

    protected:

    private:
};

#endif // P16CLASS_H
