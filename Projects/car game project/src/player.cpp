#include "../include/player.h"

using namespace std;

player::player()
{
    this->x_pos = DEFAULT_PLAYER_X_POS;
    this->y_pos = DEFAULT_PLAYER_Y_POS;
    this->player_speed = DEFAULT_PLAYER_SPEED;
    this->braking_factor = this->player_speed * BRAKING_FORCE;
    this->acceleration_factor = ACCELETATION_FORCE / this->player_speed;
    this->car_obj = new car(PLAYER_TEXTURE, this->x_pos, this->y_pos, this->player_speed);
}

player::~player()
{
    //dtor
    delete this->car_obj;
}

void player::brake()
{
    /*This function will brake the player's car*/

    if(this->player_speed - this->braking_factor > MINIMUM_TRAVELLING_SPEED)
    {
        this->player_speed -= this->braking_factor;
        this->braking_factor = this->player_speed * BRAKING_FORCE;
        this->car_obj->changeSpeed(this->player_speed);
    }
}

void player::accelerate()
{
    /*This function will accelerate the player's speed*/

    if(this->player_speed + this->acceleration_factor < MAXIMUM_TRAVELLING_SPEED)
    {
        this->player_speed += this->acceleration_factor;
        this->acceleration_factor = ACCELETATION_FORCE / this->player_speed;
        this->car_obj->changeSpeed(this->player_speed);

        if(this->y_pos < DEFAULT_PLAYER_Y_POS)
        {
            this->car_obj->move_upwards(0.5f);
        }
    }
}

void player::deccelerate()
{
    /*This function will decelerate the player's speed*/

    if(this->player_speed - DECELERATION_FORCE > MINIMUM_TRAVELLING_SPEED)
    {
        this->player_speed -= DECELERATION_FORCE;
        this->car_obj->changeSpeed(this->player_speed);
    }
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
