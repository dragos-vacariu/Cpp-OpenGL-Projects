#ifndef CURVY_WORLD_H
#define CURVY_WORLD_H

#include "../include/cross_functions.h"

//Constant defines
#define NUM_CURVY_WORLD_SEGMENTS 10

// Place these at the very top of your file, outside any class or function
#define CURVY_WORLD_SEGMENTS_HEIGHT 600 // Height of the quad
#define CURVY_WORLD_SEGMENTS_WIDTH 800 // Height of the quad
#define CURVY_ROAD_WIDTH 400
#define CURVY_FIELD_WIDTH 200
#define CURVY_ROAD_BASE_CENTER_X_POS CURVY_FIELD_WIDTH + (CURVY_ROAD_WIDTH / 2)

//the higher the SCANLINE_PIXEL_HEIGHT, the "worse" (meaning less detailed and more blocky) the graphics will appear.
#define SCANLINE_PIXEL_HEIGHT 1 // RECOMMENDED 1px per scanline

using namespace std;

struct WorldSegment
{
    int height;                  // number of scan lines
    int baseXOffset;              //this as the starting X position for a whole segment’s movement
    int y_pos;              //this as the starting X position for a whole segment’s movement
    std::vector<float> delta_x_pos;          // precomputed per line curve

    //Constructors
    WorldSegment()
    {
        //Default Constructor is MANDATORY
    }
    WorldSegment(int segment_height, int pos_y, float amplitude, float frequency, float phase)
      : height(segment_height),           // initialize the height of the world segment
        baseXOffset(0),                 // initialize baseXOffset which is the starting position on the X-Axis.
        y_pos(pos_y),                 // initialize baseYOffset which is the starting position on the Y-Axis.
        delta_x_pos(segment_height)       // initialize delta_x_pos to have segment_height elements as
        //we will have 1 scan line for each pixel within the height
    {
        /*

        amplitude = how big the shift can get
        frequency = how many curves fit in your visible height
        phase = how far down the “rope” (wave) you’ve already traveled

        higher amplitude -> wider, more dramatic turns; lower amplitude -> gentle bends.

        high frequency -> many small ripples (tight, quick curves); low frequency -> long, sweeping bends.

        phase -> shifts the entire wave left or right along the Y axis—i.e. it picks which part of the repeating
        sine pattern you’re currently showing at the top of the screen.

        */

        for (int index = 0; index < segment_height; index++)
        {
            // Calculate the vertical position within the *total pixel height* of the segment
            // This is what determines the position on the sine wave.
            float vertical_pixel_position = static_cast<float>(index) * SCANLINE_PIXEL_HEIGHT;

            /*Because the sine function returns values in the range -1 : +1 multiplying by amplitude gives you a
            range of offsets in -amplitude + amplitude.*/

            // Use the vertical_pixel_position in the sine function
            this->delta_x_pos[index] = amplitude * sin(frequency * vertical_pixel_position + phase);

            /*
            This is the shape of your curve within one segment. It tells you, at logical scan line index
            (from 0 to segment_logical_height-1), how far to wiggle left (negative) or right (positive)
            relative to that segment’s baseOffset.
            */
        }
    }
};

struct SimpleWorldSegment
{
    float topY;
    float bottomY;

    // Get X-offsets from sine curve
    float topOffset;
    float bottomOffset;

    // ROAD POSITIONS (curved)
    float roadLeftTop;
    float roadRightTop;
    float roadLeftBottom;
    float roadRightBottom;
};

class curvy_world
{
    public:
        // Constructor
        curvy_world();

        //Destructor
        virtual ~curvy_world();

        // Public functions:
        void drawWorld(float car_speed);
        void renderWorld(float car_speed, SimpleWorldSegment segment);
        static bool isObjectOffRoad(float coord_y, float left_margin_x, float right_margin_x);
        static bool getRoadMargins(float coord_y, float& left_margin_x, float& right_margin_x);


    private:
        //Private variables
        GLuint road_texture;
        GLuint world_texture;
        static WorldSegment world_segments[NUM_CURVY_WORLD_SEGMENTS];
        SimpleWorldSegment simple_world_segments[NUM_CURVY_WORLD_SEGMENTS];
        GLfloat road_left_margin;
        GLfloat road_right_margin;

        //Private functions:
        void update_phase(float car_speed, float frequency);
        void draw_world_scanline(int scanline_index, int segment_index);
        WorldSegment gen_curve_left(int y_position);
        SimpleWorldSegment gen_simple_curve(float y_pos);

};

#endif // CURVY_WORLD_H

