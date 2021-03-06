#pragma once

#include "ofMain.h"
#include "ofxMapperControl.h"
#include "ofxUI.h"
#include "ofxVideoPlaylist.h"

#define PANEL_WIDTH 255
#define PANEL_HEIGHT 550

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();
	
    private:
        ofImage imageMap;
		ofVideoPlayer * video;

		ofxVideoPlaylist playlist;
		void onSelectVideo(ofVideoPlayer &e);
		void onUnselectVideo(ofVideoPlayer &e);

		bool useFade;
		int alpha;
		float scale;

		ofxMapperControl m_mapper;
		void setGUI1();    
	
		ofPoint guiStartDrag;
		ofxUICanvas *gui1;
		ofxUIToggle *mappingToogle;
		ofxUIToggle *drawGridToogle;

		void guiEvent(ofxUIEventArgs &e);

};
