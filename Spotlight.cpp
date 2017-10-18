#include "Spotlight.h"

Spotlight::Spotlight(vec3 position) : LightSource(1.0, position){
    _cutoff = 0.0f;
    _exponent = 0.0f;
    _constant = 2.5;
    _linear = 0.045;
    _quadratic = 0.0075;
}

Spotlight::Spotlight(vec3 position, float cutoff, float exponent) : LightSource(1.0, position) {
    _cutoff = cutoff;
    _exponent = exponent;
}

void Spotlight::setDirection(const vec3& direction){
    _direction = direction;

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

float Spotlight::getConstantAttenuation(){
    return _constant;
}
float Spotlight::getLinearAttenuation(){
    return _linear;
}
float Spotlight::getQuadraticAttenuation(){
    return _quadratic;
}

vec3 Spotlight::getDirection(){
    return _direction;
}

void Spotlight::draw(VSShaderLib shader, int num){
    float res[4], resDir[4];
    float lightPos[4] = {(float) getPosition().getX(), (float) getPosition().getY(), (float) getPosition().getZ(), 1.0f};

    std::stringstream ss;

    /*Car direction*/
    float dir[3] = {(float) getDirection().getX(), (float) getDirection().getY(), (float) getPosition().getZ()};
    
    ss << "spotlights[" << num << "].position";
    GLint lPos_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    ss << "spotlights[" << num << "].direction";
    GLint spotDir_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    ss << "spotlights[" << num << "].cutoff";
    GLint spotCutOff_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    ss << "spotlights[" << num << "].exponent";
    GLint spotExp_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    ss.str("");
    ss << "spotlights[" << num << "].constant";
    GLint lConst_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    ss.str("");
    ss << "spotlights[" << num << "].linear";
    GLint lLin_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    ss.str("");
    ss << "spotlights[" << num << "].quadratic";
    GLint lQuadr_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    ss.str("");
    ss << "spotlights[" << num << "].status";
    GLint lStatus_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    
    multMatrixPoint(VIEW, lightPos, res);
    multMatrixPoint(VIEW, dir, resDir);
    glUniform1i(lStatus_uniformId, getState());
    glUniform1f(lConst_uniformId, getConstantAttenuation());
    glUniform1f(lLin_uniformId, getLinearAttenuation() );
    glUniform1f(lQuadr_uniformId, getQuadraticAttenuation());
    glUniform1f(spotCutOff_uniformId, getCutoff());
    glUniform1f(spotExp_uniformId, getExponent());
    glUniform3fv(spotDir_uniformId, 1, resDir);
    glUniform4fv(lPos_uniformId, 1, res);
}

