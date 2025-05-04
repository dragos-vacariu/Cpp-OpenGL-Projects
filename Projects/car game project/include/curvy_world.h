#ifndef CURVY_WORLD_H
#define CURVY_WORLD_H

#include "../include/cross_functions.h"

//Constant defines
#define NUM_ROAD_LANES 6 // this is the number of road lanes according to the texture that is used

// Place these at the very top of your file, outside any class or function
#define CURVY_WORLD_SEGMENTS_HEIGHT 600 // Height of the quad
#define CURVY_WORLD_SEGMENTS_WIDTH 800 // Height of the quad
#define CURVY_ROAD_WIDTH 500
#define CURVY_FIELD_WIDTH 150
#define CURVY_ROAD_BASE_CENTER_X_POS CURVY_FIELD_WIDTH + (CURVY_ROAD_WIDTH / 2)

struct SegmentParams {
    float top_amplitude;
    float top_freq;
    float bottom_amplitude; // We'll use this, but it might be redundant based on your function's behavior
    float bottom_freq;      // We'll use this, but it might be redundant
};

using namespace std;

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
        static bool isObjectOffRoad(float coord_y, float object_right_x, float object_left_x);
        static bool getRoadMargins(float coord_y, float& road_left_margin_x, float& road_right_margin_x);
        static float getHighestSegment();


    private:
        //Private variables
        GLuint road_texture;
        GLuint world_texture;
        static vector <SimpleWorldSegment> simple_world_segments;
        GLfloat road_left_margin;
        GLfloat road_right_margin;

        //Private functions:
        SimpleWorldSegment gen_simple_curve(float start_y, float start_offset, float top_amplitude, float bottom_amplitude,
                                            float top_freq, float bottom_freq);

};

#endif // CURVY_WORLD_H

