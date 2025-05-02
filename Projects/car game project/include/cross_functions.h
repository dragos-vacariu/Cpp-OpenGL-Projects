#ifndef CROSS_FUNCTIONS_H
#define CROSS_FUNCTIONS_H

//Custom Libraries Includes:
#include <SDL.h>
#include <glew.h>
#include <stdlib.h>
#include <stdio.h>
#include <SOIL.h>
#include <SDL_mixer.h>

//Built-in Libraries Includes:
#include <array>
#include <string>
#include <sstream> //used for stringstream
#include <conio.h>
#include <iostream>
#include <vector>
#include <algorithm> //used for find();
#include <iomanip> // for setprecision
#include <iostream>
#include <cfloat>
#include <cmath> // for drawing curves
#include <fstream>
#include <memory> //used for unique_ptr

//Custom Libraries Includes:
#include <SDL_ttf.h>

//CONSTANT DEFINES:
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

#define RESOURCES_DIRECTORY_FILEPATH "./resources"
#define SAVEGAME_DIRECTORY_FILEPATH "/savegame"

//Concatenating path with inner directories
#define AUDIO_RESOURCES RESOURCES_DIRECTORY_FILEPATH "/audio"
#define IMG_RESOURCES RESOURCES_DIRECTORY_FILEPATH "/img"

//Concatenating inner directories with files
#define ROAD_TEXTURE IMG_RESOURCES "/road_texture.png"
#define WORLD_TEXTURE IMG_RESOURCES "/world_texture.png"

//Concatenating inner directories with files
#define SAVEGAME RESOURCES_DIRECTORY_FILEPATH SAVEGAME_DIRECTORY_FILEPATH "/game.sav"


/*enum vs enum class

enum:
Scope: The enumerator names (Red, Green, Blue) are placed in the surrounding scope. That means you
can refer to Red directly without qualification.

Implicit conversions: The enum values implicitly convert to integers.

---------------------------------------------------------------------------------------------

enum class:
Introduced in C++ 11 ISO;
Scope: The enumerator names are scoped within the enum class. You access them with Color::Red, Color::Green, etc.

No implicit conversions: Enum class values do not implicitly convert to integers, which
improves type safety. You must explicitly cast if needed:
*/

enum class ScoreEvent
{
    /*The enumeration constants (like Collision, Overtake) are not implicitly convertible to integers.
    The values (10, -1, -5) are integers, but the enum constants are not integers directly; they are strongly typed.

    The operator+= for unsigned int does not accept a ScoreEvent directly because no implicit conversion exists
    from ScoreEvent to unsigned int.

    in order to extract the actual value from the enumeration constants use:
    static_cast<int>(ScoreEvent::Collision);
    */
    Overtake = 10,
    Overtaken = -1,
    Collision = -5
};

//Public Variables:
extern GLuint load_texture(const char* filename);
extern unsigned int Score;
extern unsigned int HighScore;
extern float Damage;


#endif // CROSS_FUNCTIONS_H
