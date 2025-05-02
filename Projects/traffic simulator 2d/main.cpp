//Predefined headers
#include <SDL_mixer.h>

//User defined headers
#include "Route.h"
#include "Car.h"
#include "Window.h"

//Prototyping the functions:
int getRealisticTraffic(const unsigned int hours);
int addCarsRealisticly(const unsigned int hours);
void DebuggingSameTracks(const int speed, const int TakeRoute, SDL_Window* window, Window windObj, unsigned int numberOfCars);
void DebuggingDifferentTracks(const int speed[], const int Routes[], SDL_Window* window, Window windObj, unsigned int numberOfCars);

//Global variables
enum DEBUG_MODE { More_on_the_same_track, More_on_different_tracks, None};
const DEBUG_MODE debugger = None;
static unsigned int identifiers = 0;

int main(int args, char** argv)
{
    Window windObject;
    SDL_Window* window = windObject.getWindow();
    //Load the audio
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_Music* music;
    music=Mix_LoadMUS("ambience/busy street.mp3");
    Mix_PlayMusic(music, -1); //-1 will play the song in infinite loop.
    if (debugger == More_on_the_same_track)
    {
        DebuggingSameTracks(2, 1, window, windObject, 5);
    }
    else if(debugger == More_on_different_tracks)
    {
        int nrOfCars  = 2;
        int speedOfCars[nrOfCars] = {2,2};
        int Routes [nrOfCars] = {5, 1};
        DebuggingDifferentTracks(speedOfCars, Routes, window, windObject, nrOfCars);
    }
    else
    {
        vector<Route> cars;
        int carsToAdd = getRealisticTraffic( windObject.getTime('h'));
        for(int i=0; i<carsToAdd; i++)
        {
            cars.push_back( Route(2, identifiers++, cars) );
        }
        unsigned int secondCounter = 0;
        while(window!=nullptr)
        {
            windObject.CheckForInput();
            windObject.DoTheRendering();
            for(unsigned int i=0; i < cars.size(); i++)
            {
                if(cars[i].getTimeGap()==0)
                {
                    cars[i].Draw( cars.size() );
                    cars[i].FollowingRoute();
                    cars[i].CollisionDetection(cars);
                }
                else
                {
                    cars[i].setTimeGap(cars[i].getTimeGap()-secondCounter);
                    secondCounter=0;
                }
               // cars[i].CollisionDetection(cars);
                if( cars[i].getCarCoordinates(0) > windObject.screen_Width || cars[i].getCarCoordinates(1) > windObject.screen_Height
                                || cars[i].getCarCoordinates(7) < 0 || cars[i].getCarCoordinates(6) < 0 )
                {
                    cars.erase( cars.begin() + i);
                }
            }
            //Check whether it's time to add a new car to the vector:
            if( addCarsRealisticly(windObject.getTime('h')) == 5 && (cars.size() < 7) && secondCounter > 2)
            {
                cars.push_back( Route(2, identifiers++) );
                secondCounter=0;
            }
            SDL_GL_SwapWindow(window);
            /*This will check weather it's the time to redraw the number of cars in cmd.*/
            if(windObject.getTimePassed())
            {
                //Clear the cmd:
                system("cls");
                //Update the message:
                cout << "Number of cars: " << cars.size() << endl;
                cout << "The time: ";
                if( windObject.getTime('h') < 10)
                {
                    cout << "0" << windObject.getTime('h');
                }
                else
                {
                    cout << windObject.getTime('h');
                }

                if(windObject.getTime('m') < 10)
                {
                    cout << ":0" << windObject.getTime('m') << endl;
                }
                else
                {
                    cout << ":" << windObject.getTime('m') << endl;
                }
                secondCounter++;
            }
        }
    }
    return 0;
}

