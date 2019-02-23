#include "p23class.h"

int main(int args, char** argv)
{
    SDL_Window* aux;
    p23class object;
    aux=object.init();
    object.draw(aux);
    getch();
    return 0;
}
