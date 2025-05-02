//Double inclusion prevention mechanism:
#ifndef GAME_H
#define GAME_H

//Classes inclusion:
#include "../include/hud.h"
#include "../include/world_map.h"
#include "../include/curvy_world.h"
#include "../include/cross_functions.h"
#include "../include/player.h"
#include "../include/traffic_spawner.h"

using namespace std;

class game
{
    public:
        //Constructor
        game();
        //Destructor
        virtual ~game();

        //Public methods
        void mainloop(); //declaring the draw function

        enum GAME_STATUS
        {
            GAME_PAUSED,
            GAME_RUNNING,
            EXIT_DIALOG,
            GAME_EXIT,
            GAME_OVER,
        };

    protected:

    private:
        //Private functions:
        void read_user_input();
        void handle_user_input();
        void play_background_music();
        int check_gameOver(SDL_Window* window, int Score, int highscore);
        void savescore();
        void handleCarCollisions();
        void calculateDamage(float x_axis_force, float y_axis_force);
        void read_highest_score();
        void write_highest_score();

        //Private variables:
        GAME_STATUS game_status;

        SDL_Window* window;

        //These are unique_ptr's - pointers that have automatic memory management, no delete required for cleanup
        unique_ptr <hud> game_hud;
        unique_ptr <world_map> game_world;
        //unique_ptr <curvy_world> curvy_world_map;;
        unique_ptr <player> game_player;
        unique_ptr <traffic_spawner> game_traffic_spawner;
};

#endif // CAR_GAME_H
