#ifndef PLAYER_H
#define PLAYER_H

//Class inclusions
#include "../include/car.h"
#include "../include/cross_functions.h"

//Constant defines
#define PLAYER_TEXTURE IMG_RESOURCES "/car.png"
#define DEFAULT_PLAYER_X_POS 430
#define DEFAULT_PLAYER_Y_POS 125
#define DEFAULT_PLAYER_SPEED 15.0f

class player
{
    public:
        player();
        virtual ~player();
        GLfloat x_pos;
        GLfloat y_pos;
        car* car_obj;

        //Public methods:
        void drawPlayer();
        void accelerate();
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
