
#ifndef __GLOBAL_H_
#define __GLOBAL_H_

// Game name 
#define GAME_NAME "Pacman-ai"

// Screen constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 640
#define SCREEN_FPS 60

// The dimensions of the level
#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 960


extern TTF_Font *gFont;
extern SDL_Renderer *gRenderer;
extern struct LWindow gWindow;
extern struct LTexture gSceneTexture;

extern struct Player gPlayer;
extern struct wall gWall;


#endif
