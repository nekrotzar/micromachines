/* --------------------------------------------------
Basic Revolution Geometry 
 *
 * based on vsResourceLib.cpp from Lighthouse3D
 *
 *
 *
 * Full documentation at 
 * http://www.lighthouse3d.com/very-simple-libs

 João Madeiras Pereira
----------------------------------------------------*/
#include <string>
#include <assert.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>

// GLUT is the toolkit to interface with the OS
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

#include "VertexAttrDef.h"
#include "basic_geometry.h"
#include "cube.h"

extern struct MyMesh mesh[];
extern int objId;

GLuint VboId[2];

void createQuad(float size_x, float size_y) {
	
	int i;
	float vert[16];
	mesh[objId].numIndexes = 2*3;

	memcpy(vert, quad_vertices, sizeof(float) * 16);

	for(i=0; i< 4; i++) {
		vert[i*4] *= size_x;
		vert[i*4+1] *= size_y;
	}

	glGenVertexArrays(1, &(mesh[objId].vao));
	glBindVertexArray(mesh[objId].vao);

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh[objId].numIndexes, quad_faceIndex , GL_STATIC_DRAW);
    
    // unbind the VAO
    glBindVertexArray(0);
  

	mesh[objId].type = GL_TRIANGLES;
}

void createCube() {

	mesh[objId].numIndexes = faceCount *3;

	glGenVertexArrays(1, &(mesh[objId].vao));
	glBindVertexArray(mesh[objId].vao);

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh[objId].numIndexes, faceIndex , GL_STATIC_DRAW);

// unbind the VAO
	glBindVertexArray(0);

	mesh[objId].type = GL_TRIANGLES;
}


void createSphere(float radius, int divisions) {

	float *p = circularProfile(-3.14159f/2.0f, 3.14159f/2.0f, radius, divisions);
	computeVAO(divisions+1, p+2, p, divisions*2, 0.0f);
}


void createTorus(float innerRadius, float outerRadius, int rings, int sides) {

	float tubeRadius = (outerRadius - innerRadius) * 0.5f;
	float *p = circularProfile(-3.14159f, 3.14159f, tubeRadius, sides, innerRadius + tubeRadius);
	computeVAO(sides+1, p+2, p, rings, 0.0f);
}


void createCylinder(float height, float radius, int sides) {

	float p[] = {
			-radius,	-height*0.5f, 
			0.0f,		-height*0.5f, 
			radius,		-height*0.5f,  
			radius,		 height*0.5f,  
			0.0f,		 height*0.5f,
			-radius,	 height*0.5f
	};

	computeVAO(4, p+2, p, sides, 0.0f);
}

void createCone(float height, float baseRadius, int sides) {

	float v[2];
	v[0] = -baseRadius;
	v[1] = height;

	std::vector<float> p;

	p.push_back(-baseRadius);	p.push_back(0.0f);
	p.push_back(0.0f);			p.push_back(0.0f);
	p.push_back(baseRadius);	p.push_back(0.0f);
	int max = (int)(1 + height/ (baseRadius*2*3.14159 / sides)) ;
	for (int i = 0; i < max; ++i) {
	
		p.push_back(baseRadius - i * baseRadius  / max); p.push_back( i * height  / max);
	}
	p.push_back(0.0f);			p.push_back(height);
	p.push_back(-baseRadius);	p.push_back(height * 2.0f);
	//float p[(sides+3)*2] = {
	//		-baseRadius,	0.0, 
	//		0.0f,			0.0, 
	//		baseRadius,		0.0f,
	//		baseRadius + v[0] * 0.1,		v[1] * 0.1,
	//		baseRadius + v[0] * 0.2,		v[1] * 0.2,
	//		baseRadius + v[0] * 0.3,		v[1] * 0.3,
	//		baseRadius + v[0] * 0.4,		v[1] * 0.4,
	//		baseRadius + v[0] * 0.5,		v[1] * 0.5,
	//		baseRadius + v[0] * 0.6,		v[1] * 0.6,
	//		baseRadius + v[0] * 0.7,		v[1] * 0.7,
	//		baseRadius + v[0] * 0.8,		v[1] * 0.8,
	//		baseRadius + v[0] * 0.9,		v[1] * 0.9,
	//		0.0f,			height,  
	//		-baseRadius,	height*2.0f,
	//	};

	computeVAO((p.size()-4)/2, &(p[2]), &(p[0]), sides, 0.0f);
}


