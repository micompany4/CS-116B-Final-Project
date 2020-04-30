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


	vector<Triangle> triList;			//vector of all the triangles in the mesh
	vector<glm::vec3> vertices;			//vector that holds all the vertices in the mesh
	//vector<int> indices;				//vector that hold all the indices to the triangle vertices

	const char* face = "f";					//constant string that signals a face
	const char* vert = "v";					//constant string that signals a vertex
	char s[1];								//used in the scanner to find either a "f" or a "v"

	int c, v, b;						//integers to hold the indices for to be made triangles
	float v1, v2, v3;					//floats for glm::vec3

	int counter = 0;
	float sizeOfFile = 0;		//counts how many bits are in the file 
};

