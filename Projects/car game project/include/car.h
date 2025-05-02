#ifndef CAR_H
#define CAR_H

//Cross-functions inclusion:
#include "../include/cross_functions.h"
#include "../include/world_map.h"

//Constant defines
#define CAR_WIDTH 40
#define CAR_HEIGHT 100
#define CAR_TURNING_FACTOR 0.2f
#define CAR_ROTATION_FACTOR 2.0f
#define DEFAULT_CAR_SPEED 5.0f
#define ITERATIONS_FOR_COLOR_EFFECT 100
#define COLORED_ITERATIONS_ON_COLOR_EFFECT 15
#define IDLE_ITERATIONS_ON_COLOR_EFFECT 20
#define OPACITY_FOR_COLOR_EFFECT 0.4f

enum Texture_Flip
{
    NORMAL,
    FLIP_VERTICALLY,
    FLIP_HORIZONTALLY,
};

enum CAR_DIRECTION
{
    LEFT,
    RIGHT,
    STRAIGHT,
    REVERSE,
};

struct CollisionInfo
{
    bool isColliding; // are the 2 object colliding with each other
    float pushX; // minimum translation vector x component
    float pushY; // minimum translation vector y component
};

struct Color_Effect
{
    int iterations_active = 0;
    int colored_iterations = 0;
    int regular_iterations = 0;

    GLfloat red_value = 1.0f;
    GLfloat green_value = 1.0f;
    GLfloat blue_value = 1.0f;
    GLfloat opacity_value = 1.0f;
};

class car
{
    public:
        car(const char* texture_location, float x_position, float y_position, GLfloat speed = DEFAULT_CAR_SPEED,
             Texture_Flip texture_flipping = Texture_Flip::NORMAL);
        virtual ~car();

        //Public functions:
        void draw_car();
        void turn(CAR_DIRECTION direction);
        void decrease_turn();
        void restore_previous_position();
        void move_downwards(float player_speed);
        void move_upwards(float factor = 1);
        void changeSpeed(GLfloat speed);
        void deflect_collision(float x_pos_factor, float y_pos_factor);
        CollisionInfo collidesWith(car* other);
        void toggleColorEffect();

        //Public variables:
        GLfloat right_top_corner[2];
        GLfloat left_top_corner[2];
        GLfloat left_bottom_corner[2];
        GLfloat right_bottom_corner[2];
        GLfloat x_pos;
        GLfloat previous_x_pos;
        GLfloat y_pos;
        GLfloat previous_y_pos;
        GLfloat car_speed;
        GLfloat car_rotation;
        car* collider;

    protected:

    private:
        GLuint texture;
        Texture_Flip texture_flip;
        Color_Effect color_effect;

        //Private functions:
        void update_car_position(float x_position, float y_position);
        void init_quad_corners_relative_to_window();
};

#endif // CAR_H
