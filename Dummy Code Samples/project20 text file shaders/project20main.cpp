#include "p20class.h"
#include "glslprogram.h"

int main(int args, char** argv)
{
    p20class object;
    SDL_Window* window;
    window=object.init();
    object.draw(window);
    getch();
    return 0;
}
