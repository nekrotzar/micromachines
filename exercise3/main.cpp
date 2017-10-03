#include <iostream>
#include <sstream>
#include <string>

#include <math.h>

#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "vsShaderLib.h"
#include "AVTmathLib.h"
#include "VertexAttrDef.h"
#include "basic_geometry.h"

#define CAPTION "AVT MicroMachines"

int WindowHandle = 0;
int WinX = 640, WinY = 480;

unsigned int FrameCount = 0;

VSShaderLib shader;

struct MyMesh mesh[4];
int objId = 0;

//External array storage defined in AVTmathLib.cpp

/// The storage for matrices
extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

/// The normal matrix
extern float mNormal3x3[9];

GLint pvm_uniformId;
GLint vm_uniformId;
GLint normal_uniformId;
GLint lPos_uniformId;

//Camera Position
float camX, camY, camZ;

//Mouse Tracking Variables
int startX, startY;
bool tracking;

//Camera Spherical Coordinates
float alpha = 30.0f, beta = 60.0f;
float r = 10.0f;

float lightPos[4] = {4.0f, 6.0f, 2.0f, 1.0f};

void display(void) {
    
    GLint loc;
    
    FrameCount++;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    loadIdentity(VIEW);
    loadIdentity(MODEL);
    
    lookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);
    
    glUseProgram(shader.getProgramIndex());
   
    float res[4];
    multMatrixPoint(VIEW, lightPos, res);
    glUniform4fv(lPos_uniformId, 1, res);
    
    objId = 0;
    for(int i=0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            // send the material
            loc = glGetUniformLocation(shader.getProgramIndex(), "mat.ambient");
            glUniform4fv(loc, 1, mesh[objId].mat.ambient);
            loc = glGetUniformLocation(shader.getProgramIndex(), "mat.diffuse");
            glUniform4fv(loc, 1, mesh[objId].mat.diffuse);
            loc = glGetUniformLocation(shader.getProgramIndex(), "mat.specular");
            glUniform4fv(loc, 1, mesh[objId].mat.specular);
            loc = glGetUniformLocation(shader.getProgramIndex(), "mat.shininess");
            glUniform1f(loc,mesh[objId].mat.shininess);
            pushMatrix(MODEL);
            translate(MODEL, i*2.0f, 0.0f, j*2.0f);
            
            computeDerivedMatrix(PROJ_VIEW_MODEL);
            glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
            glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
            computeNormalMatrix3x3();
            glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);
            
            // Render mesh
            glBindVertexArray(mesh[objId].vao);
            glDrawElements(mesh[objId].type,mesh[objId].numIndexes, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
            
            popMatrix(MODEL);
            objId++;
        }
    }
    
    glutSwapBuffers();
}

void resize(int width, int height) {
    float ratio;
    
    if(height == 0)
        height = 1;
    
    glViewport(0, 0, width, height);
    ratio = (1.0f * width) / height;
    loadIdentity(PROJECTION);
    perspective(53.13f, ratio, 0.1f, 1000.0f);
}

void idle(void){
}

void processKeys(unsigned char key, int xx, int yy) {
    switch (key) {
            // ESC key
        case 27:
            exit(EXIT_SUCCESS);
            break;
        case 49:
            // TODO: Switch to orthogonal fixed camera (top view)
            break;
        case 50:
            // TODO: Switch to perspective fixed camera (top view)
            break;
        case 51:
            // TODO: Switch to perspective moving camera (behind the car view)
            break;
        default:
            break;
    }
}

void processSpecialKeys(int key, int xx, int yy){
    switch (key) {
        case GLUT_KEY_UP:
            // Move the car forwar
            break;
        case GLUT_KEY_DOWN:
            // Move car backward
            break;
        case GLUT_KEY_LEFT:
            // Turn car left
            break;
        case GLUT_KEY_RIGHT:
            // Turn car right
            break;
        default:
            break;
    }
}

void processMouseButtons(int button, int state, int xx, int yy) {
    if(state == GLUT_DOWN) {
        startX = xx;
        startY = yy;
        
        if (button == GLUT_LEFT_BUTTON)
            tracking = true;
    }
    else if (state == GLUT_DOWN) {
        if (tracking) {
            alpha -= (xx - startX);
            beta += (yy - startY);
        }
        tracking = false;
    }
}

