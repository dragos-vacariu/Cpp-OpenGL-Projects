#include "p41class.h"

p12class::p12class()
{
}

p12class::~p12class()
{
}
GLuint texplayer, texobstacle, grass, roadtex;

char* stages [6] {"grass4.jpg", "dirt.png", "water.jpg", "sand.jpg", "grass5.png", "dry.jpg"};

FILE* fp;
GLfloat player [] //the player's initial position.
{
  230, 175, //centered on x, bottom down on y.
  260, 175,
  260, 125,
  230, 125
};
GLfloat lineleft [] // the line that draws the frontier.
{
   140, 0,
   140, 2500,
   0,2500,
   0,0
};
GLfloat lineright[]
{
     380, 0,
    380, 2500,
    500, 2500,
    500, 0
};
GLfloat road []
{
    380,0,
    380,2500, //5000
    140,2500, //5000
    140,0
};
GLfloat field [16];
int x=2;
int level=0;
int multiplier=1;
int productdone, countermp, texcounter=0;
float speed=3.0;
bool paused=false;
int distancetolevel=800;
int factor=0;

GLuint p12class::loadtexture(const char* filename)
{
    int width, height;
    unsigned char* image= SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
    if(image==nullptr)
    {
        cerr << "Failed to load the texture" << " " << filename << endl;
        return 0;
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
    fieldrand();
    //translating the normalized coordinates into pixel's
    glViewport(0,0,500,500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,500,0,500,-100,100);
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
    cout << "Multiplier: X" << multiplier << endl;
    cout << "Distance to next level: " << distancetolevel*10 << "m" << endl;
    cout << "Factor: " << factor*10 << endl;
    cout << "Level: " << level+1 << "/7" << endl;
    glEnable(GL_TEXTURE_2D);
    texplayer=loadtexture("car.png");
    texobstacle=loadtexture("car2.png");
    grass=loadtexture("grass4.jpg");
    roadtex=loadtexture("road3.jpg");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while(1) //infinite loop.
    {
        if(!paused)
        {
            distancetravel();
            if(distancetolevel<=0&&level<6)
            {
                paused=true;
                level++;
                glClear(GL_COLOR_BUFFER_BIT);
                glLoadIdentity();
                grass=loadtexture(stages[level]);
                cout << "Going to the next level in: " << endl;
                for(int countback=5; countback>=0; countback--)
                {
                    cout << countback << endl;
                    SDL_Delay(1000);
                }
                SDL_GL_SwapWindow(window);
                distancetolevel=800+(400*level);
                countermp=0;
                multiplier=1;
                productdone=0;
                speed-=0.5;
                paused=false;
            }
            movecoords();
            if(countermp==1000)
            {
                countermp=0;
                multiplier-=productdone;
                productdone=0;
            }
            if(texcounter==int(500/x))
            {
                texcounter=0;
                resetcoords();
                distancetolevel-=factor;
            }

            glClear(GL_COLOR_BUFFER_BIT); //clear the screen each time;
            glClear(GL_COLOR_BUFFER_BIT);
            glBindTexture(GL_TEXTURE_2D, roadtex);
            glBegin(GL_QUADS);
            glTexCoord2f(10,1.0);
            glVertex2f(road[0], road[1]);
            glTexCoord2f(0.0,1.0);
            glVertex2f(road[2], road[3]);
            glTexCoord2f(0.0,0.0);
            glVertex2f(road[4], road[5]);
            glTexCoord2f(10,0.0);
            glVertex2f(road[6], road[7]);
            glEnd();

            glBindTexture(GL_TEXTURE_2D, texobstacle);

            glBegin(GL_QUADS);
            glTexCoord2f(1.0,1.0);
            glVertex2f(field[0], field[1]);
            glTexCoord2f(0.0,1.0);
            glVertex2f(field[2], field[3]);
            glTexCoord2f(0.0,0.0);
            glVertex2f(field[4], field[5]);
            glTexCoord2f(1.0,0.0);
            glVertex2f(field[6], field[7]);

            glTexCoord2f(1.0,1.0);
            glVertex2f(field[8], field[9]);
            glTexCoord2f(0.0,1.0);
            glVertex2f(field[10], field[11]);
            glTexCoord2f(0.0,0.0);
            glVertex2f(field[12], field[13]);
            glTexCoord2f(1.0,0.0);
            glVertex2f(field[14], field[15]);

            glEnd();

            glBindTexture(GL_TEXTURE_2D, texplayer);

            glBegin(GL_QUADS);
            glTexCoord2f(1.0,1.0);
            glVertex2f(player[0], player[1]);
            glTexCoord2f(0.0,1.0);
            glVertex2f(player[2], player[3]);
            glTexCoord2f(0.0,0.0);
            glVertex2f(player[4], player[5]);
            glTexCoord2f(1.0,0.0);
            glVertex2f(player[6], player[7]);
            glEnd();

            glBindTexture(GL_TEXTURE_2D, grass);

            glBegin(GL_QUADS);
            glTexCoord2f(10.0,1.0);
            glVertex2f(lineleft[0], lineleft[1]);
            glTexCoord2f(0.0,1.0);
            glVertex2f(lineleft[2], lineleft[3]);
            glTexCoord2f(0.0,0.0);
            glVertex2f(lineleft[4], lineleft[5]);
            glTexCoord2f(10.0,0.0);
            glVertex2f(lineleft[6], lineleft[7]);
            glEnd();

            glBegin(GL_QUADS);
            glTexCoord2f(10.0,1.0);
            glVertex2f(lineright[0], lineright[1]);
            glTexCoord2f(0.0,1.0);
            glVertex2f(lineright[2], lineright[3]);
            glTexCoord2f(0.0,0.0);
            glVertex2f(lineright[4], lineright[5]);
            glTexCoord2f(10.0,0.0);
            glVertex2f(lineright[6], lineright[7]);
            glEnd();

            SDL_GL_SwapWindow(window); //change the empty window, with the drew one.

            field[1]-=x/2; //field's y position decreases each time the loop rotates, this make the obstacles move.
            field[3]-=x/2; //x is an integer, if it's initialized with an odd value, and then divided by 2, it will not work.
            field[5]-=x/2;
            field[7]-=x/2;
            field[9]-=x/2;
            field[11]-=x/2;
            field[13]-=x/2;
            field[15]-=x/2;

            SDL_Delay(speed); //let there be this delay, to make the game run slower, until the lever increases.
            scoremultiplier();
            frontcollision();
            Score=scoreupdate(Score,highscore);
            if(isgameover(window, Score, highscore))
            {
                break;
            }
            collisiondetection();

            texcounter++;
            countermp++;
        }
        input();
    }
}

void p12class::input ()
{
    SDL_Event a;
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
                if(player[0]>150&&paused==false) //if the player is on a x position > than 150
                {
                    player[0]-=15; //modify player's x position (so the player could mode left).
                    player[2]-=15;
                    player[4]-=15;
                    player[6]-=15;
                }
                break; //exit the switch
            }
            case SDLK_RIGHT: //if the right arrow button was pressed
            {
               if(player[0]<350&&paused==false) //if the player is on a x position < than 350
               {
                    player[0]+=15; //modify the player's x position (so the player could move right)
                    player[2]+=15;
                    player[4]+=15;
                    player[6]+=15;
               }
                break; // exit the switch
            }
            case SDLK_m:
            {
                Mix_PauseMusic();
                cout << "Sound muted!" << endl;
                break;
            }
            case SDLK_p:
            {
                cout << "Sound resumed!" << endl;
                playtrack();
                break;
            }
            case SDLK_SPACE:
            {
                if(!paused)
                {
                    cout << "Game Paused!" << endl;
                    paused=true;
                }
                else if(paused)
                {
                    paused=false;
                    cout << "Game Resumed!" << endl;
                }
                break;
            }
        }
    }
}

