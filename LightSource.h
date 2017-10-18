#ifndef LightSource_h
#define LightSource_h

#include <sstream>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Vector3.h"
#include "vsShaderLib.h"

class LightSource : public Entity {
protected:
    GLenum _num;
    bool _isOn;
public:
    LightSource(GLenum number, vec3 position);
    ~LightSource();
    GLenum getNum();
    bool getState();
    void setState(bool status);
    virtual void draw(VSShaderLib shader, GLint lPos_uniformId, int num);
};

#endif /* LightSource_h */
