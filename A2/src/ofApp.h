#pragma once

#include "ofMain.h"
#include <vector>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		glm::mat4 createToonLUT(glm::vec3 baseColor);

		//stand
		ofCylinderPrimitive stand;

		//main star
		ofIcoSpherePrimitive star;

		//planet disks
		vector<ofCylinderPrimitive> disks;

		//disk rods
		vector<ofCylinderPrimitive> rods;

		//vertical rods to hold planets
		vector<ofCylinderPrimitive> rodVerts;

		//planets
		vector<ofIcoSpherePrimitive> planets;

		//moon discs
		vector<ofCylinderPrimitive> moonDiscs;

		//moon vertical rods
		vector<ofCylinderPrimitive> moonRodVerts;

		//moons
		vector<ofIcoSpherePrimitive> moons;

		//light source
		//ofLight sun;

		//camera
		ofEasyCam cam;

		//shaders
		ofShader brassShader;
		ofShader toonShader;
		bool toonActive;

		vector<float> rotationSpeeds;
		vector<float> rotationSpeedsPlanets;
		vector<float> rotationSpeedsMoons;
};
