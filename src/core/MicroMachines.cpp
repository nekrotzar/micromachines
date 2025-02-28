#include "MicroMachines.h"

MicroMachines::MicroMachines(){
    init();
}

MicroMachines::~MicroMachines(){
    for (auto &object : _objects) {
        delete object;
    }
    
    for (auto &orange : _oranges) {
        delete orange;
    }
    
    for (auto &camera : _cameras) {
        delete camera;
    }
}

void MicroMachines::init(){
    
    // set the camera position based on its spherical coordinates
    camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
    camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
    camY = r * sin(beta * 3.14f / 180.0f);
    
    // clear all entities in the scene
    _objects.clear();
    _oranges.clear();
    _lights.clear();
    _cameras.clear();
    _lives.clear();
    _hud.clear();
    _fireworks.clear();
    
    
    _carUp = _carDown = _carLeft = _carRight = false;
    pause = false;
    kaboom = false;
    current_camera = 0;
    
    // setup shaders
    if (!setupShaders()) {
        exit(1);
    }
    
    // create objects and meshes
    _car = new Car();
    _table = new Table();
    _cup = new Cup();
    _vase = new Vase();
    _lensFlare = new LensFlare();
    _ground = new Ground();
    _sun = new Sun();
    
    // create hud
    _hud.push_back(new Pause());
    _hud.push_back(new GameOver());
    
    for (int i = 0; i < n_lives; i++) {
        _lives.push_back(new Life());
    }

    _objects.push_back(_table);
    _objects.push_back(_car);
    
    srand( static_cast<unsigned int>(time(NULL)));
    
    // create oranges
    for (int i = 0; i < 5; i++){
        _oranges.push_back(new Orange((double)(rand() % 23 + (-13) + ((rand() % 99) / 100)), (double)(rand() % 23 + (-13) + ((rand() % 99) / 100))));
        _oranges[i]->setSpeed(0);
        _oranges[i]->setAngle(rand() % 360);
    }
    
    // create butters
    for (int i = 0; i < 5; i++){
        _objects.push_back(new Butter((double)(rand() % 23 + (-13) + ((rand() % 99) / 100)), (double)(rand() % 23 + (-13) + ((rand() % 99) / 100))));
    }
    
    // create candles
    for (int i = 0; i < 6; i++){
        _objects.push_back(new Candle());
    }
    
    //create fireworks
    for(int i=0;i<MAX_PARTICULAS;i++){
        _fireworks.push_back(new Fireworks(0.8*frand() + 0.2 , frand()*M_PI , 2.0*frand()*M_PI, _car->getPosition().getX(), _car->getPosition().getY(), _car->getPosition().getZ()));
    }
    
    _objects[7]->setPosition(5 , 1.5,  0);
    _objects[8]->setPosition(-9 , 1.5,  9);
    _objects[9]->setPosition(-9 , 1.5,  -9);
    _objects[10]->setPosition(9 , 1.5,  9);
    _objects[11]->setPosition(9 , 1.5,  -9);
    _objects[12]->setPosition(-5 , 1.5,  0);
    
    _lives[0]->setPosition(-10, -10, 0);
    _lives[1]->setPosition(-9, -10, 0);
    _lives[2]->setPosition(-8, -10, 0);
    _lives[3]->setPosition(-7, -10, 0);
    _lives[4]->setPosition(-6, -10, 0);
    
    // create cheerios
    int angle = 0, angle1 = 0, g = 0, j = 0;
    float x = 0, x1 = 0;
    float y = 0, y1 = 0;
    
    //======= Exterior Elipse ======
    while (g < 45) {
        x = 9.0 * cos((angle * PI) / 180);
        y = 9.0 * sin((angle * PI) / 180);
        _objects.push_back(new Cheerio(x, y));
        angle += 8;
        g++;
    }
    //======= Interior Elipse ======
    while (j < 36) {
        x1 = 12.0 * cos((angle1 * PI) / 180);
        y1 = 10.5 * sin((angle1 * PI) / 180);
        _objects.push_back(new Cheerio(x1, y1));
        angle1 += 10;
        j++;
    }    
    
    // create cameras
    _cameras.push_back(new OrthogonalCamera(-15.5, 15.5, -15.5, 15.5, -5, 100));    // camera option #0
    _cameras.push_back(new PerspectiveCamera(53.13f, 0.1f, 1000.0f));               // camera option #1
    _cameras.push_back(new PerspectiveCamera(93.13f, 0.1f, 1000.0f));               // camera option #2
    
    // create light sources
    _lights.push_back(new DirectionalLight(vec3(-1.0,1.0,0.0)));  // Directional Light #0
    _lights.push_back(new PointLight(vec3(5,3.25,0)));         // Point Light #1
    _lights.push_back(new PointLight(vec3(-9,3.25,9)));        // Point Light #2
    _lights.push_back(new PointLight(vec3(-9,3.25,-9)));       // Point Light #3
    _lights.push_back(new PointLight(vec3(9,3.25,9)));         // Point Light #4
    _lights.push_back(new PointLight(vec3(9,3.25,-9)));        // Point Light #5
    _lights.push_back(new PointLight(vec3(-5,3.25,0)));        // Point Light #6
    
    _spot1 = new Spotlight(vec3(0.0,1,0.0));
    _spot2 = new Spotlight(vec3(0.0,1,0.0));
    
    _lights.push_back(_spot1);            // Spot Light #7
    _lights.push_back(_spot2);          // Spot Light #8
    
    // some GL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MicroMachines::explosion(){
    int i;
    float h;
    h = 0.125f;
    for (i = 0; i < MAX_PARTICULAS; i++)
    {
        if(_fireworks[i]->life <= 0){
            kaboom=false;
        }
        _fireworks[i]->setPosition(_fireworks[i]->getPosition().getX() + h *_fireworks[i]->vx,
                                   _fireworks[i]->getPosition().getY() + h * _fireworks[i]->vy,
                                   _fireworks[i]->getPosition().getZ() + h *_fireworks[i]->vz);
        //_fireworks[i]->vx = h * _fireworks[i]->ax;
        //_fireworks[i]->vy = h * _fireworks[i]->ay;
        _fireworks[i]->vz = h * _fireworks[i]->az;
        _fireworks[i]->life -= _fireworks[i]->fade;
    }
}

