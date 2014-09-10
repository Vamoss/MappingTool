#include "ofxMtlMapping2DInteractiveObject.h"


//--------------------------------------------------------------
//--------------------------------------------------------------
ofxMtlMapping2DInteractiveObject::ofxMtlMapping2DInteractiveObject()
{    
    disableAllEvents();
	enableMouseEvents();

	canDrag = true;
}

//--------------------------------------------------------------
ofxMtlMapping2DInteractiveObject::~ofxMtlMapping2DInteractiveObject(){

}

//--------------------------------------------------------------
void ofxMtlMapping2DInteractiveObject::enableDrag(){
	canDrag = true;
}

//--------------------------------------------------------------
void ofxMtlMapping2DInteractiveObject::disableDrag(){
	canDrag = false;
}

//--------------------------------------------------------------
void ofxMtlMapping2DInteractiveObject::toggleDrag(){
	if(!canDrag) enableDrag();
	else disableDrag();
}