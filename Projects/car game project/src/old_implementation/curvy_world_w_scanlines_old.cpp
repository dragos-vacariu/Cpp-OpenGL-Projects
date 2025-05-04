#include "../include/curvy_world.h"

// Definition of the static member variable
WorldSegment curvy_world::world_segments[NUM_CURVY_WORLD_SEGMENTS];

curvy_world::curvy_world()
{
    this->road_texture = load_texture(ROAD_TEXTURE);
    this->world_texture = load_texture(WORLD_TEXTURE);
    this->road_left_margin = CURVY_FIELD_WIDTH;
    this->road_right_margin = CURVY_FIELD_WIDTH + CURVY_ROAD_WIDTH;

    this->simple_world_segments[0] = this->gen_simple_curve(0);
    this->simple_world_segments[1] = this->gen_simple_curve(CURVY_WORLD_SEGMENTS_HEIGHT);
    this->simple_world_segments[2] = this->gen_simple_curve(CURVY_WORLD_SEGMENTS_HEIGHT*2);
}

curvy_world::~curvy_world()
{
    //dtor
}

WorldSegment curvy_world::gen_curve_left(int y_position)
{
    return {CURVY_WORLD_SEGMENTS_HEIGHT, y_position, 0.0f, 0.001f, 0.0f};
}

//IDEA:

SimpleWorldSegment curvy_world::gen_simple_curve(float y_pos)
{
    SimpleWorldSegment segment;
    segment.topY = y_pos + CURVY_WORLD_SEGMENTS_HEIGHT;
    segment.bottomY = y_pos;

    // Get X-offsets from sine curve
    segment.topOffset = 100 * sin(0.1f * CURVY_WORLD_SEGMENTS_HEIGHT);
    segment.bottomOffset = 400 * sin(1 * 0);

    // ROAD POSITIONS (curved)
    segment.roadLeftTop = 200 + segment.topOffset;
    segment.roadRightTop = 600 + segment.topOffset;
    segment.roadLeftBottom = 200 + segment.bottomOffset;
    segment.roadRightBottom = 600 + segment.bottomOffset;

    return segment;
}

