#pragma once

#include "ofMain.h"

template <class T>
class ofxNavigation {
public:
	
	//--------------------------------------------------------------
	// setup

    ofxNavigation() {
		previousIndex = -1;
		currentIndex = -1;
		nextIndex = -1;
		locked = false;
		waitingDeactivate = false;
	};

    void add(const T & item) {
		items.push_back(item);
	};

    void remove(const T & item) {
		remove(getIndex(item));
	};

    void remove(int index) {
		if (currentIndex == index) {
			deactivate();
		}
		items.erase(items.begin()+(index-1));
	};
	

	//--------------------------------------------------------------
	// activations

    void activate(int index) {
		changeTo(index);
	};

    void activate(const T & item) {
		changeTo(getIndex(item));
	};

    void activateNextOnList(bool loop = false) {
		if (currentIndex > -1 && currentIndex+1 < items.size()) {
			changeTo(currentIndex+1);
		} else if (loop) {
			changeTo(0);
		}
	};

    void activatePreviousOnList(bool loop = false) {
		if (currentIndex > 0 && currentIndex-1 < items.size()) {
			changeTo(currentIndex-1);
		} else if (loop) {
			changeTo(items.size()-1);
		}
	};

    void deactivate() {
		changeTo(-1);
	};
	

	//--------------------------------------------------------------
	// getters

    T getPrevious() {
		return getItem(previousIndex);
	};

    T getCurrent() {
		return getItem(currentIndex);
	};

    T getNext() {
		return getItem(nextIndex);
	};

	T getItem(int index) {
		return (index > -1 && index < items.size()) ? items[index] : NULL;
	};
	
    int getIndex(const T & item) {
		for (int i = 0; i < items.size(); i++) {
			if (items[i] == item) return i;
		}
		return -1;
	};
	

	//--------------------------------------------------------------
	// locker

    void lock() {
		locked = true;
	};

    void unlock() {
		locked = false;
		if (!waitingDeactivate && nextIndex > -1) {
			updateVars();
			ofNotifyEvent(activateEvent, *this);
		}
	};

    bool isLocked() {
		return locked;
	};
    

	//--------------------------------------------------------------
	// vars

    vector<T> items;
    int previousIndex;
    int currentIndex;
    int nextIndex;

    ofEvent<ofxNavigation> activateEvent;
    ofEvent<ofxNavigation> deactivateEvent;
    

private:
    
	//--------------------------------------------------------------
	// core

    void changeTo(int newIndex) {
		if (locked) return;
    
		//only deactivate
		if (newIndex == -1 && currentIndex > -1) {
			ofNotifyEvent(deactivateEvent, *this);
			updateVars();
		}
		else if (newIndex != currentIndex) {
        
			//only activate
			if (currentIndex == -1) {
				nextIndex = newIndex;
				updateVars();
				ofNotifyEvent(activateEvent, *this);
			}
        
			//deactivate and activate
			else {
				nextIndex = newIndex;
				waitingDeactivate = true;
				ofNotifyEvent(deactivateEvent, *this);
				waitingDeactivate = false;

				//if the someone call lock() when deactivate
				//it means that nav need to wait
				//so wait someone call unlock() to procced
				if (!locked && nextIndex > -1) {
					updateVars();
					ofNotifyEvent(activateEvent, *this);
				}
			}
		}
	}

    void updateVars() {
		previousIndex = currentIndex;
		currentIndex = nextIndex;
		nextIndex = -1;
	};
	

	//--------------------------------------------------------------
	// extra vars

    bool locked;
	bool waitingDeactivate;
    
};
