#define TILE_WIDTH
#define TILE_HEIGHT

struct Tile
{
  // The attribute of the tile
  SDL_Rect mBox;

  // the tile type
  int mType;
};

// Initilize position and type of a tile
void 
init_tile(struct Tile *self, int x, int y, int tileType)
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
void tile_render(struct Tile* self, struct LTexture *fTexture, SDL_Rect *camera)
{
  if (checkCollision(camera, &self->mBox))
  {
    // Show the tile
    ltexture_render(fTexture, self->mBox.x - camera->x, self->mBox.y - camera->y, &self->gTileClips[self->mType], NULL, 0.0, NULL, SDL_FLIP_NONE);
  }
}

// returns type of the tile
int tile_getType(struct Tile* self)
{
  return self->mType;
}

// returns copy of the current box
SDL_Rect tile_getBox(struct Tile *self)
{
  return self->mBox;
}
