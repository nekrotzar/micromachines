#include "Spotlight.h"

Spotlight::Spotlight(vec3 position) : LightSource(1.0, position){
    _cutoff = 0.0f;
    _exponent = 0.0f;
}

Spotlight::Spotlight(vec3 position, float cutoff, float exponent) : LightSource(1.0, position) {
    _cutoff = cutoff;
    _exponent = exponent;
}

void Spotlight::setCutoff(float cuttof){
    _cutoff = cuttof;
}

void Spotlight::setExponent(float exponent){
    _exponent = exponent;
}

float Spotlight::getCutoff(){
    return _cutoff;
}

float Spotlight::getExponent(){
    return _exponent;
}

void Spotlight::draw(VSShaderLib shader, GLint lPos_uniformId){
    float res[4], resDir[4];
    float lightPos[4] = {(float) getPosition().getX(), (float) getPosition().getY(), (float) getPosition().getZ(), 1.0f};

    std::stringstream ss;

    /*Car direction*/
    float dir[4] = {0,1,0,1.0};
    
    ss << "spotlights[" << getNum() << "].position";
    lPos_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    ss << "spotlights[" << getNum() << "].direction";
    GLint spotDir_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    ss << "spotlights[" << getNum() << "].cutoff";
    GLint spotCutOff_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    ss << "spotlights[" << getNum() << "].exponent";
    GLint spotExp_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    
    multMatrixPoint(VIEW, lightPos, res);
    multMatrixPoint(VIEW, dir, resDir);
    glUniform1f(spotCutOff_uniformId, getCutoff());
    glUniform1f(spotExp_uniformId, getExponent());
    glUniform3fv(spotDir_uniformId, 1, resDir);
    glUniform4fv(lPos_uniformId, 1, res);
}

