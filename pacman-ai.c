#include "initrun.h"



// current window instance
struct LWindow gWindow = _LWindow;

// font texture 
TTF_Font *gFont = NULL;

// renderer for rendering texture
SDL_Renderer* gRenderer = NULL;

// texture from image 
struct LTexture gSceneTexture = { 0 };

// our game player 
struct Player gPlayer = {0};

int main(int argc, char **argv)
{
    // initialize SDL
    if (!init())
    {
        printf("Initialization of SDL is Failed\n");
    }
    else if (!loadMedia()) {
        printf("Unable to load Media\n");
    }
    else
    {
        runMainLoop();
    }
    xclose();
}
