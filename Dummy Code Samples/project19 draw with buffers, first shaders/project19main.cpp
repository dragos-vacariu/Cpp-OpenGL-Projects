#include "p19class.h"

int main(int args, char** argv)
{
    p19class object;
    SDL_Window* aux;
    aux=object.init();
    object.draw(aux);
    getch();
    return 0;
}
