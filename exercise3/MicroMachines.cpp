#include "MicroMachines.h"

struct MyMesh mesh[NUM_OBJECTS];
int objId = 0;

MicroMachines::MicroMachines()
{
    _car = new Car();
    
    _objects.push_back(_car);
    
    _cameras.push_back(new OrthogonalCamera(-5, 5, -5, 5, -50, 50));    // camera option #0
    _cameras.push_back(new PerspectiveCamera(53.13f, 0.1f, 1000.0f));   // camera option #1
    _cameras.push_back(new PerspectiveCamera(53.13f, 0.1f, 1000.0f));   // camera option #2
    
    _current_camera = 2;
}

MicroMachines::~MicroMachines(){}

void MicroMachines::renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    loadIdentity(VIEW);
    loadIdentity(MODEL);
    
    /*FIXME: Choose lookAt according to selected camera*/
    lookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);

    // Use shader program
    glUseProgram(shader.getProgramIndex());
    
    // Send the light position in eye coordinates
    float res[4];
    multMatrixPoint(VIEW, lightPos, res);
    glUniform4fv(lPos_uniformId, 1, res);
   
    _objects[0]->render(shader, pvm_uniformId, vm_uniformId, normal_uniformId);
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
    loadIdentity(PROJECTION);
    _cameras[_current_camera]->update(ratio);
}

void MicroMachines::processKeys(unsigned char key, int xx, int yy){
    switch (key) {
        case 49:
            _current_camera = 0;
            break;
        case 50:
            _current_camera = 1;
            break;
        case 51:
            _current_camera = 2;
            break;
        case 27:
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
    
    //Assigning meshes to car
    _objects[0]->assignMesh(&mesh[0]);
    _objects[0]->assignMesh(&mesh[1]);
  
    // some GL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}
