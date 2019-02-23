#ifndef P23CLASS_H
#define P23CLASS_H
#include <glew.h>
#include <SDL.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using glm::vec3;
using glm::mat4;
using namespace std;
class p23class
{
    public:
        p23class();
        virtual ~p23class();
        SDL_Window* init();
        void draw(SDL_Window* window);
        void input();
        GLuint installshaders();
        const GLchar* readfile(ifstream &FILE, GLchar* shaderpath);
        void compilationErrors(GLuint shadername);
        void linkingErrors(GLuint programID);

    protected:

    private:
};

#endif // P23CLASS_H
