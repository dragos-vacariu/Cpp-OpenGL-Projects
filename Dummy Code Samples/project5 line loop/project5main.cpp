#include "p5class.h"

int main(int args, char** argv)
{
    p5class pclass;
    pclass.openwindow();
    while(1)
        pclass.pollevents();
    getch();
    return 0;
}