void MicroMachines::display()
{
    float backgroundColor[3];
    
    if(!night){
        backgroundColor[0] =1.0-0.19607;
        backgroundColor[1] =1-0.013333f;
        backgroundColor[2] =1-0.0432f;
    } else {
        backgroundColor[0] =0.1;
        backgroundColor[1] =0.1;
        backgroundColor[2] =0.1;
    }
    
    glClearColor(backgroundColor[0], backgroundColor[1] , backgroundColor[2], 1.0f);
    
    keySpecialOperations();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    loadIdentity(VIEW);
    loadIdentity(MODEL);
    
    // Uncomment for cameras to work properly
    reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    
    double carX = _car->getPosition().getX();
    double carY = _car->getPosition().getY();
    double carZ = _car->getPosition().getZ();
    double angle = _car->getAngle() * PI / 180;
    
    // Select camera
    switch (current_camera) {
        case 0:
            lookAt(0, 20, 0, 0, 0, 0, 1, 0, 0);
            break;
        case 1:
            lookAt(camX, camY , camZ, 0, 0, 0, 0, 1, 0);
            break;
        case 2:
            lookAt(carX - 1 * sin(angle),
                   carY + 0.6,
                   carZ - 1 * cos(angle),
                   carX,
                   carY,
                   carZ ,
                   0, 1, 0);
            break;
        default:
            break;
    }
    
    // Use shader program
    glUseProgram(shader.getProgramIndex());
    glUniform1i(tex_loc0, 0);
    glUniform1i(tex_loc1, 1);
    glUniform1i(fog_loc, fog);
    
    float fogColor[4];
    if(!night){
         fogColor[0] = 0.7, fogColor[1] = 0.7, fogColor[2] = 0.7, fogColor[3] = 1.0;
    } else {
        fogColor[0] = 0.051, fogColor[1] = 0.05, fogColor[2] = 0.05, fogColor[3] = 1.0;

    }
    
    
    glUniform4fv(fogColor_loc,1,fogColor);
    
    _spot1->setPosition(carX + sin(angle) , carY + 0.1,  carZ + cos(angle));
    _spot2->setPosition(carX + sin(angle) , carY + 0.1,  carZ + cos(angle));

    // Send the light position in eye coordinates
    
    // draw directional light
    _lights[0]->draw(shader,0);
    
    // draw point lights
    for (int i = 0; i < 6; i++)
        _lights[i+1]->draw(shader, i);
    
    // draw spot lights

    if (current_camera == 2) {
        _spot1->setDirection(vec3(carX + sin(angle),0.4,carZ + cos(angle)));
        _spot2->setDirection(vec3(carX + sin(angle),0.4,carZ + cos(angle)));

    } else {
        _spot1->setDirection(vec3(sin(angle), 8, cos(angle)));
        _spot2->setDirection(vec3(sin(angle), 8, cos(angle)));
    }
    _lights[7]->draw(shader, 0);
    _lights[8]->draw(shader, 1);
    
    
    // Draw opaque objects
    
    // render objects
    for (auto &object : _objects) {
      object->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId);
    }

    // render oranges
    for (auto &orange : _oranges) {
        orange->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId);
    }
    
    glEnable(GL_STENCIL_TEST);
    
    // Draw the ground
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0xFF);
    glDepthMask(GL_FALSE);
    glClear(GL_STENCIL_BUFFER_BIT);
    
    _ground->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId);
    
    // Draw all the other objects as reflection
    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDepthMask(GL_TRUE);
    glDisable(GL_CULL_FACE);

    glUniform1i(reflect_loc, true);
    
    pushMatrix(MODEL);
    scale(MODEL, 1, -1, 1);
    for (int i = 1; i < _objects.size(); i++) {
        _objects[i]->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId);
    }
    
    for (auto &orange : _oranges) {
        orange->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId);
    }
    
    popMatrix(MODEL);
    glEnable(GL_CULL_FACE);
    glDisable(GL_STENCIL_TEST);
    
    glUniform1i(reflect_loc, false);

    

 
   // _lensFlare->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId);
    float camPos[3];
    if(current_camera == 2){
        camPos[0] = _car->getPosition().getX();
        camPos[1] = _car->getPosition().getY();
        camPos[2] = _car->getPosition().getZ();
    }
    else if (current_camera == 1){
        camPos[0] = camX;
        camPos[1] = camY;
        camPos[2] = camZ;
    }
    _sun->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId, camPos, 3);

    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    computeDerivedMatrix(PROJ_VIEW_MODEL);

    
    SCREENwidth = glutGet( GLUT_WINDOW_WIDTH );
    SCREENheight = glutGet( GLUT_WINDOW_HEIGHT );
    pushMatrix(PROJECTION);
    loadIdentity(PROJECTION);
    pushMatrix(VIEW);
    loadIdentity(VIEW);   //viewer looking down at  negative z direction
    ortho(0, SCREENwidth, 0, SCREENheight, -10.0f, 100.0f);
    _lensFlare->render_flare(shader, xFlare, yFlare, SCREENwidth/2, SCREENheight/2, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId);
    popMatrix(PROJECTION);
    popMatrix(VIEW);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    computeDerivedMatrix(PROJ_VIEW_MODEL);
    
    pushMatrix(PROJECTION);
    loadIdentity(PROJECTION);
    pushMatrix(VIEW);
    loadIdentity(VIEW);   //viewer looking down at  negative z direction
    ortho(-15.0f, 15.0f, -15.0f, 15.0f, -15.0f, 100.0f);
    if(kaboom){
        for (auto &fireworks : _fireworks) {
            fireworks->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId);
        }
    }
    popMatrix(PROJECTION);
    popMatrix(VIEW);
    glDisable(GL_BLEND);
    
    
    if(current_camera == 2){
        camPos[0] = _car->getPosition().getX();
        camPos[1] = _car->getPosition().getY();
        camPos[2] = _car->getPosition().getZ();
        _vase->renderBillboard(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId, camPos, 3);

    }
    else if (current_camera == 1){
        camPos[0] = camX;
        camPos[1] = camY;
        camPos[2] = camZ;
        _vase->renderBillboard(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId, camPos, 2);
    }
    
    

    glEnable(GL_BLEND);
    _cup->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId);
    glDisable(GL_BLEND);
    // render hud
    pushMatrix(PROJECTION);
    loadIdentity(PROJECTION);
    pushMatrix(VIEW);
    loadIdentity(VIEW);
    
    ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 100.0f);
    
    if (pause) {
        _hud[0]->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId);
    }
    
    for (auto &life : _lives) {
        life->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId);
    }
    
    if (game_over) {
        _hud[1]->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId, texMode_uniformId);
    }
    
    popMatrix(VIEW);
    popMatrix(PROJECTION);
}

