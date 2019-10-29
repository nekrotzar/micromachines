#ifndef Spotlight_h
#define Spotlight_h

#include "LightSource.h"

class Spotlight : public LightSource {
protected:
    vec3 _direction;
    float _cutoff;
    float _exponent;
    float _constant, _linear, _quadratic;
public:
    Spotlight(vec3 position);
    Spotlight(vec3 position, float cutoff, float exponent);
    ~Spotlight();
    vec3 getDirection();
    float getCutoff();
    float getExponent();
    float getConstantAttenuation();
    float getLinearAttenuation();
    float getQuadraticAttenuation();
    void setDirection(const vec3& vec);
    void setCutoff(float cutoff);
    void setExponent(float exponent);
    void draw(VSShaderLib shader, int num);
};

#endif /* Spotlight_h */
