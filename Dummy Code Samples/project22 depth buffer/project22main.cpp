#include "p22class.h"

int main(int args, char** argv)
{
    SDL_Window* auxiliar;
    p22class object;
    auxiliar=object.init();
    object.draw(auxiliar);
    getch();
    return 0;
}
