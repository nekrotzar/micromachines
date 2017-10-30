#include "PointLight.h"

PointLight::PointLight(vec3 position) : LightSource(1.0, position){
    _constant = 1.5f;
    _linear = .0015f;
    _quadratic = 0.1f;
}
PointLight::~PointLight(){}

float PointLight::getConstantAttenuation(){
    return _constant;
}
float PointLight::getLinearAttenuation(){
    return _linear;
}
float PointLight::getQuadraticAttenuation(){
    return _quadratic;
}

void PointLight::draw(VSShaderLib shader, int num){
    float res[4];
    float lightPos[4] = {(float) getPosition().getX(), (float) getPosition().getY(), (float)getPosition().getZ(), 1.0f};
    
    GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat specular[] = { 0.7f, 0.7f, 0.4f, 1.0f };
    
    std::stringstream ss;
    
    ss.str("");
    ss << "pointlights[" << num << "].position";
    GLint lPos_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    
    ss.str("");
    ss << "pointlights[" << num << "].diffuse";
    GLint lDiff_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    
    ss.str("");
    ss << "pointlights[" << num << "].specular";
    GLint lSpec_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    
    ss.str("");
    ss << "pointlights[" << num << "].constant";
    GLint lConst_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    
    ss.str("");
    ss << "pointlights[" << num << "].linear";
    GLint lLin_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    
    ss.str("");
    ss << "pointlights[" << num << "].quadratic";
    GLint lQuadr_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());
    
    ss.str("");
    ss << "pointlights[" << num << "].status";
    GLint lStatus_uniformId = glGetUniformLocation(shader.getProgramIndex(), ss.str().c_str());

    
    multMatrixPoint(VIEW, lightPos, res);
    glUniform1i(lStatus_uniformId, getState());
    glUniform1f(lConst_uniformId, getConstantAttenuation() );
    glUniform1f(lLin_uniformId, getLinearAttenuation() );
    glUniform1f(lQuadr_uniformId, getQuadraticAttenuation() );
    glUniform4fv(lDiff_uniformId, 1, diffuse);
    glUniform4fv(lSpec_uniformId, 1, specular);
    glUniform4fv(lPos_uniformId, 1, res);
}

