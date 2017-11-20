#include "Cup.h"

Cup::Cup() {
    Entity::setPosition(3.0, 0.0, -3.0);
    
    setAmbient(0.1f, 0.1f, 0.1f, 0.4f);
    setDiffuse(0.1f, 0.1f, 0.4f, 0.2f);
    setSpecular(0.9f, 0.9f, 0.9f, 0.2f);
    setEmissive(0.0f, 0.0f, 0.0f, 0.4f);
    setShininess(100.0f);
    
    _mesh = new Mesh();
    _mesh->createObject("data/models/Coffe cup.obj");
    _mesh->setMeshMaterial(0, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 1);
    
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/textures/candle.tga", 0);
}

void Cup::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId) {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    
    
    glUniform1i(texMode_uniformId, 0);
    
    // Load body mesh
    _mesh->loadMeshMaterial(shader, 0);
    pushMatrix(MODEL);
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    _mesh->renderMeshRecursive(shader, pvm_uniformId, vm_uniformId, normal_uniformdId, _mesh->getScene(), _mesh->getScene()->mRootNode);
    popMatrix(MODEL);
}
