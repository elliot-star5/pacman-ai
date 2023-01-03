#include "LWindow.h"

bool lwindow_init(struct LWindow *self)
{
  // Create window
  self->mWindow = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);

  if (self->mWindow == NULL)
  {
    self->mMouseFocus = true;
    self->mKeyboardFocus = true;
    self->mWidth = SCREEN_WIDTH;
    self->mHeight = SCREEN_HEIGHT;
  }

  // Return window initialization success
  return self->mWindow != NULL;
}


SDL_Renderer *lwindow_createRenderer(struct LWindow *self)
{
  return SDL_CreateRenderer(self->mWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_ACCELERATED);
}


void lwindow_handleEvent(struct LWindow *self, SDL_Event *e)
{
  // Window event occured
  if (e->type == SDL_WINDOWEVENT)
  {
    // Caption update flag
    bool updateCaption = false;

    /*
       Handles each event caused 
       when we do stuff with 
       SDL_Window
       */
    switch (e->window.event)
    {
      // Get new dimenions and repaint on window size change
      case SDL_WINDOWEVENT_SIZE_CHANGED:
        self->mWidth = e->window.data1;
        self->mHeight = e->window.data2;
        SDL_RenderPresent( gRenderer );
        break;

      // Repaint on exposure
      case SDL_WINDOWEVENT_EXPOSED:
        SDL_RenderPresent(gRenderer);
        break;

        // Mouse Entered window
      case SDL_WINDOWEVENT_ENTER:
        self->mMouseFocus = true;
        updateCaption = true;
        break;

        // Mouse left window
      case SDL_WINDOWEVENT_LEAVE:
        self->mMouseFocus = false;
        updateCaption = true;
        break;


        // Window has keyboard focus
      case SDL_WINDOWEVENT_FOCUS_GAINED:
        self->mKeyboardFocus = true;
        updateCaption = true;
        break;

        // Window lost keyboard focus
      case SDL_WINDOWEVENT_FOCUS_LOST:
        self->mKeyboardFocus = false;
        updateCaption = true;
        break;

        // Window minimized
      case SDL_WINDOWEVENT_MINIMIZED:
        self->mMinimized = true;
        break;

        // Window maximized
      case SDL_WINDOWEVENT_MAXIMIZED:
        self->mMinimized = false;
        break;

        // Window restored
      case SDL_WINDOWEVENT_RESTORED:
        self->mMinimized = false;
        break;
    }
  }
  else if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN)
  {
    if (self->mFullScreen)
    {
      SDL_SetWindowFullscreen( self->mWindow, SDL_FALSE );
      self->mFullScreen;
    }
    else
    {
      SDL_SetWindowFullscreen( self->mWindow, SDL_TRUE );
      self->mFullScreen = true;
      self->mMinimized = false;
    }
  }
}

/*
   destroy window
   set state each 
   variable to initiale
   state
   */
void lwindow_free(struct LWindow *self)
{
  if (self->mWindow != NULL)
  {
    SDL_DestroyWindow( self->mWindow );
  }

  self->mMouseFocus = false;
  self->mKeyboardFocus = false;
  self->mWidth = 0;
  self->mHeight = 0;
}


// Gets window width
int lwindow_getWidth(struct LWindow *self)
{
  return self->mWidth;
}

// Gets window height
int lwindow_getHeight(struct LWindow *self)
{
  return self->mHeight;
}

// get mouse focus status
bool lwindow_hasMouseFocus(struct LWindow *self)
{
  return self->mMouseFocus;
}


// Gets keyboard focus status
bool lwindow_hasKeyboardFocus(struct LWindow *self)
{
  return self->mKeyboardFocus;
}

// Gets minimization status
bool lwindow_isMinimized(struct LWindow *self)
{
  return self->mMinimized;
}

// Gets window data
SDL_Window *lwindow_data(struct LWindow *self)
{
  return self->mWindow;
}


