#ifndef MicroMachines_h
#define MicroMachines_h

#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>

#include <math.h>
#include <GL/glew.h>
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include "Car.h"
#include "Table.h"
#include "Cheerios.h"
#include "Orange.h"
#include "Butter.h"

#include "vsShaderLib.h"
#include "VertexAttrDef.h"
#include "AVTmathLib.h"

#define NUM_OBJECTS 200

class MicroMachines{
public:
    MicroMachines();
    ~MicroMachines();
    void init();
    void display();
	int collides();
    void reshape(int width, int height);
    void processKeys(unsigned char key, int xx, int yy);
    void processSpecialKeys(int key, int x, int y);
    void processSpecialUpKeys(int key, int x, int y);
    void keySpecialOperations();
    void processMouseButtons(int button, int state, int xx, int yy);
    void processMouseMotion(int xx, int yy);
    void processMouseWheel(int wheel, int direction, int x, int y);
    GLuint setupShaders();
    void deleteAll();
    void setCamera();
protected:
    
    bool _camera_trigger;
    bool* keySpecialStates = new bool[246];
    VSShaderLib shader;
    
    GLint pvm_uniformId;
    GLint vm_uniformId;
    GLint normal_uniformId;
    GLint lPos_uniformId;
        
    float lightPos[4] = {4.0f, 6.0f, 2.0f, 1.0f};
    float camX, camY, camZ;
    int startX, startY, tracking = 0;
    float alpha = 39.0f, beta = 51.0f;
    float r = 10.0f;
    
    Car *_car;
	Table *_table;
	Butter *_butter;
    
    std::vector<Object*> _objects;
	std::vector<Orange*> _oranges;
    std::vector<Camera*> _cameras;
    int _current_camera;
};


#endif /* MicroMachines_h */