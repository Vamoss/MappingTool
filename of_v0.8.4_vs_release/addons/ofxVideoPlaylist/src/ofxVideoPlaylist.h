#pragma once

#define THUMB_WIDTH 120
#define THUMB_SPACE 10

#include "ofMain.h"
#include "ofxNavigation.h"

struct data {
    ofImage * thumbnail;
	ofVideoPlayer * video;

	float y;

	data(ofVideoPlayer * video, ofImage * thumbnail){
		this->video = video;
		this->thumbnail = thumbnail;
	}
};

class ofxVideoPlaylist
{
public:
	ofxNavigation<data*> nav;
	float scale;

    ofEvent<ofVideoPlayer> onSelectVideo;
    ofEvent<ofVideoPlayer> onUnselectVideo;

	ofxVideoPlaylist()
	{
	}

	~ofxVideoPlaylist()
	{

	}

	void setup(string videosFolder="", int x=0, int y=0, int width=THUMB_WIDTH+(THUMB_SPACE*2), int height=ofGetHeight())
	{
		scale = 1.0f;
		scrollY = 1.0f;
		currentThumbY = THUMB_SPACE;

		keyEnabled = false;
		mouseEnabled = false;
		autoDrawUI = false;

		if(videosFolder!=""){
			ofDirectory dir;
			dir.allowExt("mov");
			dir.allowExt("mp4");
			dir.listDir(videosFolder);
			for(int i =0; i < dir.size(); i++){
				addVideo(dir.getPath(i));
			}
		}

		areaUtil.set(x, y, width, height);
		
		ofAddListener(nav.activateEvent, this, &ofxVideoPlaylist::onActivateNav);
		ofAddListener(nav.deactivateEvent, this, &ofxVideoPlaylist::onDeactivateNav);

		setColorBack(ofColor(0, 100));
	}

	void update()
	{
		
	}

	void draw()
	{
		ofPushMatrix();
			ofScale(scale, scale);
			ofTranslate(areaUtil.x, areaUtil.y);
			ofPushStyle();
				if(autoDrawUI) drawUI();
			ofPopStyle();
		ofPopMatrix();
	}
	
	void addVideo(string path)
	{
		ofVideoPlayer * video = new ofVideoPlayer();
		video->loadMovie(path);
		addVideo(video);
	}
	
	void addVideo(ofVideoPlayer * video)
	{
		if(video->isLoaded()){

			//generate thumbnail
			string thumbPath = "thumbs/"+ofFilePath::getBaseName(video->getMoviePath()) + ".jpg";
			cout << "thumb: " << thumbPath << endl;
			ofImage * thumbnail = new ofImage();
			float currentPosition = video->getPosition();
			float isPlaying = video->isPlaying();
			video->play();
			video->setPosition(0.1);
				thumbnail->setFromPixels( video->getPixelsRef() );
				thumbnail->resize(THUMB_WIDTH, THUMB_WIDTH * (thumbnail->getHeight() / thumbnail->getWidth()) );
				//thumbnail->saveImage(thumbPath);
			video->setPaused(!isPlaying);
			video->setPosition(currentPosition);

			data * d = new data(video, thumbnail);
			d->y = currentThumbY;
			nav.add(d);
			
			currentThumbY+=d->thumbnail->getHeight() + THUMB_SPACE;
		}
	}

    void removeVideo(ofVideoPlayer * video) {
		nav.remove(getVideoIndex(video));
	};

    void removeVideoIndex(int index) {
		nav.remove(index);
	};

	int getVideoIndex(ofVideoPlayer * video){
		for (int i = 0; i < nav.items.size(); i++) {
			if (nav.items[i]->video == video) return i;
		}
		return -1;
	}

	// enable all event callbacks
	void enableAllEvents(){
		enableMouseEvents();
		enableKeyEvents();
		enableAppEvents();
		enableDrawUI();
	}

	// disable all event callbacks
	void disableAllEvents(){
		disableMouseEvents();
		disableKeyEvents();
		disableAppEvents();
		disableDrawUI();
	}

	// call this if object should receive mouse events
	void enableMouseEvents(){
		if(mouseEnabled) return;

		mouseEnabled = true;
		ofAddListener(ofEvents().mousePressed, this, &ofxVideoPlaylist::mousePressed);
		ofAddListener(ofEvents().mouseMoved, this, &ofxVideoPlaylist::mouseMoved);
		ofAddListener(ofEvents().mouseDragged, this, &ofxVideoPlaylist::mouseDragged);
		ofAddListener(ofEvents().mouseReleased, this, &ofxVideoPlaylist::mouseReleased);
	}
	
	// call this if object doesn't need to receive mouse events (default)
	void disableMouseEvents(){
		if(!mouseEnabled) return;

		mouseEnabled = false;
		ofRemoveListener(ofEvents().mousePressed, this, &ofxVideoPlaylist::mousePressed);
		ofRemoveListener(ofEvents().mouseMoved, this, &ofxVideoPlaylist::mouseMoved);
		ofRemoveListener(ofEvents().mouseDragged, this, &ofxVideoPlaylist::mouseDragged);
		ofRemoveListener(ofEvents().mouseReleased, this, &ofxVideoPlaylist::mouseReleased);
	}
	
