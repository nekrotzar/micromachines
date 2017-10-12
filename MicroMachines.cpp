#include "MicroMachines.h"

struct MyMesh mesh[NUM_OBJECTS];
int objId = 0;

MicroMachines::MicroMachines()
{
    int i = 0;
    while (i < 247) {
        keySpecialStates[i] = false;
        i++;
    }
    _camera_trigger = false;
    
    _table = new Table();
    _car = new Car();
	//_orange = new Orange(14.0,14.0);
	_butter = new Butter();
   
    _objects.push_back(_table);
	_objects.push_back(_car);
	_objects.push_back(new Orange(14.0, 10.0));
	_objects.push_back(new Orange(14.0, 9.0));
	_objects.push_back(_butter);

    _cameras.push_back(new OrthogonalCamera(-15, 15, -15, 15, -5, 100));    // camera option #0
    _cameras.push_back(new PerspectiveCamera(53.13f, 10.0f, 1000.0f));   // camera option #1
    _cameras.push_back(new PerspectiveCamera(93.13f, 0.1f, 1000.0f));   // camera option #2
    
    _current_camera = 0;
}

MicroMachines::~MicroMachines(){}

void MicroMachines::deleteAll(){
    
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

void MicroMachines::renderScene()
{
    keySpecialOperations();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    loadIdentity(VIEW);
    loadIdentity(MODEL);
    
    if (_current_camera == 0) {
        lookAt(0, 95, 0, 0, 0, 0, 20, 60, 0);
    }
    if (_current_camera == 1) {
        lookAt(-7.5, 20, 0.0, 0.0, 0, 0.0, 0, 1, 0);
    }
    if (_current_camera == 2)
    {
        lookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);
    }
    
    
    /*FIXME: Choose lookAt according to selected camera*/
    
    /*
    if (_camera_trigger == true) {
        _camera_trigger = false;
        
        GLuint w = glutGet(GLUT_WINDOW_WIDTH);
        GLuint h = glutGet(GLUT_WINDOW_HEIGHT);
        
        float ratio = w / h;
        _cameras[_current_camera]->update(ratio);
        
        if (_current_camera == 0) {
            //lookAt(7.5, 20, 7.5, 7.6, 0, 7.5, 0, 1, 0);
        }
        if (_current_camera == 1)
        {
            lookAt(7.5, 20, 7.5, 7.6, 0, 7.5, 0, 1, 0);
        }
        if (_current_camera == 2)
        {
            lookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);
        }
    }
    
    
   if (_current_camera == 2) {
        lookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);
    }
    */

    // Use shader program
    glUseProgram(shader.getProgramIndex());
    
    // Send the light position in eye coordinates
    float res[4];
    multMatrixPoint(VIEW, lightPos, res);
    glUniform4fv(lPos_uniformId, 1, res);
    
    for (auto &object : _objects) {
        object->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId);
    }

	for (auto &orange : _oranges) {
		orange->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId);
	}
    
    if (keySpecialStates[GLUT_KEY_UP] == false
        && keySpecialStates[GLUT_KEY_DOWN] == false) {
        if (_car->getSpeed() < 0) {
            if (_car->getSpeed() + 0.001 < 0) {
                _car->setSpeed(_car->getSpeed() + 0.001);
            } else {
                _car->setSpeed(0.0);
            }
        } else if (_car->getSpeed() > 0) {
            if (_car->getSpeed() - 0.001 > 0) {
                _car->setSpeed(_car->getSpeed() - 0.001);
            } else {
                _car->setSpeed(0.0);
            }
        }
    }
    _car->setPosition(_car->getSpeed() * sin((_car->getAngle() * PI / 180)) + _car->getPosition().getX(),
                      _car->getPosition().getY(),
                     _car->getSpeed() * cos((_car->getAngle() * PI / 180)) + _car->getPosition().getZ());
}

void MicroMachines::resize(int width, int height)
{
    float ratio;
    // Prevent a divide by zero, when window is too short
    if(height == 0)
        height = 1;
    // set the viewport to be the entire window
    glViewport(0, 0, width, height);
    // set the projection matrix
    ratio = (1.0f * width) / height;
    _cameras[_current_camera]->update(ratio);
}

