#ifndef Game_h
#define Game_h

#include <iostream>
#include <sstream>

#include <GL/glew.h>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

#include "MicroMachines.h"

#define CAPTION "MicroMachines"

MicroMachines * microMachines;

int WinX = 640, WinY = 480;
int WindowHandle = 0;

unsigned int FrameCount = 0;

void init();
void setupGLUT(int argc, char ** argv);
void setupCallbacks();
void setupGLEW();
GLuint setupShaders();

void timer(int value);
void refresh(int value);
void renderScene();
void resize(int width, int height);
void processKeys(unsigned char key, int xx, int yy);
void processMouseButtons(int buttons, int state, int xx, int yy);
void processMouseMotion(int xx, int yy);
void processMouseWheel(int wheel, int direction, int x, int y);

#endif /* Game_h */
