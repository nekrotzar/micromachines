#include "Cheerio.h"

Cheerio::Cheerio(double x, double z) {
	Entity::setPosition(x, getPosition().getY(), z);
    
    setAmbient(0.05f, 0.05f, 0.1f, 1.0f);
    setDiffuse(0.0f, 0.0f, 0.0f, 1.0f);
    setSpecular(0.0f, 0.0f, 0.0f, 1.0f);
    setEmissive(0.0f, 0.0f, 0.0f, 1.0f);
    setShininess(100.0f);
    
    _mesh = new Mesh();
    _mesh->createTorus(0.07, 0.16, 10, 15);
    _mesh->setMeshMaterial(0, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 1);
    
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/textures/cheerio.tga", 0);
}

void Cheerio::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, GLint texMode_uniformId) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 2);
    
    _mesh->loadMeshMaterial(shader, 0);
	pushMatrix(MODEL);
	translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
	scale(MODEL, 1.1, 1.1, 1.1);
    _mesh->renderMesh(shader,pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	popMatrix(MODEL);
}

