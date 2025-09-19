#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void intro();

		int char2Vel;
		int char3Vel;
		int char2Y;
		int char3X;
		bool setIntro = false;
		float c;

};
