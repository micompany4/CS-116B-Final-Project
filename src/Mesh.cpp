#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}


Mesh::Mesh(FILE* f, ofImage img)
{
	create(f, img);
	diffuseColor = ofColor::green;		//no effect on the rendering, just for scene aesthetic 
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
			diffuseColor = triList[i].diffuseColor;			//set the color of the mesh to be the color of the triangle 
			return true;
		}
	}
	
	return false;
}

//loops through all the vertices in the mesh and draws triangles based on their positions
void Mesh::draw()
{
	//cout << "mesh draw" << endl;
	for (int n = 0; n < triList.size(); n++)
	{
		ofNoFill();
		ofSetColor(ofColor::limeGreen);
		//cout << "triangle: " << n << " preparing to be drawn" << endl;

		//cout << "vertex x: " << triList[n].i - 1 << endl;
		//cout << "vertex y: " << triList[n].j - 1 << endl;
		//cout << "vertex z: " << triList[n].k - 1 << endl;

		ofDrawTriangle(vertices[triList[n].i - 1], vertices[triList[n].j - 1], vertices[triList[n].k - 1]);
		//cout << "triangle: " << n << " drawn" << endl;
	}
}

//creates a mesh from an obj file 
//scans through the entire file to find vertices and faces
void Mesh::create(FILE* f, ofImage img)
{
	//scans through the file until it reaches the end of the file
	while (fscanf(f, "%s", s) != EOF)
	{
		sizeOfFile++;

		//add triangles to the mesh's vector of triangles
		if (strcmp(s, face) == 0)
		{
			fscanf(f, "%d/%d/%*d %d/%d/%*d %d/%d/%*d", &c, &j, &v, &k, &b, &l);		//scans and only gets the index for the vertices
			//fscanf(f, "%d//%*d %d//%*d %d//%*d", &c, &v, &b);					//modification for link object file
			triList.push_back(Triangle(c, v, b, j, k, l));
		}

		if (strcmp(s, text) == 0)
		{
			fscanf(f, "%f %f", &t1, &t2);
			texture.push_back(glm::vec2(t1, t2));
		}

		//add vertices to the mesh's vector of vertices
		if (strcmp(s, vert) == 0)
		{
			fscanf(f, "%f %f %f", &v1, &v2, &v3);
			vertices.push_back(glm::vec3(v1, v2, v3));
		}
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].y -= 2;
	}

	for (int i = 0; i < triList.size(); i++)
	{
		//triangle's 1 vertex's uv texture coord
		int textureUX = texture[triList[i].t1 - 1].x;
		int textureVX = texture[triList[i].t1 - 1].y;

		//triangle's 2 vertex's uv texture coord
		int textureUY = texture[triList[i].t2 - 1].x;
		int textureVY = texture[triList[i].t2 - 1].y;

		//triangle's 3 vertex's uv texture coord
		int textureUZ = texture[triList[i].t3 - 1].x;
		int textureVZ = texture[triList[i].t3 - 1].y;
		
		//convert triangle' 1 vertex's uv to xy
		int x1 = round(textureUX * 2000 - 0.5);
		int y1 = round(textureVY * 2000 - 0.5);

		//converts triangle's 2 vertex's uv to xy
		int x2 = round(textureUY * 2000 - 0.5);
		int y2 = round(textureVY * 2000 - 0.5);
		
		//converts triangle's 3 vertex's uv to xy
		int x3 = round(textureUZ * 2000 - 0.5);
		int y3 = round(textureVZ * 2000 - 0.5);

		//made get all three colors and average them out to assign as the the triangle's diffuse color 
		ofColor average = (img.getColor(x1, y1) + img.getColor(x2, y2) + img.getColor(x3, y3)) / 3;
		triList[i].diffuseColor = average;
	}

	cout << "number of faces: " << triList.size() << endl;
	cout << "number of vertices: " << vertices.size() << endl;
	cout << "number of texture vertices: " << texture.size() << endl;

	fclose(f);
}
