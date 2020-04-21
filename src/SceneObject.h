#pragma once

#include "ofMain.h"
#include "Ray.h"

class SceneObject
{
public:
	SceneObject();
	~SceneObject();

	virtual void draw() = 0;    // pure virtual funcs - must be overloaded
	virtual bool intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal) { return false; }
	virtual bool intersectToMove(const Ray &ray, glm::vec3 &point, glm::vec3 &normal) { return false; }
	virtual float sdf(const glm::vec3 & p) { return 0.0; }

	glm::mat4 getRotateMatrix();
	glm::mat4 getTranslateMatrix();
	glm::mat4 getScaleMatrix();
	glm::mat4 SceneObject::rotateToVector(glm::vec3 v1, glm::vec3 v2);
	glm::mat4 getMatrix();

	// any data common to all scene objects goes here
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);   // rotate
	glm::vec3 scale = glm::vec3(1, 1, 1);      // scale
	glm::vec3 pivot = glm::vec3(0, 0, 0);

	// get current Position in World Space
	//
	glm::vec3 getPosition() {
		return (getMatrix() * glm::vec4(0.0, 0.0, 0.0, 1.0));
	}

	// set position (pos is in world space)
	//
	void setPosition(glm::vec3 pos) {
		position = glm::inverse(getMatrix()) * glm::vec4(pos, 1.0);
	}

	// material properties (we will ultimately replace this with a Material class - TBD)
	//
	ofColor diffuseColor = ofColor::grey;    // default colors - can be changed.
	ofColor specularColor = ofColor::lightGray;

	bool isSelectable = true;
	float radius = 1.0;
	float intensity = 75;
	float coneRad = 0.75;
	//t represents the dimensions for the torus 
	ofVec2f t = ofVec2f(0, 0);				//t.x is the radius of the dount hole, t.y is the cross length of the acutal donut
	float angleRotate = 0;

};

