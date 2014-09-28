#pragma once

#include "ofMain.h"
#include "subPage.h"

class page : public ofRectangle {
public:

	page(int index) {
		enabled = false;
		name = "page \n\nindex: "+ofToString(index);
		x = index*100;
		y = 0;
		width = 100;
		height = 100;
		
		for (int i = 0; i < 4; i++) {
			subNav.add( new subPage(i) );
		}
		
		ofAddListener(subNav.deactivateEvent, this, &page::onDeactivateSubNav);
		ofAddListener(subNav.activateEvent, this, &page::onActivateSubNav);
	};

	void activate() {
		enabled = true;
		subNav.activate(0);
	};

	void deactivate() {
		enabled = false;
		subNav.deactivate();
	};

	void draw() {
		if (!enabled) return;

		ofSetColor(255);
		ofRect(*this);
		
		ofSetColor(0);
		ofDrawBitmapString(name, x+15, y+25);
		
		ofPushMatrix();
		ofTranslate(x, y+height);
			int total = subNav.items.size();
			for (int i = 0; i < total; i++) {
				subNav.getItem(i)->draw();
			}
		ofPopMatrix();
	};

	void onDeactivateSubNav(ofxNavigation<subPage*> & e) {
		subNav.getCurrent()->deactivate();
	};

	void onActivateSubNav(ofxNavigation<subPage*> & e) {
		subNav.getCurrent()->activate();
	};


	ofxNavigation<subPage*> subNav;


private:
	
	string name;
	bool enabled;



};
