#include "../include/curvy_world.h"

// Definition of the static member variable
vector <SimpleWorldSegment> curvy_world::simple_world_segments;

curvy_world::curvy_world()
{
    this->road_texture = load_texture(ROAD_TEXTURE);
    this->world_texture = load_texture(WORLD_TEXTURE);
    this->road_left_margin = CURVY_FIELD_WIDTH;
    this->road_right_margin = CURVY_FIELD_WIDTH + CURVY_ROAD_WIDTH;

    float current_y = 0.0f; // Start at the bottom of the screen
    float current_offset = 0.0f; // Start with the road centered initially (assuming CURVY_FIELD_WIDTH is the center)

    //A sequence of curves and straights
    std::vector<SegmentParams> segmentSequence = {
        // Straight (amplitude = 0)
        { 0.0f, 0.0f, 0.0f, 0.0f },
        // Curve Right (positive top_amplitude)
        { 80.0f, 0.015f, 0.0f, 0.0f }, // Let's keep bottom params simple for continuity
        // Curve Left (negative top_amplitude)
        { -80.0f, 0.015f, 0.0f, 0.0f },
        // Straight
        { 0.0f, 0.0f, 0.0f, 0.0f },
        // Gentle Curve Right
        { 40.0f, 0.02f, 0.0f, 0.0f },
        // Gentle Curve Left
        { -40.0f, 0.02f, 0.0f, 0.0f },
        // Straight
        { 0.0f, 0.0f, 0.0f, 0.0f },
        // Sharper Curve Right
        { 100.0f, 0.01f, 0.0f, 0.0f },
        // Sharper Curve Left
        { -100.0f, 0.01f, 0.0f, 0.0f },
        // Sharpest Curve Right
        { 200.0f, 0.01f, 0.0f, 0.0f },
        // Sharper Curve Left
        { -200.0f, 0.01f, 0.0f, 0.0f },
        // Straight
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        //Continuous curve
        { -200.0f, 0.01f, 0.0f, 0.0f },
        { -100.0f, 0.01f, 0.0f, 0.0f },
        { -50.0f, 0.01f, 0.0f, 0.0f },
        { 0.0f, 0.01f, 0.0f, 0.0f },
        { 50.0f, 0.01f, 0.0f, 0.0f },
        { 100.0f, 0.01f, 0.0f, 0.0f },
        { 200.0f, 0.01f, 0.0f, 0.0f },

        //Continuous sharper curve
        { -150.0f, 0.01f, 0.0f, 0.0f },
        { -100.0f, 0.01f, 0.0f, 0.0f },
        { -50.0f, 0.01f, 0.0f, 0.0f },
        { 0.0f, 0.01f, 0.0f, 0.0f },
        { 50.0f, 0.01f, 0.0f, 0.0f },
        { 100.0f, 0.01f, 0.0f, 0.0f },
        { 150.0f, 0.01f, 0.0f, 0.0f },
        { 200.0f, 0.01f, 0.0f, 0.0f },
        { 150.0f, 0.01f, 0.0f, 0.0f },
        { 150.0f, 0.01f, 0.0f, 0.0f },
        { -200.0f, 0.01f, 0.0f, 0.0f },
        { -100.0f, 0.01f, 0.0f, 0.0f },
        { -50.0f, 0.01f, 0.0f, 0.0f },
        { 50.0f, 0.01f, 0.0f, 0.0f },
        { 50.0f, 0.01f, 0.0f, 0.0f },
        { 50.0f, 0.01f, 0.0f, 0.0f },
        { 0.0f, 0.01f, 0.0f, 0.0f },
        { -50.0f, 0.01f, 0.0f, 0.0f },
        { 20.0f, 0.01f, 0.0f, 0.0f },

        { 80.0f, 0.015f, 0.0f, 0.0f },
        { 20.0f, 0.015f, 0.0f, 0.0f },
        { 100.0f, 0.015f, 0.0f, 0.0f },
        { 20.0f, 0.015f, 0.0f, 0.0f },
        { -20.0f, 0.015f, 0.0f, 0.0f },
        // Straight
        { 0.0f, 0.0f, 0.0f, 0.0f },
    };

    int currentSegmentIndex = 0;

    for (int index = 0; index < segmentSequence.size() ; index++)
    {
        SegmentParams params = segmentSequence[currentSegmentIndex];

        //Generate the new segment using gen_simple_curve function()
        SimpleWorldSegment newSegment = this->gen_simple_curve(current_y, current_offset,
                                                               params.top_amplitude, params.top_freq,
                                                               params.bottom_amplitude, params.bottom_freq);

        //Add the new segment to your vector
        simple_world_segments.push_back(newSegment);

        //Update the starting point for the next segment to be the ending point of the current one
        current_y = newSegment.topY;
        current_offset = newSegment.topOffset;

        //Move to the next segment in the sequence, looping back to the beginning
        currentSegmentIndex = (currentSegmentIndex + 1) % segmentSequence.size();

        //Adding a check here to ensure the road stays within screen bounds.
        //The road's left edge at the top of the segment should be > 0
        //The road's right edge at the top of the segment should be < (2 * CURVY_FIELD_WIDTH + CURVY_ROAD_WIDTH)

        if (newSegment.roadLeftTop < 0 || newSegment.roadRightTop > (2 * CURVY_FIELD_WIDTH + CURVY_ROAD_WIDTH))
        {
            //Handle for out-of-bounds:
            //Print a warning:
            std::cerr << "Warning: Road segment generated out of bounds at segment " << index << "!" << std::endl;
            //Consider adjusting parameters for future segments to steer back.
            //This is more advanced procedural generation. For a simple loop,
            //you might need to adjust the amplitudes in your segmentSequence.
            //You might even decide to stop generating or mark the segment as invalid.
        }
    }
}