	// call this if object should receive key events
	void enableKeyEvents(){
		if(keyEnabled) return;

		keyEnabled = true;
		ofAddListener(ofEvents().keyPressed, this, &ofxVideoPlaylist::keyPressed);
	}
	
	// call this if object doesn't need to receive key events (default)
	void disableKeyEvents(){
		if(!keyEnabled) return;

		keyEnabled = false;
		ofRemoveListener(ofEvents().keyPressed, this, &ofxVideoPlaylist::keyPressed);
	}

	// call this if object should update/draw automatically
	void enableAppEvents() {
		ofAddListener(ofEvents().update, this, &ofxVideoPlaylist::_update);
		ofAddListener(ofEvents().draw, this, &ofxVideoPlaylist::_draw);
	}

	// call this if object doesn't need to update/draw automatically (default)
	void disableAppEvents() {
		ofRemoveListener(ofEvents().update, this, &ofxVideoPlaylist::_update);
		ofRemoveListener(ofEvents().draw, this, &ofxVideoPlaylist::_draw);
	}

	void enableDrawUI()
	{
		autoDrawUI = true;
	}

	void disableDrawUI()
	{
		autoDrawUI = false;
	}

	void setPosition(int x, int y)
	{
		areaUtil.x = x;
		areaUtil.y = y;
	}

	void setDimensions(int w, int h)
	{
		areaUtil.width = w;
		areaUtil.height = h;
	}

	void setColorBack(ofColor color)
	{
		colorBack = color;
	}

	bool isHit(int x, int y)
	{
		return areaUtil.inside(x/scale, y/scale);
	}

private:
	ofRectangle areaUtil;
	
	bool keyEnabled;
	bool mouseEnabled;
	bool autoDrawUI;
	
	ofPoint lastMousePosition;
	bool hasDragged;

	float scrollY;
	float currentThumbY;

	ofColor colorBack;

	void drawUI() {
		ofSetColor(colorBack);
		ofRect(0, 0, areaUtil.width, areaUtil.height);

		ofTranslate(0, scrollY);
		for (int i = 0; i < nav.items.size(); i++) {
			if(nav.items[i]->y+nav.items[i]->thumbnail->getHeight()+scrollY>areaUtil.height) return;
			if(nav.items[i]->y+scrollY>0) {
				ofSetColor(255, nav.getCurrent() == nav.items[i] ? 255 : 127);
				nav.items[i]->thumbnail->draw(THUMB_SPACE, nav.items[i]->y);
			}
		}
	}

	//---------------------------
	//APP EVENTS
	//---------------------------
	void _update(ofEventArgs &e)
	{
		update();
	}

    void _draw(ofEventArgs &e)
	{
		ofPushMatrix();
			draw();
		ofPopMatrix();
	}

	//---------------------------
	//NAVIGATION EVENTS
	//---------------------------
	void onActivateNav(ofxNavigation<data*> & e) {
		ofNotifyEvent(onSelectVideo, *nav.getCurrent()->video);
	};

	void onDeactivateNav(ofxNavigation<data*> & e) {
		ofNotifyEvent(onUnselectVideo, *nav.getCurrent()->video);
	};


	//---------------------------
	//USER INTERACTIONS
	//---------------------------
	void mouseMoved(ofMouseEventArgs &e)
	{
	}

	void mousePressed(ofMouseEventArgs &e)
	{
		if(!isHit(e.x, e.y)) return;

		e.x = e.x/scale;
		e.y = e.y/scale;

		hasDragged = false;

		lastMousePosition.x = e.x;
		lastMousePosition.y = e.y;
	}

	void mouseDragged(ofMouseEventArgs &e)
	{
		if(lastMousePosition.x == -1 && lastMousePosition.y == -1) return;

		e.x = e.x/scale;
		e.y = e.y/scale;

		if(ofDistSquared(e.x, e.y, lastMousePosition.x, lastMousePosition.y)>1) hasDragged = true;

		scrollY += e.y - lastMousePosition.y;
		if(scrollY>0) scrollY = 0;
		if(scrollY<-currentThumbY + areaUtil.height) scrollY = -currentThumbY + areaUtil.height;

		lastMousePosition.x = e.x;
		lastMousePosition.y = e.y;
	}

	void mouseReleased(ofMouseEventArgs &e)
	{
		lastMousePosition.x = -1;
		lastMousePosition.y = -1;

		if(!isHit(e.x, e.y)) return;
		
		e.x -= areaUtil.x;
		e.y -= areaUtil.y;

		e.x = e.x/scale;
		e.y = e.y/scale;

		if(!hasDragged){

			for (int i = 0; i < nav.items.size(); i++) {
				if(nav.items[i]->y+nav.items[i]->thumbnail->getHeight()+scrollY>areaUtil.height) return;
				if(nav.items[i]->y+scrollY>0) {
					if(e.y > nav.items[i]->y+scrollY && e.y < nav.items[i]->y+nav.items[i]->thumbnail->getHeight()+scrollY){
						nav.activate(i);
						return;
					}
				}
			}
		}
	}

	void keyPressed(ofKeyEventArgs &e)
	{
		switch(e.key) {  
		
		}
	}
};