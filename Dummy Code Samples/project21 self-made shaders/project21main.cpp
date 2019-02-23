#include "p20class.h"

int main(int args, char** argv)
{
    SDL_Window* aux;
    p20class object;
    aux=object.init();
    object.draw(aux);
    getch();
    return 0;
}
