#ifndef Init_h
#define Init_h

#include <iostream>
#include <sstream>

#include <GL/glew.h>

#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "MicroMachines.h"

#define CAPTION "MicroMachines"

// Game variable
MicroMachines * microMachines;

// Window size
int WinX = 900, WinY = 600;
int WindowHandle = 0;

// Frames per second 
unsigned int FrameCount = 0;

void timerCallback(int value){
    std::ostringstream oss;
    oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
    std::string s = oss.str();
    glutSetWindow(WindowHandle);
    glutSetWindowTitle(s.c_str());
    FrameCount = 0;
    glutTimerFunc(1000, timerCallback, 0);
}

void refreshCallback(int value){
    glutPostRedisplay();
    glutTimerFunc(1000/60, refreshCallback, 0);
}

void displayCallback(){
    FrameCount++;
    microMachines->display();
    glutSwapBuffers();
}

void reshapeCallback(int width, int height){
    microMachines->reshape(width, height);
}

void processKeysCallback(unsigned char key, int x, int y){
    microMachines->processKeys(key, x ,y);
}

void processSpecialKeysCallback(int key, int x, int y){
    microMachines->processSpecialKeys(key, x, y);
}

void processSpecialUpKeysCallback(int key, int x, int y){
    microMachines->processSpecialUpKeys(key, x, y);
}

void processMouseButtonsCallback(int button, int state, int x, int y){
    microMachines->processMouseButtons(button, state, x, y);
}

void processMouseMotionCallback(int x, int y){
    microMachines->processMouseMotion(x, y);
}

void processMouseWheelCallback(int wheel, int direction, int x, int y){
    microMachines->processMouseWheel(wheel, direction, x, y);
}

void setupGLUT(int argc, char ** argv){
    glutInit(&argc, argv);
    
    #ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    #else
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE );
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    #endif
    
    glutInitWindowPosition(200,100);
    glutInitWindowSize(WinX, WinY);
    WindowHandle = glutCreateWindow(CAPTION);
}

void setupCallbacks(){
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    //glutIdleFunc(render);
    glutKeyboardFunc(processKeysCallback);
    glutSpecialFunc(processSpecialKeysCallback);
    glutSpecialUpFunc(processSpecialUpKeysCallback);
    glutMouseFunc(processMouseButtonsCallback);
    glutMotionFunc(processMouseMotionCallback);
    
    #ifdef __APPLE__
    #else
    glutMouseWheelFunc(processMouseWheelCallback) ;
    #endif
    
    glutTimerFunc(0, timerCallback, 0);
    glutTimerFunc(0, refreshCallback, 0);
}

void setupGLEW(){
    glewExperimental = GL_TRUE;
    glewInit();
    printf ("Vendor: %s\n", glGetString (GL_VENDOR));
    printf ("Renderer: %s\n", glGetString (GL_RENDERER));
    printf ("Version: %s\n", glGetString (GL_VERSION));
    printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
}

#endif /* Init_h */
