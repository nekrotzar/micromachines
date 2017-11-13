#include "basic_geometry.h"
#include "cube.h"

extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];
extern float mNormal3x3[9];

GLuint VboId[2];

const aiScene * Mesh::getScene() {
    return scene;
}

void Mesh::renderMeshRecursive(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, const aiScene * sc, const aiNode * nd){
    //Get model transformation matrix
    aiMatrix4x4 m = nd->mTransformation;
    
    //OpenGL matrices are column major
    m.Transpose();
    
    pushMatrix(MODEL);
    float aux[16];
    memcpy(aux, &m, sizeof(float) * 16);
    multMatrix(MODEL, aux);
    
    for (unsigned int i = 0; i < nd->mNumMeshes; ++i) {
        GLint loc;
        
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.ambient");
        glUniform4fv(loc, 1, myMeshes[nd->mMeshes[i]].mat.ambient);
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.diffuse");
        glUniform4fv(loc, 1, myMeshes[nd->mMeshes[i]].mat.diffuse);
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.specular");
        glUniform4fv(loc, 1, myMeshes[nd->mMeshes[i]].mat.specular);
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.emissive");
        glUniform4fv(loc, 1, myMeshes[nd->mMeshes[i]].mat.emissive);
        
        // Bind texture
        glBindTexture(GL_TEXTURE_2D, myMeshes[nd->mMeshes[i]].texIndex);
        
        computeDerivedMatrix(PROJ_VIEW_MODEL);
        glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
        glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
        computeNormalMatrix3x3();
        glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);
        
        // Bind VAO
        glBindVertexArray(myMeshes[nd->mMeshes[i]].vao);
        
        // Draw
        glDrawElements(GL_TRIANGLES, myMeshes[nd->mMeshes[i]].numIndexes * 3, GL_UNSIGNED_INT, 0);
    }
    
    for (unsigned int i = 0; i < nd->mNumChildren; ++i) {
        renderMeshRecursive(shader, pvm_uniformId, vm_uniformId, normal_uniformId, sc, nd->mChildren[i]);
    }
    
    popMatrix(MODEL);
}

void Mesh::loadMeshMaterial(VSShaderLib shader, int meshId) {
    GLint loc;
    
    loc = glGetUniformLocation(shader.getProgramIndex(), "mat.ambient");
    glUniform4fv(loc, 1, myMeshes[meshId].mat.ambient);
    loc = glGetUniformLocation(shader.getProgramIndex(), "mat.diffuse");
    glUniform4fv(loc, 1, myMeshes[meshId].mat.diffuse);
    loc = glGetUniformLocation(shader.getProgramIndex(), "mat.specular");
    glUniform4fv(loc, 1, myMeshes[meshId].mat.specular);
    loc = glGetUniformLocation(shader.getProgramIndex(), "mat.emissive");
    glUniform4fv(loc, 1, myMeshes[meshId].mat.emissive);
}

void Mesh::setMeshMaterial(int meshId, float * ambient, float * diffuse, float * specular, float * emissive, float shininess, float texcount){
    memcpy(myMeshes[meshId].mat.ambient, ambient, 4 * sizeof(float));
    memcpy(myMeshes[meshId].mat.diffuse, diffuse, 4 * sizeof(float));
    memcpy(myMeshes[meshId].mat.specular, specular, 4 * sizeof(float));
    memcpy(myMeshes[meshId].mat.emissive, emissive, 4 * sizeof(float));
    myMeshes[meshId].mat.shininess = shininess;
    myMeshes[meshId].mat.texCount = texcount;
}

