#include "../include/traffic_spawner.h"

traffic_spawner::traffic_spawner()
{
    //ctor
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car2.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car3.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car4.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car5.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car6.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car7.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car8.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car9.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car10.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car11.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car12.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car13.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car14.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car15.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car16.png");
    this->car_textures.push_back(string(IMG_RESOURCES) + "/" + "car17.png");

    this->generate_traffic_car();
}

traffic_spawner::~traffic_spawner()
{
    //dtor
}

void traffic_spawner::generate_traffic_car()
{
    /*This function will generate a traffic car*/

    float right_road_margin;
    float left_road_margin;

    bool margins_found = curvy_world::getRoadMargins(RESPAWNING_Y_POS, left_road_margin, right_road_margin);

    if(margins_found)
    {
        GLfloat road_width = right_road_margin - left_road_margin;
        GLfloat road_lane_size = road_width / NUM_ROAD_LANES; // Assuming 3 lanes

        // Choose a random lane index (0, 1, or 2)
        int road_line = (rand() % NUM_ROAD_LANES);

        // Calculate the X position of the CENTER of the chosen lane
        GLfloat center_of_chosen_lane_x = left_road_margin + (road_line * road_lane_size) + (road_lane_size/2);

        // The car's X position should be its center X position
        GLfloat x_pos = center_of_chosen_lane_x;

        int texture_index = (rand() % this->car_textures.size());

        // Assuming the car constructor takes the center X position
        if(road_line < 3)
        {
            //The cars are on the opposite side of the road, and they will face the bottom of the screen
            this->traffic_cars.push_back(new car(this->car_textures[texture_index].c_str(), x_pos,
                                             RESPAWNING_Y_POS, road_line, -7.0f, Texture_Flip::FLIP_VERTICALLY));
        }
        else
        {
            //The cars are on the opposite side of the road, and they will face the top of the screen
            this->traffic_cars.push_back(new car(this->car_textures[texture_index].c_str(), x_pos,
                                 RESPAWNING_Y_POS, road_line, 7.0f, Texture_Flip::NORMAL));
        }

    }
}

void traffic_spawner::change_traffic_speed(GLfloat speed)
{
    /*This function will change the traffic speed*/

    for(car* traffic_car: this->traffic_cars)
    {
        traffic_car->changeSpeed(speed);
    }
}

void traffic_spawner::draw_traffic_cars(float speed)
{
    /*This function will draw the traffic cars onto the screen,
    and when they get out of range the cars will be cleared and new ones will be generated*/

    /*an iterator, which is a special object (like a pointer) that points to an element in the container*/
    vector<car*>::iterator traffic_iterator = this->traffic_cars.begin(); //or auto traffic_iterator = traffic_cars.begin();

    while (traffic_iterator != this->traffic_cars.end())
    {
        car* traffic_car = *traffic_iterator; //get the data from iterator into a local pointer variable

        traffic_car->move_downwards(speed);

        bool offRoad = curvy_world::isObjectOffRoad(traffic_car->y_pos,
                                            traffic_car->left_top_corner[0],
                                            traffic_car->right_top_corner[0]);
        if(offRoad == true)
        {
            traffic_car->severe_decceleration();
        }

        traffic_car->draw_car();

        //If the traffic cars gets out of the screen
        if (traffic_car->y_pos + (CAR_HEIGHT * 2) < 0 || traffic_car->y_pos  > WINDOW_HEIGHT * 2.5f)
        {
            // Delete the object
            delete traffic_car;

            // Erase from vector safely
            traffic_iterator = this->traffic_cars.erase(traffic_iterator); // returns the next iterator

            if(traffic_car->y_pos + (CAR_HEIGHT * 2) < 0 )
            {
                //The player's car overtook the traffic car.
                Score += static_cast<int>(ScoreEvent::Overtake);

                if(HighScore < Score)
                {
                    HighScore = Score;
                }
            }
            else if (traffic_car->y_pos  > WINDOW_HEIGHT * 2.5f)
            {
                //The traffic car overtook the player's car.
                Score += static_cast<int>(ScoreEvent::Overtaken);

                if(HighScore < Score)
                {
                    HighScore = Score;
                }
            }
        }
        else
        {
            /*
            ++traffic_iterator (pre-increment):

            Increments the iterator first, then returns the incremented iterator.
            Usually more efficient because it doesn't need to create a temporary copy.

            it++ (post-increment):
            Returns the current iterator, then increments it. Slightly less efficient because it may
            create a temporary copy.
            */

            ++traffic_iterator; // move to next if not erased
        }
    }

    if(this->traffic_cars.empty() == true)
    {
        // Vector is empty, generate a new traffic car
        this->generate_traffic_car();
    }
    else if( this->traffic_cars[traffic_cars.size()-1]->y_pos < (RESPAWNING_Y_POS-500) )
    {
        // Vector is not empty, check last car's position
        this->generate_traffic_car();
    }
}
