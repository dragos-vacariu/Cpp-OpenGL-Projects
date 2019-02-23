#include "p8class.h"

int main(int args, char** argv)
{
    GLfloat rd;
    GLint nbelem;
    p8class object;
    while(1)
    {
        cout << "Enter the radius size, [OPTIMAL would be between 50 - 400]!" << endl;
        cin >> rd;
        cout << "Enter the number of elements: [MORE elements would get a better circular shape]!" << endl;
        cin >> nbelem;
        object.init(nbelem,rd);
    }

    while(1)
        object.checkinput();
    getch();
    return 0;
}
