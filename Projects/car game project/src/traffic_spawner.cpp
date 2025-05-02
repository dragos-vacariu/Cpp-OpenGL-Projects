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

    //get another position, in the same way, random on x
    GLfloat x_pos = WORLD_SEGMENTS_WIDTH + (CAR_WIDTH);

    int road_line = (rand() % 3);

    if(road_line == 1)
    {
        x_pos = WORLD_SEGMENTS_WIDTH + (ROAD_SEGMENTS_WIDTH/3) + (CAR_WIDTH);
    }
    else if(road_line == 2)
    {
        x_pos = WORLD_SEGMENTS_WIDTH + ( 2 * (ROAD_SEGMENTS_WIDTH/3)) + (CAR_WIDTH);
    }
    else if(road_line == 0 )
    {
        /*Nothing to do. We'll use the line 0 with the predefined x_pos*/
    }

    int texture_index = (rand() % this->car_textures.size());

    this->traffic_cars.push_back(new car(this->car_textures[texture_index].c_str(), x_pos, WINDOW_HEIGHT * 1.5f, 7.0f, Texture_Flip::NORMAL));
}

void traffic_spawner::change_traffic_speed(GLfloat speed)
{
    /*This function will change the traffic speed*/

    for(car* traffic_car: this->traffic_cars)
    {
        traffic_car->changeSpeed(speed);
    }
}

void traffic_spawner::draw_traffic_cars(float player_speed)
{
    /*This function will draw the traffic cars onto the screen,
    and when they get out of range the cars will be cleared and new ones will be generated*/

    /*an iterator, which is a special object (like a pointer) that points to an element in the container*/
    vector<car*>::iterator traffic_iterator = this->traffic_cars.begin(); //or auto traffic_iterator = traffic_cars.begin();

    while (traffic_iterator != this->traffic_cars.end())
    {
        car* traffic_car = *traffic_iterator; //get the data from iterator into a local pointer variable

        traffic_car->move_downwards(player_speed);
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
    else if(this->traffic_cars[traffic_cars.size()-1]->y_pos < (WINDOW_HEIGHT/2))
    {
        // Vector is not empty, check last car's position
        this->generate_traffic_car();
    }
}
