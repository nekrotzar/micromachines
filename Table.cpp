#include "Table.h"
#define PI 3.14159265

Table::Table() {
    Entity::setPosition(-11.0, 0.0, -15.0);
    
    glGenTextures(2, TextureArray);
    TGA_Texture(TextureArray, "textures/lightwood.tga", 0);
    TGA_Texture(TextureArray, "textures/cloth.tga", 1);
    
}
Table::~Table() {}

void Table::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, GLint texMode_uniformId) {
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, TextureArray[1]);
    glUniform1i(texMode_uniformId, 3);
    
	pushMatrix(MODEL);
	translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
	//rotate(MODEL, 30.0, 0, 0, 1);
	scale(MODEL, 1.8, 1.8, 1.8);

	load(shader, 0);    // Load table mesh
	pushMatrix(MODEL);
	translate(MODEL, -1.5, -0.17, -1.5);
	scale(MODEL, 15.0f, 0.1f, 20.0f);
	renderMesh(pvm_uniformId, vm_uniformId, normal_uniformId, 0);
	popMatrix(MODEL);

	popMatrix(MODEL);
}

