#pragma once

#include "ofMain.h"

class page : public ofRectangle {
public:

	page(int index) {
		enabled = false;
		name = "page \n\nindex: "+ofToString(index);
		x = index*100;
		y = 0;
		width = 100;
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

		ofSetColor(255);
		ofRect(*this);
		
		ofSetColor(0);
		ofDrawBitmapString(name, x+15, y+25);
	};


private:
	
	string name;
	bool enabled;



};