void Mesh::renderMesh(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, int meshId){    
    computeDerivedMatrix(PROJ_VIEW_MODEL);
    glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
    glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
    computeNormalMatrix3x3();
    glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);
    
    glBindVertexArray(myMeshes[meshId].vao);
    glDrawElements(myMeshes[meshId].type, myMeshes[meshId].numIndexes, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::set_float4(float f[4], float a, float b, float c, float d){
    f[0] = a;
    f[1] = b;
    f[2] = c;
    f[3] = d;
}

void Mesh::color4_to_float4(const aiColor4D *c, float f[4]){
    f[0] = c->r;
    f[1] = c->g;
    f[2] = c->b;
    f[3] = c->a;
}

void Mesh::get_bounding_box_for_node (const aiNode* nd, aiVector3D* min, aiVector3D* max){
    aiMatrix4x4 prev;
    unsigned int n = 0, t;
    
    for (; n < nd->mNumMeshes; ++n) {
        const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
        for (t = 0; t < mesh->mNumVertices; ++t) {
            
            aiVector3D tmp = mesh->mVertices[t];
            
            min->x = aisgl_min(min->x,tmp.x);
            min->y = aisgl_min(min->y,tmp.y);
            min->z = aisgl_min(min->z,tmp.z);
            
            max->x = aisgl_max(max->x,tmp.x);
            max->y = aisgl_max(max->y,tmp.y);
            max->z = aisgl_max(max->z,tmp.z);
        }
    }
    
    for (n = 0; n < nd->mNumChildren; ++n) {
        get_bounding_box_for_node(nd->mChildren[n],min,max);
    }
}

void Mesh::get_bounding_box (aiVector3D* min, aiVector3D* max){
    min->x = min->y = min->z =  1e10f;
    max->x = max->y = max->z = -1e10f;
    get_bounding_box_for_node(scene->mRootNode,min,max);
}

bool Mesh::Import3DFromFile(const std::string& pFile){
    //check if file exists
    std::ifstream fin(pFile.c_str());
    if(!fin.fail()) {
        fin.close();
    }
    else{
        printf("Couldn't open file: %s\n", pFile.c_str());
        printf("%s\n", importer.GetErrorString());
        return false;
    }
    
    scene = importer.ReadFile( pFile, aiProcessPreset_TargetRealtime_Fast);
    
    // If the import failed, report it
    if( !scene){
        printf("%s\n", importer.GetErrorString());
        return false;
    }
    
    // Now we can access the file's contents.
    printf("Import of scene %s succeeded.\n",pFile.c_str());
    
    aiVector3D scene_min, scene_max, scene_center;
    get_bounding_box(&scene_min, &scene_max);
    float tmp;
    tmp = scene_max.x-scene_min.x;
    tmp = scene_max.y - scene_min.y > tmp?scene_max.y - scene_min.y:tmp;
    tmp = scene_max.z - scene_min.z > tmp?scene_max.z - scene_min.z:tmp;
    scaleFactor = 1.f / tmp;
    
    // We're done. Everything will be cleaned up by the importer destructor
    return true;
}

int Mesh::LoadGLTextures(const aiScene* scene){
    ILboolean success;
    
    /* initialization of DevIL */
    ilInit();
    
    /* scan scene's materials for textures */
    for (unsigned int m=0; m<scene->mNumMaterials; ++m)
    {
        int texIndex = 0;
        aiString path;    // filename
        
        aiReturn texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
        while (texFound == AI_SUCCESS) {
            //fill map with textures, OpenGL image ids set to 0
            textureIdMap[path.data] = 0;
            // more textures?
            texIndex++;
            texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
        }
    }
    
    int numTextures = textureIdMap.size();
    
    /* create and fill array with DevIL texture ids */
    ILuint* imageIds = new ILuint[numTextures];
    ilGenImages(numTextures, imageIds);
    
    /* create and fill array with GL texture ids */
    GLuint* textureIds = new GLuint[numTextures];
    glGenTextures(numTextures, textureIds); /* Texture name generation */
    
    /* get iterator */
    std::map<std::string, GLuint>::iterator itr = textureIdMap.begin();
    int i=0;
    for (; itr != textureIdMap.end(); ++i, ++itr){
        //save IL image ID
        std::string filename = (*itr).first;  // get filename
        (*itr).second = textureIds[i];      // save texture id for filename in map
        
        ilBindImage(imageIds[i]); /* Binding of DevIL image name */
        ilEnable(IL_ORIGIN_SET);
        ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
        success = ilLoadImage((ILstring)filename.c_str());
        
        if (success) {
            /* Convert image to RGBA */
            ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
            
            /* Create and load textures to OpenGL */
            glBindTexture(GL_TEXTURE_2D, textureIds[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH),
                         ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         ilGetData());
        }
        else
            printf("Couldn't load Image: %s\n", filename.c_str());
    }
    /* Because we have already copied image data into texture data
     we can release memory used by image. */
    ilDeleteImages(numTextures, imageIds);
    
    //Cleanup
    delete [] imageIds;
    delete [] textureIds;
    
    //return success;
    return true;
}

void Mesh::createObject(const std::string& pFile){
    if(!Import3DFromFile(pFile)) {
        exit(1);
    }
    
    LoadGLTextures(scene);
    
    struct MyMesh aMesh;
    struct Material aMat;
    GLuint buffer;
    
    // For each mesh
    for(unsigned int n = 0; n < scene->mNumMeshes; ++n){
        const aiMesh* mesh = scene->mMeshes[n];
        
        // create array with faces
        // have to convert from Assimp format to array
        unsigned int *faceArray;
        faceArray = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
        unsigned int faceIndex = 0;
        
        for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
            const aiFace* face = &mesh->mFaces[t];
            
            memcpy(&faceArray[faceIndex], face->mIndices,3 * sizeof(unsigned int));
            faceIndex += 3;
        }
        aMesh.numIndexes = scene->mMeshes[n]->mNumFaces;
        
        // generate Vertex Array for mesh
        glGenVertexArrays(1,&(aMesh.vao));
        glBindVertexArray(aMesh.vao);
        
        // buffer for faces
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, faceArray, GL_STATIC_DRAW);
        
        // buffer for vertex positions
        if (mesh->HasPositions()) {
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(VERTEX_COORD_ATTRIB);
            glVertexAttribPointer(VERTEX_COORD_ATTRIB, 3, GL_FLOAT, 0, 0, 0);
        }
        
        // buffer for vertex normals
        if (mesh->HasNormals()) {
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, mesh->mNormals, GL_STATIC_DRAW);
            glEnableVertexAttribArray(NORMAL_ATTRIB);
            glVertexAttribPointer(NORMAL_ATTRIB, 3, GL_FLOAT, 0, 0, 0);
        }
        
        // buffer for vertex texture coordinates
        if (mesh->HasTextureCoords(0)) {
            float *texCoords = (float *)malloc(sizeof(float)*2*mesh->mNumVertices);
            for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
                
                texCoords[k*2]   = mesh->mTextureCoords[0][k].x;
                texCoords[k*2+1] = mesh->mTextureCoords[0][k].y;
                
            }
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float)*2*mesh->mNumVertices, texCoords, GL_STATIC_DRAW);
            glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB);
            glVertexAttribPointer(TEXTURE_COORD_ATTRIB, 2, GL_FLOAT, 0, 0, 0);
        }
        
        // unbind buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        
        // create material uniform buffer
        aiMaterial *mtl = scene->mMaterials[mesh->mMaterialIndex];
        
        aiString texPath;    //contains filename of texture
        if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texPath)){
            //bind texture
            unsigned int texId = textureIdMap[texPath.data];
            aMesh.texIndex = texId;
            aMat.texCount = 1;
        }
        else
            aMat.texCount = 0;
        
        float c[4];
        
        // Diffuse
        set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
        aiColor4D diffuse;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
            color4_to_float4(&diffuse, c);
        memcpy(aMesh.mat.diffuse, c, sizeof(c));
        
        // Ambient
        set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
        aiColor4D ambient;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
            color4_to_float4(&ambient, c);
        memcpy(aMesh.mat.ambient, c, sizeof(c));
        
        // Specular
        set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
        aiColor4D specular;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
            color4_to_float4(&specular, c);
        memcpy(aMesh.mat.specular, c, sizeof(c));
        
        // Emissive
        set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
        aiColor4D emission;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
            color4_to_float4(&emission, c);
        memcpy(aMesh.mat.emissive, c, sizeof(c));
        
        // Shininess
        float shininess = 0.0;
        unsigned int max;
        aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
        aMesh.mat.shininess = shininess;
        
        aMesh.type = GL_TRIANGLES;
        myMeshes.push_back(aMesh);
    }
}

