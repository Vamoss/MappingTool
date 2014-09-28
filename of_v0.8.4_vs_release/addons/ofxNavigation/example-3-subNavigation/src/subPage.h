#pragma once

#include "ofMain.h"

class subPage : public ofRectangle {
public:

	subPage(int index) {
		enabled = false;
		name = ofToString(index);
		x = index*25;
		y = 0;
		width = 25;
		height = 100;
	};

	void activate() {
		enabled = true;
	};

	void deactivate() {
		enabled = false;
	};

	void draw() {
		if (!enabled) return;

		ofSetColor(150);
		ofRect(*this);
		
		ofSetColor(255);
		ofDrawBitmapString(name, x+8, y+25);
	};


private:
	
	string name;
	bool enabled;


};
