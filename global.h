
#ifndef __GLOBAL_H_
#define __GLOBAL_H_

// Game name 
#define GAME_NAME "Pacman-ai"

// included from some where else
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_FPS;


extern TTF_Font *gFont;
extern SDL_Renderer *gRenderer;
extern struct LWindow gWindow;
extern struct LTexture gSceneTexture;

extern struct Player gPlayer;
extern struct wall gWall;


#endif
