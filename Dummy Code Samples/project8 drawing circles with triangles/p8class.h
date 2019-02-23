#ifndef P8CLASS_H
#define P8CLASS_H
#include <SDL.h>
#include <iostream>
#include <glew.h>
#include <conio.h>
#include <math.h>

using namespace std;
class p8class
{
    public:
        p8class();
        virtual ~p8class();
        void checkinput();
        void init(GLint numberofsides, GLfloat radius);

    protected:

    private:
};

#endif // P8CLASS_H
