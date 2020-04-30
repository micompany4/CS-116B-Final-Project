#pragma once
#include "SceneObject.h"
#include "ViewPlane.h"
#include "ofMain.h"

class RenderCam : public SceneObject
{
public:
	RenderCam() {
		position = glm::vec3(0, 0, 17);		//0 0 10
		aim = glm::vec3(0, 0, -1);
	}

	Ray getRay(float u, float v);
	void draw() { ofDrawBox(position, 1.0); };
	void drawFrustum();

	glm::vec3 aim;
	ViewPlane view;          // The camera viewplane, this is the view that we will render 

	~RenderCam();
};

