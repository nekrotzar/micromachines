#include "DirectionalLight.h"

void DirectionalLight::draw(VSShaderLib shader, GLint lPos_uniformId){
    float res[4];
    GLfloat lightPos[4] = {(float) getPosition().getX(), (float) getPosition().getY(), (float) getPosition().getZ(), 0.0f};
    
    lPos_uniformId = glGetUniformLocation(shader.getProgramIndex(), "dirLight.direction");
    multMatrixPoint(VIEW, lightPos, res);
    glUniform4fv(lPos_uniformId, 1, res);
}