void MicroMachines::update(int delta_t){
    
    int t = delta_t;
    
    if (pause || game_over)
        t = 0;
    
    keySpecialOperations();
    vec3 tempPos = _car->getPosition();
    
    _car->update(t);
    
    
    for (int i = 0; i < _oranges.size(); i++) {
        _oranges[i]->setAcceleration(_oranges[i]->getAcceleration() + (rand() % 10) * 0.00000000001);
        _oranges[i]->update(t);
        
        if (_oranges[i]->getPosition().getX() >= 15 || _oranges[i]->getPosition().getX() <= -15 || _oranges[i]->getPosition().getZ() >= 15 || _oranges[i]->getPosition().getZ() <= -15) {
            _oranges[i]->setPosition((double)(rand() % 23 + (-13) + ((rand() % 99) / 100)), _oranges[i]->getPosition().getY(), (double)(rand() % 23 + (-13) + ((rand() % 99) / 100)));
        }
        else {
            _oranges[i]->setPosition(_oranges[i]->getSpeed()    * cos((_oranges[i]->getAngle() * PI / 180))    * t / 10000 + _oranges[i]->getPosition().getX(), _oranges[i]->getPosition().getY(), _oranges[i]->getSpeed() * sin((_oranges[i]->getAngle() * PI / 180)) * t / 10000 + _oranges[i]->getPosition().getZ());
        }
    }
    
    // object collision
    int object_collide;
    object_collide = collides();
    
    if (object_collide != 10000) {
        
        if (_car->getSpeed() > 0) {
            _objects[object_collide]->setPosition(_objects[object_collide]->getPosition().getX() + 0.1 * sin((_car->getAngle() * PI / 180)),
                                                  _objects[object_collide]->getPosition().getY(),
                                                  _objects[object_collide]->getPosition().getZ() + 0.1 * cos((_car->getAngle() * PI / 180)));
        
        }

        // Reverse
        else if (_car->getSpeed() < 0) {
            _objects[object_collide]->setPosition(_objects[object_collide]->getPosition().getX() - 0.1 * sin((_car->getAngle() * PI / 180)),
                                                  _objects[object_collide]->getPosition().getY(),
                                                  _objects[object_collide]->getPosition().getZ() - 0.1 * cos((_car->getAngle() * PI / 180)));
        }
        _carUp = false;
        _carDown = false;
        _car->setAcceleration(0.0);
        _car->setSpeed(0.0);

        
    }
    else {
        /*_car->setPosition(_car->getSpeed() * sin((_car->getAngle() * PI / 180)) + _car->getPosition().getX(),
                          _car->getPosition().getY(),
                          _car->getSpeed() * cos((_car->getAngle() * PI / 180)) + _car->getPosition().getZ());
         */
    }

    
    int orang = orange_collide();
    
    // check if car is out of the table
    if (orang == 1 | abs(tempPos.getX()) > 15.5 || abs(tempPos.getZ()) > 15.5) {
        _car->setSpeed(0.0);
        _car->setAcceleration(0.0);
        _car->setAngle(90);
        _car->setPosition(1.4, 0.0, 9.8);

        if (!_lives.empty()) {
            _lives.pop_back();
            orang = 10;
            n_lives--;
        } else{
            game_over = true;
        }
    }
    
    if(kaboom){
        explosion();
    }
    
}

