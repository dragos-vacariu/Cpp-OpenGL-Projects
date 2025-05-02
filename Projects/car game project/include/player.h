#ifndef PLAYER_H
#define PLAYER_H

//Class inclusions
#include "../include/car.h"
#include "../include/cross_functions.h"

//Constant defines
#define PLAYER_TEXTURE IMG_RESOURCES "/car.png"
#define MINIMUM_TRAVELLING_SPEED 1.0f
#define MAXIMUM_TRAVELLING_SPEED 20.0f
#define BRAKING_FORCE 0.02f
#define DECELERATION_FORCE 0.005f
#define ACCELETATION_FORCE 2.0f
#define MINIMUM_BRAKING_VALUE 0.1f
#define MINIMUM_ACCELERATION_VALUE 0.1f
#define DEFAULT_PLAYER_X_POS 230
#define DEFAULT_PLAYER_Y_POS 125
#define DEFAULT_PLAYER_SPEED 20.0f

class player
{
    public:
        player();
        virtual ~player();
        GLfloat x_pos;
        GLfloat y_pos;
        GLfloat player_speed;
        GLfloat braking_factor;
        GLfloat acceleration_factor;
        car* car_obj;

        //Public methods:
        void drawPlayer();
        void brake();
        void accelerate();
        void deccelerate();
        GLfloat getTopLeftXCoor();
        GLfloat getTopLeftYCoor();
        GLfloat getTopRightXCoor();
        GLfloat getTopRightYCoor();
        GLfloat getBottomLeftXCoor();
        GLfloat getBottomLeftYCoor();
        GLfloat getBottomRightXCoor();
        GLfloat getBottomRightYCoor();

    protected:

    private:

        //Private methods:

};

#endif // PLAYER_H
