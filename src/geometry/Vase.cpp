#include "Vase.h"

extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

// The normal matrix
extern float mNormal3x3[9];

Vase::Vase() {
    Entity::setPosition(0.0, 1.5, 0.0);
    
    setAmbient(0.3f, 0.3f, 0.3f, 1.0f);
    setDiffuse(0.4f, 0.4f, 0.4f, 1.0f);
    setSpecular(0.9, 0.9f, 0.9f, 1.0f);
    setEmissive(0.0f, 0.0f, 0.0f, 1.0f);
    setShininess(10.0f);
    
    _mesh = new Mesh();
    _mesh->createQuad(5, 5);
    _mesh->setMeshMaterial(0, getSpecular(), getEmissive(), getShininess(), 1);
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/textures/vase.tga", 0);
}

void Vase::renderBillboard(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId, float camPos[], int type) {
    
    float modelview[16];
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    
    glUniform1i(texMode_uniformId, 3);
    
    pushMatrix(MODEL);
    translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
    
    
    float pos[3] = {(float)getPosition().getX(), (float)getPosition().getY(), (float)getPosition().getZ()};
    
    if (type == 2) {
        l3dBillboardSphericalBegin(camPos, pos);
    } else if (type == 3) {
        l3dBillboardCylindricalBegin(camPos, pos);
    }
    
    GLint loc;
    
    loc = glGetUniformLocation(shader.getProgramIndex(), "mat.specular");
    glUniform4fv(loc, 1, _mesh->myMeshes[0].mat.specular);
    loc = glGetUniformLocation(shader.getProgramIndex(), "mat.emissive");
    glUniform4fv(loc, 1, _mesh->myMeshes[0].mat.emissive);
    
    pushMatrix(MODEL);
    
    if (type == 0 | type == 1) {
        computeDerivedMatrix(VIEW_MODEL);
        memcpy(modelview, mCompMatrix[VIEW_MODEL], sizeof(float) * 16);
        
        if (type == 0) {
            BillboardCheatSphericalBegin();
        } else {
            BillboardCheatCylindricalBegin();
        }
        
        computeDerivedMatrix_PVM();
        
    } else {
        computeDerivedMatrix(PROJ_VIEW_MODEL);
    }
    
    _mesh->renderMesh(shader ,pvm_uniformId,  vm_uniformId, normal_uniformdId, 0);
    popMatrix(MODEL);
    
    if (type == 0 || type == 1) {
        BillboardEnd(modelview);
    }
    
    popMatrix(MODEL);    
}
