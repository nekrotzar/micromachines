#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(vec3 direction) : LightSource(0.0, direction) {
}

void DirectionalLight::draw(VSShaderLib shader, int num){
    float res[4];
    GLfloat lightPos[4] = {(float) getPosition().getX(), (float) getPosition().getY(), (float) getPosition().getZ(), 0.0f};
    multMatrixPoint(VIEW, lightPos, res);
    
    GLfloat diffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    GLint lPos_uniformId = glGetUniformLocation(shader.getProgramIndex(), "dirLight.direction");
    GLint lStatus_uniformId = glGetUniformLocation(shader.getProgramIndex(), "dirLight.status");
    GLint lDiff_uniformId = glGetUniformLocation(shader.getProgramIndex(), "dirLight.diffuse");
    GLint lSpec_uniformId = glGetUniformLocation(shader.getProgramIndex(), "dirLight.specular");

    glUniform1i(lStatus_uniformId, getState());
    glUniform4fv(lDiff_uniformId, 1, diffuse);
    glUniform4fv(lSpec_uniformId, 1, specular);
    glUniform4fv(lPos_uniformId, 1, res);
}
