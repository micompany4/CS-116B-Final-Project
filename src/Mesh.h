#pragma once
#include "SceneObject.h"


class Mesh : public SceneObject
{
public:
	Mesh();
	~Mesh();

	bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal); 
	void draw();
};

