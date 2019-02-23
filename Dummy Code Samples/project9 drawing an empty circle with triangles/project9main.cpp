#include "p9class.h"

int main(int args, char** argv)
{
    p8class object;
    object.init();
    while(1)
        object.checkinput();
    getch();
    return 0;
}
