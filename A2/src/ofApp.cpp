#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(ofColor::black);
	ofSetCircleResolution(64);
	ofSetFrameRate(60);
	ofEnableDepthTest();

	//shaders
	brassShader.load("shaders/lighting.vert", "shaders/lighting.frag");
	toonShader.load("shaders/lighting.vert", "shaders/toon.frag");
	toonActive = false;

	//Main stand
	int standRadius = 20;
	int standHeight = 100;
	stand.set(standRadius, standHeight);
	stand.setPosition(ofGetWidth() * 0.5, ofGetHeight() * 0.5, 0);
	stand.setResolution(20, 8, 3);

	//system star
	int starRadius = 40;
	star.set(starRadius, 2);
	star.setParent(stand);
	star.setPosition(0, -standHeight / 2, 0);

	//planet disks
	for (int i = 0; i < 3; i++) {
		ofCylinderPrimitive current;
		current.set(40, 40);
		current.setResolution(20, 8, 3);
		current.setParent(stand);
		current.setPosition(0, (standHeight / 2) + (i*40), 0);
		disks.push_back(current);
	}

	//planet rods
	for (int i = 0; i < 3; i++) {
		ofCylinderPrimitive current;
		current.set(10, 150 + (i*130));
		current.setResolution(20, 8, 3);
		current.setParent(disks[i]);
		current.setPosition(current.getHeight() / 2 - 10, 0, 0);
		current.rotate(90, 0, 0, 1);
		rods.push_back(current);
	}

	//vertical rods
	for (int i = 0; i < 3; i++) {
		ofCylinderPrimitive current;
		current.set(10, 100);
		current.setResolution(20, 8, 3);
		current.setParent(rods[i]);
		current.setPosition(-current.getHeight() / 2, (-rods[i].getHeight() / 2) + 10, 0);
		current.rotate(90, 0, 0, 1);
		rodVerts.push_back(current);
	}

	//planets
	for (int i = 0; i < 3; i++) {
		ofIcoSpherePrimitive current;
		current.set(20 + (i+1 * ofRandom(0, 15)), 2);
		current.setParent(rodVerts[i]);
		current.setPosition(0, rodVerts[i].getHeight() / 2, 0);
		planets.push_back(current);
	}

	//moon discs
	for (int i = 0; i < 3; i++) {
		ofCylinderPrimitive current;
		current.set(((planets[i].getRadius()))+30, 5);
		current.setResolution(20, 8, 3);
		current.setParent(rodVerts[i]);
		current.setPosition(0, 10, 0);
		moonDiscs.push_back(current);
	}

	//moon rods
	for (int i = 0; i < 3; i++) {
		ofCylinderPrimitive current;
		current.set(3, rodVerts[i].getHeight()/2 - 10);
		current.setResolution(20, 8, 3);
		current.setParent(moonDiscs[i]);
		current.setPosition(moonDiscs[i].getRadius() - 10, rodVerts[i].getHeight() / 4 - 5, 0);
		moonRodVerts.push_back(current);
	}

	//moons
	for (int i = 0; i < 3; i++) {
		ofIcoSpherePrimitive current;
		current.set(5 + (i+1 * ofRandom(0, 10)), 2);
		current.setParent(moonRodVerts[i]);
		current.setPosition(0, moonRodVerts[i].getHeight() / 2, 0);
		moons.push_back(current);
	}

	//rotation
	for (int i = 0; i < 3; i++) {
		bool direction = round(ofRandom(-1, 1));
		direction == 0 ? direction = 1 : direction;
		rotationSpeeds.push_back(direction * ofRandom(0.2, 0.5));
		rotationSpeedsPlanets.push_back(direction*ofRandom(0.1, 1));
		rotationSpeedsMoons.push_back(direction * ofRandom(0.5, 1));
	}

	/* sun.setPointLight();
	sun.setGlobalPosition(0, 0, 1000);
	sun.enable();

	ofEnableLighting();*/
}