void Mesh::createCube() {
    
    struct MyMesh aMesh;
    
    aMesh.numIndexes = faceCount * 3;
    
    glGenVertexArrays(1, &(aMesh.vao));
    glBindVertexArray(aMesh.vao);
    
    glGenBuffers(2, VboId);
    glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(normals)+sizeof(texCoords),NULL,GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(normals), normals);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+ sizeof(normals), sizeof(texCoords), texCoords);
    
    glEnableVertexAttribArray(VERTEX_COORD_ATTRIB);
    glVertexAttribPointer(VERTEX_COORD_ATTRIB, 4, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(NORMAL_ATTRIB);
    glVertexAttribPointer(NORMAL_ATTRIB, 4, GL_FLOAT, 0, 0, (void *)sizeof(vertices));
    glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB);
    glVertexAttribPointer(TEXTURE_COORD_ATTRIB, 4, GL_FLOAT, 0, 0, (void *)(sizeof(vertices)+ sizeof(normals)));
    
    //index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * aMesh.numIndexes, faceIndex , GL_STATIC_DRAW);
    
    // unbind the VAO
    glBindVertexArray(0);
    
    aMesh.type = GL_TRIANGLES;
    myMeshes.push_back(aMesh);
}

void Mesh::createQuad(float size_x, float size_y){
    
    struct MyMesh aMesh;
    
    int i;
    float vert[16];
    aMesh.numIndexes = 2*3;
    
    memcpy(vert, quad_vertices, sizeof(float) * 16);
    
    for(i=0; i< 4; i++) {
        vert[i*4] *= size_x;
        vert[i*4+1] *= size_y;
    }
    
    glGenVertexArrays(1, &(aMesh.vao));
    glBindVertexArray(aMesh.vao);
    
    glGenBuffers(2, VboId);
    glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices)+sizeof(quad_normals)+sizeof(quad_texCoords),NULL,GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(quad_vertices), vert);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(quad_vertices), sizeof(quad_normals), quad_normals);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(quad_vertices)+ sizeof(quad_normals), sizeof(quad_texCoords), quad_texCoords);
    
    glEnableVertexAttribArray(VERTEX_COORD_ATTRIB);
    glVertexAttribPointer(VERTEX_COORD_ATTRIB, 4, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(NORMAL_ATTRIB);
    glVertexAttribPointer(NORMAL_ATTRIB, 4, GL_FLOAT, 0, 0, (void *)sizeof(quad_vertices));
    glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB);
    glVertexAttribPointer(TEXTURE_COORD_ATTRIB, 4, GL_FLOAT, 0, 0, (void *)(sizeof(quad_vertices)+ sizeof(quad_normals)));
    
    
    //index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * aMesh.numIndexes, quad_faceIndex , GL_STATIC_DRAW);
    
    // unbind the VAO
    glBindVertexArray(0);
    
    aMesh.type = GL_TRIANGLES;
    myMeshes.push_back(aMesh);
}

