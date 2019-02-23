#include "p15class.h"

int main(int args, char** argv)
{
    p15class object;
    SDL_Window* auxiliar;
    auxiliar=object.init();
    object.draw(auxiliar);
    getch();
    return 0;
}
