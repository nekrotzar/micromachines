#include "Cheerio.h"

Cheerio::Cheerio(double x, double z) {
	Entity::setPosition(x, getPosition().getY(), z);
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, "textures/cheerio.tga", 0);
}
Cheerio::~Cheerio() {}

void Cheerio::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, GLint texMode_uniformId) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 2);
    
	load(shader, 0);
	pushMatrix(MODEL);
	translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
	scale(MODEL, 1.1, 1.1, 1.1);
	renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	popMatrix(MODEL);

}

