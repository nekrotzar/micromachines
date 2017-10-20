#ifndef Object_h
#define Object_h

#include "Entity.h"
#include "vsShaderLib.h"
#include "basic_geometry.h"
#include "TGA.h"

extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];
extern float mNormal3x3[9];

class Object : public Entity
{
protected:
    double _radius;
    std::vector<struct MyMesh*> _meshes;
    GLuint TextureArray[2];
public:
    void assignMesh(struct MyMesh* mesh);
    void load(VSShaderLib shader, int myId);
    void renderMesh(GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, int myId);
    virtual void render(VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
    void setRadius(double radius);
    double getRadius();
};


#endif /* Object_h */