void Mesh::createCone(float height, float baseRadius, int sides) {
    
    float v[2];
    v[0] = -baseRadius;
    v[1] = height;
    
    std::vector<float> p;
    
    p.push_back(-baseRadius);    p.push_back(0.0f);
    p.push_back(0.0f);            p.push_back(0.0f);
    p.push_back(baseRadius);    p.push_back(0.0f);
    int max = (int)(1 + height/ (baseRadius*2*3.14159 / sides)) ;
    for (int i = 0; i < max; ++i) {
        
        p.push_back(baseRadius - i * baseRadius  / max); p.push_back( i * height  / max);
    }
    p.push_back(0.0f);            p.push_back(height);
    p.push_back(-baseRadius);    p.push_back(height * 2.0f);
    
    computeVAO((p.size()-4)/2, &(p[2]), &(p[0]), sides, 0.0f);
}

void Mesh::createSphere(float radius, int divisions) {
    float *p = circularProfile(-3.14159f/2.0f, 3.14159f/2.0f, radius, divisions);
    computeVAO(divisions+1, p+2, p, divisions*2, 0.0f);
}

void Mesh::createTorus(float innerRadius, float outerRadius, int rings, int sides) {
    float tubeRadius = (outerRadius - innerRadius) * 0.5f;
    float *p = circularProfile(-3.14159f, 3.14159f, tubeRadius, sides, innerRadius + tubeRadius);
    computeVAO(sides+1, p+2, p, rings, 0.0f);
}

