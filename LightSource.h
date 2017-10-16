#ifndef LightSource_h
#define LightSource_h

#include "Entity.h"
#include "Vector3.h"

class LightSource : public Entity {
protected:
    vec3 _direction;
    float _ambient[4];
    float _diffuse[4];
    float _specular[4];
    float _cut_off;
    float _exponent;
    GLenum _num;
    bool _state;
public:
    LightSource(GLenum number);
    ~LightSource();
    bool getState();
    GLenum getNum();
    void setState(bool state);
    void setDirection(const vec3& direction);
    void setCutOff(float cut_off);
    void setExponent(float exponent);
    void setAmbient(float x, float y, float z, float w);
    void setDiffuse(float x, float y, float z, float w);
    void setSpecular(float x, float y, float z, float w);
    void draw(GLint lPos_uniformId, vec3 position ,float w);
};

#endif /* LightSource_h */
