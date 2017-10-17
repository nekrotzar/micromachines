#include "PointLight.h"

PointLight::PointLight(vec3 position) : LightSource(1.0, position){}
PointLight::~PointLight(){}

void PointLight::draw(VSShaderLib shader, GLint lPos_uniformId, int num){
}