void Mesh::createCylinder(float height, float radius, int sides) {
    float p[] = {
        -radius,    -height*0.5f,
        0.0f,        -height*0.5f,
        radius,        -height*0.5f,
        radius,         height*0.5f,
        0.0f,         height*0.5f,
        -radius,     height*0.5f
    };
    
    computeVAO(4, p+2, p, sides, 0.0f);
}

void Mesh::computeVAO(int numP, float *p, float *points, int sides, float smoothCos) {
    // Compute and store vertices
    
    struct MyMesh aMesh;
    
    int numSides = sides;
    int numPoints = numP + 2;
    
    float *vertex = (float *)malloc(sizeof(float)*numP * 2 * 4 * (numSides+1));
    float *normal = (float *)malloc(sizeof(float)*numP * 2 * 4 * (numSides+1));
    float *textco = (float *)malloc(sizeof(float)*numP * 2 * 4 * (numSides+1));
    
    
    float inc = 2 * 3.14159f / (numSides);
    float nx,ny;
    float delta;
    int smooth;
    std::vector<int> smoothness;
    int k = 0;
    for(int i=0; i < numP; i++) {
        revSmoothNormal2(points+(i*2),&nx,&ny, smoothCos, 0);
        for(int j=0; j<=numSides;j++) {
            
            if ((i == 0 && p[0] == 0.0f) || ( i == numP-1 && p[(i+1)*2] == 0.0))
                delta = inc * 0.5f;
            else
                delta = 0.0f;
            
            normal[((k)*(numSides+1) + j)*4]   = nx * cos(j*inc+delta);
            normal[((k)*(numSides+1) + j)*4+1] = ny;
            normal[((k)*(numSides+1) + j)*4+2] = nx * sin(-j*inc+delta);
            normal[((k)*(numSides+1) + j)*4+3] = 0.0f;
            
            vertex[((k)*(numSides+1) + j)*4]   = p[i*2] * cos(j*inc);
            vertex[((k)*(numSides+1) + j)*4+1] = p[(i*2)+1];
            vertex[((k)*(numSides+1) + j)*4+2] = p[i*2] * sin(-j*inc);
            vertex[((k)*(numSides+1) + j)*4+3] = 1.0f;
            
            textco[((k)*(numSides+1) + j)*4]   = ((j+0.0f)/numSides);
            textco[((k)*(numSides+1) + j)*4+1] = (i+0.0f)/(numP-1);
            textco[((k)*(numSides+1) + j)*4+2] = 0;
            textco[((k)*(numSides+1) + j)*4+3] = 1.0f;
        }
        k++;
        if (i < numP-1) {
            smooth = revSmoothNormal2(points+((i+1)*2),&nx,&ny, smoothCos, 1);
            
            if (!smooth) {
                smoothness.push_back(1);
                for(int j=0; j<=numSides;j++) {
                    
                    normal[((k)*(numSides+1) + j)*4]   = nx * cos(j*inc);
                    normal[((k)*(numSides+1) + j)*4+1] = ny;
                    normal[((k)*(numSides+1) + j)*4+2] = nx * sin(-j*inc);
                    normal[((k)*(numSides+1) + j)*4+3] = 0.0f;
                    
                    vertex[((k)*(numSides+1) + j)*4]   = p[(i+1)*2] * cos(j*inc);
                    vertex[((k)*(numSides+1) + j)*4+1] = p[((i+1)*2)+1];
                    vertex[((k)*(numSides+1) + j)*4+2] = p[(i+1)*2] * sin(-j*inc);
                    vertex[((k)*(numSides+1) + j)*4+3] = 1.0f;
                    
                    textco[((k)*(numSides+1) + j)*4]   = ((j+0.0f)/numSides);
                    textco[((k)*(numSides+1) + j)*4+1] = (i+1+0.0f)/(numP-1);
                    textco[((k)*(numSides+1) + j)*4+2] = 0;
                    textco[((k)*(numSides+1) + j)*4+3] = 1.0f;
                }
                k++;
            }
            else
                smoothness.push_back(0);
        }
    }
    
    unsigned int *faceIndex = (unsigned int *)malloc(sizeof(unsigned int) * (numP-1) * (numSides+1 ) * 6);
    unsigned int count = 0;
    k = 0;
    for (int i = 0; i < numP-1; ++i) {
        for (int j = 0; j < numSides; ++j) {
            
            /*if (i != 0 || p[0] != 0.0)*/ {
                faceIndex[count++] = k * (numSides+1) + j;
                faceIndex[count++] = (k+1) * (numSides+1) + j + 1;
                faceIndex[count++] = (k+1) * (numSides+1) + j;
            }
            /*if (i != numP-2 || p[(numP-1)*2] != 0.0)*/ {
                faceIndex[count++] = k * (numSides+1) + j;
                faceIndex[count++] = k * (numSides+1) + j + 1;
                faceIndex[count++] = (k+1) * (numSides+1) + j + 1;
            }
            
        }
        k++;
        k += smoothness[i];
    }
    
    int numVertices = numP*2 * (numSides+1);
    aMesh.numIndexes = count;
    
    glGenVertexArrays(1, &(aMesh.vao));
    glBindVertexArray(aMesh.vao);
    
    //Implementation with glBufferSubData just for learning purposes
    
    glGenBuffers(2, VboId);
    glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
    glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(float)*4*3, NULL,GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, numVertices*sizeof(float)*4, vertex);
    glBufferSubData(GL_ARRAY_BUFFER, numVertices*sizeof(float)*4, numVertices*sizeof(float)*4, normal);
    glBufferSubData(GL_ARRAY_BUFFER, numVertices*sizeof(float)*4*2, numVertices*sizeof(float)*4, textco);
    
    glEnableVertexAttribArray(VERTEX_COORD_ATTRIB);
    glVertexAttribPointer(VERTEX_COORD_ATTRIB, 4, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(NORMAL_ATTRIB);
    glVertexAttribPointer(NORMAL_ATTRIB, 4, GL_FLOAT, 0, 0, (void *)(numVertices*sizeof(float)*4));
    glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB);
    glVertexAttribPointer(TEXTURE_COORD_ATTRIB, 4, GL_FLOAT, 0, 0, (void *)(numVertices*sizeof(float)*4*2));
    
    //index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * aMesh.numIndexes, faceIndex , GL_STATIC_DRAW);
    
    // unbind the VAO
    glBindVertexArray(0);
    
    aMesh.type = GL_TRIANGLES;
    myMeshes.push_back(aMesh);
}

