#pragma once
#include "ofMain.h"
#include "box.h"
#include "ray.h"
#include "vector3.h"
#include "Mesh.h"


class TreeNode {
public:
	Box box;
	vector<int> points;
	vector<TreeNode> children;
};

class Octree {
public:
	
	void create(const Mesh & mesh, int numLevels);
	void subdivide(const Mesh & mesh, TreeNode & node, int numLevels, int level);
	bool intersect(const Ray &, const TreeNode & node, TreeNode & nodeRtn);
	bool intersect(const ofVec3f &, TreeNode & node, TreeNode & nodeRtn);
	void draw(TreeNode & node, int numLevels, int level);
	void draw(int numLevels, int level) {
		draw(root, numLevels, level);
	}
	void drawLeafNodes(TreeNode & node);
	static void drawBox(const Box &box);
	static Box meshBounds(const Mesh &);
	int getMeshPointsInBox(const Mesh &mesh, const vector<int> & points, Box & box, vector<int> & pointsRtn);
	void subDivideBox8(const Box &b, vector<Box> & boxList);

	
	ofTime time;

	ofMesh mesh;
	TreeNode root;
};