#include "Wall.h"

// Initilize position and type of a tile
void 
init_tile(struct wall *self, int x, int y, int tileType)
{
  // Get the offsets
  self->mBox.x = x;
  self->mBox.y = y;

  // Set the collision box
  self->mBox.w = TILE_WIDTH;
  self->mBox.h = TILE_HEIGHT;

  // Get the tile type 
  self->mType = tileType;
}


// Renders tile on renderer
void wall_render(struct wall* self, struct LTexture *fTexture, SDL_Rect *camera)
{
  if (checkCollision(camera, &self->mBox))
  {
    // Show the tile
    ltexture_render(fTexture, self->mBox.x - camera->x, self->mBox.y - camera->y, &self->gwallClips[self->mType], 0.0, NULL, SDL_FLIP_NONE);
  }
}

// returns type of the tile
int wall_getType(struct wall* self)
{
  return self->mType;
}

// returns pointer to the box
SDL_Rect* wall_getBox(struct wall *self)
{
  return &self->mBox;
}


