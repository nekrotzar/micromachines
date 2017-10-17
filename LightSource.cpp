#include "LightSource.h"

LightSource::LightSource(GLenum num, vec3 position){
    _num = num;
    setPosition(position);
}

LightSource::~LightSource(){}

GLenum LightSource::getNum(){
    return _num;
}


void LightSource::draw(VSShaderLib shader, GLint lPos_uniformId){}


