#pragma once
#include "SceneObject.h"


class Sphere : public SceneObject
{
public:
	Sphere();
	Sphere(glm::vec3 p, float r, ofColor diffuse = ofColor::lightGray) 
	{ 
		position = p; 
		radius = r; 
		diffuseColor = diffuse; 
	}
	~Sphere();

	bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal) {
		return (glm::intersectRaySphere(ray.p, ray.d, position, radius, point, normal));
	}

	bool intersectToMove(const Ray &ray, glm::vec3 &point, glm::vec3 &normal);
	float sdf(const glm::vec3 &p);
	void draw();


};
