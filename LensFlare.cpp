#include "LensFlare.h"

LensFlare::LensFlare() {
    Entity::setPosition(0.0, 5.0, -20.0);
    
    setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
    setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
    setSpecular(0.0f, 0.0f, 0.0f, 0.0f);
    setEmissive(1.0f, 1.0f, 1.0f, 1.0f);
    setShininess(69.0f);
    
    _mesh = new Mesh();
    _mesh->createQuad(2, 2);
    _mesh->setMeshMaterial(0, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 1);
    
    glGenTextures(3, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/textures/tex9.tga", 0);
    TGA_Texture(TextureArray, (char*) "data/textures/flare3.tga", 1);
    //TGA_Texture(TextureArray, (char*) "data/textures/tex7.tga", 2);
    TGA_Texture(TextureArray, (char*) "data/textures/tex6.tga", 2);
//    TGA_Texture(TextureArray, (char*) "data/textures/tex5.tga", 4);
//    TGA_Texture(TextureArray, (char*) "data/textures/tex4.tga", 5);
//    TGA_Texture(TextureArray, (char*) "data/textures/tex3.tga", 6);
//    TGA_Texture(TextureArray, (char*) "data/textures/tex2.tga", 7);
//    TGA_Texture(TextureArray, (char*) "data/textures/tex1.tga", 8);

    //TGA_Texture(TextureArray, (char*) "data/textures/sun.tga", 3);
}

void LensFlare::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId) {

    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 1);
    
    _mesh->loadMeshMaterial(shader, 0);
    pushMatrix(MODEL);
    translate(MODEL, 2.0f, 5.0f, 0.0f);
    _mesh->renderMesh(shader, pvm_uniformId, vm_uniformId, normal_uniformdId, 0);
    popMatrix(MODEL);
    
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[1]);
    glUniform1i(texMode_uniformId, 1);
    
    _mesh->loadMeshMaterial(shader, 0);
    pushMatrix(MODEL);
    translate(MODEL, 4.0f, 6.0f, 0.0f);
    _mesh->renderMesh(shader, pvm_uniformId, vm_uniformId, normal_uniformdId, 0);
    popMatrix(MODEL);
    
    
    
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    
}

void LensFlare::render_flare(VSShaderLib shader, int lx, int ly, int cx, int cy, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId)
{

    int     dx, dy;          // Screen coordinates of "destination"
    int     px, py;          // Screen coordinates of flare element
    int     maxflaredist, flaredist, flaremaxsize, flarescale;
    int     width, height, alpha;    // Piece parameters;
    int     i;

    float fScale = 0.2f;
    float fMaxSize = 0.5f;

    
    // Compute how far off-center the flare source is.
    maxflaredist = sqrt(cx * cx + cy * cy);
    flaredist = sqrt((lx - cx)*(lx - cx)+(ly - cy)*(ly - cy));
    flaredist = (maxflaredist - flaredist);
    flaremaxsize = (int)(cx*2 * fMaxSize);
    flarescale = (int)(cx*2 * fScale);
    
    // Destination is opposite side of centre from source
    dx = cx + (cx - lx);
    dy = cy + (cy - ly);
    
    // Render each element.
    for (i = 0; i < 3; i++)
    {
        
        // Position is interpolated along line between start and destination.
        px = (int)((1.0f - relativePositions[i]) * lx + relativePositions[i] * dx);
        py = (int)((1.0f - relativePositions[i]) * ly + relativePositions[i] * dy);
        
        // Piece size are 0 to 1; flare size is proportion of
        // screen width; scale by flaredist/maxflaredist.
        width = (int)((flaredist * flarescale * relativePositions[i]) / maxflaredist);
        
        // Width gets clamped, to allows the off-axis flares
        // to keep a good size without letting the elements get
        // too big when centered.
        if (width > flaremaxsize)
        {
            width = flaremaxsize;
        }
        
        // Flare elements are square (round) so height is just
        // width scaled by aspect ratio.
        height = (320 * (width) * (cy * 2)) / (240 * (cx * 2));
        alpha = (flaredist*(relativePositions[i] > 24)) / maxflaredist;
        
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureArray[i]);
        glUniform1i(texMode_uniformId, 1);
        
        _mesh->loadMeshMaterial(shader, 0);
        pushMatrix(MODEL);
        translate(MODEL, px, py, 0.0f);
        scale(MODEL, width, width, 0.0f);
        _mesh->renderMesh(shader, pvm_uniformId, vm_uniformId, normal_uniformdId, 0);
        popMatrix(MODEL);
        
        glDisable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        
    }
}
