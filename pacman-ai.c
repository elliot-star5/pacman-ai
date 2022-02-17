#include "initrun.h"

// Screen constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 640;
const int SCREEN_FPS = 60;


// current window instance
struct LWindow gWindow = _LWindow;

// font texture 
TTF_Font *gFont = NULL;

// renderer for rendering texture
SDL_Renderer* gRenderer = NULL;

// texture from image 
struct LTexture gSceneTexture = _LTexture;

