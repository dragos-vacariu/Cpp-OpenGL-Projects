#include "../include/player.h"

using namespace std;

player::player()
{
    this->x_pos = DEFAULT_PLAYER_X_POS;
    this->y_pos = DEFAULT_PLAYER_Y_POS;
    this->car_obj = new car(PLAYER_TEXTURE, this->x_pos, this->y_pos, 4, DEFAULT_PLAYER_SPEED);
}

player::~player()
{
    //dtor
    delete this->car_obj;
}

void player::drawPlayer()
{
    /*This function will draw the player onto the screen*/

    this->car_obj->draw_car();

    //In case the coordinates of the care were changes due to collision or other factors
    //update the player's coordinates also
    this->y_pos = this->car_obj->y_pos;
    this->x_pos = this->car_obj->x_pos;
}

void player::accelerate()
{
    /*This function will accelerate the player's speed*/

    this->car_obj->accelerate();
    if(this->y_pos < DEFAULT_PLAYER_Y_POS)
    {
        this->car_obj->move_upwards(0.5f);
    }
}

GLfloat player::getBottomLeftXCoor()
{
    return this->car_obj->left_bottom_corner[0];
}

GLfloat player::getBottomLeftYCoor()
{
    return this->car_obj->left_bottom_corner[1];
}

GLfloat player::getBottomRightXCoor()
{
    return this->car_obj->right_bottom_corner[0];
}

GLfloat player::getBottomRightYCoor()
{
    return this->car_obj->right_bottom_corner[1];
}

GLfloat player::getTopLeftXCoor()
{
    return this->car_obj->left_top_corner[0];
}

GLfloat player::getTopLeftYCoor()
{
    return this->car_obj->left_top_corner[1];
}

GLfloat player::getTopRightXCoor()
{
    return this->car_obj->right_top_corner[0];
}

GLfloat player::getTopRightYCoor()
{
    return this->car_obj->right_top_corner[1];
}
