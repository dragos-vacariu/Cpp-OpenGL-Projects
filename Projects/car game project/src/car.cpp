#include "car.h"

using namespace std;

car::car(const char* texture_location, float x_position, float y_position, GLfloat speed,
         Texture_Flip texture_flipping)
{
    this->texture = load_texture(texture_location);
    this->car_speed = DEFAULT_CAR_SPEED;
    this->previous_x_pos = x_position;
    this->previous_y_pos = y_position;
    this->collider = nullptr;
    this->car_rotation = 0.0f;
    this->braking_factor = this->car_speed * BRAKING_FORCE;
    this->acceleration_factor = ACCELETATION_FORCE / this->car_speed;
    this->update_car_position(x_position, y_position);
    this->draw_car();
    this->texture_flip = texture_flipping;

    if(speed != DEFAULT_CAR_SPEED)
    {
        this->car_speed = speed;
    }
}

car::~car()
{
    //dtor
    if (this->texture != 0)
    {
        glDeleteTextures(1, &this->texture);
        this->texture = 0;
    }
}

void car::update_car_position(float x_position, float y_position)
{
    /*This function will update the car position and calculate the coordinates for the quad*/

    this->x_pos = x_position;
    this->y_pos = y_position;

    init_quad_corners_relative_to_window();
}

void car::toggleColorEffect()
{
    /*This function will initiate a color effect on the cars that collide*/

    if(this->color_effect.iterations_active <= 0)
    {
        this->color_effect.iterations_active = ITERATIONS_FOR_COLOR_EFFECT;
        this->color_effect.colored_iterations = COLORED_ITERATIONS_ON_COLOR_EFFECT;
        this->color_effect.regular_iterations = IDLE_ITERATIONS_ON_COLOR_EFFECT;
        this->color_effect.opacity_value = OPACITY_FOR_COLOR_EFFECT;
    }
}

void car::init_quad_corners_relative_to_window()
{
    /*This function will initialize the car quad corners used for drawing the vertices
    of the car quad. The positions taken under consideration will be relative to the window.

    By using this function upon calling glTranslatef() - the car position will be translated to window coordinate system
    which we already did manually, hence the object will be moved off the screen.
    ;
    */

    this->left_bottom_corner[0] = this->x_pos - CAR_WIDTH/2;
    this->left_bottom_corner[1] = this->y_pos - CAR_HEIGHT/2;

    this->right_bottom_corner[0] = this->x_pos + CAR_WIDTH/2;
    this->right_bottom_corner[1] = this->y_pos - CAR_HEIGHT/2;

    this->left_top_corner[0] = this->x_pos - CAR_WIDTH/2;
    this->left_top_corner[1] = this->y_pos + CAR_HEIGHT/2;

    this->right_top_corner[0] = this->x_pos + CAR_WIDTH/2;
    this->right_top_corner[1] = this->y_pos + CAR_HEIGHT/2;
}


void car::brake()
{
    /*This function will brake the player's car*/

    if(this->car_speed - this->braking_factor > MINIMUM_TRAVELLING_SPEED)
    {
        this->car_speed -= this->braking_factor;
        this->braking_factor = this->car_speed * BRAKING_FORCE;
        this->changeSpeed(this->car_speed);
    }
}

void car::accelerate()
{
    /*This function will accelerate the player's speed*/

    if(this->car_speed + this->acceleration_factor < MAXIMUM_TRAVELLING_SPEED)
    {
        this->car_speed += this->acceleration_factor;
        this->acceleration_factor = ACCELETATION_FORCE / this->car_speed;
        this->changeSpeed(this->car_speed);
    }
}

void car::slight_decceleration()
{
    /*This function will severely decelerate the player's speed*/

    if(this->car_speed - DECELERATION_FORCE > MINIMUM_TRAVELLING_SPEED)
    {
        this->car_speed -= DECELERATION_FORCE;
        this->changeSpeed(this->car_speed);
    }
}

void car::severe_decceleration()
{
    /*This function will decelerate the player's speed*/

    if(this->car_speed - DECELERATION_FORCE > MINIMUM_TRAVELLING_SPEED)
    {
        this->car_speed -= (DECELERATION_FORCE*3);
        this->changeSpeed(this->car_speed);
    }
}

