
# compile without debugging
all:
	gcc pacman-ai.c  MainWindow.c Scene1.c include/LTexture.c `sdl2-config --cflags --libs` -lSDL2_image -lm -o game.out; ./game.out

# for debugging 
debug:
	gcc pacman-ai.c  MainWindow.c include/LTexture.c `sdl2-config --cflags --libs` -lSDL2_image -lm -g -o game.out;  
	gdb -q -ex "break main" -ex "run" ./game.out;

# remove stuff
clean:
	rm -rf game.out
