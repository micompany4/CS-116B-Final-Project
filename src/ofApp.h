#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"

#include "Ray.h"
#include "SceneObject.h"
#include "Sphere.h"
#include "Triangle.h"
#include "ViewPlane.h"
#include "Plane.h"
#include "Light.h"
#include "RenderCam.h"
#include "Mesh.h"
#include "Octree.h"

/*
	Michael Wong and Areeq Yaqub's CS 116B Final Project
*/
class ofApp : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void drawAxis(glm::vec3 pos);
	void rayTrace();
	void rayMarch();
	bool rayMarch(Ray r, glm::vec3 &p);
	float sceneSDF(const glm::vec3 &p);
	ofColor ofApp::lambert(const glm::vec3 &p, const glm::vec3 &norm, const ofColor diffuse);
	ofColor ofApp::phong(const glm::vec3 &p, const glm::vec3 &norm, const ofColor diffuse, const ofColor specular, float power);
	bool isShadow(const Ray &r);
	bool isSpotlightShadow(const Ray &r, const Light &l);
	bool isSpotlightShadowRM(const Ray &r, const Light &l);
	ofColor allShader(const glm::vec3 &p, const glm::vec3 &norm, const ofColor diffuse, const ofColor specular, float power, SceneObject* obj);
	ofColor lookup(float u, float v);
	bool objSelected() { return (selected.size() ? true : false); };
	bool ofApp::mouseToDragPlane(int x, int y, glm::vec3 &point);
	void printChannel();
	void deleteObj();
	bool inSpotLight(const Light &l, const glm::vec3 &p);
	glm::vec3 getNormalRM(const glm::vec3 &p);

	bool bMouse = true;
	bool bHide;
	bool bTrace = true;

	ofEasyCam easyCam;
	ofCamera viewCam, sideCam;			//camera to give view of the view plane and of the side
	ofCamera *theCam;					//pointer to switch cameras

	RenderCam renderCam;
	ofImage image, map;
	ofImage texture;
	Mesh *objMesh;
	FILE* f;
	Octree tree;
	ofxAssimpModelLoader characterModel;

	Plane plane;
	ViewPlane vp;
	vector<SceneObject *> scene;				//vector to hold all the objects in the scene
	vector<SceneObject*> selected;				//vector to hold an object that is selected
	int imageH = 200, imageW = 300;			//dimensions for the image to render
	float squares = 10;							//the dimensions for how many tiles you want layed on the plane
	int sceneIdx = 0;
	int lvls = 5;
	ofSoundPlayer ping;

	glm::vec3 hitpoint, normal;					//vec3s to be used later for intersect
	Light light;
	vector<Light *> lights;

	glm::vec3 lastPoint;
	glm::vec3 cursor;							//vec3 that tracks the movement of the mouse cursor

	ofxPanel gui;
	ofxFloatSlider intensity;
	ofxFloatSlider power;
	ofxFloatSlider radiusSlider;
	ofxColorSlider colorWheel;
	ofxFloatSlider coneRadius;
	ofxFloatSlider angleRot;
	ofxVec2Slider tValue;

	ofColor ambient = ofColor::lightGray;	//a constant ambient color
	float pWidth = 20, pHeight = 20;
	//double check these for what values need to be in them
	const float MAX_RAY_STEPS = 200;			//maximum amount of iterations for moving along the ray
	const float DIST_THRESHOLD = 0.01;			//margin of seperation to deem a hit
	const float MAX_DISTANCE = 50;				//furthest distance from "bullseye" that will be considered as a hit

	bool bDrag = false;
	bool bRad = false;
	bool bColor = false;
	bool bIntense = false;
	bool bCone = false;
	bool bRotateX = false;
	bool bRotateY = false;
	bool bRotateZ = false;
	bool bAnimate = false;
	bool bAngle = false;
	bool bTValue = false;
	bool bDrawOctree = false;
	bool bDrawObj = false;
};
