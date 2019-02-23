#ifndef P1CLASS_H
#define P1CLASS_H
#include <SDL.h>
#include <glew.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

class p1class
{
    public:
        p1class();
        int closed;
        virtual ~p1class();
        void init();
        int checkbut();

    protected:

    private:
};

#endif // P1CLASS_H