//--------------------------------------------------------------
void ofApp::update(){
	//sun.setPosition(cam.getGlobalPosition());
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	ofShader & current = toonActive ? toonShader : brassShader;
	current.begin();

	current.setUniformMatrix4f("viewMatrix", cam.getModelViewMatrix());
	current.setUniformMatrix4f("modelViewProjectionMatrix", cam.getModelViewProjectionMatrix());
	current.setUniformMatrix4f("projectionMatrix", cam.getProjectionMatrix());
	current.setUniform3f("lightPos", glm::vec3(100, 420, 100));
	current.setUniform3f("viewPos", cam.getPosition());
	current.setUniform3f("lightColor", glm::vec3(1, 1, 1));

	glm::vec3 brassColor = glm::vec3(0.8, 0.6, 0.2);
	vector<ofColor> colors = { ofColor::red, ofColor::blue, ofColor::saddleBrown };
	vector<ofColor> colorsMoons = { ofColor::darkGreen, ofColor::white, ofColor::deepSkyBlue };

	if (toonActive) {
		glm::mat4 colorLUT = createToonLUT(brassColor);
		current.setUniformMatrix4f("colorLUT", colorLUT);
		current.setUniform3f("thresholds", 0.85, 0.6, 0.35);
	} else {
		current.setUniform3f("objectColor", brassColor);
	}

	for (int i = 0; i < 3; i++) {
		disks[i].rotate(rotationSpeeds[i], 0, 1, 0);
		moonDiscs[i].rotate(rotationSpeedsMoons[i], 0, 1, 0);
	}

	//ofSetColor(ofColor::white);
	current.setUniformMatrix4f("worldMatrix", stand.getGlobalTransformMatrix());
	stand.draw();	
	for (int i = 0; i < 3; i++) {
		if (toonActive) {
			glm::mat4 colorLUT = createToonLUT(brassColor);
			current.setUniformMatrix4f("colorLUT", colorLUT);
			current.setUniform3f("thresholds", 0.85, 0.6, 0.35);
		} else {
			current.setUniform3f("objectColor", brassColor);
		}
		//ofSetColor(ofColor::darkGoldenRod);
		current.setUniformMatrix4f("worldMatrix", disks[i].getGlobalTransformMatrix());
		disks[i].draw();
		current.setUniformMatrix4f("worldMatrix", rods[i].getGlobalTransformMatrix());
		rods[i].draw();
		current.setUniformMatrix4f("worldMatrix", rodVerts[i].getGlobalTransformMatrix());
		rodVerts[i].draw();
		current.setUniformMatrix4f("worldMatrix", moonDiscs[i].getGlobalTransformMatrix());
		moonDiscs[i].draw();
		current.setUniformMatrix4f("worldMatrix", moonRodVerts[i].getGlobalTransformMatrix());
		moonRodVerts[i].draw();
		//ofSetColor(colors[i]);
		current.setUniformMatrix4f("worldMatrix", planets[i].getGlobalTransformMatrix());
		glm::vec3 planetColor = glm::vec3(colors[i].r / 255.f, colors[i].g / 255.f, colors[i].b / 255.f);
		if (toonActive) {
			glm::mat4 colorLUT = createToonLUT(planetColor);
			current.setUniformMatrix4f("colorLUT", colorLUT);
			current.setUniform3f("thresholds", 0.85, 0.6, 0.35);
		} else {
			current.setUniform3f("objectColor", planetColor);
		}
		planets[i].draw();
		//ofSetColor(colorsMoons[i]);
		glm::vec3 moonColor = glm::vec3(colorsMoons[i].r / 255.f, colorsMoons[i].g / 255.f, colorsMoons[i].b / 255.f);
		current.setUniformMatrix4f("worldMatrix", moons[i].getGlobalTransformMatrix());
		if (toonActive) {
			glm::mat4 colorLUT = createToonLUT(moonColor);
			current.setUniformMatrix4f("colorLUT", colorLUT);
			current.setUniform3f("thresholds", 0.85, 0.6, 0.35);
		} else {
			current.setUniform3f("objectColor", moonColor);
		}
		moons[i].draw();
	}

	current.end();

	ofSetColor(ofColor::yellow);
	star.draw();
	cam.end();
}

glm::mat4 ofApp::createToonLUT(glm::vec3 baseColor) {
	glm::mat4 lut;
	// Create four shades of the base color, from bright to dark
	lut[0] = glm::vec4(baseColor * 1.2f, 1.0); // Highlight
	lut[1] = glm::vec4(baseColor, 1.0); // Mid-tone
	lut[2] = glm::vec4(baseColor * 0.6f, 1.0); // Shadow
	lut[3] = glm::vec4(baseColor * 0.2f, 1.0); // Deep shadow
	return lut;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	toonActive = !toonActive;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
