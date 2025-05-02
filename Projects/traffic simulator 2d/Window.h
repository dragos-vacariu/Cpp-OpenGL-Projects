#ifndef WINDOW_H
#define WINDOW_H

//User-defined headers:
#include "Car.h"

class Window
{
    public:
        Window();
        Window(unsigned int hours, unsigned int minutes);
        virtual ~Window();
        //Fields:
        const int screen_Height = 594;
        const int screen_Width = 1001;

        //Getters
        SDL_Window* getWindow()
        {
            return window;
        }

        //Functionality of the window:
        void CheckForInput ()
        {
            SDL_Event event;
            while(SDL_PollEvent(&event)) //if there is an event set
            {
                switch(event.type)
                {
                    case SDL_QUIT:
                    {
                        exit(1);
                    }
                }
            }
        }
        void DoTheRendering()
        {
             //translating the normalized coordinates into pixel's
            glViewport(0,0,screen_Width,screen_Height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0,screen_Width,0,screen_Height,
                    /*These 2 coordinates are for 3D: z axis*/
                    -100,100);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            //translating done.

            //Setting the environment for texturing:
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            //Let's draw the content:
            glClear(GL_COLOR_BUFFER_BIT); //clear the screen each time;
            glBindTexture(GL_TEXTURE_2D, worldTexture);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0);
            glVertex2f(0.0, 0.0);
            glTexCoord2f(0.0, 1.0);
            glVertex2f(0.0, screen_Height);
            glTexCoord2f(1.0, 1.0);
            glVertex2f(screen_Width, screen_Height);
            glTexCoord2f(1.0, 0.0);
            glVertex2f(screen_Width, 0.0);
            glEnd();
        }
        bool getTimePassed()
        {
            int amountOfSecondsPassed = difftime( time(0), start_time);
            if(amountOfSecondsPassed > 1)
            {
                start_time = time(0);
                the_time[1]+=1;
                if(the_time[1]>59)
                {
                    the_time[1]=0;
                    the_time[0]++;
                    if(the_time[0]>23)
                    {
                        the_time[0]=0;
                    }
                    setBackgroundTexture();
                }
                return true;
            }
            return false;
        }
        unsigned int getTime(const char c)
        {
            switch (c)
            {
                case 'm':
                case 'M':
                    {
                        return (unsigned int)the_time[1];
                    }
                case 'h':
                case 'H':
                    {
                        break;
                    }
            }
            //when H is passed the break statement will bring here:
            return (unsigned int)the_time[0];
        }
    protected:

    private:
        SDL_Window* window;
        SDL_GLContext glContext;
        GLuint worldTexture;
        time_t start_time;
        //Private functionality
        void setBackgroundTexture()
        {
            switch(the_time[0])
            {
                case 0:
                case 1:
                {
                    worldTexture = Car::loadTexture("textures/environment/environment00.gfx");
                    break;
                }
                case 2:
                case 3:
                {
                    worldTexture = Car::loadTexture("textures/environment/environment01.gfx");
                    break;
                }
                case 4:
                case 5:
                {
                    worldTexture = Car::loadTexture("textures/environment/environment02.gfx");
                    break;
                }
                case 6:
                case 7:
                {
                    worldTexture = Car::loadTexture("textures/environment/environment03.gfx");
                    break;
                }
                case 8:
                case 9:
                {
                    worldTexture = Car::loadTexture("textures/environment/environment04.gfx");
                    break;
                }
                case 10:
                case 11:
                {
                    worldTexture = Car::loadTexture("textures/environment/environment05.gfx");
                    break;
                }
                case 12:
                case 13:
                {
                    worldTexture = Car::loadTexture("textures/environment/environment06.gfx");
                    break;
                }
                case 14:
                case 15:
                {
                    worldTexture = Car::loadTexture("textures/environment/environment07.gfx");
                    break;
                }
                case 16:
                case 17:
                {
                    worldTexture = Car::loadTexture("textures/environment/environment08.gfx");
                    break;
                }
                case 18:
                case 19:
                {
                    worldTexture = Car::loadTexture("textures/environment/environment09.gfx");
                    break;
                }
                case 20:
                case 21:
                {
                    worldTexture = Car::loadTexture("textures/environment/environment10.gfx");
                    break;
                }
                case 22:
                case 23:
                {
                    worldTexture = Car::loadTexture("textures/environment/environment11.gfx");
                    break;
                }
            }
        }
        unsigned char the_time[2]; //this variable will hold the virtual clock value;
};

#endif // WINDOW_H
