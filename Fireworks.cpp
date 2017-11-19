#include "Fireworks.h"

Fireworks::Fireworks(GLfloat v,GLfloat phi, GLfloat theta) {
    
    setPosition(2.0, 2.0, 2.0);
    setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
    setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
    setSpecular(0.0f, 0.0f, 0.0f, 0.0f);
    setEmissive(1.0f, 1.0f, 1.0f, 1.0f);
    setShininess(69.0f);
    
    _mesh = new Mesh();
    _mesh->createQuad(0.2, 0.2);
    _mesh->setMeshMaterial(0, getAmbient(), getDiffuse(), getSpecular(), getEmissive(), getShininess(), 0);
    
    glGenTextures(1, TextureArray);
    TGA_Texture(TextureArray, (char*) "data/textures/fireball.tga", 0);
    life = 1.0f;
    fade = 0.005f;
    vx = v * cos(theta) * sin(phi);
    vy = v * cos(phi);
    vz = v * sin(theta) * sin(phi);
    ax = 0.1f;
    ay = -0.15f;
    az = 0.0f;
    
}

void Fireworks::render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId) {
    
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
    glUniform1i(texMode_uniformId, 1);
    
    if (life > 0.0f){ /* sÛ desenha as que ainda est„o vivas */
        
        //particle_color[0] = 0.882f;
        //particle_color[1] = 0.552f;
        //particle_color[2] = 0.211f;
        //particle_color[3] = life;
        
        setDiffuse(0.882f, 0.552f, 0.211f, life);
        
        //loc = glGetUniformLocation(shader.getProgramIndex(), "mat.diffuse");
        //glUniform4fv(loc, 1, particle_color);
        pushMatrix(MODEL);
        translate(MODEL, getPosition().getX(), getPosition().getY(), getPosition().getZ());
        _mesh->renderMesh(shader, pvm_uniformId, vm_uniformId, normal_uniformdId, 0);
        popMatrix(MODEL);
    }
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

//void Fireworks::iniParticulas(void){
//    GLfloat v, theta, phi;
//    int i;
//
//    for (i = 0; i<MAX_PARTICULAS; i++)
//    {
//        v = 0.8*frand() + 0.2;
//        phi = frand()*M_PI;
//        theta = 2.0*frand()*M_PI;
//
//        particula[i].x = 0.0f;
//        particula[i].y = 10.0f;
//        particula[i].z = 0.0f;
//        particula[i].vx = v * cos(theta) * sin(phi);
//        particula[i].vy = v * cos(phi);
//        particula[i].vz = v * sin(theta) * sin(phi);
//        particula[i].ax = 0.1f; /* simular um pouco de vento */
//        particula[i].ay = -0.15f; /* simular a aceleraÁ„o da gravidade */
//        particula[i].az = 0.0f;
//
//        /* tom amarelado que vai ser multiplicado pela textura que varia entre branco e preto */
//        particula[i].r = 0.882f;
//        particula[i].g = 0.552f;
//        particula[i].b = 0.211f;
//
//        particula[i].life = 1.0f;        /* vida inicial */
//        particula[i].fade = 0.005f;        /* step de decrÈscimo da vida para cada iteraÁ„o */
//    }
//}
//
//void Fireworks::iterate(int value)
//{
//    int i;
//    float h;
//
//    /* MÈtodo de Euler de integraÁ„o de eq. diferenciais ordin·rias
//     h representa o step de tempo; dv/dt = a; dx/dt = v; e conhecem-se os valores iniciais de x e v */
//
//    h = 0.125f;
//    //    h = 0.033;
//    if (fireworks) {
//
//        for (i = 0; i < MAX_PARTICULAS; i++)
//        {
//            particula[i].x += (h*particula[i].vx);
//            particula[i].y += (h*particula[i].vy);
//            particula[i].z += (h*particula[i].vz);
//            particula[i].vx += (h*particula[i].ax);
//            particula[i].vy += (h*particula[i].ay);
//            particula[i].vz += (h*particula[i].az);
//            particula[i].life -= particula[i].fade;
//        }
//        //glutPostRedisplay();
//        //iterate(1);
//        //glutTimerFunc(33, iterate, 0);
//    }
//}


