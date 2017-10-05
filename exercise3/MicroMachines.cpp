#include "MicroMachines.h"

struct MyMesh mesh[OBJECT_NUMBER];
int objId = 0;

MicroMachines::MicroMachines()
{
    _cameras.push_back(new OrthogonalCamera(-5, 5, -5, 5, -50, 50));    // camera option #0
    _cameras.push_back(new PerspectiveCamera(53.13f, 0.1f, 1000.0f));   // camera option #1
    _cameras.push_back(new PerspectiveCamera(53.13f, 0.1f, 1000.0f));   // camera option #2
    
    _current_camera = 1;
}

MicroMachines::~MicroMachines(){}

void MicroMachines::renderScene()
{
    GLint loc;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    loadIdentity(VIEW);
    loadIdentity(MODEL);
    
    /*FIXME: Choose lookAt according to selected camera*/
    //lookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);
    
    if (_current_camera == 2) {
            lookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);
    } else {
        lookAt(0, -10, 0, 0, 0, 0, 0, 0, 1);
    }

    // Use shader program
    glUseProgram(shader.getProgramIndex());
    
    // Send the light position in eye coordinates
    float res[4];
    multMatrixPoint(VIEW, lightPos, res);
    glUniform4fv(lPos_uniformId, 1, res);
    
    /*FIXME: Send the material and apply transformations for each object */
    objId = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            loc = glGetUniformLocation(shader.getProgramIndex(), "mat.ambient");
            glUniform4fv(loc, 1, mesh[objId].mat.ambient);
            loc = glGetUniformLocation(shader.getProgramIndex(), "mat.diffuse");
            glUniform4fv(loc, 1, mesh[objId].mat.diffuse);
            loc = glGetUniformLocation(shader.getProgramIndex(), "mat.specular");
            glUniform4fv(loc, 1, mesh[objId].mat.specular);
            loc = glGetUniformLocation(shader.getProgramIndex(), "mat.shininess");
            glUniform1f(loc,mesh[objId].mat.shininess);
            
            pushMatrix(MODEL);
            translate(MODEL, i * 2.0f, 0.0f, j * 2.0f);
            
            // send matrices to OGL
            computeDerivedMatrix(PROJ_VIEW_MODEL);
            glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
            glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
            computeNormalMatrix3x3();
            glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);
            
            // Render mesh
            glBindVertexArray(mesh[objId].vao);
            glDrawElements(mesh[objId].type,mesh[objId].numIndexes, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
            
            popMatrix(MODEL);
            objId++;
        }
    }
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

void MicroMachines::load()
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
    
    // create geometry and VAO of the pawn
    objId=0;
    memcpy(mesh[objId].mat.ambient, amb,4*sizeof(float));
    memcpy(mesh[objId].mat.diffuse, diff,4*sizeof(float));
    memcpy(mesh[objId].mat.specular, spec,4*sizeof(float));
    memcpy(mesh[objId].mat.emissive, emissive,4*sizeof(float));
    mesh[objId].mat.shininess = shininess;
    mesh[objId].mat.texCount = texcount;
    createPawn();
    
    // create geometry and VAO of the sphere
    objId=1;
    memcpy(mesh[objId].mat.ambient, amb,4*sizeof(float));
    memcpy(mesh[objId].mat.diffuse, diff,4*sizeof(float));
    memcpy(mesh[objId].mat.specular, spec,4*sizeof(float));
    memcpy(mesh[objId].mat.emissive, emissive,4*sizeof(float));
    mesh[objId].mat.shininess = shininess;
    mesh[objId].mat.texCount = texcount;
    createSphere(1.0f, 20);
    
    float amb1[]= {0.3f, 0.0f, 0.0f, 1.0f};
    float diff1[] = {0.8f, 0.1f, 0.1f, 1.0f};
    float spec1[] = {0.9f, 0.9f, 0.9f, 1.0f};
    shininess=500.0;
    
    // create geometry and VAO of the cylinder
    objId=2;
    memcpy(mesh[objId].mat.ambient, amb1,4*sizeof(float));
    memcpy(mesh[objId].mat.diffuse, diff1,4*sizeof(float));
    memcpy(mesh[objId].mat.specular, spec1,4*sizeof(float));
    memcpy(mesh[objId].mat.emissive, emissive,4*sizeof(float));
    mesh[objId].mat.shininess = shininess;
    mesh[objId].mat.texCount = texcount;
    createCylinder(1.5f,0.5f,20);
    
    // create geometry and VAO of the
    objId=3;
    memcpy(mesh[objId].mat.ambient, amb1,4*sizeof(float));
    memcpy(mesh[objId].mat.diffuse, diff1,4*sizeof(float));
    memcpy(mesh[objId].mat.specular, spec1,4*sizeof(float));
    memcpy(mesh[objId].mat.emissive, emissive,4*sizeof(float));
    mesh[objId].mat.shininess = shininess;
    mesh[objId].mat.texCount = texcount;
    createCone(1.5f,0.5f, 20);
    
    // some GL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}
