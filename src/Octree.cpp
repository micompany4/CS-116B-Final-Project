//  Kevin M. Smith - Basic Octree Class - CS134/235 4/18/18
//


#include "Octree.h"
 

// draw Octree (recursively)
//
void Octree::draw(TreeNode & node, int numLevels, int level) {
	if (level >= numLevels) return;
	ofSetColor(ofColor::red);
	drawBox(node.box);
	level++;

	//cout << "draw box" << endl;

	for (int i = 0; i < node.children.size(); i++) 
	{
		draw(node.children[i], numLevels, level);
		//cout << "draw child" << endl;
	}
}

// draw only leaf Nodes
//
void Octree::drawLeafNodes(TreeNode & node) 
{
	ofSetColor(ofColor::red);
	if (node.children.size() > 0)
	{
		for (int i = 0; i < node.children.size(); i++)
		{
			drawLeafNodes(node.children[i]);
		}
	}
	else
	{
		if (node.points.size() > 0)
		{
			drawBox(node.box);
		}
		
	}
	
}


//draw a box from a "Box" class  
//
void Octree::drawBox(const Box &box) {
	Vector3 min = box.parameters[0];
	Vector3 max = box.parameters[1];
	Vector3 size = max - min;
	Vector3 center = size / 2 + min;
	ofVec3f p = ofVec3f(center.x(), center.y(), center.z());
	float w = size.x();
	float h = size.y();
	float d = size.z();
	ofSetColor(ofColor::red);
	ofDrawBox(p, w, h, d);
}

// return a Mesh Bounding Box for the entire Mesh
//
Box Octree::meshBounds(const Mesh & mesh) {
	int n = mesh.vertices.size();
	ofVec3f v = mesh.vertices[0];
	ofVec3f max = v;
	ofVec3f min = v;
	for (int i = 1; i < n; i++) {
		ofVec3f v = mesh.vertices[i];

		if (v.x > max.x) max.x = v.x;
		else if (v.x < min.x) min.x = v.x;

		if (v.y > max.y) max.y = v.y;
		else if (v.y < min.y) min.y = v.y;

		if (v.z > max.z) max.z = v.z;
		else if (v.z < min.z) min.z = v.z;
	}
	
//	cout << "min: " << min << "max: " << max << endl;
	return Box(Vector3(min.x, min.y, min.z), Vector3(max.x, max.y, max.z));
}

// getMeshPointsInBox:  return an array of indices to points in mesh that are contained 
//                      inside the Box.  Return count of points found;
//
int Octree::getMeshPointsInBox(const Mesh & mesh, const vector<int>& points,
	Box & box, vector<int> & pointsRtn)
{
	int count = 0;

	//cout << "getMeshPointsInBox start" << endl;

	for (int i = 0; i < points.size(); i++) 
	{
		
		ofVec3f v = mesh.vertices[(points[i])];
		if (box.inside(Vector3(v.x, v.y, v.z))) 
		{
			count++;
			pointsRtn.push_back(points[i]);
		}
	}

	//cout << "getMeshPointsInBox end " << endl;

	return count;
}



//  Subdivide a Box into eight(8) equal size boxes, return them in boxList;
//
void Octree::subDivideBox8(const Box &box, vector<Box> & boxList) {
	Vector3 min = box.parameters[0];
	Vector3 max = box.parameters[1];
	Vector3 size = max - min;
	Vector3 center = size / 2 + min;
	float xdist = (max.x() - min.x()) / 2;
	float ydist = (max.y() - min.y()) / 2;
	float zdist = (max.z() - min.z()) / 2;
	Vector3 h = Vector3(0, ydist, 0);

	//  generate ground floor
	//
	Box b[8];
	b[0] = Box(min, center);
	b[1] = Box(b[0].min() + Vector3(xdist, 0, 0), b[0].max() + Vector3(xdist, 0, 0));
	b[2] = Box(b[1].min() + Vector3(0, 0, zdist), b[1].max() + Vector3(0, 0, zdist));
	b[3] = Box(b[2].min() + Vector3(-xdist, 0, 0), b[2].max() + Vector3(-xdist, 0, 0));

	boxList.clear();
	for (int i = 0; i < 4; i++)
		boxList.push_back(b[i]);

	// generate second story
	//
	for (int i = 4; i < 8; i++) {
		b[i] = Box(b[i - 4].min() + h, b[i - 4].max() + h);
		boxList.push_back(b[i]);
	}
}

