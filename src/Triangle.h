#pragma once
#include "SceneObject.h"

class Triangle : public SceneObject
{
public:
	Triangle();
	Triangle(int i1, int j1, int k1, int t4, int t5, int t6);
	Triangle(glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3, ofColor diffuse = ofColor::green)
	{
		v1 = vert1;
		v2 = vert2;
		v3 = vert3;

		diffuseColor = diffuse;
	}
	~Triangle();


	bool intersectToMove();
	void draw();
	bool intersect(const Ray &ray, glm::vec3 &p, glm::vec3 &normal)
	{
		float x = (v1.x + v2.x + v3.x) / 3;
		float y = (v1.y + v2.y + v3.y) / 3;
		float z = (v1.z + v1.z + v3.z) / 3;
		
		glm::vec3 baryPos = glm::vec3(x, y, z);
		p = baryPos;	//assign the point of intersection to be the center of the triangle

		//calcuate the face normal
		glm::vec3 v1v2 = v2 - v1;
		glm::vec3 v1v3 = v3 - v1;
		normal = glm::cross(v1v2, v1v3);
		
		return glm::intersectRayTriangle(ray.p, ray.d, v1, v2, v3, baryPos);
		
	}

	int i, j, k;			//the three vertices that make up the triangle
	int t1, t2, t3;			//the three texture vertices that the triangle has
	glm::vec3 v1, v2, v3;
};

