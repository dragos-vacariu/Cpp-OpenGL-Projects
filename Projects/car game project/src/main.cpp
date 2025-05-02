#include "../include/game.h"

int main (int args, char** argv)
{
    game* object = new game();
    object->mainloop();

    delete object;

    return 0;
}
