#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_ 1
#include "include/global.h"

// #include "include/LTexture.h"
struct MainWindow {
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
};

bool init(struct MainWindow *);
void xclose(struct MainWindow *);
void runMainLoop(struct MainWindow *);
#endif
