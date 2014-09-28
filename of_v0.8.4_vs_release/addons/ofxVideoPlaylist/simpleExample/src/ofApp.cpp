#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	video = NULL;

	playlist.setup("videos");
	playlist.enableAllEvents();

	ofAddListener(playlist.onSelectVideo, this, &ofApp::onSelectVideo);
	ofAddListener(playlist.onUnselectVideo, this, &ofApp::onUnselectVideo);

	playlist.nav.activate(0);
}

void ofApp::onSelectVideo(ofVideoPlayer &e) {
	video = &e;
	video->play();
};

void ofApp::onUnselectVideo(ofVideoPlayer &e) {
	e.stop();
};

//--------------------------------------------------------------
void ofApp::update(){
	if(video!=NULL) video->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	if(video!=NULL) video->draw(100, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
	if(button==1)
		playlist.scale = (float)x*2.0f/(float)ofGetWidth();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
