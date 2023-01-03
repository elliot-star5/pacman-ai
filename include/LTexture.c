#include "LTexture.c"

bool ltexture_loadTextureFromFile(struct LTexture *self, char *path)
{
	//Get rid of preexisting texture
	ltexture_free(self);

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
	}
	else
	{
        // Convert surface to display format
        SDL_Surface *formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_GetWindowPixelFormat(lwindow_data(&gWindow)), 0);
        if (formattedSurface == NULL)
        {
          printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
          // Create blank streamable texture
          newTexture = SDL_CreateTexture(gRenderer, SDL_GetWindowPixelFormat(lwindow_data(&gWindow)), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
          if (newTexture == NULL)
          {

            printf("Unable to create blank texture! SDL_Error: %s\n", SDL_GetError());
          }
          else
          {
            // Lock texture for manipulation
            SDL_LockTexture(newTexture, NULL, &self->mPixels, &self->mPitch);

            // Copy loadeed/formattedSurface
            memcpy(self->mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

            // Unlock texture to update
            SDL_UnlockTexture(newTexture);
            self->mPixels = NULL;

			//Get image dimensions
			self->mWidth = loadedSurface->w;
			self->mHeight = loadedSurface->h;
          }

          //Get rid of old loaded surface
          SDL_FreeSurface( formattedSurface );
        }

        SDL_FreeSurface(loadedSurface);
    }
	//Return success
	self->mTexture = newTexture;
	return self->mTexture != NULL;
}




bool ltexture_loadFromRenderedText(struct LTexture *self, char *textureText, SDL_Color textColor)
{
  // Get rid of preexisting texture
  ltexture_free(self);

  // Render texture surface
  SDL_Surface* textureSurface = TTF_RenderText_Solid(gFont, textureText, textColor);
  if (textureSurface != NULL)
  {
    // Create texture from surface
    SDL_Texture *loadedTexture = SDL_CreateTextureFromSurface(gRenderer, textureSurface);

    if (loadedTexture == NULL)
    {
      printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
      // Get image dimensions
      self->mWidth = textureSurface->w;
      self->mHeight = textureSurface->h;
    }

    // get rid of old surface
    SDL_FreeSurface(textureSurface);
  }
  else
  {
    printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
  }

  // Return surface
  return self->mTexture != NULL;
}


void ltexture_free(struct LTexture *self)
{
  // Free texture if it exists
  if (self->mTexture != NULL)
  {
    SDL_DestroyTexture(self->mTexture);
    self->mTexture = NULL;
    self->mWidth = 0;
    self->mHeight = 0;
    self->mPixels = NULL;
    self->mPitch = 0;
  }
}

void ltexture_setColor(struct LTexture *self, Uint8 red, Uint8 green, Uint8 blue)
{
  // Modulate texture rgb
  SDL_SetTextureColorMod(self->mTexture, red, green, blue);
}


void ltexture_setBlendMode(struct LTexture *self, SDL_BlendMode blending)
{
  // Set blending functions
  SDL_SetTextureBlendMode(self->mTexture, blending);
}


void ltexture_setAlpha(struct LTexture *self, Uint8 alpha)
{
  // Modulate texture alpha
  SDL_SetTextureAlphaMod(self->mTexture, alpha);
}



bool ltexture_render(struct LTexture *self, int x, int y, SDL_Rect* clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
  // Set rendering space and render to screen
  SDL_Rect renderQuad = { x, y, self->mWidth, self->mHeight };

  // Set clip rendering dimensions
  if (clip != NULL)
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  // Render to screen
  SDL_RenderCopyEx(gRenderer, self->mTexture, clip, &renderQuad, angle, center, flip);
}



int ltexture_getWidth(struct LTexture *self)
{
  return self->mWidth;
}


int ltexture_getHeight(struct LTexture *self)
{
  return self->mHeight;
}


bool ltexture_lockTexture(struct LTexture *self)
{
  bool success = true;

  // Texture is already locked
  if (self->mPixels != NULL)
  {
    printf("Texture is already locked!\n");
    success = false;
  }
  // Lock texture
  else
  {
    if (SDL_LockTexture(self->mTexture, NULL, &self->mPixels, &self->mPitch) != 0)
    {
      printf("Unable to load texture! %s\n", SDL_GetError());
      success = false;
    }
  }
  return success;
}


bool ltexture_unlockTexture(struct LTexture *self)
{
  bool success = true;

  // Texture is not locked
  if (self->mPixels == NULL)
  {
    printf("Unable to lock texture! %s\n", SDL_GetError());
    success = false;
  }
  else
  {
    SDL_UnlockTexture(self->mTexture);
    self->mPixels = NULL;
    self->mPitch = 0;
  }

  return success;
}

void* ltexture_getPixels(struct LTexture *self)
{
  return self->mPixels;
}

int ltexture_getPitch(struct LTexture *self)
{
  return self->mPitch;
}


void ltexture_setColorKey(struct LTexture *self, Uint8 red, Uint8 green, Uint8 blue)
{
  if (!ltexture_lockTexture(self))
  {
    printf("Unable to lock gSceneTexture!\n");
  }
  else
  {
    //Allocate format from window
    Uint32 format = SDL_GetWindowPixelFormat( lwindow_data(&gWindow));
    SDL_PixelFormat* mappingFormat = SDL_AllocFormat( format );

    //Get pixel data
    Uint32* pixels = (Uint32*)ltexture_getPixels(self);
    int pixelCount = ( ltexture_getPitch(self) / 4 ) * ltexture_getHeight(self);

    //Map colors
    Uint32 colorKey = SDL_MapRGB( mappingFormat, red, green, blue);
    Uint32 transparent = SDL_MapRGBA( mappingFormat, 0xFF, 0xFF, 0xFF, 0x00 );

    //Color key pixels
    for( int i = 0; i < pixelCount; ++i )
    {
        if( pixels[ i ] == colorKey )
        {
            pixels[ i ] = transparent;
        }
    }

    //Unlock texture
    ltexture_unlockTexture(self);

    //Free format
    SDL_FreeFormat( mappingFormat );
  }
}