CollisionInfo car::collidesWith(car* other)
{
    /*This function will check whether this car collides with another*/

    CollisionInfo collision_info = { false, 0.0f, 0.0f };

    //Getting the coordinates
    float thisLeft = this->left_bottom_corner[0];
    float thisRight = this->right_bottom_corner[0];
    float thisBottom = this->left_bottom_corner[1];
    float thisTop = this->left_top_corner[1];

    float otherLeft = other->left_bottom_corner[0];
    float otherRight = other->right_bottom_corner[0];
    float otherBottom = other->left_bottom_corner[1];
    float otherTop = other->left_top_corner[1];

    float overlapXLeft = thisRight - otherLeft;
    float overlapXRight = otherRight - thisLeft;
    float overlapYBottom = thisTop - otherBottom;
    float overlapYTop = otherTop - thisBottom;

    // Find the minimal overlap
    float minOverlapX = (overlapXLeft < overlapXRight) ? overlapXLeft : overlapXRight;
    float minOverlapY = (overlapYBottom < overlapYTop) ? overlapYBottom : overlapYTop;

    // Check for collision
    if (minOverlapX > 0 && minOverlapY > 0)
    {
        collision_info.isColliding = true;
        this->collider = other;
        other->collider = this;

        // Decide which side to push based on smaller overlap

        //the abs() function computes the absolute value of a number (returns a strictly positive value).
        if (abs(minOverlapX) < abs(minOverlapY))
        {
            // Horizontal collision
            collision_info.pushX = (overlapXLeft < overlapXRight) ? -minOverlapX : minOverlapX;
        }
        else
        {
            // Vertical collision
            collision_info.pushY = (overlapYBottom < overlapYTop) ? -minOverlapY : minOverlapY;
        }
    }
    else if(this->collider == other && other->collider == this)
    {
        /*Clear the collision - as the 2 objects no longer collide*/
        this->collider = nullptr;
        other->collider = nullptr;
    }

    return collision_info;
}

void car::deflect_collision(float x_pos_factor, float y_pos_factor)
{
    /*This function will be called when 2 elements collide and will push both to opposite direction
        according to the 2 parameters passed as arguments.
    */

    if(this->x_pos + x_pos_factor - CAR_WIDTH/2 > 50 &&
       this->x_pos + x_pos_factor + CAR_WIDTH/2 < WINDOW_WIDTH-50)
    {
        this->x_pos += x_pos_factor;
    }
    if( this->y_pos + y_pos_factor + CAR_HEIGHT/2 < WINDOW_HEIGHT &&
        this->y_pos + y_pos_factor - CAR_HEIGHT/2 > 0)
    {
        this->y_pos += y_pos_factor;
    }
    this->update_car_position(this->x_pos, this->y_pos);
}

void car::changeSpeed(GLfloat speed)
{
    /*This function will change the speed of the car*/

    this->car_speed = speed;
}

void car::turn(CAR_DIRECTION direction)
{
    /*This function will gradually turn the car on one direction*/

    // direction: -1 for left, +1 for right
    if(direction == CAR_DIRECTION::LEFT || direction == CAR_DIRECTION::RIGHT)
    {
        this->previous_x_pos = this->x_pos;
        this->previous_y_pos = this->y_pos;

        if(direction == CAR_DIRECTION::LEFT)
        {
            this->car_rotation += CAR_ROTATION_FACTOR;

            // Clamp
            if (this->car_rotation > 15.0f) //maximum rotation is 15 degrees
            {
                this->car_rotation = 15.0f;
            }

            // Convert rotation to radians
            float angle_rad = this->car_rotation * M_PI / 180.0f;

            // Update position based on rotation
            this->x_pos -= this->car_speed * cos(angle_rad) *0.2f;
        }
        else
        {
            this->car_rotation -= CAR_ROTATION_FACTOR;

            if (this->car_rotation < -15.0f) //maximum rotation is 15 degrees
            {
                this->car_rotation = -15.0f;
            }

            // Convert rotation to radians
            float angle_rad = this->car_rotation * M_PI / 180.0f;

            // Update position based on rotation
            this->x_pos += this->car_speed * cos(angle_rad) *0.2f;
        }

        this->update_car_position(this->x_pos, this->y_pos);
    }
}

