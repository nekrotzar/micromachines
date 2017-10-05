#ifndef MicroMachines_h
#define MicroMachines_h

#include <vector>

#include <math.h>
#include <GL/glew.h>

#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"

#include "vsShaderLib.h"
#include "AVTmathLib.h"
#include "VertexAttrDef.h"
#include "basic_geometry.h"

#define OBJECT_NUMBER 4

extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];
extern float mNormal3x3[9];

class MicroMachines
{
protected:
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
    
    std::vector<Camera*> _cameras;
    int _current_camera;
    
public:
    MicroMachines();
    ~MicroMachines();
    void load();
    void renderScene();
    void resize(int width, int height);
    void processKeys(unsigned char key, int xx, int yy);
    void processMouseButtons(int button, int state, int xx, int yy);
    void processMouseMotion(int xx, int yy);
    void processMouseWheel(int wheel, int direction, int x, int y);
    GLuint setupShaders();
    
    void setCamera();
};


#endif /* MicroMachines_h */
