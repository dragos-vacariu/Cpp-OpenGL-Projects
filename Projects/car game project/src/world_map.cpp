#include "world_map.h"

world_map::world_map()
{
    //ctor
    this->road_texture = load_texture(ROAD_TEXTURE);
    this->world_texture = load_texture(WORLD_TEXTURE);
    this->initializeWorldSegments();
    this->renderWorld();
}

world_map::~world_map()
{
    //dtor
}

void world_map::drawWorld(const float playerSpeed)
{
    // Initialize things before the loop

    updateWorld(playerSpeed);
    renderWorld(); // Draw the road/world segments
}

void world_map::initializeWorldSegments()
{
    for (int i = 0; i < NUM_ROAD_SEGMENTS; i++)
    {
        //Initialize Road
        this->roadSegments[i][0] = WORLD_SEGMENTS_WIDTH; // Keep x constant
        this->roadSegments[i][1] = i*ROAD_SEGMENTS_HEIGHT; //one on top of the other
    }

    for (int i = 0; i < NUM_WORLD_SEGMENTS; i++)
    {
        //Initialize world
        this->left_side_world[i][0] = 0.0f; // Keep x constant
        this->right_side_world[i][0] = WORLD_SEGMENTS_WIDTH + ROAD_SEGMENTS_WIDTH; // Keep x constant

        this->left_side_world[i][1] = i*WORLD_SEGMENTS_HEIGHT; //one on top of the other
        this->right_side_world[i][1] = i*WORLD_SEGMENTS_HEIGHT; //one on top of the other
    }
}

float world_map::getRoadLeftMargin()
{
    return WORLD_SEGMENTS_WIDTH;
}

float world_map::getRoadRightMargin()
{
    return WORLD_SEGMENTS_WIDTH + ROAD_SEGMENTS_WIDTH;
}

void world_map::updateWorld(const float playerSpeed)
{
    //Update the road
    for (int i = 0; i < NUM_ROAD_SEGMENTS; i++)
    {
        // Move the road segments based on player speed
        this->roadSegments[i][1] -= playerSpeed; // Move downwards

        // Check if the segment has moved off the screen (adjust depending on your screen size)
        if (this->roadSegments[i][1] + ROAD_SEGMENTS_HEIGHT < 0)
        {
            // Reposition segment on top of the highest segment.
            float maxRoadY = this->getHighestY(this->roadSegments, NUM_ROAD_SEGMENTS);
            this->roadSegments[i][1] = maxRoadY + ROAD_SEGMENTS_HEIGHT - playerSpeed;
        }
    }

    //Update the world
    for (int i = 0; i < NUM_WORLD_SEGMENTS; i++)
    {
        // Move the road segments based on player speed
        this->left_side_world[i][1] -= playerSpeed; // Move downwards
        this->right_side_world[i][1] -= playerSpeed; // Move downwards

        // Check if the segment has moved off the screen (adjust depending on your screen size)
        if (this->left_side_world[i][1] + WORLD_SEGMENTS_HEIGHT < 0)
        {
            // Reposition segment on top of the highest segment.
            float maxRoadY = this->getHighestY(this->left_side_world, NUM_WORLD_SEGMENTS);
            this->left_side_world[i][1] = maxRoadY + WORLD_SEGMENTS_HEIGHT - playerSpeed;

        }
        if (this->right_side_world[i][1] + WORLD_SEGMENTS_HEIGHT < 0)
        {
            // Reposition segment on top of the highest segment.
            float maxRoadY = this->getHighestY(this->right_side_world, NUM_WORLD_SEGMENTS);
            this->right_side_world[i][1] = maxRoadY + WORLD_SEGMENTS_HEIGHT - playerSpeed;
        }
    }
}

float world_map::getHighestY(const float (*segments)[2], int numSegments)
{
    /*This function will take a 2D array and find the element with the greatest Y coordinate*/

    float maxY = -FLT_MAX; /*initializing with the smallest possible negative floating point value*/
    for (int i = 0; i < numSegments; i++)
    {
        //Finding the element on top
        if (segments[i][1] > maxY)
        {
            maxY = segments[i][1];
        }
    }
    return maxY;
}

void world_map::renderWorld()
{
    glBindTexture(GL_TEXTURE_2D, road_texture); // Bind road texture

    for (int i = 0; i < NUM_ROAD_SEGMENTS; i++)
    {
        //Rendering the road
        float x = roadSegments[i][0];
        float y = roadSegments[i][1];

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(x + ROAD_SEGMENTS_WIDTH, y);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(x + ROAD_SEGMENTS_WIDTH, y + ROAD_SEGMENTS_HEIGHT);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + ROAD_SEGMENTS_HEIGHT);
        glEnd();
    }

    glBindTexture(GL_TEXTURE_2D, world_texture); // Bind world texture
    for (int i = 0; i < NUM_WORLD_SEGMENTS; i++)
    {
        //Rendering the left side world
        float x = left_side_world[i][0];
        float y = left_side_world[i][1];

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(x + WORLD_SEGMENTS_WIDTH, y);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(x + WORLD_SEGMENTS_WIDTH, y + WORLD_SEGMENTS_HEIGHT);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + WORLD_SEGMENTS_HEIGHT);
        glEnd();

        //Rendering the right side world
        x = right_side_world[i][0];
        y = right_side_world[i][1];

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(x + WORLD_SEGMENTS_WIDTH, y);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(x + WORLD_SEGMENTS_WIDTH, y + WORLD_SEGMENTS_HEIGHT);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + WORLD_SEGMENTS_HEIGHT);
        glEnd();
    }
}
