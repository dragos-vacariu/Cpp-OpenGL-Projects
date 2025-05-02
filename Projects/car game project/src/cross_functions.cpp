#include "../include/cross_functions.h"

using namespace std;

//Common variables:
unsigned int Score;
unsigned int HighScore;
float Damage;

//Common functions to be called across the modules:
GLuint load_texture(const char* filename)
{
    int width, height;
    unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

    if(image == nullptr)
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
