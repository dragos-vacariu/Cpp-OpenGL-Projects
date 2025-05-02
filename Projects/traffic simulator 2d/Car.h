#ifndef CAR_H
#define CAR_H

/*Predefined Headers:*/
#include <SDL.h>
#include <glew.h>
#include <SOIL.h>
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <iostream>

//Defining constants:
#define CarHeight 40
#define CarWidth 20

using namespace std;

class Car
{
    public:

        virtual ~Car();
        virtual void FollowingRoute() = 0; //Let this class be abstract
        //Car Public Functionality;
        void Draw(unsigned int DelayDecreaser)
        {
            if(DelayDecreaser==1)
            {
                DelayDecreaser=0; //in case of 1 car, don't do anything;
            }
            glBindTexture(GL_TEXTURE_2D, this->CarTexture);
            switch(CarRotatedPosition)
            {
                case 1:{
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0, 0.0);
                    glVertex2f(CarCoordinates[0], CarCoordinates[1]);
                    glTexCoord2f(0.0, 1.0);
                    glVertex2f(CarCoordinates[2], CarCoordinates[3]);
                    glTexCoord2f(1.0, 1.0);
                    glVertex2f(CarCoordinates[4], CarCoordinates[5]);
                    glTexCoord2f(1.0, 0.0);
                    glVertex2f(CarCoordinates[6], CarCoordinates[7]);
                    glEnd();
                    break;
                }
                case 2: {
                    glBegin(GL_QUADS);
                    glTexCoord2f(1.0, 0.0);
                    glVertex2f(CarCoordinates[0], CarCoordinates[1]);
                    glTexCoord2f(0.0, 0.0);
                    glVertex2f(CarCoordinates[2], CarCoordinates[3]);
                    glTexCoord2f(0.0, 1.0);
                    glVertex2f(CarCoordinates[4], CarCoordinates[5]);
                    glTexCoord2f(1.0, 1.0);
                    glVertex2f(CarCoordinates[6], CarCoordinates[7]);
                    glEnd();
                    break;
                }
                case 3: {
                    glBegin(GL_QUADS);
                    glTexCoord2f(1.0, 1.0);
                    glVertex2f(CarCoordinates[0], CarCoordinates[1]);
                    glTexCoord2f(1.0, 0.0);
                    glVertex2f(CarCoordinates[2], CarCoordinates[3]);
                    glTexCoord2f(0.0, 0.0);
                    glVertex2f(CarCoordinates[4], CarCoordinates[5]);
                    glTexCoord2f(0.0, 1.0);
                    glVertex2f(CarCoordinates[6], CarCoordinates[7]);
                    glEnd();
                    break;
                }
                case 4:{
                    glBegin(GL_QUADS);
                    glTexCoord2f(0.0, 1.0);
                    glVertex2f(CarCoordinates[0], CarCoordinates[1]);
                    glTexCoord2f(1.0, 1.0);
                    glVertex2f(CarCoordinates[2], CarCoordinates[3]);
                    glTexCoord2f(1.0, 0.0);
                    glVertex2f(CarCoordinates[4], CarCoordinates[5]);
                    glTexCoord2f(0.0, 0.0);
                    glVertex2f(CarCoordinates[6], CarCoordinates[7]);
                    glEnd();
                    break;
                }
            }
            SDL_Delay( 21-(DelayDecreaser*3) ); //the DelayDecreaser will try to keep the same rendering speed
            //regardless of the number of cars it appears on the screen.
        }
        static GLuint loadTexture(const char* filename)
        {
            int width, height;
            unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
            if(image==nullptr)
            {
                cerr << "Failed to load the texture" << " " << filename << endl;
                cout << "Please check the integrity of the project." << endl;
                exit(1);
            }
            GLuint textureid;
            glGenTextures(1, &textureid);
            glBindTexture(GL_TEXTURE_2D, textureid);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            SOIL_free_image_data(image);
            return textureid;
        }
        //Getters and setters:
        void setTimeGap(unsigned int gap)
        {
            timeGap = gap;
        }
        unsigned int getTimeGap()
        {
            return timeGap;
        }

    protected:
        //Declaration of the constructor
        Car();
        Car(const unsigned int speed, const unsigned int ID);
        GLuint CarTexture;
        GLfloat CarCoordinates[8];
        int Speed;
        unsigned int CarRotatedPosition;
        bool isCarMoving;
        bool hasPriority;
        int uniqueID;
        time_t waiting_time;
        unsigned int timeGap;
        //Functionality to be inherited:
        void MovingCarUp()
        {
            if(isCarMoving)
            {
                CarCoordinates[1]+=Speed;
                CarCoordinates[3]+=Speed;
                CarCoordinates[5]+=Speed;
                CarCoordinates[7]+=Speed;
            }
        }
        void MovingCarDown()
        {
            if(isCarMoving)
            {
                CarCoordinates[1]-=Speed;
                CarCoordinates[3]-=Speed;
                CarCoordinates[5]-=Speed;
                CarCoordinates[7]-=Speed;
            }
        }
        void MovingCarLeft()
        {
            if(isCarMoving)
            {
                CarCoordinates[0]-=Speed;
                CarCoordinates[2]-=Speed;
                CarCoordinates[4]-=Speed;
                CarCoordinates[6]-=Speed;
            }
        }
        void MovingCarRight()
        {
            if (isCarMoving)
            {
                CarCoordinates[0]+=Speed;
                CarCoordinates[2]+=Speed;
                CarCoordinates[4]+=Speed;
                CarCoordinates[6]+=Speed;
            }
        }
        void StopTheCar()
        {
            if(isCarMoving)
            {
                waiting_time = time(0);
                isCarMoving = false;
            }
        }
        void StartTheCar()
        {
            if(!isCarMoving)
            {
                isCarMoving = true;
            }
        }
        void RotateCarHorizontally()
        {
            CarCoordinates[3] = CarCoordinates[1] + CarWidth;
            CarCoordinates[4] = CarCoordinates[2] + CarHeight;
            CarCoordinates[5] = CarCoordinates[1] + CarWidth;
            CarCoordinates[6] = CarCoordinates[2] + CarHeight;
        }
        void RotateCarVertically()
        {
            CarCoordinates[3] = CarCoordinates[1] + CarHeight;
            CarCoordinates[4] = CarCoordinates[2] + CarWidth;
            CarCoordinates[5] = CarCoordinates[1] + CarHeight;
            CarCoordinates[6] = CarCoordinates[2] + CarWidth;
        }

        void CarTextureSelector()
        {
            const string textures[14] = {"car.pngs", "car2.pngs", "car3.pngs", "car4.pngs", "car5.pngs", "car6.pngs", "car7.pngs",
                            "car8.pngs", "car9.pngs", "car10.pngs", "car11.pngs", "car12.pngs", "car13.pngs", "car14.pngs"};
            int selector = (rand()% 14);
            string filepath = "textures/cars/";
            filepath += textures[selector]; //append the filepath to the chosen texture.
            CarTexture = loadTexture( filepath.c_str() );
        }
        bool getStopageTime()
        {
            int amountOfSecondsPassed = difftime( time(0), waiting_time);
            if(amountOfSecondsPassed == 2)
            {
                return true;
            }
            return false;
        }

    private:

};

#endif // CAR_H