int MicroMachines::collides() {
    for (int i = 2; i < 7; i++) {
        if ((_objects[i]->getPosition().getX() - 0.4 < _car->getPosition().getX()) &&
            (_car->getPosition().getX() < _objects[i]->getPosition().getX() + 1.4) &&
            (_objects[i]->getPosition().getZ() - 0.4 < _car->getPosition().getZ()) &&
            (_car->getPosition().getZ() < _objects[i]->getPosition().getZ() + 1.0)) {
            return i;
        }
    }
    for (int i = 13; i < 94; i++) {
        if ((_objects[i]->getPosition().getX() - 0.4 < _car->getPosition().getX()) &&
            (_car->getPosition().getX() < _objects[i]->getPosition().getX() + 0.4) &&
            (_objects[i]->getPosition().getZ() - 0.4 < _car->getPosition().getZ()) &&
            (_car->getPosition().getZ() < _objects[i]->getPosition().getZ() + 0.4)) {
            return i;
        }
    }
    return 10000;
}

int MicroMachines::orange_collide() {
    for (int i = 0; i < 5; i++) {
        if ((_oranges[i]->getPosition().getX() - 0.8 < _car->getPosition().getX()) &&
            (_car->getPosition().getX() < _oranges[i]->getPosition().getX() + 0.8) &&
            (_oranges[i]->getPosition().getZ() - 0.8 < _car->getPosition().getZ()) &&
            (_car->getPosition().getZ() < _oranges[i]->getPosition().getZ() + 0.8)) {
            return 1;
        }
    }
    return 0;
}

