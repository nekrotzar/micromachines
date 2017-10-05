#include "Game.h"

int main(int argc, char ** argv)
{
    setupGLUT(argc, argv);
    microMachines = new MicroMachines();
    setupCallbacks();
    setupGLEW();
    
    if(!setupShaders())
        return EXIT_FAILURE;
    
    init();
    glutMainLoop();
    return EXIT_SUCCESS;
}

void setupGLUT(int argc, char ** argv)
{
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
    
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WinX, WinY);
    WindowHandle = glutCreateWindow(CAPTION);
}

void setupCallbacks()
{
    microMachines = new MicroMachines();
    
    glutDisplayFunc(renderScene);
    glutReshapeFunc(resize);
    //glutIdleFunc(render);
    glutKeyboardFunc(processKeys);
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);
    
    #ifdef __APPLE__
        // TODO
    #else
        glutMouseWheelFunc(processMouseWheel) ;
    #endif
    
    glutTimerFunc(0,timer,0);
    glutTimerFunc(0,refresh,0);
}

void setupGLEW()
{
    glewExperimental = GL_TRUE;
    glewInit();
    printf ("Vendor: %s\n", glGetString (GL_VENDOR));
    printf ("Renderer: %s\n", glGetString (GL_RENDERER));
    printf ("Version: %s\n", glGetString (GL_VERSION));
    printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
}

void timer(int value)
{
    std::ostringstream oss;
    oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
    std::string s = oss.str();
    glutSetWindow(WindowHandle);
    glutSetWindowTitle(s.c_str());
    FrameCount = 0;
    glutTimerFunc(1000, timer, 0);
}

void refresh(int value)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60, refresh, 0);
}

void renderScene()
{
    FrameCount++;
    microMachines->renderScene();
    glutSwapBuffers();
}

void resize(int width, int height)
{
    microMachines->resize(width, height);
}

void processKeys(unsigned char key, int xx, int yy)
{
    microMachines->processKeys(key, xx ,yy);
}

void processMouseButtons(int button, int state, int xx, int yy)
{
    microMachines->processMouseButtons(button, state, xx, yy);
}

void processMouseMotion(int xx, int yy)
{
    microMachines->processMouseMotion(xx, yy);
}

void processMouseWheel(int wheel, int direction, int xx, int yy)
{
    microMachines->processMouseWheel(wheel, direction, xx, yy);
}

GLuint setupShaders()
{
    return microMachines->setupShaders();
}

void init()
{
    microMachines->load();
}
