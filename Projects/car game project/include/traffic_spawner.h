#ifndef TRAFFIC_SPAWNER_H
#define TRAFFIC_SPAWNER_H

//Cross-functions inclusion:
#include "../include/cross_functions.h"
#include "../include/car.h"
#include "../include/world_map.h"

//Constant defines
#define TRAFFIC_CAR_TEXTURE IMG_RESOURCES "/car2.png"

using namespace std;

class traffic_spawner
{
    public:
        traffic_spawner();
        virtual ~traffic_spawner();

        //Public functions:
        void draw_traffic_cars(float player_speed);
        void change_traffic_speed(GLfloat speed);

        //Public variables:
        vector <car*> traffic_cars;
        vector <string> car_textures;

    protected:

    private:
        //Private functions
        void generate_traffic_car();

        //Private variables:
};

#endif // TRAFFIC_SPAWNER_H