void car::decrease_turn()
{
    /*This function will gradually reset the car rotation after turning*/

    if(this->car_rotation > 0.0f)
    {
        this->car_rotation -= CAR_ROTATION_FACTOR;
    }
    else if(this->car_rotation < 0.0f)
    {
        this->car_rotation += CAR_ROTATION_FACTOR;
    }
}

void car::restore_previous_position()
{
    /*This function will restore the previous position of the car - could be used for collision detection*/

    this->x_pos = this->previous_x_pos;
    this->y_pos = this->previous_y_pos;
    this->update_car_position(this->x_pos, this->y_pos );
}

void car::move_downwards(float speed)
{
    //This function will move the car downwards - used for the traffic_cars

    float road_margin_left;
    float road_margin_right;
    float y_pos = this->y_pos + this->car_speed - speed;

    bool margins_found = curvy_world::getRoadMargins(y_pos, road_margin_left, road_margin_right);
    if(margins_found)
    {
        float distance_from_margin_left = this->x_pos - road_margin_left;

        this->y_pos = y_pos;
        this->x_pos = road_margin_left + distance_from_margin_left;
        this->update_car_position(this->x_pos, this->y_pos);
    }


    /*
    this->previous_y_pos = this->y_pos;

    this->update_car_position(this->x_pos, this->y_pos);
    */
    this->draw_car();
}

void car::move_upwards(float factor)
{
    /*This function will move the car upwards - used for the player car when a collision pushed the player downwards*/

    this->previous_y_pos = this->y_pos;
    this->y_pos += this->car_speed * factor;
    this->update_car_position(this->x_pos, this->y_pos);
    this->draw_car();
}

