#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	c = 0;
	ofBackground(0, 0, 0);
	char2Vel = 4;
	char2Y = ofGetHeight() / 2;
	char3Vel = 3;
	char3X = ofGetWidth() / 2;
}

//--------------------------------------------------------------
void ofApp::update(){
	c += 3.005; // counter goes up

	//setting intro depending on time
	if (ofGetElapsedTimef() < 3) {
		setIntro = true;
	}
	else {
		setIntro = false;
	}

	//Bounce if reaching offscreen
	if (char2Y <= 50 || char2Y >= ofGetHeight() - 50) {
		if (char2Y >= ofGetHeight() - 50) {
			char2Vel = -12;
		}
		else if (char2Y <= 50) {
			char2Vel = 4;
		}
	}
	if (char3X <= 50 || char3X >= ofGetWidth() - 50) {
		if (char3X >= ofGetWidth() - 50) {
			char3Vel = -15;
		} else if (char3X <= 50) {
			char3Vel = 3;
		}
	}
	char2Y += char2Vel;
	char3X += char3Vel;
}

//--------------------------------------------------------------
void ofApp::draw(){
	//check if to display intro
	if (setIntro) {
		intro();
		return;
	}

	//Static obj
	ofSetColor(100, 50, 75);
	if (char3X <= 100) {
		ofSetColor(255);
	}
	ofDrawRectangle(10, 10, 100, ofGetHeight()-10);

	//Obj 1 Circle
	ofSetColor(200, 200, 200);
	//Using Noise for bonus
	float x1 = ofMap(ofNoise(ofGetElapsedTimef()), 0, 1, 0, ofGetWidth());
	float y1 = ofMap(ofNoise(ofGetElapsedTimef() + 400), 0, 1, 0, ofGetHeight());
	ofDrawCircle(x1, y1, 10); // draw the character at this location

	//Obj 2 Triangle
	ofSetColor(0, 0, 250);
	float x3 = ofGetWidth() / 2;
	float y3 = char2Y;
	ofDrawTriangle(x3, y3, x3 + 50, y3, x3, y3 + 50); // draw the character at this location

	//Obj 3 Square
	ofSetColor(250, 0, 0);
	float x2 = char3X;
	float y2 = ofGetHeight() / 2;
	ofRotateDeg(c, x2, y2, 0); //Rotation
	ofDrawRectangle(x2, y2, 30, 30); // draw the character at this location
}

//Credits Screen as per spec
void ofApp::intro() {
	ofBackground(0,0,0);
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("Name: Ansh Sachinkumar Arora", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
	ofDrawBitmapString("Student #: 101218267", ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 50);
	ofDrawBitmapString("Title: COMP4900L A1", ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	c = 0; // reset timer, start over from zero
}

