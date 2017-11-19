#include "Table.h"

Table::Table(){
    setPosition(0.0, 0.0, 0.0);
    
    setAmbient(0.1f, 0.1f, 0.1f, 1.0f);
    setDiffuse(0.1f, 0.5f, 0.1f, 1.0f);
    setSpecular(0.1f, 0.1f, 0.1f, 1.0f);
    setEmissive(0.0f, 0.0f, 0.0f, 1.0f);
    setShininess(100.0f);
    
    _mesh = new Mesh();
    _mesh->createCube();
    _mesh->createQuad(30, 1.0);
    _mesh->setMeshMaterial(0, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 2);
    _mesh->setMeshMaterial(1, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 2);


    glGenTextures(3, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/textures/wood.tga", 0);
    TGA_Texture(TextureArray, (char*) "data/textures/floor_disp.tga", 1);
    TGA_Texture(TextureArray, (char*) "data/textures/floor_diff.tga", 2);    
}

void Table::draw_tile(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, GLint texMode_uniformId , vec3 position, vec3 m_scale){
    _mesh->loadMeshMaterial(shader, 0);
    pushMatrix(MODEL);
    translate(MODEL, position.getX(), position.getY(), position.getZ());
    scale(MODEL, m_scale.getX(), m_scale.getY(), m_scale.getZ());
    _mesh->renderMesh(shader,pvm_uniformId, vm_uniformId, normal_uniformId, 0);
    popMatrix(MODEL);
}

void Table::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, GLint texMode_uniformId) {
    
	pushMatrix(MODEL);
	translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    
    // Draw 1st cube with wooden texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 1);
    
    
    // Draw table sides
    _mesh->loadMeshMaterial(shader, 1);
    pushMatrix(MODEL);
    translate(MODEL, 0, -0.5, 15);
    _mesh->renderMesh(shader, pvm_uniformId, vm_uniformId, normal_uniformId, 1);
    popMatrix(MODEL);
    
    _mesh->loadMeshMaterial(shader, 1);
    pushMatrix(MODEL);
    translate(MODEL, 0, -0.5, -15);
    rotate(MODEL, 180, 0, 1, 0);
    _mesh->renderMesh(shader, pvm_uniformId, vm_uniformId, normal_uniformId, 1);
    popMatrix(MODEL);
    
    pushMatrix(MODEL);
    translate(MODEL, 15, -0.5, 0);
    rotate(MODEL, 90, 0, 1, 0);
    _mesh->renderMesh(shader, pvm_uniformId, vm_uniformId, normal_uniformId, 1);
    popMatrix(MODEL);
    
    pushMatrix(MODEL);
    translate(MODEL, -15, -0.5, 0);
    rotate(MODEL, -90, 0, 1, 0);
    _mesh->renderMesh(shader, pvm_uniformId, vm_uniformId, normal_uniformId, 1);
    popMatrix(MODEL);
    
    // Draw table top
    //draw_tile(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId ,vec3(0.0f, -1.0f, 0.0f), vec3(15.0f, 1.0f, 15.0f));
    //draw_tile(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId ,vec3(-15.0f, -1.0f, 0.0f), vec3(15.0f, 1.0f, 15.0f));
    //draw_tile(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId ,vec3(-15.0f, -1.0f, -15.0f), vec3(15.0f, 1.0f, 15.0f));
    //draw_tile(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId ,vec3(0.0f, -1.0f, -15.0f), vec3(15.0f, 1.0f, 15.0f));
    
    // Draw table legs
    draw_tile(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId ,vec3(14.0f, -9.5f, 14.0f), vec3(1.0f, 8.5f, 1.0f));
    draw_tile(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId ,vec3(14.0f, -9.5f, -15.0f), vec3(1.0f, 8.5f, 1.0f));
    draw_tile(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId ,vec3(-15.0f, -9.5f, -15.0f), vec3(1.0f, 8.5f, 1.0f));
    draw_tile(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId ,vec3(-15.0f, -9.5f, 14.0f), vec3(1.0f, 8.5f, 1.0f));

    // Draw 3rd cube with checkered texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[1]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, TextureArray[2]);
    glUniform1i(texMode_uniformId, 4);
    
    // Ground
    for (int x = 15.0; x >= -30; x-=15) {
        for (int z = 15.0 ; z >= -30; z-=15) {
            draw_tile(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId, vec3(x, -10.5f, z), vec3(15.0f, 1.0f, 15.0f));
        }
    }
	popMatrix(MODEL);
}

