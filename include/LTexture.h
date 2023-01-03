#ifndef __LTexture_H_
#define __LTexture_H_


/* 
texture loading 
wrapper struct 
 */
struct LTexture
{
  // the actual hardware texture
  SDL_Texture* mTexture;

  // Image dimensions
  int mWidth;
  int mHeight;

  void *mPixels;
  int mPitch;

};

/*
   Load texture from file supplied as argument
   checks for success of loading image with success flag
   loads image 
        
   */

bool ltexture_loadTextureFromFile(struct LTexture *, char *);


/*
   load Rendered text
   from file
   */
//bool ltexture_loadFromRenderedText(struct LTexture *, char*, SDL_Color);


/*
   sets blendmode for given texture 
*/
void ltexture_setBlendMode(struct LTexture *, SDL_BlendMode);

/*
   sets rgb color key for given texture
   */
void ltexture_setColor(struct LTexture *, Uint8, Uint8, Uint8);


/*
   sets alpha mode for given texture
   as supplied in argument 
*/
void ltexture_setAlpha(struct LTexture *, Uint8);


/*
   draw texture from image
   on buffer
   */
bool ltexture_render(struct LTexture *, int, int, SDL_Rect *, double, SDL_Point *, SDL_RendererFlip);

/*
   frees texture
   related stuff
   from memory and
   cleanit up
   */
void ltexture_free(struct LTexture *);

// Gets image dimensions
int ltexture_getWidth(struct LTexture *);
int ltexture_getHeight(struct LTexture *);


// Pixel manipulators
bool ltexture_lockTexture(struct LTexture *);
bool ltexture_unlockTexture(struct LTexture *);
void* ltexture_getPixels(struct LTexture *);
int ltexture_getPitch(struct LTexture *);

// Set colorkey from loadedpixels
void ltexture_setColorKey(struct LTexture *, Uint8, Uint8, Uint8);

#endif
