#define TILE_WIDTH            80
#define TILE_HEIGHT           80
#define TOTAL_TILES           192
#define TOTAL_TILE_SPRITES    12


enum {
  TILE_RED,
  TILE_GREEN,
  TILE_BLUE,
  TILE_CENTER,
  TILE_TOP,
  TILE_TOPRIGHT,
  TILE_RIGHT,
  TILE_BOTTOMRIGHT,
  TILE_BOTTOM,
  TILE_BOTTOMLEFT,
  TILE_LEFT,
  TILE_TOPLEFT

} TILE_TYPE;

struct wall
{
  // The attribute of the tile
  SDL_Rect mBox;

  // the tile type
  TILE_TYPE mType;
};



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
    ltexture_render(fTexture, self->mBox.x - camera->x, self->mBox.y - camera->y, &self->gwallClips[self->mType], NULL, 0.0, NULL, SDL_FLIP_NONE);
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