//functionality derived from the lecture slides
//creates an octree with @param numLevels levels
void Octree::create(const Mesh & geo, int numLevels) 
{
	// initialize octree structure
	//
	
	//cout << "Time started to create Octree: " << time.getAsMilliseconds() << endl;

	//Box firstBox = meshBounds(geo);
	//createst he bounding box around the mesh
	root.box = meshBounds(geo);

	cout << "meshBounds done" << endl;

	//populates the root's vertices with the veritces found in the mesh's bounding box
	for (int i = 0; i < geo.vertices.size(); i++)
	{
		//cout << "push back points to the root" << endl;
		root.points.push_back(i);
	}
	cout << "root's vertices populate done" << endl;
	
	//start the creation of the octree starting from the root of the TreeNode
	subdivide(geo, root, numLevels, 0);

	//cout << "Time ended to create Octree: " << time.getAsMilliseconds() << endl;
}

//algorithm derived from the lecture slides
//subdivides the octree into 8 boxes for each level
void Octree::subdivide(const Mesh & mesh, TreeNode & node, int numLevels, int level) 
{
	//create a node for the box containing:
	//the box
	//list of point indices
	//list of child boxes, can access the boxes from the children

	//increment the level if the level does not exceed the number of levels specificed 
	/*if (numLevels < level)
	{
		return;
	}
	else
	{
		level++;
	}*/
	if (level >= numLevels) return;
	level++;
	

	//subdivide the box into 8 equally sized boxes
	vector <Box> eightBoxes;
	subDivideBox8(node.box, eightBoxes);

	//cout << "Size of eight boxes: " << eightBoxes.size() << endl;

	//create a node for each of the 8 child boxes
	for (int i = 0; i < 8; i++)
	{
		TreeNode boxChild;
		boxChild.box = eightBoxes[i];
		
		//cout << "creating node for each of the 8 childrens" << endl;

		//for all indices in the box, add to an index list in each child node if the point is in the child box
		int count = getMeshPointsInBox(mesh, node.points, eightBoxes[i], boxChild.points);

		//if a child box is not empty, add to the parent list of child boxes
		if (count > 0)
		{
			//cout << "child box is not empty" << endl;
			node.children.push_back(boxChild);
		}

		//if there is more than one vertex stored in a child recursiely call subdivide
		if (count > 1)
		{
			//cout << "recursive call of subdivide" << endl;
			subdivide(mesh, node.children[node.children.size()-1], numLevels, level);
		}


	}	
	
}

bool Octree::intersect(const Ray &ray, const TreeNode & node, TreeNode & nodeRtn) 
{
	//int count = node.children.size();
	//
	////node is a leaf node
	//if (count == 0)
	//{
	//	if (node.box.intersect(ray, -1000, -1000))
	//	{
	//		//if the leaf box contains vertices then we can stop traversing the tree, returns true
	//		return(node.points.size() > 0);
	//	}
	//}
	//else
	//{
	//	//get all the leaf nodes that were intersected by the ray
	//	vector<TreeNode> leaves;
	//	for (int i = 0; i < count; i++)
	//	{
	//		TreeNode child = node.children[i];
	//		//if we interesect that child node, put it in the list so that we can see if their childern are intersected 
	//		if (intersect(ray, child, child))
	//		{
	//			leaves.push_back(child);
	//		}
	//	}
	//	count = leaves.size();
	//	if (count > 0)
	//	{
	//		//get the vertices in those leaves
	//		for (int i = 0; i < count; i++)
	//		{
	//			TreeNode n = leaves[i];
	//			for (int j = 0; j < n.points.size(); j++)
	//			{
	//				nodeRtn.points.push_back(j);
	//			}
	//		}
	//		return true;
	//	}
	//}
	//
	ofMesh m;
	m.getNumVertices();

	return false;
}

bool Octree::intersect(const ofVec3f &point, TreeNode & node, TreeNode & nodeRtn)
{

	return false;
}

