#include "../include/text_label.h"

//Initializing the static fields outside of the class as required by C++ ISO
bool text_label::ttf_initialized = false;

text_label::text_label(SDL_Window* window, int font_size)
{
    //ctor
    if(ttf_initialized == false)
    {
        if (TTF_Init() == -1)
        {
            SDL_Log("Failed to initialize TTF: %s", TTF_GetError());
        }
        else
        {
            ttf_initialized = true;
            SDL_Log("TTF initialized successfully");
        }
        ttf_initialized = true;
    }

    this->HUD_font = TTF_OpenFont("./resources/fonts/FjallaOne-Regular.ttf", font_size);
    if (this->HUD_font == nullptr) //equivalent to !font
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }
}

text_label::~text_label()
{
    //dtor
    //Cleaning up the resources used through the pointers
    //delete this->HUD_font;
    //delete this->textSurface;
}

void text_label::Update_Text(const char* text, SDL_Color color, int x_position, int y_position)
{
    /*Function that will create a text surface/texture with the given text and will render it to the screen*/

    /*
    STEP1: Render text to an SDL_Surface (with system-native pixel format)

    TTF_RenderText_Blended creates an SDL surface with whatever pixel format SDL deems fit,
    which is not guaranteed to be RGBA32 — it could be ARGB or some other layout.
    */
    this->textSurface = TTF_RenderText_Blended(this->HUD_font, text, color);

    /*
    STEP2: Convert the surface to a known RGBA format for OpenGL

    Converting from TTF Surface to SDL Surface
    SDL_ConvertSurfaceFormat takes that surface and rebuilds it with pixels in a guaranteed RGBA32 format,
    ensuring OpenGL will interpret the pixel data correctly when you call glTexImage2D.
    */

    this->textSurface = SDL_ConvertSurfaceFormat(this->textSurface, SDL_PIXELFORMAT_RGBA32, 0);


    //Basic error check to ensure the surface was created.
    if (this->textSurface == nullptr) //equivalent to !textSurface
    {
        SDL_Log("Failed to render text surface: %s", TTF_GetError());
    }

    /*Converting SDL Surface to OpenGL Texture*/
    glGenTextures(1, &this->textTexture); //generate a texture and store it into this->textTexture

    //telling OpenGL that the texture we generated is to be interpreted as 2D texture
    //from now on if we operate on the texture it will be this->textTexture until we glBindTexture with something else.
    glBindTexture(GL_TEXTURE_2D, this->textTexture);

    //storing the width and height required to draw the texture. This will be taken out of the SDL_Surface used for
    //generating the OpenGL texture
    this->textHeight = textSurface->h;
    this->textWidth = textSurface->w;

    /*Telling OpenGL how to align pixel rows in memory.
    1 means no alignment padding
    (required for non-multiple-of-4 widths in pixel data).*/
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //STEP4: Uploading the surface's pixels into the texture
    //This will send the image data from the surface to the GPU.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->textWidth, this->textHeight, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, this->textSurface->pixels);


    //STEP 5: Set texture filtering (smooth scaling)
    //This will control how the texture is scaled (for example, if resized on screen).
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Cleanup the SDL_Surface as it's no longer needed
    SDL_FreeSurface(this->textSurface);


    /*Render the text texture to the screen
    Activates 2D texturing and binds the text texture for drawing.
    */
    glEnable(GL_TEXTURE_2D);

    /*
    From now on, any texture-related operations (uploading, drawing, setting parameters)
    will apply to this texture ID.
    */
    glBindTexture(GL_TEXTURE_2D, this->textTexture);

    /*
    The modelview matrix defines where the object is located in 3D space and how it’s oriented.
    The projection matrix defines how the 3D world is projected onto the 2D screen.
    */

    // Set orthographic projection for 2D overlay

    /*
     I'm saving the object that are on the screen, with their own transformations, scaling and rotation,
     then I add the new object which I may or may not rotate, or scale explicitly, but by adding it to the screen
     I affect its transformation, which is also part of that matrix, and to ensure that the other object are
     not affected by this new object added, we have to glPushMatrix()

    Scenario:
    Imagine you're rendering two objects:

    Object A: Needs to be drawn at position (0, 0), with no rotation and no scaling.
    Object B: Needs to be drawn at position (2, 2), with a rotation or scaling applied.

    Without glPushMatrix() and glPopMatrix(), any transformation you apply (such as a translation, rotation,
    or scaling) will affect both objects, because OpenGL uses a single transformation matrix that is modified globally.
    */
    glMatrixMode(GL_PROJECTION); // switches to the projection matrix.
    glPushMatrix(); //saves the current GL_PROJECTION transformation matrix

    /*
    glLoadIdentity() is a function used to reset the current matrix (either the modelview matrix or projection
    matrix, depending on the current matrix mode) to the identity matrix. The identity matrix is a special
    matrix that represents no transformation (i.e., no translation, no rotation, no scaling).
    */
    glLoadIdentity(); //clearing out any previous transformations and resetting the matrix to its default state.
    glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);  // 2D mode

    glMatrixMode(GL_MODELVIEW); // switches to the model/view matrix.
    glPushMatrix(); //saves the current GL_MODELVIEW transformation matrix
    glLoadIdentity(); //clearing out any previous transformations and resetting the matrix to its default state.

    /*
    If you don't call glLoadIdentity() and don't reset the matrix between drawing objects, the transformations
    from previous objects will accumulate and affect the new objects you're drawing

    NOTE: If you're drawing the first object in a fresh window context (i.e., right after you start your OpenGL
    program, where no transformations have been applied yet), omitting the glLoadIdentity() and
    glPushMatrix()/glPopMatrix() calls won't have any immediate impact.
    */

    /*
    OpenGL maintains an internal matrix stack. When you call glPushMatrix(), it:

    Copies the current transformation matrix (e.g., modelview or projection) and pushes it
    onto a stack.

    This lets you temporarily modify the matrix (like translate, rotate, scale) for specific
    objects without affecting the rest of your scene.

    Then, later on, when you call glPopMatrix(), it:

    Restores the matrix that was on the top of the stack — as if you never made the temporary changes.
    */

    // Draw the textured quad (top-left of screen)
    glBegin(GL_QUADS);

    //Define Texture Coordinates:
    glTexCoord2f(0.0, 0.0); //maps to the bottom-left corner of the texture.
    glVertex2f(x_position, y_position); //this vertex will position the bottom-left corner of the texture

    glTexCoord2f(1.0, 0.0); //maps to the bottom-right corner.
    glVertex2f(x_position + this->textWidth, y_position); //this vertex will position the bottom-right corner of the texture

    glTexCoord2f(1.0, 1.0); //maps to the top-right corner.
    glVertex2f(x_position + this->textWidth, y_position + this->textHeight); //this vertex will position the top-left corner of the texture

    glTexCoord2f(0.0, 1.0); //maps to the top-left corner.
    glVertex2f(x_position, y_position + this->textHeight); //this vertex will position the top-left corner of the texture

    glEnd(); //Vertices were drawn now combine and render:
    //Quad was drawn


    //Restore the Previous OpenGL State

    /*
    The glPopMatrix() function removes the most recent matrix from the matrix stack. It’s like “popping” a matrix off the stack,
    so you return to the previous matrix that was there before the last one was pushed.
    */
    glPopMatrix(); // removing the last matrix from the stack for GL_MODELVIEW

    /*
    Switching the matrix mode to GL_PROJECTION.
    GL_MODELVIEW: is the matrix for modeling and viewing transformations (translation, rotation, scaling, etc.).
    */
    glMatrixMode(GL_PROJECTION); //changing matrices to GL_PROJECTION
    glPopMatrix(); // removing the last matrix from the stack for GL_PROJECTION

    /*
    Switching the matrix mode to GL_PROJECTION.
    GL_PROJECTION: This matrix is used to define the projection (such as perspective or orthogonal projection)
    that determines how 3D objects are mapped onto the 2D screen.
    */
    glMatrixMode(GL_MODELVIEW); //now the most current matrix is on top and we will draw it
}