void processMouseMotion(int xx, int yy){
    int deltaX, deltaY;
    float alphaAux = alpha, betaAux = beta;
    float rAux = r;
    
    deltaX = -xx + startX;
    deltaY =  yy - startY;
    
    // Camera #3 must also be activated to move mouse around
    if(tracking) {
        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;
        
        if (betaAux > 90.0f)
            betaAux = 90.0f;
        else if (betaAux < 0.0f)
            betaAux = 0.0f;
    }
    
    //Set camera position
    camX = rAux * sin(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
    camZ = rAux * cos(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
    camY = rAux * sin(betaAux * 3.14f / 180.0f);
}

void timer(int value) {
    std::ostringstream oss;
    oss << CAPTION << ":" << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
    std::string s = oss.str();
    glutSetWindow(WindowHandle);
    glutSetWindowTitle(s.c_str());
    FrameCount = 0;
    glutTimerFunc(1000, timer, 0);
}

void refresh(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, refresh, 0);
}

void setupGLUT(int argc, char** argv) {
    glutInit(&argc, argv);
    
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
#else
    glutInitDisplayMode(GLUT_DEPTH |GLUT_DOUBLE |GLUT_RGBA |GLUT_MULTISAMPLE);
    glutInitContextVersion (3, 3);
    glutInitContextProfile (GLUT_CORE_PROFILE );
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif
    
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WinX, WinY);
    WindowHandle = glutCreateWindow(CAPTION);
    
    if (WindowHandle < 1) {
        std::cerr << "Error: Could not create a new rendering window." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void setupCallbacks() {
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutIdleFunc(idle);
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);
    
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(0, refresh, 0);
}

void setupGLEW() {
    glewExperimental = GL_TRUE;
    glewInit();
    
    GLenum result = glewInit() ;
    if (result != GLEW_OK) {
        std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
        exit(EXIT_FAILURE);
    }
    
    printf ("Vendor: %s\n", glGetString (GL_VENDOR));
    printf ("Renderer: %s\n", glGetString (GL_RENDERER));
    printf ("Version: %s\n", glGetString (GL_VERSION));
    printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
}

GLuint setupShaders() {
    
    // Shaders for models
    shader.init();
    shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/pointlight.vert");
    shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/pointlight.frag");
    
    // Set semantics for shader variables
    glBindFragDataLocation(shader.getProgramIndex(), 0 , "colorOut");
    glBindAttribLocation(shader.getProgramIndex(), VERTEX_COORD_ATTRIB, "position");
    glBindAttribLocation(shader.getProgramIndex(), NORMAL_ATTRIB, "normal");
    
    glLinkProgram(shader.getProgramIndex());
    
    pvm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_pvm");
    vm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_viewModel");
    normal_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_normal");
    lPos_uniformId = glGetUniformLocation(shader.getProgramIndex(), "l_pos");
    
    printf("InfoLog for Pointlight shader\n%s\n\n", shader.getAllInfoLogs().c_str());
    
    return(shader.isProgramLinked());
    
}

void loadModels() {
    
    // set the camera position based on its spherical coordinates
    camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
    camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
    camY = r * sin(beta * 3.14f / 180.0f);
    
    
    float amb[]= {0.2f, 0.15f, 0.1f, 1.0f};
    float diff[] = {0.8f, 0.6f, 0.4f, 1.0f};
    float spec[] = {0.8f, 0.8f, 0.8f, 1.0f};
    float emissive[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float shininess= 100.0f;
    int texcount = 0;
    
     
    // create geometry and VAO of the pawn
    objId=0;
    memcpy(mesh[objId].mat.ambient, amb,4*sizeof(float));
    memcpy(mesh[objId].mat.diffuse, diff,4*sizeof(float));
    memcpy(mesh[objId].mat.specular, spec,4*sizeof(float));
    memcpy(mesh[objId].mat.emissive, emissive,4*sizeof(float));
    mesh[objId].mat.shininess = shininess;
    mesh[objId].mat.texCount = texcount;
    createPawn();
    
    
    // create geometry and VAO of the sphere
    objId=1;
    memcpy(mesh[objId].mat.ambient, amb,4*sizeof(float));
    memcpy(mesh[objId].mat.diffuse, diff,4*sizeof(float));
    memcpy(mesh[objId].mat.specular, spec,4*sizeof(float));
    memcpy(mesh[objId].mat.emissive, emissive,4*sizeof(float));
    mesh[objId].mat.shininess = shininess;
    mesh[objId].mat.texCount = texcount;
    createSphere(1.0f, 20);
    
    float amb1[]= {0.3f, 0.0f, 0.0f, 1.0f};
    float diff1[] = {0.8f, 0.1f, 0.1f, 1.0f};
    float spec1[] = {0.9f, 0.9f, 0.9f, 1.0f};
    shininess=500.0;
    
    // create geometry and VAO of the cylinder
    objId=2;
    memcpy(mesh[objId].mat.ambient, amb1,4*sizeof(float));
    memcpy(mesh[objId].mat.diffuse, diff1,4*sizeof(float));
    memcpy(mesh[objId].mat.specular, spec1,4*sizeof(float));
    memcpy(mesh[objId].mat.emissive, emissive,4*sizeof(float));
    mesh[objId].mat.shininess = shininess;
    mesh[objId].mat.texCount = texcount;
    createCylinder(1.5f,0.5f,20);
    
    // create geometry and VAO of the
    objId=3;
    memcpy(mesh[objId].mat.ambient, amb1,4*sizeof(float));
    memcpy(mesh[objId].mat.diffuse, diff1,4*sizeof(float));
    memcpy(mesh[objId].mat.specular, spec1,4*sizeof(float));
    memcpy(mesh[objId].mat.emissive, emissive,4*sizeof(float));
    mesh[objId].mat.shininess = shininess;
    mesh[objId].mat.texCount = texcount;
    createCone(1.5f,0.5f, 20);
    
    
}

void setupOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

int main(int argc, char **argv) {
    setupGLUT(argc, argv);
    setupCallbacks();
    setupGLEW();
    
    if(!setupShaders())
        return EXIT_FAILURE;
    
    loadModels();
    setupOpenGL();
    
    glutMainLoop();
    return EXIT_SUCCESS;
    
}


