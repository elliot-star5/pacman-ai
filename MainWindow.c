#include "MainWindow.h"
#include "WindowScene.h"
#include "Scene1.h"

void runMainLoop(struct MainWindow *self) {
	SDL_Event e;
	bool quit = false;
	struct WindowScene scene = { 
		.initScene = scene1_init // initialize with scene 1
	};		
	
	
						// we load data for scene
						// and thand change methods
						// according to the scene
						// somewhat like linux file system

	scene.initScene(&scene, self);
	while (!quit)
	{
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
			else
				scene.handleEvent(&scene, self);

		}
		scene.render(&scene, self);
	}
}

