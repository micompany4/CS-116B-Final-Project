#include "SceneObject.h"


SceneObject::SceneObject()
{
	
}


SceneObject::~SceneObject()
{
}


// commonly used transformations
	//
glm::mat4 SceneObject::getRotateMatrix() {
	return (glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z)));   // yaw, pitch, roll 
}
glm::mat4 SceneObject::getTranslateMatrix() {
	return (glm::translate(glm::mat4(1.0), glm::vec3(position.x, position.y, position.z)));
}
glm::mat4 SceneObject::getScaleMatrix() {
	return (glm::scale(glm::mat4(1.0), glm::vec3(scale.x, scale.y, scale.z)));
}

// Generate a rotation matrix that rotates v1 to v2
// v1, v2 must be normalized
//
glm::mat4 SceneObject::rotateToVector(glm::vec3 v1, glm::vec3 v2) {

	glm::vec3 axis = glm::cross(v1, v2);
	glm::quat q = glm::angleAxis(glm::angle(v1, v2), glm::normalize(axis));
	return glm::toMat4(q);
}

glm::mat4 SceneObject::getMatrix() {

	// get the local transformations + pivot
	//
	glm::mat4 scale = getScaleMatrix();
	glm::mat4 rotate = getRotateMatrix();
	glm::mat4 trans = getTranslateMatrix();

	// handle pivot point  (rotate around a point that is not the object's center)
	//
	glm::mat4 pre = glm::translate(glm::mat4(1.0), glm::vec3(-pivot.x, -pivot.y, -pivot.z));
	glm::mat4 post = glm::translate(glm::mat4(1.0), glm::vec3(pivot.x, pivot.y, pivot.z));



	return (trans * post * rotate * pre * scale);

}