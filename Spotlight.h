#ifndef Spotlight_h
#define Spotlight_h

#include "LightSource.h"

class Spotlight : public LightSource {
protected:
    float _cutoff;
    float _exponent;
public:
    Spotlight(vec3 position);
    Spotlight(vec3 position, float cutoff, float exponent);
    ~Spotlight();
    float getCutoff();
    float getExponent();
    void setCutoff(float cutoff);
    void setExponent(float exponent);
    void draw(VSShaderLib shader, GLint lPos_uniformId);
};

#endif /* Spotlight_h */
