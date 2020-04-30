#include "Sphere.h"



Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

bool Sphere::intersectToMove(const Ray &ray, glm::vec3 &point, glm::vec3 &normal)
{
	// transform Ray to object space.  
//
	glm::mat4 mInv = glm::inverse(getMatrix());
	glm::vec4 p = mInv * glm::vec4(ray.p.x, ray.p.y, ray.p.z, 1.0);
	glm::vec4 p1 = mInv * glm::vec4(ray.p + ray.d, 1.0);
	glm::vec3 d = glm::normalize(p1 - p);

	return (glm::intersectRaySphere(glm::vec3(p), d, glm::vec3(0, 0, 0), radius, point, normal));
}

float Sphere::sdf(const glm::vec3 &p)
{
	return glm::length(p - position) - radius;			//straight from the slides
}

void Sphere::draw() {
	//   get the current transformation matrix for this object
	//
	ofFill();
	glm::mat4 m = getMatrix();

	//   push the current stack matrix and multiply by this object's
	//   matrix. now all vertices drawn will be transformed by this matrix
	//
	ofPushMatrix();
	ofMultMatrix(m);
	ofDrawSphere(radius);
	ofPopMatrix();
}