void MicroMachines::reshape(int width, int height)
{
    float ratio;
    // Prevent a divide by zero, when window is too short
    if(height == 0)
        height = 1;
    // set the viewport to be the entire window
    glViewport(0, 0, width, height);
    // set the projection matrix
    ratio = (1.0f * width) / height;
    _cameras[current_camera]->update(ratio);
}

void MicroMachines::processKeys(unsigned char key, int xx, int yy){
    switch (key) {
        case 52:
            current_camera = 0;
            break;
        case 53:
            current_camera = 1;
            break;
        case 54:
            current_camera = 2;
            break;
        case 27:
            #ifdef __APPLE__
            exit(1);
            #else
            glutLeaveMainLoop();
            #endif
            break;
        case 'c':
            for (int i = 1; i < 7 ; ++i) {
                _lights[i]->setState(!_lights[i]->getState());
            }
            break;
        case 'h':
            for (int i = 7; i < 9; ++i) {
                _lights[i]->setState(!_lights[i]->getState());
            }
            break;
        case 'm':
            glEnable(GL_MULTISAMPLE);
            break;
        case 'n':
            night = !night;
            _lights[0]->setState(!_lights[0]->getState());
            break;
		case 's':
			pause = !pause;
        case 'r':
            if(game_over){
                n_lives = 5;
                game_over = false;
                init();
            }
            break;
        case 'f':
            fog = !fog;
            break;
        case 'e':
            //            _fireworks->fireworks = 1;
            //            _fireworks->iniParticulas();
            //            _fireworks->iterate(1);
            //            //glutTimerFunc(0, _fireworks->iterate, 0);  //timer for particle system
            if(kaboom){
                kaboom = false;
                _fireworks.clear();
            }else{
                for(int i=0;i<MAX_PARTICULAS;i++){
                    v = 0.8*frand() + 0.2;
                    phi = frand()*M_PI;
                    theta = 2.0*frand()*M_PI;
                    _fireworks.push_back(new Fireworks( v, phi , theta, _car->getPosition().getX(), _car->getPosition().getY(), _car->getPosition().getZ()));
                    _fireworks[i]->life = 1.0f;
                    _fireworks[i]->fade = 0.005f;
                    _fireworks[i]->ax = 0.1f;
                    _fireworks[i]->ay = -0.15f;
                    _fireworks[i]->az = 0.0f;
                }
                kaboom = true;
            }
            break;
    }
}

void MicroMachines::processSpecialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            _carUp = true;
            break;
        case GLUT_KEY_DOWN:
            _carDown = true;
            break;
        case GLUT_KEY_LEFT:
            _carLeft = true;
            break;
        case GLUT_KEY_RIGHT:
            _carRight = true;
            break;
    }
}

void MicroMachines::processSpecialUpKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            _carUp = false;
            break;
        case GLUT_KEY_DOWN:
            _carDown = false;
            break;
        case GLUT_KEY_LEFT:
            _carLeft = false;
            break;
        case GLUT_KEY_RIGHT:
            _carRight = false;
            break;
    }
}

void MicroMachines::keySpecialOperations() {
    if (!pause && !game_over) {
        if (_carUp) {
            _car->setAcceleration(0.0001);
        } else if (_carDown) {
            _car->setAcceleration(-0.00009);
        } else if (_car->getSpeed() != 0) {
            if (fabs(_car->getSpeed()) < 0.0001) {
                _car->setSpeed(0);
                _car->setAcceleration(0);
            } else if (_car->getSpeed() < 0) {
                _car->setAcceleration(0.000004);
            } else {
                _car->setAcceleration(-0.00004);
            }
        }
    }
    
    if (_car->getSpeed() != 0 && !pause && !game_over) {
        if (_carLeft) {
            _car->setAngle(_car->getAngle() + 2);
        } else if (_carRight) {
            _car->setAngle(_car->getAngle() - 2);
        }
    }
}

