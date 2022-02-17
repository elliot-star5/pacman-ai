
# compile without debugging
all:
	gcc pacman-ai.c -I/usr/local/include/SDL2 -D_REENTRANT -L/usr/local/lib -Wl,-rpath,/usr/local/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2_image -lSDL2_ttf -lm -o game.out; ./game.out

# for debugging 
debug:
	gcc pacman-ai.c -I/usr/local/include/SDL2 -D_REENTRANT -L/usr/local/lib -Wl,-rpath,/usr/local/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2_image -lSDL2_ttf -lm -g -o game.out; 
	gdb -q -ex "break main" -ex "run" ./game.out;

# remove stuff
clean:
	rm -rf game.out
