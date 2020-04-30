#include "Plane.h"


Plane::~Plane()
{
}

float Plane::sdf(const glm::vec3 & p)
{
	if (normal == glm::vec3(0, 1, 0))
	{
		return p.y - position.y;
	}
	else if (normal == glm::vec3(0, 0, 1))
	{
		return p.z - position.z;
	}
	else
	{
		return 0.0;
	}
}

glm::vec3 Plane::getNormal(const glm::vec3 &p) { return this->normal; }

bool Plane::intersect(const Ray &ray, glm::vec3 & point, glm::vec3 &
	normalAtIntersect) {
	float dist;
	bool insidePlane = false;
	bool hit = glm::intersectRayPlane(ray.p, ray.d, position, this->normal,
		dist);
	if (hit) {
		Ray r = ray;
		point = r.evalPoint(dist);
		normalAtIntersect = this->normal;
		glm::vec2 xrange = glm::vec2(position.x - width / 2, position.x + width
			/ 2);
		glm::vec2 zrange = glm::vec2(position.z - height / 2, position.z +
			height / 2);
		if (point.x < xrange[1] && point.x > xrange[0] && point.z < zrange[1]
			&& point.z > zrange[0]) {
			insidePlane = true;
		}
	}
	return insidePlane;
}

void Plane::draw() {
	plane.setPosition(position);
	plane.setWidth(width);
	plane.setHeight(height);
	plane.setResolution(4, 4);
	plane.drawWireframe();
}