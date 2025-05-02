#include "../include/game.h"

using namespace std;

//Constructor
game::game()
{
    this->game_status = GAME_STATUS::GAME_RUNNING;

    //initialize SDL.
    SDL_Init(SDL_INIT_EVERYTHING);

    //Creating a windows which will be referenced by SDL_Window* window
    this->window = SDL_CreateWindow("Car Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

    //Creating a context to be placed on the window.
    SDL_GL_CreateContext(this->window);

    //Unique pointers - these pointers don't need to be deleted to free the memory:
    this->game_hud = unique_ptr<hud>(new hud(this->window));
    this->game_world = unique_ptr<world_map>(new world_map());
    //this->curvy_world_map = unique_ptr<curvy_world>(new curvy_world());
    this->game_player = unique_ptr<player>(new player());
    this->game_traffic_spawner = unique_ptr<traffic_spawner>(new traffic_spawner());
}

//Destructor
game::~game()
{
    //Cleaning up the resources used through the pointers
    //delete this->window;
}

//Global Variables

bool INPUT_ACCELERATE = false;
bool INPUT_BRAKE = false;
bool INPUT_LEFT = false;
bool INPUT_RIGHT = false;

void game::mainloop() //function that draw on the window.
{
    //Setting up the environment

    //translating the normalized coordinates into pixel's
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,WINDOW_HEIGHT,0,WINDOW_WIDTH,-100,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //translating done.

    this->read_highest_score();

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //This is the mainloop, everything happens below:
    while(this->game_status != GAME_STATUS::GAME_EXIT)
    {
        if(this->game_status == GAME_STATUS::GAME_RUNNING)
        {
            glClear(GL_COLOR_BUFFER_BIT); //clear the screen each time;

            //Drawing the road
            this->game_world->drawWorld(this->game_player->player_speed);
            //this->curvy_world_map->drawRoad();

            this->game_player->drawPlayer();
            this->game_traffic_spawner->draw_traffic_cars(this->game_player->player_speed);

            this->game_hud->updateScore(Score);
            this->game_hud->updateHighestScore();
            this->game_hud->updateSpeedLabel(int(this->game_player->player_speed * 10));
            this->game_hud->updateDamageLabel(Damage);

            if(Damage >= 100)
            {
                this->game_hud->showGameOverDialog();
                this->game_status = GAME_STATUS::GAME_OVER;
            }

            handleCarCollisions();

            SDL_GL_SwapWindow(this->window); //change the empty window, with the drew one.
        }

        handle_user_input();
    }
}

void game::handle_user_input()
{
    /*This function will process the user inputs in real-time based on the flags.
    By handling the user input here we can ensure that we can that we can take multiple actions at once.
    Example: accelerate and turn-left;
    */

    this->read_user_input();
    if(INPUT_ACCELERATE)
    {
        this->game_player->accelerate();
    }
    else
    {
        if(this->game_status == GAME_STATUS::GAME_RUNNING)
        {
            this->game_player->deccelerate();
        }
    }
    if(INPUT_BRAKE)
    {
        this->game_player->brake();
    }
    if(INPUT_LEFT)
    {
        if( (this->game_player->getTopLeftXCoor() - CAR_TURNING_FACTOR > this->game_world->getRoadLeftMargin()) &&
           (this->game_status == GAME_STATUS::GAME_RUNNING) )
        {
            this->game_player->car_obj->turn(CAR_DIRECTION::LEFT);
        }
    }
    if(INPUT_RIGHT)
    {
        if( (this->game_player->getTopRightXCoor() + CAR_TURNING_FACTOR < this->game_world->getRoadRightMargin()) &&
            (this->game_status == GAME_STATUS::GAME_RUNNING) )
        {
            this->game_player->car_obj->turn(CAR_DIRECTION::RIGHT);
        }
    }
    if(INPUT_LEFT == false && INPUT_RIGHT == false)
    {
        this->game_player->car_obj->decrease_turn();
    }
}

void game::read_user_input()
{
    /*This function will read user input from the keyboard in real-time*/

    SDL_Event event;

    while( SDL_PollEvent(&event) ) //if there is an event set
    {
        if(event.type == SDL_KEYDOWN)//verify if at the event is any key pressed
        {
            switch(event.key.keysym.sym) // if the key was pressed, verify which key that was
            {
                case SDLK_a:
                case SDLK_LEFT: //if the left arrow button was pressed
                {
                    INPUT_LEFT = true;
                    break; //exit the switch
                }

                case SDLK_RIGHT: //if the right arrow button was pressed
                case SDLK_d:
                {
                    INPUT_RIGHT = true;
                    break;
                }
                case SDLK_DOWN:
                case SDLK_s:
                {
                    INPUT_BRAKE = true;
                    break;
                }
                case SDLK_UP:
                case SDLK_w:
                {
                    INPUT_ACCELERATE = true;
                    break;
                }
                case SDLK_m:
                {
                    Mix_PauseMusic();
                    //cout << "Sound muted!" << endl;
                    break;
                }
                case SDLK_p:
                case SDLK_SPACE:
                {
                    if(this->game_status == GAME_STATUS::GAME_RUNNING)
                    {
                        this->game_hud->showGamePausedLabel();
                        //The label will be cleared in the game loop
                        SDL_GL_SwapWindow(this->window);
                        this->game_status = GAME_STATUS::GAME_PAUSED;
                    }
                    else if(this->game_status == GAME_STATUS::GAME_PAUSED)
                    {
                        this->game_status = GAME_STATUS::GAME_RUNNING;
                        //The label will be cleared in the game loop
                    }
                    break;
                }
                case SDLK_ESCAPE:
                {
                    if(this->game_status == GAME_STATUS::EXIT_DIALOG)
                    {
                        this->game_status = GAME_STATUS::GAME_PAUSED;
                        this->game_hud->showGamePausedLabel();
                        //The label will be cleared in the game loop
                        SDL_GL_SwapWindow(this->window);
                    }
                    else
                    {
                        this->game_hud->showExitGameDialog();
                        //The label will be cleared in the game loop
                        SDL_GL_SwapWindow(this->window);
                        this->game_status = GAME_STATUS::EXIT_DIALOG;
                    }
                    break;
                }
                case SDLK_y:
                {
                    if(this->game_status == GAME_STATUS::EXIT_DIALOG)
                    {
                        this->write_highest_score();
                        this->game_status = GAME_STATUS::GAME_EXIT;
                    }
                    else if(this->game_status == GAME_STATUS::GAME_OVER)
                    {
                        //Cleaning up the pointers
                        this->game_hud.reset();
                        this->game_world.reset();
                        //this->curvy_world_map.reset();
                        this->game_player.reset();
                        this->game_traffic_spawner.reset();
                        Score = 0;
                        Damage = 0;

                        //Creating new references
                        this->game_hud = unique_ptr<hud>(new hud(this->window));
                        this->game_world = unique_ptr<world_map>(new world_map());
                        //this->curvy_world_map = unique_ptr<curvy_world>(new curvy_world());
                        this->game_player = unique_ptr<player>(new player());
                        this->game_traffic_spawner = unique_ptr<traffic_spawner>(new traffic_spawner());

                        SDL_GL_SwapWindow(this->window);
                        this->game_status = GAME_STATUS::GAME_RUNNING;
                    }
                    break;
                }
                case SDLK_n:
                {
                    if(this->game_status == GAME_STATUS::EXIT_DIALOG)
                    {
                        this->game_status = GAME_STATUS::GAME_RUNNING;
                    }
                    else if(this->game_status == GAME_STATUS::GAME_OVER)
                    {
                        this->game_status = GAME_STATUS::GAME_EXIT;
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        else if(event.type == SDL_KEYUP)//verify if at the event is any key pressed
        {
            switch(event.key.keysym.sym) // if the key was pressed, verify which key that was
            {
                case SDLK_UP:
                case SDLK_w:
                {
                    INPUT_ACCELERATE = false;
                }
                case SDLK_DOWN:
                case SDLK_s:
                {
                    INPUT_BRAKE = false;
                    break;
                }
                case SDLK_a:
                case SDLK_LEFT: //if the left arrow button was pressed
                {
                    INPUT_LEFT = false;
                    break; //exit the switch
                }

                case SDLK_RIGHT: //if the right arrow button was pressed
                case SDLK_d:
                {
                    INPUT_RIGHT = false;
                    break;
                }
            }
        }
        else if (event.type == SDL_QUIT)
        {
            this->write_highest_score();
            this->game_status = GAME_STATUS::GAME_EXIT;
        }
    }
}

void game::handleCarCollisions()
{
    // Check collisions among traffic cars

    /*
    size_t is an unsigned integer type in C++ (and C) that is used to represent sizes and counts — such as the size
    of arrays, vectors, strings, and other containers.
    */
    for (size_t outer_index = 0; outer_index < this->game_traffic_spawner->traffic_cars.size(); outer_index++)
    {
        for (size_t inner_index = outer_index + 1; inner_index < this->game_traffic_spawner->traffic_cars.size();
            inner_index++)
        {
            car* inner_car = this->game_traffic_spawner->traffic_cars[inner_index];
            car* outer_car = this->game_traffic_spawner->traffic_cars[outer_index];

            CollisionInfo collision_info = inner_car->collidesWith(outer_car);

            if (collision_info.isColliding == true)
            {
                inner_car->restore_previous_position();
                inner_car->deflect_collision(collision_info.pushX, collision_info.pushY);
                outer_car->restore_previous_position();
                outer_car->deflect_collision(-collision_info.pushX, -collision_info.pushY);
            }
        }
    }

    // Check collisions between traffic cars and the player
    //auto& will become car* at compile time

    /*
    auto deduces the type, including whether it's a reference or not.
    auto& explicitly makes the variable a reference to the element in the container.
    */

    for (auto& traffic_car : this->game_traffic_spawner->traffic_cars)
    {
        //auto matching_iterator = find(PLAYER_COLLISIONS.begin(), PLAYER_COLLISIONS.end(), static_cast<car*>(traffic_car));
        car* previous_collider = this->game_player->car_obj->collider;
        CollisionInfo collision_info = this->game_player->car_obj->collidesWith(traffic_car);

        if (collision_info.isColliding == true)
        {
            //this->game_player->car_obj->restore_previous_position();
            this->game_player->car_obj->deflect_collision(collision_info.pushX/2, collision_info.pushY/2);
            //traffic_car->restore_previous_position();
            traffic_car->deflect_collision(-collision_info.pushX/2, -collision_info.pushY/2);
            this->game_player->brake();


            if(previous_collider != this->game_player->car_obj->collider)
            {
                //New collision detected
                //The 2 cars entered in a collision
                //PLAYER_COLLISIONS.push_back(traffic_car);
                Score += static_cast<int>(ScoreEvent::Collision);
                if(HighScore < Score)
                {
                    HighScore = Score;
                }
                calculateDamage(collision_info.pushX, collision_info.pushY);
                this->game_player->car_obj->toggleColorEffect();
            }
            else
            {
                //collision persists, do nothing
                //The 2 cars were already colliding
            }
        }

    }
}

void game:: calculateDamage(float x_axis_force, float y_axis_force)
{
    //frontal collision
    if(y_axis_force > 0)
    {
        Damage += abs(this->game_player->player_speed) / 4;
    }
    //backside_collision
    else if(y_axis_force < 0)
    {
        Damage += abs(this->game_player->player_speed) / 20;
    }
    //Horizontal collision
    if(abs(x_axis_force) > 0)
    {
        Damage += abs(this->game_player->player_speed) / 10;
    }
}

void game::read_highest_score()
{
    FILE* fp = fopen(SAVEGAME, "r");
    if(fp) //if the file exists.
    {
        fscanf(fp, "%d", &HighScore); //get the record.
        fclose(fp); //close the file.
    }
}

void game::write_highest_score()
{
    std::ofstream file(SAVEGAME);

    if (file)
    {
        // Write some text to the file
        file << HighScore;

        // Close the file
        file.close();
    }
    else
    {
        //cerr << "Failed to open or create the file." << std::endl;
    }
}
