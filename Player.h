#ifndef __PLAYER_H
#define __PLAYER_H

struct vector
{
    float x, y;
};

struct Player
{
    // player coordinates
    struct vector player_coord;

    // store players texture
    struct LTexture playerTexture;
};


// loads player texture from image
bool player_loadTexture(struct Player *iplayer, char *path)
{
    return ltexture_loadTextureFromFile(&iplayer->playerTexture, path);
}

// frees player texture
void player_freeTexture(struct Player *iplayer)
{
    ltexture_free(&iplayer->playerTexture);
}


// update x and y coordinates of player
void player_setPosition(struct Player* iplayer, struct vector *ivect)
{
    iplayer->player_coord.x = ivect->x;
    iplayer->player_coord.y = ivect->y;
}

// render player texture
void player_render(struct Player* iplayer)
{
    ltexture_render(&iplayer->playerTexture, iplayer->player_coord.x, iplayer->player_coord.y, NULL, 0.0, NULL, SDL_FLIP_NONE);
}

#endif
