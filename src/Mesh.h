#pragma once
#include "SceneObject.h"
#include "Triangle.h"

class Mesh : public SceneObject
{
public:
	Mesh();
	~Mesh();
	Mesh(FILE* f);

	void create(FILE* f);
	bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal); 
	void draw();


	vector<Triangle> triList;				//vector of all the triangles in the mesh
	vector<glm::vec3> vertices;				//vector that holds all the vertices in the mesh
	vector<glm::vec2> texture;				//vector that holds the uv points for the texture map
	

	const char* face = "f";					//constant string that signals a face
	const char* vert = "v";					//constant string that signals a vertex
	const char* text = "vt";				//constant strign that signals a vertex texture
	char s[1];								//used in the scanner to find either a "f" or a "v"

	int c, v, b;						//integers to hold the indices for to be made triangles
	float v1, v2, v3;					//floats for vertices
	float t1, t2;						//float for texture map
	int j, k, l;						//indices for the texture vertices

	int counter = 0;
	float sizeOfFile = 0;		//counts how many bits are in the file 
	ofImage textureMap;
};