void createPawn() {

		float p[] = {0.0f, 0.0f, 
					  0.98f, 0.0f, 
					  0.98f, 0.01f,
					  0.99f, 0.02f,
					  1.0f , 0.02f,
					  1.0f , 0.3f,
					  0.99f, 0.31f,
					  0.98f, 0.32f,
					  0.93f, 0.32f,

					  0.95f, 0.38f,
					  0.965f, 0.44f,
					  0.97f, 0.48f,
					  0.965f, 0.52f,
					  0.95f, 0.56f,
					  0.89f, 0.62f,
					  0.83f, 0.66f,
					  0.75f, 0.70f,
					  0.66f, 0.735f,
					  0.65f, 0.74f,

					  
					  0.611f, 0.83f,
					  0.5f,   0.83f,

					  0.35f,  2.0f,

					  0.58f,  2.075f,
					  0.610f, 2.10f,
					  0.6225f, 2.1125f,
					  0.625f, 2.125f,
					  0.6225f, 2.1375f,
					  0.610f, 2.15f,
					  0.58f,  2.175f,

					  0.32f, 2.27f,
					  0.46f, 2.38f,
					  0.56f, 2.514f,
					  0.628f, 2.67f,
					  0.65f, 2.84f,

					  0.628f, 3.01f,
					  0.56f, 3.164f,
					  0.46f, 3.3f,
					  0.32f, 3.40f,
					  0.168f, 3.467f,
					  0.0f, 3.486f
					 };
		int numP=40;
		int sides=30;
		int closed = 1;
		float smoothCos = 0.6f;

	int i; 
	// two extra points are added for normal computation

	float *points = (float *)malloc(sizeof(float) * (numP+2) * 2);

	for(i=2;i<(numP+1)*2;i++) {
		points[i] = p[i-2];
	}

	// distinguishes between closed curves and open curves
	// for normal computation
	int numPoints = numP + 2;

	if (closed) {

		points[0] = p[(numP-2)*2];
		points[1] = p[(numP-2)*2+1];

		points[(numPoints-1)*2]     = p[2];
		points[(numPoints-1)*2 + 1] = p[3];
	}
	else {

		points[0] = points[2] + (points[2]-points[4]);
		points[1] = points[3] + (points[3]-points[5]);

		points[(numPoints-1)*2]     = points[(numPoints-2)*2]     + 
											(points[(numPoints-2)*2]     - points[(numPoints-3)*2]);
		points[(numPoints-1)*2 + 1] = points[(numPoints-2)*2 + 1] + 
											(points[(numPoints-2)*2 + 1] - points[(numPoints-3)*2 + 1]);
	}

	computeVAO(numP, p, points, sides, smoothCos);
}

void computeVAO(int numP, float *p, float *points, int sides, float smoothCos) {
	// Compute and store vertices

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
	mesh[objId].numIndexes = count;

	glGenVertexArrays(1, &(mesh[objId].vao));
	glBindVertexArray(mesh[objId].vao);

	//Implementation without glBufferSubData so we will need 3 bufers for vertex attributes 
/*
	GLuint buffers[4];
	glGenBuffers(4, buffers);

	//vertex coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(float)*4, vertex, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTEX_COORD_ATTRIB);
	glVertexAttribPointer(VERTEX_COORD_ATTRIB, 4, GL_FLOAT, 0, 0, 0);

	//texture coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(float)*4, textco, GL_STATIC_DRAW);
	glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB);
	glVertexAttribPointer(TEXTURE_COORD_ATTRIB, 4, GL_FLOAT, 0, 0, 0);

	//normals buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(float)*4, normal, GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMAL_ATTRIB);
	glVertexAttribPointer(NORMAL_ATTRIB, 4, GL_FLOAT, 0, 0, 0);

	//index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh[objId].numIndexes, faceIndex , GL_STATIC_DRAW);
*/	

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh[objId].numIndexes, faceIndex , GL_STATIC_DRAW);

// unbind the VAO
	glBindVertexArray(0);

	mesh[objId].type = GL_TRIANGLES;
}

int revSmoothNormal2(float *p, float *nx, float *ny, float smoothCos, int beginEnd) {

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

float *circularProfile(float minAngle, float maxAngle, float radius, int divisions, float transX, float transY ) {

	float *p = (float *)malloc(sizeof(float) * 2 * (divisions+3));
	float step = (maxAngle - minAngle)/ divisions;

	for (int i = 0, k = -1; i < divisions+3; ++i,++k) {
	
		p[i*2]   = radius * cos(minAngle + k * step) + transX;
		p[i*2+1] = radius * sin(minAngle + k * step) + transY;
//		printf("%f %f\n", p[i*2], p[i * 2 + 1]);
	}
	return p;
}
