#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	/* terrainMesh.setMode(OF_PRIMITIVE_TRIANGLES);

	//generate vertices
	for (int y = 0; y < terrainHeight; y++) {
		for (int x = 0; x < terrainWidth; x++) {
			float noiseVal = ofNoise(x * noiseFrequency, y * noiseFrequency);

			//noise for height
			float z = ofMap(noiseVal, 0, 1, -30, 30);
			terrainMesh.addVertex(glm::vec3(x - terrainWidth / 2, y - terrainHeight / 2, z));

			//noise for color
			ofColor b = ofColor::blue;
			ofColor w = ofColor::white;
			terrainMesh.addColor(b.lerp(w, noiseVal));
		}
	}

	//generate indices to connect vertices
	int gridW = terrainWidth / terrainGridStep;
	int gridH = terrainHeight / terrainGridStep;
	for (int y = 0; y < gridW - 1; y++) {
		for (int x = 0; x < gridH - 1; x++) {
			int i1 = (y * gridW) + x; // Top-left
			int i2 = (y * gridW) + (x + 1); // Top-right
			int i3 = ((y + 1) * gridW) + x; // Bottom-left
			int i4 = ((y + 1) * gridW) + (x + 1); // Bottom-right

			// Triangle 1 (Top-left, Top-right, Bottom-left)
			terrainMesh.addIndex(i1);
			terrainMesh.addIndex(i2);
			terrainMesh.addIndex(i3);

			// Triangle 2 (Top-right, Bottom-right, Bottom-left)
			terrainMesh.addIndex(i2);
			terrainMesh.addIndex(i4);
			terrainMesh.addIndex(i3);
		}
	}*/

	ofSetBackgroundColor(135, 206, 235); // Sky blue
	easyCam.setDistance(1000);

	// Generate terrain mesh (grid with noise heights)
	int res = 80; // Higher for smoother, but slower
	terrain.setMode(OF_PRIMITIVE_TRIANGLES);
	for (int iy = 0; iy <= res; ++iy) {
		for (int ix = 0; ix <= res; ++ix) {
			float x = ix * terrain_size / res;
			float y = iy * terrain_size / res;
			float z = getTerrainHeight(x, y);
			terrain.addVertex(ofVec3f(x, y, z));

			// Color: bluer near shore, sandier inland
			float shore_t = (y - shoreline_y) / terrain_size;
			if (shore_t < 0) {
				terrain.addColor(ofColor::navy);
			} else {
				terrain.addColor(ofColor::sandyBrown);
			}
			/* ofColor b = ofColor::blue;
			ofColor w = ofColor::brown;
			terrain.addColor(w.lerp(b, shore_t));*/
		}
	}
	for (int iy = 0; iy < res; ++iy) {
		for (int ix = 0; ix < res; ++ix) {
			int i = iy * (res + 1) + ix;
			terrain.addTriangle(i, i + 1, i + res + 1);
			terrain.addTriangle(i + res + 1, i + 1, i + res + 2);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	easyCam.begin();
	terrain.draw();
	easyCam.end();
}

float ofApp::getTerrainHeight(float x, float y) {
	float slope = (y - shoreline_y) / terrain_size * 20.0f; // Gentle rise inland
	float noise1 = ofNoise(x * 0.005f, y * 0.005f) * 10.0f; // Large waves
	float noise2 = ofNoise(x * 0.02f, y * 0.02f) * 5.0f; // Small details
	return slope + noise1 + noise2;
}