curvy_world::~curvy_world()
{
    //dtor
}

SimpleWorldSegment curvy_world::gen_simple_curve(float start_y, float start_offset,
                                                      float top_amplitude, float top_freq,
                                                      float bottom_amplitude, float bottom_freq)
{
    //This function will generated a road segment which can be curved, or straight

    SimpleWorldSegment segment;
    segment.bottomY = start_y;
    segment.bottomOffset = start_offset; //The bottom offset of the new segment is the top offset of the previous

    segment.topY = start_y + CURVY_WORLD_SEGMENTS_HEIGHT;

    //Calculate the top offset based on the sine function relative to the start offset
    //This is the key to continuity
    //We need the sine wave to start at 'start_offset' at 'start_y' and end at a new 'topOffset' at 'topY'
    //The sine function describes the 'change' in offset.
    //A simple way to think about this is the sine wave is centered around the current offset.

    segment.topOffset = start_offset + top_amplitude * sin(top_freq * CURVY_WORLD_SEGMENTS_HEIGHT);
    //Similarly for the bottom offset (which is already set)
    //segment.bottomOffset = start_offset + bottom_amplitude * sin(bottom_freq * 0); //This would be start_offset

    //ROAD POSITIONS (curved)
    segment.roadLeftTop = CURVY_FIELD_WIDTH + segment.topOffset;
    segment.roadRightTop = CURVY_FIELD_WIDTH + CURVY_ROAD_WIDTH + segment.topOffset;
    segment.roadLeftBottom = CURVY_FIELD_WIDTH + segment.bottomOffset;
    segment.roadRightBottom = CURVY_FIELD_WIDTH + CURVY_ROAD_WIDTH + segment.bottomOffset;

    return segment;
}

void curvy_world::drawWorld(float car_speed)
{
    for(unsigned int index=0; index < simple_world_segments.size(); index++)
    {
        simple_world_segments[index].bottomY-=car_speed;
        simple_world_segments[index].topY-=car_speed;

        renderWorld(car_speed, simple_world_segments[index]);

        if(simple_world_segments[index].topY < 0)
        {
            float maxY = getHighestSegment();
            simple_world_segments[index].topY = maxY - car_speed + CURVY_WORLD_SEGMENTS_HEIGHT;
            simple_world_segments[index].bottomY = maxY - car_speed;
        }
    }

}

float curvy_world::getHighestSegment()
{
    /*This function will take a 2D array and find the element with the greatest Y coordinate*/

    float maxY = -FLT_MAX; /*initializing with the smallest possible negative floating point value*/
    for (unsigned int i = 0; i < simple_world_segments.size(); i++)
    {
        //Finding the element on top
        if (simple_world_segments[i].topY > maxY)
        {
            maxY = simple_world_segments[i].topY;
        }
    }
    return maxY;
}

