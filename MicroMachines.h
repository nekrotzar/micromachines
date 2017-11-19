#ifndef MicroMachines_h
#define MicroMachines_h

#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>

#include <math.h>
#include <GL/glew.h>
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "vsShaderLib.h"

#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include "LightSource.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Spotlight.h"
#include "Life.h"
#include "Pause.h"
#include "GameOver.h"
#include "Car.h"
#include "Table.h"
#include "Cheerio.h"
#include "Orange.h"
#include "Butter.h"
#include "Candle.h"
#include "Cup.h"
#include "Celery.h"
#include "LensFlare.h"
#include "Fireworks.h"
#include "Ground.h"

class MicroMachines{
public:
    MicroMachines();
    ~MicroMachines();
    void init();
    void display();
    void update(int delta_t);
    void reshape(int width, int height);
    void processKeys(unsigned char key, int xx, int yy);
    void processSpecialKeys(int key, int x, int y);
    void processSpecialUpKeys(int key, int x, int y);
    void keySpecialOperations();
    void processMouseButtons(int button, int state, int xx, int yy);
    void processMouseMotion(int xx, int yy);
    void processMouseWheel(int wheel, int direction, int x, int y);
    int collides();
    int orange_collide();
    GLuint setupShaders();
    void explosion();

protected:
    bool fog = false;
	bool pause = false;
    bool game_over = false;
    bool _carUp, _carDown, _carLeft, _carRight = false;
    
    int current_camera;
    int n_lives = 5;

    VSShaderLib shader;
    
    GLint pvm_uniformId;
    GLint vm_uniformId;
    GLint normal_uniformId;
    GLint texMode_uniformId;
    GLint tex_loc0, tex_loc1;
    GLint fog_loc, fogColor_loc;

    GLfloat v, theta, phi;
    bool kaboom;
    
    float camX, camY, camZ;
    int startX, startY, tracking = 0;
    float alpha = 39.0f, beta = 51.0f;
    float r = 10.0f;
    int SCREENwidth = 640;
    int SCREENheight = 480;
    int xFlare = 10;
    int yFlare = 10;

    
    Car *_car;
	Table *_table;
    Cup *_cup;
    Celery *_celery;
    LensFlare *_lensFlare;
    Ground *_ground;
    
    
    Spotlight * _spot1;
    Spotlight * _spot2;
    
    std::vector<Object*> _objects;
    std::vector<Orange*> _oranges;
    std::vector<Camera*> _cameras;
    std::vector<LightSource*> _lights;
    std::vector<Object*> _hud;
    std::vector<Life*> _lives;
    std::vector<Fireworks*> _fireworks;
};


#endif /* MicroMachines_h */