void car::draw_car()
{
    //This function will draw and render the textured car quad
    glPushMatrix();

    //When you call glTranslatef(), you are essentially moving the coordinate
    //system origin to the position where you want to place your object.
    //This is like moving a cursor over the specified position
    glTranslatef(this->x_pos, this->y_pos, 0); //

    // Rotate around the center
    glRotatef(this->car_rotation, 0, 0, 1);

    glBindTexture(GL_TEXTURE_2D, this->texture);

    //Handle texture flipping via texture matrix
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();

    // Switch back to modelview matrix mode
    glMatrixMode(GL_MODELVIEW);


    // Save current color if needed
    GLfloat prevColor[4];
    if(this->color_effect.iterations_active > 0 && this->color_effect.colored_iterations > 0)
    {

        glGetFloatv(GL_CURRENT_COLOR, prevColor);

        glColor4f(this->color_effect.red_value, this->color_effect.green_value, this->color_effect.blue_value,
                  this->color_effect.opacity_value);
    }
    if(this->texture_flip == Texture_Flip::NORMAL)
    {
        //Drawing the quad

        /*
            the sequence in which you specify vertices in your glBegin(GL_QUADS) block affects the
            orientation of the polygon when rendered, which can influence face culling, normal
            direction, and winding order.
        */

        //The texture will be rendered as present in the image
        glBegin(GL_QUADS);

        /*Coordinates relative to the car object.
        Since we called glTranslatef() we are now at the position of the car
        */

        // bottom-left corner of the texture to be applied over...
        glTexCoord2f(0.0, 0.0);
        //with the commented approach when we rotate we are orbiting the origin
        //because the texture is not centered on the origin. This means we rotate the origin, but since there is some
        //margin between the texture and the actual position of the origin, it will be like a earth around the sun.
        //glVertex2f(0, 0);

        // bottom-left corner of the quad
        // this will ensure we rotate accurate because we are centered on the origin
        glVertex2f(-CAR_WIDTH/2, CAR_HEIGHT/2);

        // bottom-left right of the texture to be applied over...
        glTexCoord2f(1.0, 0.0);
        //with this approach when we rotate we are orbiting the origin because the texture is not centered on the origin
        //glVertex2f(CAR_WIDTH, 0);
        // bottom-right corner of the quad.
        // this will ensure we rotate accurate because we are centered on the origin
        glVertex2f(CAR_WIDTH/2, CAR_HEIGHT/2);

        // top-right corner of the texture to be applied over...
        glTexCoord2f(1.0, 1.0);
        // top-right corner of the quad.
        //glVertex2f(CAR_WIDTH, CAR_HEIGHT);
        glVertex2f(CAR_WIDTH/2, -CAR_HEIGHT/2);

        // top-right right of the texture to be applied over...
        glTexCoord2f(0.0, 1.0);
        // top-right corner of the quad.
        //glVertex2f(0, CAR_HEIGHT);
        glVertex2f(-CAR_WIDTH/2, -CAR_HEIGHT/2);

        glEnd();

        /*
        //This approach is not going to work after calling the glTranslatef, as now we are pointing over the
        //car_object, but we count again the car_object x_pos and y_pos meaning we create a x_pos and y_pos
        //margina between where the car_object is placed and where our texture/quad is going to be.

        glBegin(GL_QUADS);

            //the bottom-left corner
            glTexCoord2f(0.0, 0.0);
            glVertex2f(left_bottom_corner[0], left_bottom_corner[1]);

            //the bottom-right corner
            glTexCoord2f(1.0, 0.0);
            glVertex2f(right_bottom_corner[0], right_bottom_corner[1]);

            //the top-right corner.
            glTexCoord2f(1.0, 1.0);
            glVertex2f(right_top_corner[0], right_top_corner[1]);

            //the top-left corner.
            glTexCoord2f(0.0, 1.0);
            glVertex2f(left_top_corner[0], left_top_corner[1]);

        glEnd();
        */
    }
    else if(this->texture_flip == Texture_Flip::FLIP_VERTICALLY)
    {
        //The texture will be flipped horizontally
        //The texture will be rendered as present in the image
        glBegin(GL_QUADS);

        // bottom-left corner of the texture to be applied over...
        glTexCoord2f(0.0, 0.0);
        glVertex2f(-CAR_WIDTH/2, -CAR_HEIGHT/2);

        // bottom-left right of the texture to be applied over...
        glTexCoord2f(1.0, 0.0);
        glVertex2f(CAR_WIDTH/2, -CAR_HEIGHT/2);

        // top-right corner of the texture to be applied over...
        glTexCoord2f(1.0, 1.0);
        // top-right corner of the quad.
        glVertex2f(CAR_WIDTH/2, CAR_HEIGHT/2);

        // top-right right of the texture to be applied over...
        glTexCoord2f(0.0, 1.0);
        // top-right corner of the quad.
        glVertex2f(-CAR_WIDTH/2, CAR_HEIGHT/2);

        glEnd();
    }
    else if(this->texture_flip == Texture_Flip::FLIP_HORIZONTALLY)
    {
        //The texture will be flipped vertically

        //The texture will be rendered as present in the image
        glBegin(GL_QUADS);

        /*Coordinates relative to the car object.
        Since we called glTranslatef() we are now at the position of the car
        */

        // bottom-left corner of the texture to be applied over...
        glTexCoord2f(0.0, 0.0);
        glVertex2f(CAR_WIDTH/2, -CAR_HEIGHT/2);

        // bottom-left right of the texture to be applied over...
        glTexCoord2f(1.0, 0.0);
        glVertex2f(-CAR_WIDTH/2, -CAR_HEIGHT/2);

        // top-right corner of the texture to be applied over...
        glTexCoord2f(1.0, 1.0);
        glVertex2f(-CAR_WIDTH/2, CAR_HEIGHT/2);

        // top-right right of the texture to be applied over...
        glTexCoord2f(0.0, 1.0);
        glVertex2f(CAR_WIDTH/2, CAR_HEIGHT/2);

        glEnd();

        //using glScalef() is wrong, as it may flip other textures as well, if they were not properly Pushed and Popped
        //glScalef(1, -1, 1); // Flips along Y
    }
    if(this->color_effect.iterations_active > 0 && this->color_effect.colored_iterations > 0)
    {
        this->color_effect.iterations_active--;
        this->color_effect.colored_iterations--;
        if(this->color_effect.iterations_active > 0 && this->color_effect.colored_iterations <= 0)
        {
            this->color_effect.regular_iterations = IDLE_ITERATIONS_ON_COLOR_EFFECT;
        }
        glColor4fv(prevColor);
    }
    else if(this->color_effect.iterations_active && this->color_effect.regular_iterations > 0)
    {
        this->color_effect.iterations_active--;
        this->color_effect.regular_iterations--;

        if(this->color_effect.iterations_active > 0 && this->color_effect.regular_iterations <= 0)
        {
            this->color_effect.colored_iterations = COLORED_ITERATIONS_ON_COLOR_EFFECT;
        }
    }

    glPopMatrix();
    glPopMatrix();
}
