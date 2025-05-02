#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

#include "../include/cross_functions.h"

using namespace std;

class text_label
{
    public:
        text_label(SDL_Window* window, int font_size);
        virtual ~text_label();

        //Public methods:
        void Update_Text(const char* text, SDL_Color color, int x_position, int y_position);

        //Public fields/variables:

    protected:

    private:
        //Private fields/variables
        TTF_Font* HUD_font;
        SDL_Surface* textSurface;
        GLuint textTexture;
        int textHeight, textWidth;

        static bool ttf_initialized;
};

#endif // HUD_TEXT_H
