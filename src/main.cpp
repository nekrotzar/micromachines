#include "Init.h"

int main(int argc, char ** argv)
{
    setupGLUT(argc, argv);
    setupCallbacks();
    setupGLEW();
    
    microMachines = new MicroMachines();
    glutMainLoop();
    delete microMachines;
    
    return EXIT_SUCCESS;
}