void MicroMachines::processKeys(unsigned char key, int xx, int yy){
    switch (key) {
        case 49:
            _current_camera = 0;
            _camera_trigger = true;
            break;
        case 50:
            _current_camera = 1;
            _camera_trigger = true;
            break;
        case 51:
            _current_camera = 2;
            _camera_trigger = true;
            break;
        case 27:
            deleteAll();
            exit(1);
            break;
        case 'c':
            printf("Camera Spherical Coordinates (%f, %f, %f)\n", alpha, beta, r);
            break;
        case 'm':
            glEnable(GL_MULTISAMPLE);
            break;
        case 'n':
            glDisable(GL_MULTISAMPLE);
            break;
        default:
            break;
    }
}

void MicroMachines::keyPressed(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        keySpecialStates[key] = true;
    } else if (key == GLUT_KEY_DOWN) {
        keySpecialStates[key] = true;
    }
    if (key == GLUT_KEY_RIGHT) {
        keySpecialStates[key] = true;
    }
    else if (key == GLUT_KEY_LEFT) {
        keySpecialStates[key] = true;
    }
    
}

void MicroMachines::specialUpKey(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        keySpecialStates[key] = false;
    }
    if (key == GLUT_KEY_DOWN) {
        keySpecialStates[key] = false;
    }
    if (key == GLUT_KEY_RIGHT) {
        keySpecialStates[key] = false;
    }
    if (key == GLUT_KEY_LEFT) {
        keySpecialStates[key] = false;
    }
}

