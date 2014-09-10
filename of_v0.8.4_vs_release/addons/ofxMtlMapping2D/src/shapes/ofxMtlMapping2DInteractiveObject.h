#pragma once

//OF
#include "ofMain.h"

#include "ofxMtlMapping2DShapeType.h"
#include "ofxMtlMapping2DSettings.h"
#include "mtlUtils.h"

//MSA Libs
#include "ofxMSAInteractiveObject.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxMtlMapping2DInteractiveObject : public ofxMSAInteractiveObject {
	
    public:
        ofxMtlMapping2DInteractiveObject();
        ~ofxMtlMapping2DInteractiveObject();

		void enableDrag();
		void disableDrag();
		void toggleDrag();

	protected:
		bool canDrag;
};