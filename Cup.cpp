#include "Cup.h"

Cup::Cup() {
    Entity::setPosition(10.0, 0.0, 9.0);
    
    setAmbient(0.0f, 0.0f, 0.0f, 0.5f);
    setDiffuse(1.0f, 1.0f, 0.9f, 0.5f);
    setSpecular(1.0f, 1.0f, 0.5f, 0.5f);
    setEmissive(0.0f, 0.0f, 0.0f, 0.5f);
    setShininess(10.0f);
    
    _mesh = new Mesh();
    _mesh->createObject("data/models/Coffe cup.obj");
    _mesh->setMeshMaterial(0, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 1);
}

void Cup::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId) {
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glUniform1i(texMode_uniformId, 0);
    
    // Load body mesh
    _mesh->loadMeshMaterial(shader, 0);
    pushMatrix(MODEL);
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    _mesh->renderMeshRecursive(shader, pvm_uniformId, vm_uniformId, normal_uniformdId, _mesh->getScene(), _mesh->getScene()->mRootNode);
    popMatrix(MODEL);
    
    glDisable(GL_BLEND);
}
