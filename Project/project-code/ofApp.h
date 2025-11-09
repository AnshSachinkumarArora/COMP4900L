#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		//Terrain
		ofMesh terrain;
		int terrainWidth = 500;
		int terrainHeight = 500;
		int terrainGridStep = 10;
		ofVec2f flow_dir = ofVec2f(0, 1); // Inland flow (from shore at y=0)
		float terrain_size = 800.0f;
		float shoreline_y = terrain_size * 0.1f; // Shore near lower y
		float getTerrainHeight(float x, float y);

		//noise
		float noiseFrequency = 0.01;
		float time = 0.0;
		float timeSpeed = 0.02;

		//camera
		ofEasyCam easyCam;
};
