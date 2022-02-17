// Using standard library, standard bool, standard IO, SDL, SDL_image..
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "include/global.h"

#include "include/LWindow.h"        /* Window Events */

#include "include/LTexture.h"       /* texture loading */
#include "include/LTimer.h"         /* timer */


// Screen constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 640;
const int SCREEN_FPS = 60;

// LWindow
struct LWindow gWindow = _LWindow;

// TTF_font
TTF_Font *gFont = NULL;

// Renderer
SDL_Renderer* gRenderer = NULL;


// texture
struct LTexture gSceneTexture = _LTexture;


// initialize SDL 
bool init()
{
  // initialization success
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not albe initialize itself SDL_Error: %s\n", SDL_GetError());
  }
  else
  {
    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
      printf("Waning: Linear textur filtering not enabled!");
    }

    // Create window
    if (!lwindow_init(&gWindow))
    {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    }
    else
    {
      // Create renderer for window
      gRenderer = lwindow_createRenderer(&gWindow);
      if (gRenderer == NULL)
      {

        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      }
      else
      {
        // Initialize renderer color
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

        // Initialize Png loading
        int imgFlags = IMG_INIT_PNG;
        if (!IMG_Init(imgFlags) & imgFlags)
        {
          printf("SDL_imge could not initialize! SDL_image Error: %s\n", IMG_GetError());
          success = false;
        }
      }
    }
  }
  return success;
}




// Load media
bool loadMedia()
{

  // Loading success flag
  bool success = true;

  // Load scene texture
  if (!ltexture_loadTextureFromFile(&gSceneTexture, "assets/monster.bmp"))
  {
    printf("Failed to load window texture\n");
    success = false;
  }
  else
  {
    // Set color key from pixels
    ltexture_setColorKey(&gSceneTexture, 0x00, 0xff, 0xff);
  }


  return success;
}


void xclose()
{
  // Free loaded images
  ltexture_free(&gSceneTexture);

  // Destroy window
  SDL_DestroyRenderer(gRenderer);
  lwindow_free(&gWindow);

  // Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

bool collision(SDL_Rect a, SDL_Rect b)
{
  

}


void render()
{

  SDL_Rect rect = { 0, 0, 80, 80 };
  // Clear screen
  SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(gRenderer);


  // Render text textures
  ltexture_render(&gSceneTexture, (lwindow_getWidth(&gWindow) - lwindow_getHeight(&gWindow)) / 2, 
      (lwindow_getHeight(&gWindow) - lwindow_getHeight(&gWindow)) / 2, NULL, 0.0, NULL, SDL_FLIP_NONE);


  // Set draw color to blue
  SDL_SetRenderDrawColor(gRenderer, 0, 0, 0xff, 0xff);

  // Draw a rectangle
  SDL_RenderDrawRect(gRenderer, &rect);

  // Update screen
  SDL_RenderPresent(gRenderer);

}

void runMainLoop()
{
  // Main loop flag
  bool quit = false;

  // SDL Device Events 
  SDL_Event e;

  // Keeps track of time between steps
  struct LTimer stepTimer = _LTimer;

  float timeStep;

  // While application is running
  while (!quit)
  {

    // Handle events in queue
    while( SDL_PollEvent(&e) != 0)
    {
      // User requests quit
      if (e.type == SDL_QUIT)
      {
        quit = true;
      }

      // Handle window events
      lwindow_handleEvent(&gWindow, &e);
    }

   /*
      To prevent occurence of race  condition
      when window change size we don't
      render on screen
    */
    if (!lwindow_isMinimized(&gWindow))
    {
      // Get Ticks of timer
      timeStep = ltimer_getTicks(&stepTimer) / 1000.f;

      // Restart step timer
      ltimer_start(&stepTimer);

      render();
    }

  }
}

int main()
{
  // Initialize SDL ..etc
  if (!init())
  {
    printf("Failed to initialize SDL\n");
  }
  else 
  {
    // Load media
    if (!loadMedia())
    {
      printf("Failed to load media\n");
    }
    else
    {
      // Run application main loop
      runMainLoop();
    }
  }

  // deallocates stuff
  xclose();

  return 0;
}
