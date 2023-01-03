
#ifndef __LWindow_H_
#define __LWindow_H_

#include "global.h"

// Window initialization defination
#define _LWindow {            \
  .mWindow = NULL,            \
  .mWidth = SCREEN_WIDTH,     \
  .mHeight = SCREEN_HEIGHT,   \
  .mMouseFocus = false,       \
  .mKeyboardFocus = false,    \
  .mFullScreen = false,       \
  .mMinimized = false,        \
} 

// Window wrapper struct
struct LWindow
{
  // Window data
  SDL_Window *mWindow;

  // Window dimensions
  int mWidth;
  int mHeight;

  // Window focus
  bool mMouseFocus;
  bool mKeyboardFocus;
  bool mFullScreen;
  bool mMinimized;

};


// Creates window
bool lwindow_init(struct LWindow *);

// Creates renderer from internal window
SDL_Renderer *lwindow_createRenderer(struct LWindow *);

// Handles window events
void lwindow_handleEvent(struct LWindow *, SDL_Event *);

// Deallocate internals
void lwindow_free(struct LWindow *);

// Window dimensions
int lwindow_getWidth(struct LWindow *);
int lwindow_getHeight(struct LWindow *);

// Window focii
bool lwindow_hasMouseFocus(struct LWindow *);
bool lwindow_hasKeyboardFocus(struct LWindow *);
bool lwindow_isMinimized(struct LWindow *);


// Gets window data
SDL_Window *lwindow_data(struct LWindow *);



#endif