void curvy_world::drawWorld(float car_speed)
{
    for(unsigned int index=0; index < NUM_CURVY_WORLD_SEGMENTS; index++)
    {
        this->simple_world_segments[index].bottomY-=car_speed;
        this->simple_world_segments[index].topY-=car_speed;

        this->renderWorld(car_speed, this->simple_world_segments[index]);

        if(this->simple_world_segments[index].topY < 0)
        {

            this->simple_world_segments[index] = this->gen_simple_curve(CURVY_WORLD_SEGMENTS_HEIGHT*2+car_speed);
        }
    }

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

bool curvy_world::isObjectOffRoad(float coord_y, float left_margin_x, float right_margin_x)
{
    //Finding the segment that this coord_y belongs to
    for (const auto& segment : world_segments)
    {
        float segment_bottom_y = static_cast<float>(segment.y_pos);

        float segment_top_y = static_cast<float>(segment.y_pos) + static_cast<float>(segment.height) *
                                SCANLINE_PIXEL_HEIGHT;

        //Checking if the coord_y falls within this segment's vertical range
        if (coord_y >= segment_bottom_y && coord_y < segment_top_y)
        {

            //Calculating the vertical position within the segment (in world units)
            float y_in_segment = coord_y - static_cast<float>(segment.y_pos);

            //Converting the vertical position within the segment to a scanline index within the segment
            //Using floor to handle potential floating point inaccuracies and ensure we get a valid index
            int segment_scanline_index = static_cast<int>(floor(y_in_segment / SCANLINE_PIXEL_HEIGHT));

            //Add a boundary check just in case (shouldn't be needed if the logic is correct,
            //but it's good practice)
            if (segment_scanline_index < 0 || segment_scanline_index >= segment.height)
            {
                //This shouldn't happen if the coord_y was correctly identified within the segment
                return false; //Indicate an error or out of bounds
            }

            //Get the horizontal offset for this specific scanline from the segment's precomputed data
            float curve_offset_x = segment.delta_x_pos[segment_scanline_index];

            //Calculate the center of the road at this scanline
            //This is the base road center plus the curve offset
            float road_center_x = CURVY_ROAD_BASE_CENTER_X_POS + curve_offset_x;

            // Calculate the left and right margin positions based on the road center and fixed width
            float out_left_margin_x = road_center_x - (CURVY_ROAD_WIDTH / 2.0f);
            float out_right_margin_x = road_center_x + (CURVY_ROAD_WIDTH / 2.0f);

            if(left_margin_x > out_left_margin_x && right_margin_x < out_right_margin_x)
            {
                /*The coordinate is on the road*/
                return false;
            }
            else
            {
                /*The coordinate is off the road*/
                 return true; // Successfully found and returned the margin positions
            }

        }
    }
    // If the loop finishes without finding a segment, the coord_y is outside the world bounds
    return false; // Indicate out of bounds
}

bool curvy_world::getRoadMargins(float coord_y, float& left_margin_x, float& right_margin_x)
{
    for (const auto& segment : world_segments)
    {
        float segment_bottom_y = static_cast<float>(segment.y_pos);
        float segment_top_y = static_cast<float>(segment.y_pos) + static_cast<float>(segment.height) * SCANLINE_PIXEL_HEIGHT;

        if (coord_y >= segment_bottom_y && coord_y < segment_top_y)
        {
            float y_in_segment = coord_y - segment_bottom_y;

            // Calculate the exact floating-point scanline index
            float exact_scanline_index = y_in_segment / SCANLINE_PIXEL_HEIGHT;

            // Get indices of the two nearest scanlines
            int index1 = static_cast<int>(floor(exact_scanline_index));
            int index2 = static_cast<int>(ceil(exact_scanline_index));

            float interpolated_curve_offset_x;

            // Handle edge cases (at the top of a scanline or the end of the segment)
            if (index1 == index2 || index2 >= (int)segment.delta_x_pos.size())
            {
                // No interpolation needed, or at the end of the segment
                // interpolate means to estimate a value that lies between two known values.
                if (index1 < (int)segment.delta_x_pos.size())
                {
                    interpolated_curve_offset_x = segment.delta_x_pos[index1];
                }
                else
                {
                    // Should ideally not happen if coord_y is within segment_top_y,
                    // but as a safeguard, use the last valid offset.
                    interpolated_curve_offset_x = segment.delta_x_pos.back();
                }
            }
            else
            {
                // Interpolate between the two nearest scanlines
                float offset1 = segment.delta_x_pos[index1];
                float offset2 = segment.delta_x_pos[index2];
                float t = exact_scanline_index - index1; // Interpolation factor

                interpolated_curve_offset_x = offset1 + t * (offset2 - offset1);
            }

            float road_center_x = CURVY_ROAD_BASE_CENTER_X_POS + interpolated_curve_offset_x;

            left_margin_x = road_center_x - (CURVY_ROAD_WIDTH / 2.0f);
            right_margin_x = road_center_x + (CURVY_ROAD_WIDTH / 2.0f);

            return true;
        }
    }
    return false; // coord_y is not within any segment
}


//OLD IMPLEMENTATIONS

/*
curvy_world::curvy_world()
{
    this->road_texture = load_texture(ROAD_TEXTURE);
    this->world_texture = load_texture(WORLD_TEXTURE);
    this->road_left_margin = CURVY_FIELD_WIDTH;
    this->road_right_margin = CURVY_FIELD_WIDTH + CURVY_ROAD_WIDTH;

    for(int index=0; index < NUM_CURVY_WORLD_SEGMENTS; index++)
    {
        world_segments[index] = this->gen_curve_left(index*CURVY_WORLD_SEGMENTS_HEIGHT);
    }
}
*/


/*
void curvy_world::drawWorld(float car_speed)
{
    //HANDLE THE SCROLLING OF WORLD SEGMENTS:
    for(int segment_index = 0; segment_index < NUM_CURVY_WORLD_SEGMENTS; segment_index++)
    {
        this->world_segments[segment_index].y_pos -= car_speed; // Scrolling

        // LOGIC BEHIND:
        // If a WORLD SEGMENT is entirely below the bottom of the window, move it to the top
        // A segment is entirely below if its top edge (last scan line) is below Y=0
        // As my Y=0 is the bottom of the screen as set via glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -100, 100);

        //The reason for using static_cast<> is to explicitly convert integer or other numeric types
        float world_height_float = static_cast<float>(this->world_segments[segment_index].height);

        float segment_top_y = this->world_segments[segment_index].y_pos + world_height_float * SCANLINE_PIXEL_HEIGHT;


        //IF THE SEGMENT IF OFF THE SCREEN
        if (segment_top_y < 0)
        {

            //The following line is used to initialize a variable max_y to a value that is guaranteed to be
            //smaller than any
            //finite floating-point number. This is a common technique when you want to find the maximum value
            //within a set of numbers.
            float max_y = -std::numeric_limits<float>::infinity(); //This line initializes max_y to negative infinity.
            //-infinity  ...  -100  ...  -1  ...  0  ...  1  ...  100  ...  +infinity

            //FINDING THE HIGHEST SEGMENT IN THE WORLD:
            for (int i = 0; i < NUM_CURVY_WORLD_SEGMENTS; i++)
            {
                world_height_float = static_cast<float>(this->world_segments[i].height);

                float current_segment_top_y = this->world_segments[i].y_pos + world_height_float * SCANLINE_PIXEL_HEIGHT;

                //THIS CONDITION WILL ALWAYS BE TRUE:
                if (current_segment_top_y > max_y)
                {
                    max_y = current_segment_top_y;
                }
            }

            // Position the wrapped segment immediately above the current top segment
            this->world_segments[segment_index].y_pos = max_y;

        }
    }

    //DRAW THE WORLD SEGMENTS:
    for(int segment_index = 0; segment_index < NUM_CURVY_WORLD_SEGMENTS; segment_index++)
    {
        const WorldSegment& segment = this->world_segments[segment_index];

        //Only draw if the segment is at least partially visible
        float segment_bottom_y = segment.y_pos;
        float segment_height_float = static_cast<float>(segment.height);

        float segment_top_y = segment.y_pos + segment_height_float * SCANLINE_PIXEL_HEIGHT;

        //IF THE SEGMENT IS NOT VISIBLE ON THE SCREEN - WE WILL IGNORE THE STATEMENTS BELOW THE IF
        if (segment_top_y < 0 || segment_bottom_y > WINDOW_HEIGHT)
        {
            continue; // Segment is completely off-screen
        }

        // Draw each scanline of the visible portion of the segment
        // We need to figure out which scanlines are actually visible.

        // Calculate the first visible scanline index
        // A scanline 'i' starts at segment.y_pos + i * SCANLINE_PIXEL_HEIGHT
        // We want the smallest 'i' such that segment.y_pos + i * SCANLINE_PIXEL_HEIGHT < WINDOW_HEIGHT
        // and segment.y_pos + (i+1) * SCANLINE_PIXEL_HEIGHT > 0
        // The first visible scanline starts at or above Y=0.
        // CONDITION: segment.y_pos + first_visible_index * SCANLINE_PIXEL_HEIGHT >= 0


        //The usual screen coordinate system puts position Y = 0 at the top and the Y position increases
        //while we travel downwards. But my coordinate system set via glOrtho() put position Y=0 at the very bottom
        //of the window, so the world's Y-axis increases as they go upwards.

        //By negating the world Y position to align it with the screen's vertical direction.
        //A higher segment.y_pos (further up in the world) will result in a smaller -segment.y_pos
        //(closer to the top of the screen in screen space).


        int negated_y_pos = static_cast<int>( std::ceil( 0 - segment.y_pos / SCANLINE_PIXEL_HEIGHT) );
        int first_visible_scanline = std::max(0, negated_y_pos);

        // Calculating the last visible scanline index
        // A scanline 'i' ends at segment.y_pos + (i+1) * SCANLINE_PIXEL_HEIGHT
        // We want the largest 'i' such that segment.y_pos + i * SCANLINE_PIXEL_HEIGHT < WINDOW_HEIGHT
        // and segment.y_pos + (i+1) * SCANLINE_PIXEL_HEIGHT > 0
        // The last visible scanline ends at or below WINDOW_HEIGHT.

        float segment_y_pos_relative_to_screen = std::floor((static_cast<float>(WINDOW_HEIGHT) - segment.y_pos));

        int line_index = static_cast<int>(segment_y_pos_relative_to_screen / SCANLINE_PIXEL_HEIGHT - 1.0f);

        int last_visible_scanline = std::min(segment.height-1, line_index);


        // Iterate only through the visible scanlines
        for(int scanline_index = first_visible_scanline; scanline_index <= last_visible_scanline; scanline_index++)
        {
            // Calculate the horizontal offset for this scanline based on delta_x_pos

            // The scanlines are stored in delta_x_pos ranging from (0 to height-1)

            // The road_left_margin/right_margin are member variables
            // and we update them per scanline, but pre-calculating in the segment struct is better.

            // Call the drawing function for this scanline
            draw_world_scanline(scanline_index, segment_index);
        }
    }
}*/

/*
void curvy_world::draw_world_scanline(int scanline_index, int segment_index)
{
    // Get the current segment
    const WorldSegment& segment = this->world_segments[segment_index];

    // Calculate the actual vertical position of this scanline in window coordinates
    // Y=0 is at the bottom
    float window_y_bottom = static_cast<float>(segment.y_pos) + static_cast<float>(scanline_index) * SCANLINE_PIXEL_HEIGHT;
    float window_y_top    = static_cast<float>(segment.y_pos) + static_cast<float>(scanline_index + 1) * SCANLINE_PIXEL_HEIGHT; // Assuming SCANLINE_PIXEL_HEIGHT is 1

    // Clip drawing to the window's bounds (0 to WINDOW_HEIGHT)
    if (window_y_top < 0 || window_y_bottom > WINDOW_HEIGHT)
    {
        return; // Scanline is completely off-screen
    }

    // Calculate the actual drawing range within the window (handle partial visibility)
    float draw_y_bottom = std::max(0.0f, window_y_bottom);
    float draw_y_top = std::min(static_cast<float>(WINDOW_HEIGHT), window_y_top);

    // Calculate the per-scanline horizontal offset (already done in drawWorld, but re-calculating for clarity here)
    // Note: It's more efficient to calculate road_left_margin and road_right_margin once per scanline in drawWorld
    // and pass them or use member variables, but doing it here matches your original structure.
    float offset = segment.baseXOffset + segment.delta_x_pos[scanline_index];
    float current_road_left_margin = CURVY_FIELD_WIDTH + offset;
    float current_road_right_margin = CURVY_FIELD_WIDTH + CURVY_ROAD_WIDTH + offset;

    // Calculate texture coordinates for the visible portion of this scanline
    // The vertical texture coordinates should map the scanline's position within the segment's height (0.0 to 1.0)
    // The texture coordinates need to be adjusted if the scanline is partially clipped at the top or bottom of the window.

    // Calculate the vertical position of the current scanline within the world_segment's original height
    float scanline_segment_y = static_cast<float>(scanline_index) * SCANLINE_PIXEL_HEIGHT; // Position from bottom of segment

    // Calculate the proportion of the original scanline that is clipped at the bottom and top IN WINDOW PIXELS
    // This is the amount of clipping relative to the full height of the scanline in window coordinates (SCANLINE_PIXEL_HEIGHT)
    float bottom_clip_amount_window = std::max(0.0f, 0.0f - window_y_bottom);
    float top_clip_amount_window = std::max(0.0f, window_y_top - static_cast<float>(WINDOW_HEIGHT));

    // Calculate the vertical texture coordinates (0.0 to 1.0) for the segment's full height
    // 0.0 corresponds to the bottom of the segment, 1.0 to the top.
    float tex_segment_bottom = scanline_segment_y / (static_cast<float>(segment.height) * SCANLINE_PIXEL_HEIGHT);
    float tex_segment_top = (scanline_segment_y + SCANLINE_PIXEL_HEIGHT) / (static_cast<float>(segment.height) * SCANLINE_PIXEL_HEIGHT);

    // Adjust texture coordinates based on clipping
    // We need to find what proportion of the texture corresponds to the visible part of the scanline.
    // The visible height of the scanline is SCANLINE_PIXEL_HEIGHT - bottom_clip_amount_window - top_clip_amount_window.
    // The texture range for the full scanline is tex_segment_top - tex_segment_bottom.
    // The clipped texture range starts from tex_segment_bottom + (proportion of bottom clip) * (full texture range for scanline)
    // The proportion of bottom clip is bottom_clip_amount_window / SCANLINE_PIXEL_HEIGHT.
    // The proportion of top clip is top_clip_amount_window / SCANLINE_PIXEL_HEIGHT.

    float tex_range_for_scanline = tex_segment_top - tex_segment_bottom;

    float tBottom = tex_segment_bottom + (bottom_clip_amount_window / SCANLINE_PIXEL_HEIGHT) * tex_range_for_scanline;
    float tTop = tex_segment_top - (top_clip_amount_window / SCANLINE_PIXEL_HEIGHT) * tex_range_for_scanline;

    // Clamp texture coordinates to the 0.0 to 1.0 range just in case of floating point inaccuracies near edges
    tBottom = std::max(0.0f, std::min(1.0f, tBottom));
    tTop = std::max(0.0f, std::min(1.0f, tTop));


    // Draw the road quad
    glBindTexture(GL_TEXTURE_2D, this->road_texture);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    // Horizontal texture coordinates (s) typically go from 0.0 to 1.0 across the road width
    glTexCoord2f(0.0f, tBottom); glVertex2f(current_road_left_margin, draw_y_bottom);
    glTexCoord2f(1.0f, tBottom); glVertex2f(current_road_right_margin, draw_y_bottom);
    glTexCoord2f(1.0f, tTop);    glVertex2f(current_road_right_margin, draw_y_top);
    glTexCoord2f(0.0f, tTop);    glVertex2f(current_road_left_margin, draw_y_top);
    glEnd();

    // Draw the left and right fields similarly
    // The vertical texture coordinates for the fields are the same as the road's vertical texture coordinates (tBottom, tTop)
    // assuming the world texture maps vertically in the same way over the segment height.
    float vBottom = tBottom;
    float vTop = tTop;

    // Left field
    glBindTexture(GL_TEXTURE_2D, this->world_texture);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    // Horizontal texture coordinates (s) for the left field go from 0.0 (left edge of window) to 1.0 (left edge of road)
    glTexCoord2f(0.0f, vBottom); glVertex2f(0, draw_y_bottom);
    glTexCoord2f(1.0f, vBottom); glVertex2f(current_road_left_margin, draw_y_bottom);
    glTexCoord2f(1.0f, vTop);    glVertex2f(current_road_left_margin, draw_y_top);
    glTexCoord2f(0.0f, vTop);    glVertex2f(0, draw_y_top);
    glEnd();

    // Right field
    glBindTexture(GL_TEXTURE_2D, this->world_texture);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    // Horizontal texture coordinates (s) for the right field go from 0.0 (right edge of road) to 1.0 (right edge of window)
    glTexCoord2f(0.0f, vBottom); glVertex2f(current_road_right_margin, draw_y_bottom);
    glTexCoord2f(1.0f, vBottom); glVertex2f(WINDOW_WIDTH, draw_y_bottom);
    glTexCoord2f(1.0f, vTop);    glVertex2f(WINDOW_WIDTH, draw_y_top);
    glTexCoord2f(0.0f, vTop);    glVertex2f(current_road_right_margin, draw_y_top);
    glEnd();
}
*/
