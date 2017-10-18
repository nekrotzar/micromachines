#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(vec3 direction) : LightSource(0.0, direction) {
}

void DirectionalLight::draw(VSShaderLib shader, int num){
    float res[4];
    GLfloat lightPos[4] = {(float) getPosition().getX(), (float) getPosition().getY(), (float) getPosition().getZ(), (float) getNum()};
    
    GLint lPos_uniformId = glGetUniformLocation(shader.getProgramIndex(), "dirLight.direction");
    GLint lStatus_uniformId = glGetUniformLocation(shader.getProgramIndex(), "dirLight.status");

    multMatrixPoint(VIEW, lightPos, res);
    glUniform1i(lStatus_uniformId, getState());
    glUniform4fv(lPos_uniformId, 1, res);
}
