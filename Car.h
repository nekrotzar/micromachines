#ifndef Car_h
#define Car_h

#include "DynamicObject.h"
#define PI 3.14159265

class Car : public DynamicObject
{
protected:
    vec3 _direction;
public:
    Car();
    ~Car();
    void render(VSShaderLib shader, GLint pvm_uniformId , GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);

};

#endif /* Car_h */
