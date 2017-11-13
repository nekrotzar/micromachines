#include "Celery.h"

Celery::Celery() {
    Entity::setPosition(5.0, 2.5, 5.0);
    
    setAmbient(1.0f, 1.0f, 1.0f, 0.0f);
    setDiffuse(0.0f, 0.0f, 0.0f, 1.0f);
    setSpecular(0.0f, 0.0f, 0.0f, 1.0f);
    setEmissive(0.0f, 0.0f, 0.0f, 1.0f);
    setShininess(10.0f);
    
    _mesh = new Mesh();
    _mesh->createQuad(5, 5);
    _mesh->setMeshMaterial(0, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 1);
    
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/textures/celery.tga", 0);
}

void Celery::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glUniform1i(texMode_uniformId, 1);
    
    // Load body mesh
    _mesh->loadMeshMaterial(shader, 0);
    pushMatrix(MODEL);
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    
    
    //l3dBillboardSphericalBegin(cam, pos);
    
    _mesh->renderMesh(shader ,pvm_uniformId,  vm_uniformId, normal_uniformdId, 0);
    popMatrix(MODEL);
    
    glDisable(GL_BLEND);
}
