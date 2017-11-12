#ifndef Object_h
#define Object_h

#include "Entity.h"
#include "vsShaderLib.h"
#include "TGA.h"
#include "basic_geometry.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

class Object : public Entity {
protected:
    float _ambient[4];
    float _diffuse[4];
    float _specular[4];
    float _emissive[4];
    float _shininess;
    int _texCount;
    
    double _radius;
    GLuint TextureArray[3];
    Mesh * _mesh;
public:
    float * getAmbient();
    float * getDiffuse();
    float * getSpecular();
    float * getEmissive();
    float getShininess();
    void setAmbient(float r, float g, float b, float a);
    void setDiffuse(float r, float g, float b, float a);
    void setSpecular(float r, float g, float b, float a);
    void setEmissive(float r, float g, float b, float a);
    void setShininess(float shininess);

    virtual void render(VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
    void setRadius(double radius);
    double getRadius();
};


#endif /* Object_h */