void curvy_world::renderWorld(float car_speed, SimpleWorldSegment segment)
{
    // LEFT FIELD (curved)
    glBindTexture(GL_TEXTURE_2D, this->world_texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0, segment.bottomY);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(segment.roadLeftBottom, segment.bottomY);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(segment.roadLeftTop, segment.topY);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0, segment.topY);
    glEnd();

    // ROAD
    glBindTexture(GL_TEXTURE_2D, this->road_texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(segment.roadLeftBottom, segment.bottomY);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(segment.roadRightBottom, segment.bottomY);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(segment.roadRightTop, segment.topY);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(segment.roadLeftTop, segment.topY);
    glEnd();

    // RIGHT FIELD (curved)
    glBindTexture(GL_TEXTURE_2D, this->world_texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(segment.roadRightBottom, segment.bottomY);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(800, segment.bottomY);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(800, segment.topY);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(segment.roadRightTop, segment.topY);
    glEnd();
}

bool curvy_world::isObjectOffRoad(float coord_y, float object_right_x, float object_left_x)
{
    float road_left_margin;
    float road_right_margin;

    // Get the road margins at the object's Y-coordinate
    if (getRoadMargins(coord_y, road_left_margin, road_right_margin) == false)
    {
        //If getRoadMargins failed (e.g., coord_y is outside the world),
        //we will consider the object off-road.
        return true;
    }

    //Check if the object is completely to the left of the road
    if (object_right_x <= road_left_margin)
    {
        return true; //Object is off-road to the left
    }

    //Check if the object is completely to the right of the road
    if (object_left_x >= road_right_margin)
    {
        return true; //Object is off-road to the right
    }

    //If neither of the above conditions is met, the object is at least partially on the road
    return false;
}


bool curvy_world::getRoadMargins(float coord_y, float& road_left_margin_x, float& road_right_margin_x)
{
    int segment_index = -1;

    //Find the segment that contains the given coord_y
    for (unsigned int i = 0; i < simple_world_segments.size(); i++)
    {
        //Check if coord_y is within the current segment's Y range (inclusive of bottom, exclusive of top)
        if (coord_y >= simple_world_segments[i].bottomY && coord_y < simple_world_segments[i].topY)
        {
            segment_index = i;
            break; //Found the segment, no need to check further
        }
    }

    //If no segment is found (coord_y is outside the world's Y range), return false
    if (segment_index == -1)
    {
        //You might want to handle this case, perhaps by returning default margins or an error
        return false;
    }

    const SimpleWorldSegment& segment = simple_world_segments[segment_index];

    // Calculate the position of coord_y within the segment (0.0 at bottom, 1.0 at top)
    float segment_y_range = segment.topY - segment.bottomY;

    if (segment_y_range <= 0) //Avoid division by zero or negative range
    {
        //Should not happen with correctly generated segments, but good for robustness
        return false;
    }

    //blending_factor is a variable used for linear interpolation. It represents the normalized position of
    //coord_y within the vertical range of the current segment.
    //The result, blending_factor, will be a value between 0.0 and 1.0 (inclusive, assuming coord_y
    //is within the segment's range)
    float  blending_factor = (coord_y - segment.bottomY) / segment_y_range;

    //blending_factor is the key to performing linear interpolation. In this context, the road's left and right edges
    //are defined by their X-coordinates at the bottom (segment.roadLeftBottom, segment.roadRightBottom)
    //and at the top (segment.roadLeftTop, segment.roadRightTop) of the segment.

    //Interpolate the road's left and right margins based on t
    //Linear interpolation: value = (1 - t) * start_value + t * end_value
    road_left_margin_x = (1.0f - blending_factor) * segment.roadLeftBottom + blending_factor * segment.roadLeftTop;
    road_right_margin_x = (1.0f - blending_factor) * segment.roadRightBottom + blending_factor * segment.roadRightTop;

    //FORMULA: interpolated_value = (1 - blending_factor) * start_value + blending_factor * end_value;

    //Successfully found the segment and calculated margins
    return true;
}
