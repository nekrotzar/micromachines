#ifndef basic_geometry_h
#define basic_geometry_h

#include <assert.h>
#include <fstream>
#include <map>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include <IL/il.h>

// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>

// GLUT is the toolkit to interface with the OS
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

#include "AVTmathLib.h"
#include "VertexAttrDef.h"
#include "vsShaderLib.h"

#define MAX_TEXTURES 4

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];
extern float mNormal3x3[9];

struct Material{
	float diffuse[4];
	float ambient[4];
	float specular[4];
	float emissive[4];
	float shininess;
	int texCount;
};

struct MyMesh {
		GLuint vao;
        GLuint texIndex;
		GLuint texUnits[MAX_TEXTURES];
		GLuint texTypes[MAX_TEXTURES];
		float transform[16];
		int numIndexes;
		unsigned int type;
		struct Material mat;
};

class Mesh {
protected:
    Assimp::Importer importer;
    const aiScene * scene = NULL;
    float scaleFactor;
    
    std::map<std::string, GLuint> textureIdMap;
    std::vector<struct MyMesh> myMeshes;
public:
    const aiScene * getScene();
    void set_float4(float f[4], float a, float b, float c, float d);
    void color4_to_float4(const aiColor4D *c, float f[4]);
    void get_bounding_box_for_node (const aiNode* nd, aiVector3D* min, aiVector3D* max);
    void get_bounding_box(aiVector3D* min, aiVector3D* max);
    bool Import3DFromFile(const std::string& pFile);
    int LoadGLTextures(const aiScene* scene);
    void createObject(const std::string& pFile);
    void loadMeshMaterial(VSShaderLib shader, int meshId);
    void renderMesh(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, int meshId);
    void renderMeshRecursive(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, const aiScene * scene, const aiNode * node);
    
    void createCube();
    void createQuad(float size_x, float size_y);
    void createSphere(float radius, int divisions);
    void createCylinder(float height, float radius, int sides);
    void createTorus(float innerRadius, float outerRadius, int rings, int sides);
    void createCone(float height, float baseRadius, int sides);
    void computeVAO(int numP, float *p, float *pfloatoints, int sides, float smoothCos);
    int revSmoothNormal2(float *p, float *nx, float *ny, float smoothCos, int beginEnd);
    float *circularProfile(float minAngle, float maxAngle, float radius, int divisions, float transX= 0.0f, float transY = 0.0f);
    void setMeshMaterial(int meshId, float ambient[], float diffuse[], float specular[], float emissive[], float shininess, float texcount);
};
#endif /* basic_geometry_h */
