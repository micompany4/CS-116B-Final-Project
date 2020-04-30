#include "Light.h"



Light::Light()
{
}

bool Light::intersectToMove(const Ray &ray, glm::vec3 &point, glm::vec3 &normal)
{
	// transform Ray to object space.  
//
	glm::mat4 mInv = glm::inverse(getMatrix());
	glm::vec4 p = mInv * glm::vec4(ray.p.x, ray.p.y, ray.p.z, 1.0);
	glm::vec4 p1 = mInv * glm::vec4(ray.p + ray.d, 1.0);
	glm::vec3 d = glm::normalize(p1 - p);

	return (glm::intersectRaySphere(glm::vec3(p), d, glm::vec3(0, 0, 0), radius, point, normal));
}

void Light::draw()
{
	glm::mat4 m = getMatrix();
	ofSetColor(ofColor::yellow);
	if (btarget) {
		ofSetColor(ofColor::orangeRed);
		ball = coneRad;
		intensity = 0;		//enforces the intensity to be always 0 if its a target
	}

	//draw a small sphere to represent a light
	ofPushMatrix();
	ofMultMatrix(m);
	ofDrawSphere(ball);
	ofPopMatrix();

	if (spotlight)
	{

		pointAt = this->target->getPosition() - this->getPosition();

		coneAngle = glm::atan(coneRad / coneLength);	//set the max angle of the spotlight

		glm::vec3 v1 = glm::normalize(glm::vec3(0, 1, 0));
		glm::vec3 v2 = glm::normalize(pointAt);
		glm::mat4 rotationMatrix = rotateToVector(v1, v2);								//gets the rotation matrix for the cone

		//then draw the cone
		ofPushMatrix();
		glm::mat4 transMat = glm::translate(this->getPosition());
		glm::mat4 offsetMat = glm::translate(glm::vec3(0, coneLength / 2, 0));
		ofMultMatrix(transMat * rotationMatrix * offsetMat);
		ofDrawCone(coneRad, coneLength);

		ofPopMatrix();

	}

	ofSetLineWidth(1.0);

	// X Axis
	ofSetColor(ofColor::red);
	ofDrawLine(glm::vec3(m*glm::vec4(0, 0, 0, 1)), glm::vec3(m*glm::vec4(1.5, 0, 0, 1)));


	// Y Axis
	ofSetColor(ofColor::green);
	ofDrawLine(glm::vec3(m*glm::vec4(0, 0, 0, 1)), glm::vec3(m*glm::vec4(0, 1.5, 0, 1)));

	// Z Axis
	ofSetColor(ofColor::blue);
	ofDrawLine(glm::vec3(m*glm::vec4(0, 0, 0, 1)), glm::vec3(m*glm::vec4(0, 0, 1.5, 1)));

}

Light::~Light()
{
}
