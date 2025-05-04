#ifndef CAR_H
#define CAR_H

//Cross-functions inclusion:
#include "../include/cross_functions.h"
#include "../include/world_map.h"
#include "../include/curvy_world.h"

//Constant defines
#define CAR_WIDTH 40 //Car object width in pixels
#define CAR_HEIGHT 100 //Car object height in pixels
#define CAR_TURNING_FACTOR 0.2f //A factor used to determine how much to steer/turn the car on a single loop iteration
#define CAR_ROTATION_FACTOR 2.0f //A factor used to determine how much to rotate the car on a single loop iteration
#define DEFAULT_CAR_SPEED 5.0f //A default value used to determine the car speed when building a car object
#define ITERATIONS_FOR_COLOR_EFFECT 100 //time (in loop iterations) in which the color effect will take place
#define COLORED_ITERATIONS_ON_COLOR_EFFECT 15 //time (in loop iterations) in which the color effect is VISIBLE.
#define IDLE_ITERATIONS_ON_COLOR_EFFECT 20 //time (in loop iterations) in which the color effect is NOT visible.
#define OPACITY_FOR_COLOR_EFFECT 0.4f //opacity for the color effects applied

#define MINIMUM_TRAVELLING_SPEED 2.0f //the minimum speed with which the car is allowed to travel
#define MAXIMUM_TRAVELLING_SPEED 15.0f //the maximum speed with which the car is allowed to travel
#define BRAKING_FORCE 0.02f  //a factor used to calculate a value for decrease the speed/brake based on the current car speed
#define DECELERATION_FORCE 0.005f  //a factor used to calculate a value for decrease the speed based on the current car speed
#define ACCELETATION_FORCE 2.0f //a factor used to calculate a value for increasing the speed based on the current car speed
#define MINIMUM_BRAKING_VALUE 0.1f //determines the minimum braking value (used at high speeds)
#define MINIMUM_ACCELERATION_VALUE 0.1f //determines the minimum acceleration value (used at high speeds)
#define MAXIMUM_STEERING_ADJUSTMENT 5.0f //determines the maximum value of the steering
#define LOOK_AHEAD_DISTANCE 50.0f // determines the distance to which the cars will see ahead to prepare for steering

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
        car(const char* texture_location, float x_position, float y_position, int road_lane_index ,
            GLfloat speed = DEFAULT_CAR_SPEED, Texture_Flip texture_flipping = Texture_Flip::NORMAL);
        virtual ~car();

        //Public functions:
        void draw_car();
        void turn(CAR_DIRECTION direction);
        void decrease_turn();
        void restore_previous_position();
        void move_downwards(float speed);
        void move_upwards(float factor = 1);
        void changeSpeed(GLfloat speed);
        void deflect_collision(float x_pos_factor, float y_pos_factor);
        CollisionInfo collidesWith(car* other);
        void toggleColorEffect();
        void brake();
        void accelerate();
        void slight_decceleration();
        void severe_decceleration();

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
        GLfloat braking_factor;
        GLfloat acceleration_factor;
        GLfloat steering_factor;
        int target_lane_index;
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
