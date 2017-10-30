#include "LightSource.h"

LightSource::LightSource(GLenum num, vec3 position){
    _isOn = true;
    _num = num;
    setPosition(position);
}

LightSource::~LightSource(){}

GLenum LightSource::getNum(){
    return _num;
}

bool LightSource::getState(){
    return _isOn;
}

void LightSource::setState(bool status){
    _isOn = status;
}

void LightSource::draw(VSShaderLib shader, int num){}


