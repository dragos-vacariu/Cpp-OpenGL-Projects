/*User defined headers:*/
#include "Car.h"

Car::Car(const unsigned int speed, const unsigned int ID)
{
    CarTextureSelector();
    //Validating the speed:
    if(speed > 0 && speed < 5)
    {
        Speed = speed;
    }
    else
    {
        Speed = 2; //let this be the default value;
    }
    isCarMoving = true;
    hasPriority = false;
    uniqueID = ID;
    timeGap = 0; //if it's the case the timeGap is set within Route constructor.
}
//Overriding the constructor
Car::Car(){
}

Car::~Car()
{
}

