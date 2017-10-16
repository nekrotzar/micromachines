#include "LightSource.h"

LightSource::LightSource(GLenum num){
    _num = num;
}

bool LightSource::getState(){
    return _state;
}

GLenum LightSource::getNum(){
    return _num;
}

void LightSource::setState(bool state){
    _state = state;
}

void LightSource::draw(GLint lPos_uniformId, vec3 position, float w ){
    float res[4];
    float lightPos[4] = {(float) position.getX(), (float) position.getY(), (float) position.getZ(), w};
    multMatrixPoint(VIEW, lightPos, res);
    glUniform4fv(lPos_uniformId, 1, res);
}

