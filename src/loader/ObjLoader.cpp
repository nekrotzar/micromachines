#include "ObjLoader.h"

bool ObjLoader::import3dFromFile(const std::string& fileName){
    std::ifstream fin(fileName.c_str());
    
    // Check if file exists
    if (!fin.fail()) {
        fin.close();
    } else {
        printf("Couldn't open file: %s\n", fileName.c_str());
        printf("%s\n", importer.GetErrorString());
        return false;
    }
    
    scene = importer.ReadFile(fileName, aiProcessPreset_TargetRealtime_Quality);
    
    if (!scene) {
        printf("%s\n", importer.GetErrorString());
        return false;
    }
    
    printf("Import of scene %s succeeded.", fileName.c_str());
    aiVector3D scene_min, scene_max, scene_center;
    getBoundingBox(&scene_min, &scene_max);
    
    float tmp;
    tmp = scene_max.x-scene_min.x;
    tmp = scene_max.y - scene_min.y > tmp?scene_max.y - scene_min.y:tmp;
    tmp = scene_max.z - scene_min.z > tmp?scene_max.z - scene_min.z:tmp;
    scaleFactor = 1.f / tmp;
    
    return true;
}

void ObjLoader::getBoundingBox(aiVector3D* min , aiVector3D* max){
    min->x = min->y = min->z = 1e10f;
    max->x = max->y = max->z = -1e10f;
    getBoundingBoxForNode(scene->mRootNode,min,max);
}

void ObjLoader::getBoundingBoxForNode (const aiNode* nd, aiVector3D* min, aiVector3D* max){
    aiMatrix4x4 prev;
    unsigned int n = 0 ;
    
    for (; n < nd->mNumMeshes; ++n) {
        const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
        for (int t = 0; t < mesh->mNumVertices; ++t) {
            
            aiVector3D tmp = mesh->mVertices[t];
            
            min->x = aisgl_min(min->x,tmp.x);
            min->y = aisgl_min(min->y,tmp.y);
            min->z = aisgl_min(min->z,tmp.z);
            
            max->x = aisgl_max(max->x,tmp.x);
            max->y = aisgl_max(max->y,tmp.y);
            max->z = aisgl_max(max->z,tmp.z);
        }
        
        for (n = 0; n < nd->mNumChildren; ++n) {
            getBoundingBoxForNode(nd->mChildren[n],min,max);
        }
    }
    
}


