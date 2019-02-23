#include "p12class.h"

p12class::p12class()
{
    //ctor
}

p12class::~p12class()
{
    //dtor
}
SDL_Window* p12class::init() //the function that initialize the game.
{
    SDL_Init(SDL_INIT_EVERYTHING); //initialize SDL.
    SDL_Window* window; //get a window pointer called "window".
    window=SDL_CreateWindow("Project12", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500,500, SDL_WINDOW_OPENGL);
    //window is creating a window
    SDL_GLContext context; //get a context called context.
    context=SDL_GL_CreateContext(window);
    //the context should be placed on the window.
    glewInit(); //initialize everything that glew has to offer.
    if(glewInit()!=GLEW_OK) //is it glew ok?
    {
        cerr << "Glew initialization has failed" << endl;
    }
    else //if glew was not ok, enter here.
    {
        cout << "Glew has been successfully initialized!" << endl;
    }
    return window;
}
void p12class::draw(SDL_Window* window) //function that draw on the window.
{
    FILE* fp; //get a FILE pointer called fp.
    int counter; // get a counter.
    float speed=2; // set some speed for the delay, (2 means 2ms).
    GLfloat field [6]; //this is the field's initial position, the obstacles falling towards the player.
    field[0]=((rand()%200)+150); //get a random x position between 150 and 350
    field[1]=500; //y position always on the top.
    field[2]=((rand()%200)+150); //get a random x position between 150 and 350
    field[3]=500; //y position always on the top.
    field[4]=((rand()%200)+150); //get a random x position between 150 and 350
    field[5]=500; //y position always on the top.

    GLfloat player [] //the player's initial position.
    {
      250, 25 //centered on x, bottom down on y.
    };
    GLfloat line [] // the line that draws the frontier.
    {
       135, 0,
       135, 500,
       365, 0,
       365, 500
    };
    //translating the normalized coordinates into pixel's
    glViewport(0,0,500,500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,500,0,500,0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //translating done.
    int Score=0; //the initial score.
    int highscore=0;
    fp=fopen("D:/highscore.txt", "r");
    if(fp) //if the file exists.
    {
        fscanf(fp, "%d", &highscore); //get the record.
        cout << "Highscore: " << highscore << endl; //print to the screen.
    }
    else //if the file does not exist
    {
        cout << "No previous records!" << endl;
    }
    SDL_Event a; //create and event.
    while(1) //infinite loop.
    {
        if(counter ==5000) //after 5000 loop rotations, decrease the delay, (make the game faster)
        {
            speed-=0.1;
        }
        glClear(GL_COLOR_BUFFER_BIT); //clear the screen each time.
        glEnableClientState(GL_VERTEX_ARRAY); //enable this state.
        glEnable(GL_POINT_SIZE); //enable this state.
        glPointSize(20); //points size/
        glVertexPointer(2,GL_FLOAT,0,player);//pointer for the player's array.
        glDrawArrays(GL_POINTS, 0,2);//draw the player.
        glVertexPointer(2,GL_FLOAT,0,field);//pointer for the field's array.
        glDrawArrays(GL_POINTS, 0,6);//draw the field.
        glVertexPointer(2,GL_FLOAT,0,line);//pointer for the lines.
        glDrawArrays(GL_LINES, 0,8);//draw the lines.
        glDisable(GL_POINT_SIZE);//disable point's size.
        glDisableClientState(GL_VERTEX_ARRAY); // disable this state.
        SDL_GL_SwapWindow(window); //change the empty window, with the drew one.
        field[1]--; //field's y position decreases each time the loop rotates, this make the obstacles move.
        field[3]--;
        field[5]--;
        SDL_Delay(speed); //let there be this delay, to make the game run slower, until the lever increases.
        if(field[1]<=0) //when the field is no longer on the screen
        {
            field[0]=((rand()%200)+150); //get another position, in the same way, random on x
            field[1]=500; //fixed on y, in the top of the screen
            //when the loop will rotate again, we will have another obstacles falling towards the player.
            field[2]=((rand()%200)+150);
            field[3]=500;
            field[4]=((rand()%200)+150);
            field[5]=500;
            Score+=10; //if the obstacles run out of the screen, increase the score, because the player wasn't hit.
            system("cls"); //clear the console each time.
            cout << "Score: " << Score << endl; //on the empty console, write the new score.
            if(highscore<Score) //if the highest score has been defeated
            {
                cout << "Highscore: " << Score << endl; //print the score
            }
            else //let the highscore be printed on the console.
            cout << "Highscore: " << highscore << endl;
        }
        if(player[1]==field[1]) //if the obstacles are on the same y line with the player
        if( player[0]>=(field[0]-25) && player[0]<=(field[0]+25) ||player[0]>=(field[2]-25) && player[0]<=(field[2]+25) ||player[0]>=(field[4]-25) && player[0]<=(field[4]+25) ) //check if the player hit any of the obstacles.
        {
            //if entered here, means that the player hit an object, so the game is over.
            cout << "Gameover!" << endl;
            SDL_DestroyWindow(window); //close the window.
            SDL_QUIT; //quit SDL
            if(fp) //if the file is already opened by the game
            {
                fclose(fp); //close it, because it's opened for reading.
                if(highscore<Score)//if the highscore has been defetead
                {
                    fp=fopen("D:/highscore.txt", "w"); //open the file for writing.
                    fprintf(fp,"%d", Score); //write the new highscore on the file.
                    fclose(fp); //close the file.
                }
            }
            else //if the file is not opened, because there was no file.
            {
                fclose(fp);//be sure it's closed.
                fp=fopen("D:/highscore.txt", "w");//then open/create a file for writing.
                fprintf(fp,"%d", Score); //print there the value of Score.
                fclose(fp);//close the file.
            }
            break; //if the game is over, exit from infinity
        }
        while(SDL_PollEvent(&a)) //if there is an event set
        {
        if(a.type==SDL_KEYDOWN)//verify if at the event is any key pressed
            switch(a.key.keysym.sym) // if the key was pressed, verify which key that was
            {
                case SDL_QUIT: //if the window close button pressed
                {
                    cout << "Close the console to quit!" << endl; //print this message in the console.
                }
                case SDLK_LEFT: //if the left arrow button was pressed
                {
                    if(player[0]>150) //if the player is on a x position > than 150
                    {
                        player[0]-=15; //modify player's x position (so the player could mode left).
                    }
                    break; //exit the switch
                }
                case SDLK_RIGHT: //if the right arrow button was pressed
                {
                   if(player[0]<350) //if the player is on a x position < than 350
                   {
                        player[0]+=15; //modify the player's x position (so the player could move right)
                    }
                    break; // exit the switch
                }
            }
        }
        counter++; //the loop is ending, count it on.
    }
}
