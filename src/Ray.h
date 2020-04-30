#pragma once

#include "ofMain.h"


class Ray
{
public:
	Ray(glm::vec3 p, glm::vec3 d);
	~Ray();

	void draw(float t) { ofDrawLine(p, p + t * d); }

	glm::vec3 evalPoint(float t) {
		return (p + t * d);
	}

	glm::vec3 p, d;
};

