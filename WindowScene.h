#ifndef _WINDOW_SCENE_H_
#define _WINDOW_SCENE_H_ 1

struct WindowScene 
{
	void *private_ptr;				// a private pointer that stores memory
							//
	void (*initScene)(struct WindowScene*, struct MainWindow*);
	void (*freeScene)(struct WindowScene*);

	void (*handleEvent)(struct WindowScene*, struct MainWindow*);
	void (*render)(struct WindowScene*, struct MainWindow*);
};

#endif