int Mesh::revSmoothNormal2(float *p, float *nx, float *ny, float smoothCos, int beginEnd){
    
    float v1x,v1y,v2x,v2y,x,y,norm;
    float auxX, auxY, angle;
    
    auxX = p[0] - p[2];
    auxY = p[1] - p[3];
    v1x = -auxY;
    v1y = auxX;
    norm=sqrt((v1x*v1x) + (v1y*v1y));
    v1x /= norm;
    v1y /= norm;
    
    auxX = p[2] - p[4];
    auxY = p[3] - p[5];
    v2x = -auxY;
    v2y = auxX;
    norm=sqrt((v2x*v2x) + (v2y*v2y));
    v2x /= norm;
    v2y /= norm;
    
    angle = v1x * v2x + v1y * v2y;
    
    if (angle > smoothCos) {
        x = v1x + v2x;
        y = v1y + v2y;
    }
    else if (beginEnd == 0) {
        x = v2x;
        y = v2y;
    }
    else  {
        x = v1x;
        y = v1y;
        
    }
    
    norm=sqrt(x*x+ y*y);
    
    assert(norm!=0);
    x /= norm;
    y /= norm;
    
    *nx = x;
    *ny = y;
    if (angle > smoothCos)
        return 1;
    else
        return 0;
}

float * Mesh::circularProfile(float minAngle, float maxAngle, float radius, int divisions, float transX, float transY ) {
    
    float *p = (float *)malloc(sizeof(float) * 2 * (divisions+3));
    float step = (maxAngle - minAngle)/ divisions;
    
    for (int i = 0, k = -1; i < divisions+3; ++i,++k) {
        
        p[i*2]   = radius * cos(minAngle + k * step) + transX;
        p[i*2+1] = radius * sin(minAngle + k * step) + transY;
        //        printf("%f %f\n", p[i*2], p[i * 2 + 1]);
    }
    return p;
}
