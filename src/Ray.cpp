#include "Ray.h"


Ray::Ray(glm::vec3 p, glm::vec3 d) 
{ 
	this->p = p; this->d = d; 
}


Ray::~Ray()
{
}