void p12class::resetcoords()
{
    road[1]=0;
    road[3]=2500;
    road[5]=2500;
    road[7]=0;
    lineleft[1]=0;
    lineleft[3]=2500;
    lineleft[5]=2500;
    lineleft[7]=0;
    lineright[1]=0;
    lineright[3]=2500;
    lineright[5]=2500;
    lineright[7]=0;
}
void p12class::movecoords()
{
    road[1]-=x;
    road[3]-=x;
    road[5]-=x;
    road[7]-=x;
    lineleft[1]-=x;
    lineleft[3]-=x;
    lineleft[5]-=x;
    lineleft[7]-=x;
    lineright[1]-=x;
    lineright[3]-=x;
    lineright[5]-=x;
    lineright[7]-=x;
}
void p12class::fieldrand()
{
    field[0]=((rand()%90)+150); //get another position, in the same way, random on x
    field[1]=550; //y position always on the top.
    field[2]=field[0]+30;
    field[3]=550;
    field[4]=field[2];
    field[5]=500;
    field[6]=field[0];
    field[7]=500;
    field[8]=((rand()%90)+250);
    field[9]=550;
    field[10]=field[8]+30;
    field[11]=550;
    field[12]=field[10];
    field[13]=500;
    field[14]=field[8];
    field[15]=500;
}