//Function definitions:
void DebuggingDifferentTracks(const int speed[], const int Routes[], SDL_Window* window, Window windObj, unsigned int numberOfCars)
{
    cout << "_________DEBUGGING_MODE_________" << endl;
    vector<Route> cars;
    if(numberOfCars == 0) {numberOfCars=1;}
    else if(numberOfCars > 7) {numberOfCars=7;}
    for(unsigned int i=0; i<numberOfCars; i++)
    {
        cars.push_back( Route(speed[i], Routes[i], identifiers++, cars) );
    }
    unsigned int secondCounter = 0;
    while(window!=nullptr)
    {
        windObj.CheckForInput();
        windObj.DoTheRendering();
        for(unsigned int i=0; i <  cars.size(); i++)
        {
            if(cars[i].getTimeGap()==0)
            {
                cars[i].Draw( cars.size() );
                cars[i].FollowingRoute();
                cars[i].CollisionDetection(cars);
            }
            else
            {
                cars[i].setTimeGap(cars[i].getTimeGap()-secondCounter);
                secondCounter=0;
            }
            if( cars[i].getCarCoordinates(2) > 1000 || cars[i].getCarCoordinates(1) > 600
                                       || cars[i].getCarCoordinates(2) < 0 || cars[i].getCarCoordinates(1) < 0 )
            {
                cars[i] = Route(speed[i], Routes[i], identifiers++);
            }
        }
        SDL_GL_SwapWindow(window);
        /*This will check weather it's the time to redraw the number of cars in cmd.*/
        if(windObj.getTimePassed())
        {
            system("cls");
            cout << "_________DEBUGGING_MODE_________" << endl;
            //Update the message:
            cout << "The time: ";
            cout << "Number of cars: " << numberOfCars << endl;
            if( windObj.getTime('h') < 10)
            {
                cout << "0" << windObj.getTime('h');
            }
            else
            {
                cout << windObj.getTime('h');
            }

            if(windObj.getTime('m') < 10)
            {
                cout << ":0" << windObj.getTime('m') << endl;
            }
            else
            {
                cout << ":" << windObj.getTime('m') << endl;
            }
            secondCounter++;
        }
    }
}
void DebuggingSameTracks(const int speed, const int TakeRoute, SDL_Window* window, Window windObj, unsigned int numberOfCars)
{
    cout << "_________DEBUGGING_MODE_________" << endl;

    vector <Route> cars;
    if(numberOfCars == 0) {numberOfCars=1;}
    else if(numberOfCars > 7) {numberOfCars=7;}
    for(unsigned int i=0; i < numberOfCars; i++)
    {
        cars.push_back( Route(2, TakeRoute, identifiers++, cars) );
    }
    unsigned int secondCounter = 0;
    while(window!=nullptr)
    {
        windObj.CheckForInput();
        windObj.DoTheRendering();
        for(unsigned int i=0; i <  cars.size(); i++)
        {
            if(cars[i].getTimeGap()==0)
            {
                cars[i].Draw( cars.size() );
                cars[i].FollowingRoute();
                cars[i].CollisionDetection(cars);
            }
            else
            {
                cars[i].setTimeGap(cars[i].getTimeGap()-secondCounter);
                secondCounter=0;
            }
            if( cars[i].getCarCoordinates(2) > 1000 || cars[i].getCarCoordinates(1) > 600
                                       || cars[i].getCarCoordinates(2) < 0 || cars[i].getCarCoordinates(1) < 0 )
            {
                cars[i]  = Route(2, TakeRoute, identifiers++);
            }
        }
        SDL_GL_SwapWindow(window);
        /*This will check weather it's the time to redraw the number of cars in cmd.*/
        if(windObj.getTimePassed())
        {
            system("cls");
            cout << "_________DEBUGGING_MODE_________" << endl;
            //Update the message:
            cout << "The time: ";
            cout << "Number of cars: " << numberOfCars << endl;
            if( windObj.getTime('h') < 10)
            {
                cout << "0" << windObj.getTime('h');
            }
            else
            {
                cout << windObj.getTime('h');
            }

            if(windObj.getTime('m') < 10)
            {
                cout << ":0" << windObj.getTime('m') << endl;
            }
            else
            {
                cout << ":" << windObj.getTime('m') << endl;
            }
            secondCounter++;
        }
    }
}
int getRealisticTraffic(const unsigned int hours)
{

    srand (time(NULL));
    int nrOfCars;
    switch(hours)
    {
        case 0:
        case 1:
        {
            nrOfCars = (rand()%3 )+ 1;
            break;
        }
        case 2:
        case 3:
        case 4:
        {
            nrOfCars = (rand()%4 )+ 1;
            break;
        }
        case 5:
        case 6:
        {
            nrOfCars = (rand()%5 )+ 1;
            break;
        }
        case 7:
        case 8:
        case 9:
        {
           nrOfCars = (rand()%6 )+ 1;
           break;
        }
        case 10:
        case 11:
        {
           nrOfCars = (rand()%5 )+ 1;
           break;
        }
        case 12:
        case 13:
        case 14:
        {
            nrOfCars = (rand()%6 )+ 1;
            break;
        }
        case 15:
        case 16:
        case 17:
        {
            nrOfCars = (rand()%5 )+ 1;
            break;
        }
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        {
            nrOfCars = (rand()%4 )+ 1;
            break;
        }
        default:
        {
            /*Hopefully it will never reach here:*/
            nrOfCars = 2;
        }

    }
    return nrOfCars;
}
int addCarsRealisticly(const unsigned int hours)
{
    int choice;
    switch(hours)
    {
        case 0:
        case 1:
        {
            choice = (rand()%100)+ 1;
            break;
        }
        case 2:
        case 3:
        case 4:
        {
            choice = (rand()%70)+ 1;
            break;
        }
        case 5:
        case 6:
        {
            choice = (rand()%60)+ 1;
            break;
        }
        case 7:
        case 8:
        case 9:
        {
           choice = (rand()%40)+ 1;
           break;
        }
        case 10:
        case 11:
        {
           choice = (rand()%50)+ 1;
           break;
        }
        case 12:
        case 13:
        case 14:
        {
            choice = (rand()%60)+ 1;
            break;
        }
        case 15:
        case 16:
        case 17:
        {
            choice = (rand()%40)+ 1;
            break;
        }
        case 18:
        case 19:
        case 20:
        {
            choice = (rand()%70 )+ 1;
            break;
        }
        case 21:
        case 22:
        {
            choice = (rand()%80 )+ 1;
            break;
        }
        case 23:
        {
            choice = (rand()%90 )+ 1;
            break;
        }
        default:
        {
            /*Hopefully it will never reach here:*/
            choice = 2;
        }
    }
    return choice;
}