void MicroMachines::keySpecialOperations() {

    double angle = _car->getAngle();
    if (keySpecialStates[GLUT_KEY_UP]) {
        _car->setSpeed(_car->getSpeed() + 0.003);
    }
    else if (keySpecialStates[GLUT_KEY_DOWN]) {
        _car->setSpeed(_car->getSpeed() - 0.003);
    }

    if (keySpecialStates[GLUT_KEY_RIGHT]) {
        angle -= 3;
        _car->setAngle(angle);
    }
    else if (keySpecialStates[GLUT_KEY_LEFT]) {
        angle += 3;
        _car->setAngle(angle);
    }

    if (_car->getSpeed() >= 0.025) {
        _car->setSpeed(0.025);
    }

    if (_car->getSpeed() <= -0.025) {
        _car->setSpeed(-0.025);
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
        
        if (betaAux > 85.0f)
            betaAux = 85.0f;
        else if (betaAux < -85.0f)
            betaAux = -85.0f;
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

GLuint MicroMachines::setupShaders()
{
    // Shader for models
    shader.init();
    shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/pointlight.vert");
    shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/pointlight.frag");
    
    // set semantics for the shader variables
    glBindFragDataLocation(shader.getProgramIndex(), 0,"colorOut");
    glBindAttribLocation(shader.getProgramIndex(), VERTEX_COORD_ATTRIB, "position");
    glBindAttribLocation(shader.getProgramIndex(), NORMAL_ATTRIB, "normal");
    
    //Following line comment because shader file does not have texCoord attribute
    //glBindAttribLocation(shader.getProgramIndex(), TEXTURE_COORD_ATTRIB, "texCoord");
    
    glLinkProgram(shader.getProgramIndex());
    
    pvm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_pvm");
    vm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_viewModel");
    normal_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_normal");
    lPos_uniformId = glGetUniformLocation(shader.getProgramIndex(), "l_pos");
    
    printf("InfoLog for Hello World Shader\n%s\n\n", shader.getAllInfoLogs().c_str());
    
    return(shader.isProgramLinked());
}

void MicroMachines::init()
{
    // set the camera position based on its spherical coordinates
    camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
    camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
    camY = r * sin(beta * 3.14f / 180.0f);
    
    float amb[]= {0.2f, 0.15f, 0.1f, 1.0f};
    float diff[] = {0.8f, 0.6f, 0.4f, 1.0f};
    float spec[] = {0.8f, 0.8f, 0.8f, 1.0f};
    float emissive[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float shininess= 100.0f;
    int texcount = 0;
    
    // create geometry and VAO of the car body
    objId = 0;
    memcpy(mesh[objId].mat.ambient, amb,4*sizeof(float));
    memcpy(mesh[objId].mat.diffuse, diff,4*sizeof(float));
    memcpy(mesh[objId].mat.specular, spec,4*sizeof(float));
    memcpy(mesh[objId].mat.emissive, emissive,4*sizeof(float));
    mesh[objId].mat.shininess = shininess;
    mesh[objId].mat.texCount = texcount;
    createCube();
    
    float amb1[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float diff1[] = {0.1f, 0.1f, 0.1f, 1.0f};
    float spec1[] = {0.1f, 0.1f, 0.1f, 1.0f};
    shininess = 300.0f;
    
    // create geometry and VAO of the car wheel
    objId = 1;
    memcpy(mesh[objId].mat.ambient, amb1,4*sizeof(float));
    memcpy(mesh[objId].mat.diffuse, diff1,4*sizeof(float));
    memcpy(mesh[objId].mat.specular, spec1,4*sizeof(float));
    memcpy(mesh[objId].mat.emissive, emissive,4*sizeof(float));
    mesh[objId].mat.shininess = shininess;
    mesh[objId].mat.texCount = texcount;
    createTorus(0.07, 0.16, 10, 15);

	float amb_table[] = { 0.1f, 0.5f, 0.1f, 1.0f };
	float diff_table[] = { 0.1f, 0.5f, 0.1f, 1.0f };
	float spec_table[] = { 0.1f, 0.5f, 0.1f, 1.0f };
	float emissive_table[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float shininess_table = 100.0f;
	int texcount_table = 0;

	// create geometry and VAO of the table
	objId = 2;
	memcpy(mesh[objId].mat.ambient, amb_table, 4 * sizeof(float));
	memcpy(mesh[objId].mat.diffuse, diff_table, 4 * sizeof(float));
	memcpy(mesh[objId].mat.specular, spec_table, 4 * sizeof(float));
	memcpy(mesh[objId].mat.emissive, emissive_table, 4 * sizeof(float));
	mesh[objId].mat.shininess = shininess_table;
	mesh[objId].mat.texCount = texcount_table;
	createCube();

	float amb_orange[] = { 1.0f, 0.5f, 0.0f, 1.0f };
	float diff_orange[] = { 1.0f, 0.5f, 0.0f, 1.0f };
	float spec_orange[] = { 1.0f, 0.5f, 0.0f, 1.0f };
	float emissive_orange[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float shininess_orange = 100.0f;
	int texcount_orange = 0;

	// create geometry and VAO of the orange
	objId = 3;
	memcpy(mesh[objId].mat.ambient, amb_orange, 4 * sizeof(float));
	memcpy(mesh[objId].mat.diffuse, diff_orange, 4 * sizeof(float));
	memcpy(mesh[objId].mat.specular, spec_orange, 4 * sizeof(float));
	memcpy(mesh[objId].mat.emissive, emissive_orange, 4 * sizeof(float));
	mesh[objId].mat.shininess = shininess_orange;
	mesh[objId].mat.texCount = texcount_orange;
	createSphere(1.0,70);


	float amb_butter[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	float diff_butter[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	float spec_butter[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	float emissive_butter[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float shininess_butter = 100.0f;
	int texcount_butter = 0;

	// create geometry and VAO of the orange
	objId = 4;
	memcpy(mesh[objId].mat.ambient, amb_butter, 4 * sizeof(float));
	memcpy(mesh[objId].mat.diffuse, diff_butter, 4 * sizeof(float));
	memcpy(mesh[objId].mat.specular, spec_butter, 4 * sizeof(float));
	memcpy(mesh[objId].mat.emissive, emissive_butter, 4 * sizeof(float));
	mesh[objId].mat.shininess = shininess_butter;
	mesh[objId].mat.texCount = texcount_butter;
	createCube();

    //Assigning meshes to table
    _objects[0]->assignMesh(&mesh[2]);
    _objects[0]->assignMesh(&mesh[1]);
    
    //Assigning meshes to car
    _objects[1]->assignMesh(&mesh[0]);
    _objects[1]->assignMesh(&mesh[1]);

	//Assigning meshes to orange
	/*for (auto &orange : _oranges)
	{
		orange->assignMesh(&mesh[3]);
	}*/
	_objects[2]->assignMesh(&mesh[3]);
	_objects[3]->assignMesh(&mesh[3]);
	//Assigning meshes to butter
	_objects[4]->assignMesh(&mesh[4]);

    // some GL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}
