#include "Triangle.h"



Triangle::Triangle()
{
}

Triangle::Triangle(int i1, int j1, int k1, int t4, int t5, int t6)
{
	i = i1;
	j = j1;
	k = k1;
	t1 = t4;
	t2 = t5;
	t3 = t6;
	diffuseColor = ofColor::green;		//default color to assign to the triangles since reading from .obj file format
}

Triangle::~Triangle()
{
}

void Triangle::draw()
{
	//   get the current transformation matrix for this object
	//
	ofFill();
	glm::mat4 m = getMatrix();

	//   push the current stack matrix and multiply by this object's
	//   matrix. now all vertices drawn will be transformed by this matrix
	//
	ofPushMatrix();
	ofMultMatrix(m);
	ofDrawTriangle(v1, v2, v3);
	ofPopMatrix();
}

bool Triangle::intersectToMove()
{
	return false;
}
