#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}


Mesh::Mesh(FILE* f)
{
	create(f);
}

bool Mesh::intersect(const Ray &ray, glm::vec3 &point, glm::vec3 &normal) 
{ 
	
	for (int i = 0; i < triList.size(); i++)
	{
		float x = (vertices[triList[i].i - 1].x + vertices[triList[i].j - 1].x + vertices[triList[i].k - 1].x) / 3;
		float y = (vertices[triList[i].i - 1].y + vertices[triList[i].j - 1].y + vertices[triList[i].k - 1].y) / 3;
		float z = (vertices[triList[i].i - 1].z + vertices[triList[i].j - 1].z + vertices[triList[i].k - 1].z) / 3;

		glm::vec3 baryPos = glm::vec3(x, y, z);
		point = baryPos;
		glm::vec3 v1v2 = vertices[triList[i].j - 1] - vertices[triList[i].i - 1];
		glm::vec3 v1v3 = vertices[triList[i].k - 1] - vertices[triList[i].i - 1];
		normal = glm::cross(v1v2, v1v3);

		if (glm::intersectRayTriangle(ray.p, ray.d, vertices[triList[i].i - 1], vertices[triList[i].j - 1], vertices[triList[i].k - 1], baryPos))
		{
			this->diffuseColor = triList[i].diffuseColor;
			return true;
		}
	}
	
	return false;
}

//loops through all the vertices in the mesh and draws triangles based on their positions
void Mesh::draw()
{
	for (int n = 0; n < triList.size(); n++)
	{
		ofNoFill();
		ofSetColor(ofColor::limeGreen);
		ofDrawTriangle(vertices[triList[n].i - 1], vertices[triList[n].j - 1], vertices[triList[n].k - 1]);
	}
}

//creates a mesh from an obj file 
//scans through the entire file to find vertices and faces
void Mesh::create(FILE* f)
{
	//scans through the file until it reaches the end of the file
	while (fscanf(f, "%s", s) != EOF)
	{
		sizeOfFile++;

		//add triangles to the mesh's vector of triangles
		if (strcmp(s, face) == 0)
		{
			fscanf(f, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &c, &v, &b);		//scans and only gets the index for the vertices
			triList.push_back(Triangle(c, v, b));
		}

		//add vertices to the mesh's vector of vertices
		if (strcmp(s, vert) == 0)
		{
			fscanf(f, "%f %f %f", &v1, &v2, &v3);
			vertices.push_back(glm::vec3(v1, v2, v3));
		}
	}

	cout << "number of faces: " << triList.size() << endl;
	cout << "number of vertices: " << vertices.size() << endl;
	cout << "Size of mesh structure: " << sizeOfFile / 1000 << " kB" << endl;


	fclose(f);
}
