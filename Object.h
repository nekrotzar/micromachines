#ifndef Object_h
#define Object_h

#include "Entity.h"
#include "vsShaderLib.h"
#include "basic_geometry.h"

extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];
extern float mNormal3x3[9];

class Object : public Entity
{
protected:
    std::vector<struct MyMesh*> _meshes;
public:
    void assignMesh(struct MyMesh* mesh);
    void load(VSShaderLib shader, int myId);
    void renderMesh(GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, int myId);
    virtual void render(VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformdId);
};


#endif /* Object_h */
