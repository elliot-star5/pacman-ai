#ifndef __PLAYER_H
#define __PLAYER_H

struct vector
{
    int x, y;
};

// The player will move around on the 
// screen
struct Player
{
    // player coordinates
    struct vector mCoordinate;
    // Player Velocity
    struct vector mVelocity;

    // store players texture
    struct LTexture playerTexture;

    // Collision box of the Player
    SDL_Rect mBox;
};


bool player_loadTexture(struct Player *iplayer, char *path);
void player_setColorKey(struct Player* iplayer, Uint8 red, Uint8 green, Uint8 blue);
void player_freeTexture(struct Player *iplayer);
void player_setPosition(struct Player* iplayer, struct vector *ivect);
void player_render(struct Player* iplayer);
void playerhandleEvent(struct Player* iplayer, SDL_Event* e);
void player_move(struct Player* iplayer);
void playerSetCamera(struct Player* iplayer, SDL_Rect *camera);

#endif
