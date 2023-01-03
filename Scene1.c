#include "Scene1.h"

void scene1_init(struct WindowScene* self, struct MainWindow* window)
{
	struct scene1 *scene1_ptr = malloc(sizeof(struct scene1));
	assert(scene1_ptr != NULL);

	// size of struct LTexture
	memset(&scene1_ptr->pacmanImage, 0, sizeof(struct LTexture));
	// load image in memory
	ltexture_loadTextureFromFile(&scene1_ptr->pacmanImage, window, "assets/player.bmp");

	self->private_ptr = scene1_ptr;
	self->handleEvent = scene1_handleEvent;
	self->freeScene = scene1_freeScene;
	self->render = scene1_render;
}

void scene1_freeScene(struct WindowScene* self)
{
	struct scene1 *scene1_ptr = self->private_ptr;
	ltexture_free(&scene1_ptr->pacmanImage);
}

void scene1_render(struct WindowScene* self, struct MainWindow* window)
{
	struct scene1 *scene1_ptr = self->private_ptr;

	SDL_SetRenderDrawColor(window->gRenderer, 0, 0, 0, 0xff);
	SDL_RenderClear(window->gRenderer);
	
	ltexture_render(&scene1_ptr->pacmanImage, window, 0, 0, NULL, 0.0, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(window->gRenderer);
}

void scene1_handleEvent(struct WindowScene* self, struct MainWindow *)
{
	// SDL_Event *e
}
