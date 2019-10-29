#ifndef Fireworks_h
#define Fireworks_h

#include <stdio.h>
#include "DYnamicObject.h"
#define MAX_PARTICULAS 1500
#define frand()            ((float)rand()/RAND_MAX)
#define M_PI            3.14159265

class Fireworks : public DynamicObject {
protected:
    GLint loc;
    //        float relativePositions[4] = {0.7f, 0.8f, 0.9f, 1.0f};
    float particle_color[4];
    //
    //        int dead_num_particles = 0;
    //
    //        typedef struct {
    //            float    life;        // vida
    //            float    fade;        // fade
    //            float    r, g, b;    // color
    //            GLfloat x, y, z;    // posição
    //            GLfloat vx, vy, vz; // velocidade
    //            GLfloat ax, ay, az; // aceleração
    //        } Particle;
    //         int fireworks = 0;
    //        Particle particula[MAX_PARTICULAS];
public:
    
    Fireworks(GLfloat v,GLfloat phi, GLfloat theta, float x, float y, float z);
    void render(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformdId, GLint texMode_uniformId);
    float vx,vy,vz,ax,ay,az,life,fade;
    //        void iniParticulas(void);
    //        void iterate(int value);
};

#endif /* Fireworks_h */

