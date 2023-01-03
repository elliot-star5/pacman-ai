#ifndef SCENE_1
#define SCENE_1 1
#include "include/LTexture.h"
#include "WindowScene.h"

struct scene1 {
	struct LTexture pacmanImage;
};

void scene1_init(struct WindowScene*, struct MainWindow*);
void scene1_handleEvent(struct WindowScene*, struct MainWindow*);
void scene1_freeScene(struct WindowScene* self);

void scene1_render(struct WindowScene*, struct MainWindow*);
#endif
