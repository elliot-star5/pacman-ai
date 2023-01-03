#ifndef _WALL_H_
#define _WALL_H_ 1

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
  int mType;
};
#endif
