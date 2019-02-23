#include "p41class.h"

int main (int args, char** argv)
{
    char ans;
    bool selected;
    p12class object;
    SDL_Window* window=object.init();
    while(1) //infinite loop
    {
        selected=false;
        object.draw(window); // call the draw function, and let the window deliver the information to that function.
        cout << "Do you want to play again? Y/N" << endl; //print this after the draw has exit
        while(1)
        {
            ans=getchar(); //take the answear and store it in ans.
            ans=tolower(ans); //convert it to lowercase
            switch(ans)//verify what is the answear.
            {
                case 'y': //if it was y
                    {
                        selected=true; //make this bool variable true.
                        break; //exit the switch.
                    }
                case 'n': //if the answear was n
                    {
                        SDL_DestroyWindow(window); //close the window.
                        SDL_QUIT; //quit SDL
                        exit(1); //exit the whole game.
                        break; //this should not be here, but I want to keep it.
                    }
                default: //for any other answears
                    {
                        break; // break the switch.
                    }

            }
            if(selected==true) //if a valid answear was selected
            {
                cout << "Prepare yourself, the game starts in: " << endl;
                for(int countback=5; countback>=0; countback--)
                {
                    cout << countback << endl;
                    SDL_Delay(1000);
                }
                 break; //exit this infinite loop.
            }
        }
        //once reached this it means that the answear was y, so the game will be replayed
        system("cls"); //clear the screen for the next iteration
    }
    getch();
    return 0;
}
