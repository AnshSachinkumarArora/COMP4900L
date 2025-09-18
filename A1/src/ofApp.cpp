#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	c = 0;
	ofBackground(0, 0, 0);
	/* curve = ofPolyline::ofPolyline_(); // new polyline
	for (int i = 0; i < 100; i++) // add a bunch of points
	{ 
		curve.addVertex(400+200*cos(i / 20.), 400+300*sin(i / 20.), 0.0); // put them in a circle (or whatever)
	}*/
}

//--------------------------------------------------------------
void ofApp::update(){
	c += 5.005; // counter goes up
}

//--------------------------------------------------------------
void ofApp::draw(){

	//ofSetColor(0, 250, 250);
	//curve.draw(); // show the trajectory the character will follow

	//Obj 1 Circle
	ofSetColor(200, 200, 200);
	//glm::vec3 x = curve.getPointAtPercent(c); // find the location on the curve corresponding to current time
	float x1 = ofMap(ofNoise(ofGetElapsedTimef()), 0, 1, 0, ofGetWidth());
	float y1 = ofMap(ofNoise(ofGetElapsedTimef() + 400), 0, 1, 0, ofGetHeight());
	ofDrawCircle(x1, y1, 10); // draw the character at this location

	//Obj 2 Square
	ofSetColor(250, 0, 0);
	float x2 = std::pow(ofGetElapsedTimef(), 1.2) + 50;
	float y2 = ofGetHeight() / 2;
	ofDrawRectangle(x2, y2, 30, 30);

	//Obj 3 Triangle
	ofSetColor(0, 0, 250);
	float x3 = ofGetWidth() / 2;
	float y3 = std::pow(ofGetElapsedTimef(), 2) + 50;
	ofDrawTriangle(x3, y3, x3 + 50, y3, x3, y3 + 50);

	//static object 1

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	c = 0; // reset timer, start over from zero
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
