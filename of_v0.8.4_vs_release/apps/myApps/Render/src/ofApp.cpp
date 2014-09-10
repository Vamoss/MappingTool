#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofBackground(50);

	grid.loadImage("grid.png");
    
    // ----
    _mapping = new ofxMtlMapping2D();
	_mapping->init(grid.width, grid.height, "mapping/xml/shapes.xml", "mapping/controls/mapping.xml");
	_mapping->disableDrag();
}

//--------------------------------------------------------------
void ofApp::update(){

    _mapping->update();

}

//--------------------------------------------------------------
void ofApp::draw(){    
    _mapping->bind();
    ofSetColor(255);
    grid.draw(0, 0);
    _mapping->unbind();
    
    ofSetColor(255);
    _mapping->draw();
    //_mapping->drawFbo();
    

//    ofBeginShape();
//    ofFill();
//    ofSetColor(0, 255, 0);
//    for (int i = 0; i < _mapping->getMaskShapes()[0]->size(); i++) {
//        ofVertex(_mapping->getMaskShapes()[0]->getVertices()[i].x, _mapping->getMaskShapes()[0]->getVertices()[i].y);
//    }
//    ofEndShape(true);
    
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