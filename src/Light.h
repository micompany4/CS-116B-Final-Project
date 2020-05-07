#pragma once
#include "SceneObject.h"
class Light :
	public SceneObject
{
public:
	Light();
	Light(float intense, glm::vec3 pos, bool spot)
	{
		intensity = intense;
		position = pos;
		spotlight = spot;
	}

	void draw();
	bool intersectToMove(const Ray &ray, glm::vec3 &point, glm::vec3 &normal);

	bool spotlight = false;
	bool btarget = false;

	float ball = 0.2;
	glm::vec3 pointAt;			//vec3 that indicates what the spotlight is pointing at
	float coneAngle = 180;		//default for point light
	Light *target = NULL;		//default for point light
	float coneLength = 3;

	float angleToLight = 90;	//angle to recieve maximum light from a light to determine shadow gradient
	~Light();
};