void MicroMachines::processMouseButtons(int button, int state, int xx, int yy){
    // start tracking the mouse
    if (state == 0)  {
        startX = xx;
        startY = yy;
        if (button == 0)
            tracking = 1;
        else if (button == 2)
            tracking = 2;
    }
    
    //stop tracking the mouse
    else if (state == 1) {
        if (tracking == 1) {
            alpha -= (xx - startX);
            beta += (yy - startY);
        }
        else if (tracking == 2) {
            r += (yy - startY) * 0.01f;
            if (r < 0.1f)
                r = 0.1f;
        }
        tracking = 0;
    }
}

void MicroMachines::processMouseMotion(int xx, int yy)
{
    int deltaX, deltaY;
    float alphaAux, betaAux;
    float rAux;
    
    deltaX =  - xx + startX;
    deltaY =    yy - startY;
    
    // left mouse button: move camera
    if (tracking == 1) {
        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;
        
        if (betaAux > 60)
            betaAux = 60;
        else if (betaAux < 15.0f)
            betaAux = 15.0f;
        rAux = r;
    }
    // right mouse button: zoom
    else if (tracking == 2) {
        
        alphaAux = alpha;
        betaAux = beta;
        rAux = r + (deltaY * 0.01f);
        if (rAux < 0.1f)
            rAux = 0.1f;
    }
    
    camX = rAux * sin(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
    camZ = rAux * cos(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
    camY = rAux * sin(betaAux * 3.14f / 180.0f);
    
    //  uncomment this if not using an idle func
    //    glutPostRedisplay();
    
    if (current_camera == 1) {
        xFlare = deltaX * SCREENwidth/glutGet(GLUT_WINDOW_WIDTH);
        yFlare = deltaY * SCREENheight/glutGet(GLUT_WINDOW_HEIGHT);
        if ( xFlare >= SCREENwidth )
            xFlare = SCREENwidth - 1;
        if ( xFlare < 0 )
            xFlare = 0;
        if ( yFlare >= SCREENheight )
            yFlare = SCREENheight - 1;
        if ( yFlare < 0 )
            yFlare = 0;
    } else {
        
    }

}

void MicroMachines::processMouseWheel(int wheel, int direction, int x, int y){
    r += direction * 0.1f;
    if (r < 0.1f)
        r = 0.1f;
    
    camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
    camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
    camY = r *                                sin(beta * 3.14f / 180.0f);
    
    //  uncomment this if not using an idle func
    //    glutPostRedisplay();
}

GLuint MicroMachines::setupShaders(){
    // Shader for models
    shader.init();
    shader.loadShader(VSShaderLib::VERTEX_SHADER, "data/shaders/pointlight.vert");
    shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "data/shaders/pointlight.frag");
    
    // set semantics for the shader variables
    glBindFragDataLocation(shader.getProgramIndex(), 0,"colorOut");
    glBindAttribLocation(shader.getProgramIndex(), VERTEX_COORD_ATTRIB, "position");
    glBindAttribLocation(shader.getProgramIndex(), NORMAL_ATTRIB, "normal");
    glBindAttribLocation(shader.getProgramIndex(), TEXTURE_COORD_ATTRIB, "texCoord");
    
    glLinkProgram(shader.getProgramIndex());
    
    pvm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_pvm");
    vm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_viewModel");
    normal_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_normal");
    //lPos_uniformId = glGetUniformLocation(shader.getProgramIndex(), "l_pos");

    texMode_uniformId = glGetUniformLocation(shader.getProgramIndex(), "texMode");
    tex_loc0 = glGetUniformLocation(shader.getProgramIndex(), "texmap0");
    tex_loc1 = glGetUniformLocation(shader.getProgramIndex(), "texmap1");
    fog_loc = glGetUniformLocation(shader.getProgramIndex(), "fog");
    fogColor_loc = glGetUniformLocation(shader.getProgramIndex(), "fogColor");
    reflect_loc = glGetUniformLocation(shader.getProgramIndex(), "darkReflections");

    
    printf("InfoLog for Hello World Shader\n%s\n\n", shader.getAllInfoLogs().c_str());
    
    return(shader.isProgramLinked());
}