void p12class::playtrack()
{
    bool pausecheck=false;
    if(paused==false)
    {
        paused=true;
        pausecheck=true;
    }
    char* filename=nullptr;
    cout << "\nMusic Selector: Press key 1, 2 or 3 to select the music track! "<< endl;
    cout << "Press any other key to skip!" << endl;
    char a;
    cin >> a;
    switch(a)
    {
        case '1': {filename ="t1.wav"; break;}
        case '2': {filename ="t2.wav"; break;}
        case '3': {filename ="t3.wav"; break;}
        default: break;
    }
    if(filename!=nullptr)
    {
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
        Mix_Music* track1=Mix_LoadMUS(filename);
        if(track1==nullptr)
        {
            cerr << "Unable to load the file: " << filename << endl;
        }
        else
        {
            Mix_PlayMusic(track1, -1);
        }
    }
    else
    {
        cout << "Music Selector Skipped!" << endl;
    }
    if(pausecheck==true)
    {
        int countback;
        cout << "Game will resume in: " << endl;
        for(countback=5; countback>=0; countback--)
        {
            cout << countback << endl;
            SDL_Delay(1000);
        }
        paused=false;
    }
}
void p12class::collisiondetection()
{
  if(player[7]<field[1]&&player[1]>field[1])
    {
        if(player[4]>field[0] && player[4]<field[2] || player[4]>field[8] && player[4]<field[10])//260
        {
            multiplier-=productdone;
            productdone=0;
            player[0]-=15;
            player[2]-=15;
            player[4]-=15;
            player[6]-=15;
        }
        if(player[0]<field[2] && player[0]>field[0] || player[0]<field[10] && player[0]>field[8])
        {
            multiplier-=productdone;
            productdone=0;
            player[0]+=15;
            player[2]+=15;
            player[4]+=15;
            player[6]+=15;
        }
    }
}
void p12class::frontcollision()
{
  if(player[1]+(x-1)<=field[1]&&player[1]+(x-1)>=field[7] || player[1]+(x-1)<=field[9]&&player[1]+(x-1)>=field[15]) //if the obstacles are on the same y line with the player
   //player+ (x-1) is there just in case, that x is increased (if x is set greater than 4 collisions won't working).
   {
        if( player[0]>=(field[0]-25) && player[2] <= (field[2]+25) || player[0]>=(field[8]-25) && player[2] <= (field[10]+25))
        {
            if(player[2]+5>field[0]-5 && player[2]+5<field[0]+16 || player[2]+5>field[8]-5 && player[2]+5<field[8]+16)//push left
            //player+5 and field-5 just add there more precision;
            {
                player[0]-=20;
                player[1]-=25;
                player[2]-=20;
                player[3]-=25;
                player[4]-=20;
                player[5]-=25;
                player[6]-=20;
                player[7]-=25;
                multiplier-=productdone;
                productdone=0;
            }
            if(player[2]-5<field[2]+5 && player[2]-5>field[0]+16 || player[2]-5<field[10]+5 && player[2]-5>field[8]+16)//push right
            //player-5 and field+5 just add there more precision;
            {
                player[0]+=20;
                player[1]-=25;
                player[2]+=20;
                player[3]-=25;
                player[4]+=20;
                player[5]-=25;
                player[6]+=20;
                player[7]-=25;
                multiplier-=productdone;
                productdone=0;
            }
        }
    }
}
int p12class::scoreupdate(int Score, int highscore)
{
    if(field[1]<=0) //when the field is no longer on the screen
    {
        fieldrand();
        Score+=(10*multiplier); //if the obstacles run out of the screen, increase the score, because the player wasn't hit.
        system("cls"); //clear the console each time.
        cout << "Score: " << Score << endl; //on the empty console, write the new score.
        cout << "Multiplier: X" << multiplier << endl;
        cout << "Distance to next level: " << distancetolevel*10 << "m" << endl;
        cout << "Factor: " << factor*10 << endl;
        cout << "Level: " << level+1 << "/7" << endl;
        if(highscore<Score) //if the highest score has been defeated
        {
            cout << "Highscore: " << Score << endl; //print the score
        }
        else //let the highscore be printed on the console.
        cout << "Highscore: " << highscore << endl;
    }
    return Score;
}
void p12class::distancetravel()
{
    if(speed<3&&speed>2 || speed<2&&speed>1 || speed<1&&speed>0)
    {
        if(speed==2.5)
        {
            factor=15;
        }
        else if(speed==1.5)
        {
            factor=30;
        }
        else if(speed==0.5)
        {
            factor=60;
        }
    }
    else
    {
        switch(int(speed))
        {
            case 3: {factor=10; break;}
            case 2: {factor=20; break;}
            case 1: {factor=40; break;}
            case 0: {factor=80; break;}
        }
    }
}
int p12class::isgameover(SDL_Window* window, int Score, int highscore)
{
    if(player[1]<=0)
    {
        cout << "Gameover!" << endl;
        distancetolevel=800;
        factor=0;
        level=0;
        multiplier=1;
        speed=3.0;
        productdone=0;
        player[0]=230;
        player[1]=175;
        player[2]=260;
        player[3]=175;
        player[4]=260;
        player[5]=125;
        player[6]=230;
        player[7]=125;
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
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
        return 1;
    }
    return 0;
}
void p12class::pushup()
{
    if(multiplier%10==0) //if multiplier is multiple of 10.
    {
        cout << "In pushup!" << endl;
        if(player[1]<200)
        {
            cout << "Increasing values!" << endl;
            player[1]+=10;
            player[3]+=10;
            player[5]+=10;
            player[7]+=10;
        }
    }
}
void p12class::scoremultiplier()
{
    if(player[1]==field[7])
    {
        if( player[0]>=(field[6]-50) && player[2] <= (field[2]+50) || player[0]>=(field[14]-50) && player[2] <= (field[10]+50))
        //from the distance 50 below until collision for passing a car, increase the multiplier to increase the score.
        {
            countermp=0;
            multiplier++;
            productdone++;
        }
        pushup();
    }
}
