#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	for (int i = 0; i < 5; i++) {
		nav.add( new page(i) );
	}
	
	ofAddListener(nav.deactivateEvent, this, &testApp::onDeactivateNav);
	ofAddListener(nav.activateEvent, this, &testApp::onActivateNav);

	nav.activate(0);
}

void testApp::onDeactivateNav(ofxNavigation<page*> & e) {
	nav.getCurrent()->deactivate();
};

void testApp::onActivateNav(ofxNavigation<page*> & e) {
	nav.getCurrent()->activate();
};

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofSetColor(0);

	string message = "press the arrows to change the index\n";
	message += "press the numbers between 0-4 to change the index\n";
	message += "press the keys <> to change the subindex\n";
	ofDrawBitmapString(message, 20, 30);

	ofTranslate(20,70);
	
	int total = nav.items.size();
	for (int i = 0; i < total; i++) {
		nav.getItem(i)->draw();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch(key)
	{
		case OF_KEY_LEFT:
		case OF_KEY_UP:
			nav.activatePreviousOnList(true);
			break;
		case OF_KEY_RIGHT:
		case OF_KEY_DOWN:
			nav.activateNextOnList(true);
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
			nav.activate( ofToInt( ofToString((char)key) ) );
			break;
		case '>':
		case '.':
			nav.getCurrent()->subNav.activateNextOnList(true);
			break;
		case '<':
		case ',':
			nav.getCurrent()->subNav.activatePreviousOnList(true);
			break;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}