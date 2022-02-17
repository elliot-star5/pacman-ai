#include "initrun.h"
#include "include/global.h"


// Screen constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 640;
const int SCREEN_FPS = 60;



int main(int argc, char **argv)
{
    // initialize SDL
    if (!init())
    {
        printf("Initialization of SDL is Failed\n");
    }
    else if (!loadMedia()) {
        printf("Unable to load Media\n");
    }
    else
    {
        runMainLoop();
    }
    xclose();
}
