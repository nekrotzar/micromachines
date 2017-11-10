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

#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include "LightSource.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Spotlight.h"
#include "Life.h"
#include "Points.h"
#include "Pause.h"
#include "GameOver.h"
#include "Car.h"
#include "Table.h"
#include "Cheerio.h"
#include "Orange.h"
#include "Butter.h"
#include "Candle.h"

#include "vsShaderLib.h"
#include "VertexAttrDef.h"
#include "AVTmathLib.h"

#define NUM_OBJECTS 100
#define NUM_LIGHTS 10
#define NUM_TEXTURES 6

class MicroMachines{
public:
    MicroMachines();
    ~MicroMachines();
    void start();
    void init();
    void display();
	int collides();
    int orange_collide();
    void reshape(int width, int height);
    void processKeys(unsigned char key, int xx, int yy);
    void processSpecialKeys(int key, int x, int y);
    void processSpecialUpKeys(int key, int x, int y);
    void keySpecialOperations();
    void processMouseButtons(int button, int state, int xx, int yy);
    void processMouseMotion(int xx, int yy);
    void processMouseWheel(int wheel, int direction, int x, int y);
    GLuint setupShaders();
    void deleteAll();
    void setCamera();
	bool getPause();
    void initTextureMappedFont();
    void DrawString(float x, float y, const std::string& str);
protected:
    bool _camera_trigger;
    bool* keySpecialStates = new bool[246];
	bool pause = false;
    
    VSShaderLib shader;
    
    GLint pvm_uniformId;
    GLint vm_uniformId;
    GLint normal_uniformId;
    GLint texMode_uniformId;
    GLint tex_loc0, tex_loc1;
    
    GLuint TextureArray[NUM_TEXTURES];
        
    float camX, camY, camZ;
    int startX, startY, tracking = 0;
    float alpha = 39.0f, beta = 51.0f;
    float r = 10.0f;
    
    Car *_car;
	Table *_table;
    
    Spotlight * _spot1;
    Spotlight * _spot2;
    
    std::vector<LightSource*> _lights;
    std::vector<Object*> _objects;
	std::vector<Orange*> _oranges;
    std::vector<Life*> _lives;
    std::vector<Camera*> _cameras;
    std::vector<Object*> _hud;
    
    int _current_camera;
    int lives = 5;
    int points = 0;
    bool finished = false;
    
    //===Fonts
    float _fontSize = 16.0;
    GLuint text_vaoID;
    GLuint text_texCoordBuffer;
    GLuint text_vertexBuffer;
    GLint doingText_uniformId;
    GLint doingTextV_uniformId;
};


#endif /* MicroMachines_h */
