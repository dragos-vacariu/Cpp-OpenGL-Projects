#ifndef WORLD_MAP_H
#define WORLD_MAP_H

//Built-in includes:
#include <glew.h>

#include "../include/cross_functions.h"

//Constant defines
#define NUM_ROAD_SEGMENTS 3
#define NUM_WORLD_SEGMENTS 10

// Place these at the very top of your file, outside any class or function
#define WORLD_SEGMENTS_WIDTH 200
#define WORLD_SEGMENTS_HEIGHT 200 // Height of the quad
#define ROAD_SEGMENTS_HEIGHT 800
#define ROAD_SEGMENTS_WIDTH 200

class world_map
{
    public:
        world_map();
        virtual ~world_map();

        //Public functions:
        void drawWorld(const float playerSpeed);
        static float getRoadLeftMargin();
        static float getRoadRightMargin();

        //Public variables
        float roadSegments[NUM_ROAD_SEGMENTS][2]; // x, y positions for each segment

    protected:

    private:
        //Private functions:
        void renderWorld();
        void updateWorld(const float playerSpeed);
        void initializeWorldSegments();
        float getHighestY(const float (*segments)[2], int numSegments);

        /*Private variables*/
        GLuint road_texture;
        float left_side_world[NUM_WORLD_SEGMENTS][2];
        float right_side_world[NUM_WORLD_SEGMENTS][2];

        GLuint world_texture;
};

#endif // ROAD_H
