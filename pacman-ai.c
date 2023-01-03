#include "include/global.h"
#include "MainWindow.h"
#include "include/LTexture.h"


bool init(struct MainWindow* self)
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Unable to Initialize SDL %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		self->gWindow = SDL_CreateWindow(
					GAME_NAME, 
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					SCREEN_WIDTH, 
					SCREEN_HEIGHT, 
					SDL_WINDOW_SHOWN
				);
		if (self->gWindow == NULL)
		{
			printf("Unable to Initialize window SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			self->gRenderer = SDL_CreateRenderer(self->gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (self->gRenderer == NULL)
			{
				printf("Unable to Initialize Renderer SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				int pngflag = IMG_INIT_PNG;
				if (!(IMG_Init(pngflag) & pngflag))
				{
					printf("Error SDL2_image Initialization");
					success = false;
				}
			}
		}
	}
	return success;
}

void xclose(struct MainWindow* self) 
{

}


int main(int argc, char **argv)
{
	struct MainWindow winfo;

	// initialize SDL
	if (!init(&winfo))
		printf("Initialization of SDL is Failed\n");
	else
		runMainLoop(&winfo);
	xclose(&winfo);
	return 0;
}

