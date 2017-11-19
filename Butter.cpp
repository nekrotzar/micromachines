#include "Butter.h"

Butter::Butter(double x, double z){
    Object::setRadius(0.9);
    Entity::setPosition(x, 0.0, z);
    
    setAmbient(0.3, 0.3f, 0.1f, 1.0f);
    setDiffuse(1.0f, 1.0f, 0.0f, 1.0f);
    setSpecular(1.0f, 1.0f, 0.0f, 1.0f);
    setEmissive(0.0f, 0.0f, 0.0f, 1.0f);
    setShininess(100.0f);
    
    _mesh = new Mesh();
    _mesh->createCube();
    _mesh->setMeshMaterial(0, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 1);
    
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/textures/butter.tga", 0);
}

void Butter::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, GLint texMode_uniformId){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 1);
    
    // Load body mesh
    _mesh->loadMeshMaterial(shader, 0);
	pushMatrix(MODEL);
	translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
	scale(MODEL, 1.0f, 0.8f, 0.6f);
    _mesh->renderMesh(shader,pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	popMatrix(MODEL);
}
