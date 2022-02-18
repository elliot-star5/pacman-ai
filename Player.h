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


// loads player texture from image
bool player_loadTexture(struct Player *iplayer, char *path)
{
    return ltexture_loadTextureFromFile(&iplayer->playerTexture, path);
}

// set color key for the texture
void player_setColorKey(struct Player* iplayer, Uint8 red, Uint8 green, Uint8 blue)
{
  ltexture_setColorKey(&iplayer->playerTexture, red, green, blue);
}

// frees player texture
void player_freeTexture(struct Player *iplayer)
{
    ltexture_free(&iplayer->playerTexture);
}


// update x and y coordinates of player
void player_setPosition(struct Player* iplayer, struct vector *ivect)
{
    iplayer->mCoordinate.x = ivect->x;
    iplayer->mCoordinate.y = ivect->y;
}

// render player texture
void player_render(struct Player* iplayer)
{
    ltexture_render(&iplayer->playerTexture, iplayer->mCoordinate.x, iplayer->mCoordinate.y, NULL, 0.0, NULL, SDL_FLIP_NONE);
}

// handle events on key SDL_events
void playerhandleEvent(struct Player* iplayer, SDL_Event* e)
{
 // update velocity of 
 // player as per arrow key
  if (e->type == SDL_KEYDOWN && e->key.repeat == 0)
  {
    switch (e->key.keysym.sym)
    {
      case SDLK_UP: 
        iplayer->mVelocity.y -= 5; 
        break;
      case SDLK_DOWN: 
        iplayer->mVelocity.y += 5; 
        break;
      case SDLK_LEFT: 
        iplayer->mVelocity.x -= 5; 
        break;
      case SDLK_RIGHT: 
        iplayer->mVelocity.x += 5;
        break;
    }
  }
  else if (e->type == SDL_KEYUP && e->key.repeat == 0)
  {
    switch (e->key.keysym.sym)
    {
      case SDLK_UP:
        iplayer->mVelocity.y += 5;
        break;

      case SDLK_DOWN:
        iplayer->mVelocity.y -= 5;
        break;

      case SDLK_LEFT:
        iplayer->mVelocity.x += 5;
        break;

      case SDLK_RIGHT:
        iplayer->mVelocity.x -= 5;
        break;
    }
  }
}

// move the player
void player_move(struct Player* iplayer)
{

  iplayer->mCoordinate.x += iplayer->mVelocity.x;
  if (iplayer->mCoordinate.x < 0 || (iplayer->mCoordinate.x + iplayer->playerTexture.mWidth > lwindow_getWidth(&gWindow)))
  {
    iplayer->mCoordinate.x -= iplayer->mVelocity.x;
  }
  
  iplayer->mCoordinate.y += iplayer->mVelocity.y;
  if (iplayer->mCoordinate.y < 0 || (iplayer->mCoordinate.y + iplayer->playerTexture.mHeight > lwindow_getHeight(&gWindow)))
  {
    iplayer->mCoordinate.y -= iplayer->mVelocity.y;
  }
}

void playerSetCamera(struct Player* iplayer, SDL_Rect *camera)
{
  // Set the camera width and height to window
  // dimensions
  camera->w = lwindow_getWidth(&gWindow);
  camera->h = lwindow_getHeight(&gWindow);

  // Center the camera over the Player
  camera->x = (iplayer->mCoordinate.x + iplayer->playerTexture.mWidth / 2) -  camera->w / 2;
  camera->y = (iplayer->mCoordinate.y + iplayer->playerTexture.mHeight / 2) - camera->h / 2;
  

  // Keep the camera in bounds
  if (camera->x < 0)
    camera->x = 0;

  if (camera->y < 0)
    camera->y = 0;

  if (camera->x > LEVEL_WIDTH - camera->w)
    camera->x = LEVEL_WIDTH - camera->w;

  if (camera->x > LEVEL_HEIGHT - camera->h)
    camera->y = LEVEL_HEIGHT - camera->h;
}


#endif
