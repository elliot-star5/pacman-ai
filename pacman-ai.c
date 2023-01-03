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
        runMainLoop();

    xclose();
}
