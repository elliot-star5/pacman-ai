#ifndef __INIT_RUN_H
#define __INIT_RUN_H 1

// Using standard library, standard bool, standard IO, SDL, SDL_image..
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "global.h"
#include "include/LWindow.h"        /* Window Events */

#include "include/LTexture.h"       /* texture loading */
#include "include/LTimer.h"         /* timer */
#include "Player.h"


/*                                
 *        ^                      ^ topB
 *   topA |                      |  
 *      ----------            ----------
 *      |        |rightA      |        |
 * leftA| box A  |--->        | box B  |---->rightB
 *  <---|        |        <---|        |
 *      ----------      leftB ----------
 *         |bottomA               | bottomB
 *         v                      v
 *
 *         four conditions:
 *         bottomA <= topB then it's outside of B
 *         topA >= bottomB then it's outside of B
 *         rightA <= leftB then it's outside of B
 *         leftA >= rightB then it's outside of B
 */

bool collision(const SDL_Rect* a, const SDL_Rect* b)
{
  // the sides of rectangle
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA,  bottomB;

  // if any of the side from A are outside of B
  if (bottomA <= topB)
    return false;

  if (topA >= bottomB)
    return false;

  if (rightA <= leftB)
    return false;

  if (leftA >= rightB)
    return false;

  // if None of the sides from A are outside B
  return true;
}



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

  if (!player_loadTexture(&gPlayer, "assets/player.bmp"))
  {
    printf("Failed to load player texture\n");
    success = false;
  }
  else
  {
    player_setColorKey(&gPlayer, 0x00, 0x00, 0x00);
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

void render()
{
  // gets center of window
  int win_center = (lwindow_getWidth(&gWindow) - lwindow_getHeight(&gWindow)) / 2;

  SDL_Rect rect = { 0, 0, 80, 80 };
  // Clear screen
  SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(gRenderer);


  // Render text textures
  ltexture_render(&gSceneTexture, win_center, win_center, NULL, 0.0, NULL, SDL_FLIP_NONE);

  player_move(&gPlayer);
  player_render(&gPlayer);

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

      // handle Player events
      playerhandleEvent(&gPlayer, &e);
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

#endif
