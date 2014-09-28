#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofxXmlSettings settings;
	settings.loadFile("settings.xml");
	int xx = settings.getAttribute("settings:window", "x", 0);
	int yy = settings.getAttribute("settings:window", "y", 0);
	int ww = settings.getAttribute("settings:window", "width", 1024);
	int hh = settings.getAttribute("settings:window", "height", 768);

    ofEnableAlphaBlending(); 
	ofSetWindowPosition(xx, yy);
	ofSetWindowShape(ww, hh);
	
	imageMap.loadImage("grid.png");
	
	int nOut = settings.getAttribute("settings:grid", "out", 4);
	int nCols = settings.getAttribute("settings:grid", "cols", 13);
	int nRows = settings.getAttribute("settings:grid", "rows", 14);
	
	int canvasWidth = 768;
	int canvasHeight = 1024;

	scale = 1.0f;
	useFade = true;

	m_mapper = ofxMapperControl((canvasWidth+1)*nOut,canvasHeight);
	m_mapper.enableAllEvents();
	
	if(!m_mapper.load()){
		int celW = canvasWidth/nCols;
		int celH = canvasHeight/nRows;
		for(int o=0; o<nOut; o++){
			for(int col=0; col<nCols; col++){
				for(int row=0; row<nRows; row++){
					int xx = (col*celW) + ((canvasWidth+1)*o);
					int yy = row*celH;
					m_mapper.addSquare(xx, yy, celW, celH);
				}
			}
		}
	}
	
	setGUI1(); 

	video = NULL;

	ofAddListener(playlist.onSelectVideo, this, &ofApp::onSelectVideo);
	ofAddListener(playlist.onUnselectVideo, this, &ofApp::onUnselectVideo);
	
	playlist.setup("videos");
	playlist.enableAllEvents();
	playlist.nav.activate(0);
	playlist.setPosition(PANEL_WIDTH, 0);
	playlist.setDimensions(THUMB_WIDTH+(THUMB_SPACE*2), PANEL_HEIGHT);
	playlist.setColorBack(ofColor(125, 200));
}

void ofApp::onSelectVideo(ofVideoPlayer &e) {
	video = &e;
	video->setPosition(0.0f);
	video->play();
	if(useFade) alpha = 0;
};

void ofApp::onUnselectVideo(ofVideoPlayer &e) {
	e.stop();
};

//--------------------------------------------------------------
void ofApp::update(){
	if(video!=NULL && !drawGridToogle->getValue())video->update();

	if(alpha<255) alpha += 5;
}

//--------------------------------------------------------------
void ofApp::draw(){    
	ofClear(0,0,0,0);
	m_mapper.begin();
		if(drawGridToogle->getValue()){
			imageMap.draw(0, 0);
		}else{
			ofSetColor(255, alpha);
			if(video!=NULL)video->draw(0,0);
		}
	m_mapper.end();
}

void ofApp::setGUI1()
{
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = PANEL_WIDTH-xInit;
	
    vector<string> modes; 
	modes.push_back("INPUT");
	modes.push_back("OUTPUT");
	modes.push_back("BOTH");
	
    vector<string> tools; 
	tools.push_back("NONE");
	tools.push_back("SELECT");
	tools.push_back("SCALE");
	tools.push_back("ROTATE");
	tools.push_back("QUICKCORNER");
	
	gui1 = new ofxUICanvas(0, 0, PANEL_WIDTH, PANEL_HEIGHT); 
	gui1->addWidgetDown(new ofxUILabel("PROJETACAO", OFX_UI_FONT_LARGE)); 
	gui1->setWidgetFontSize(OFX_UI_FONT_SMALL);
	gui1->setColorBack(ofxUIColor(125, 200));

	gui1->addSpacer(length-xInit, 2);

	gui1->addFPS();

	mappingToogle = new ofxUIToggle("MAPPING", true, dim, dim);
	gui1->addWidgetDown(mappingToogle);

	drawGridToogle = new ofxUIToggle("DRAW GRID", false, dim, dim);
	gui1->addWidgetDown(drawGridToogle);
	gui1->addSpacer(length-xInit, 2);
	
	ofxUIRadio * radioModes = new ofxUIRadio("MODES", modes, OFX_UI_ORIENTATION_VERTICAL, dim, dim);
	gui1->addWidgetDown(radioModes);
	gui1->addSpacer(length-xInit, 2);

	ofxUIRadio * radioTools = new ofxUIRadio("TOOLS", tools, OFX_UI_ORIENTATION_VERTICAL, dim, dim);
	gui1->addWidgetDown(radioTools);
	gui1->addSpacer(length-xInit, 2);

	gui1->addToggle( "COORDS", false, dim, dim);
	gui1->addToggle( "SQUARE GRID", false, dim, dim);
	gui1->addSpacer(length-xInit, 2);

	gui1->addSlider( "SIZE", 0, 3, 1, length-xInit, dim);
	
	gui1->addLabel("PRECISION", OFX_UI_FONT_SMALL);
	ofxUITextInput * precisionInput  = new ofxUITextInput("PRECISION", "1", 50);
	precisionInput->setAutoClear( false );
	gui1->addWidgetRight(precisionInput);

	gui1->addToggle( "FADE", true, dim, dim);

	gui1->addLabelButton("SAVE", false);
    
	ofAddListener(gui1->newGUIEvent,this,&ofApp::guiEvent);
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	cout << "got event from: " << name << endl; 	
	
	if(name == "SAVE")
	{
		m_mapper.save(); 
	}
	else if(name == "MAPPING")
	{
		if(mappingToogle->getValue()){
			m_mapper.enableDrawEditMode();
		}else{
			m_mapper.disableDrawEditMode();
		}
	}
	else if(name == "INPUT")
	{
		m_mapper.setVertexInputType(m_mapper.VERTEX_IN);
	}
	else if(name == "OUTPUT")
	{
		m_mapper.setVertexInputType(m_mapper.VERTEX_OUT);
	}
	else if(name == "BOTH")
	{
		m_mapper.setVertexInputType(m_mapper.VERTEX_BOTH);
	}
	else if(name == "NONE")
	{
		m_mapper.setEditModeType(m_mapper.MODE_NONE);
	}
	else if(name == "SELECT")
	{
		m_mapper.setEditModeType(m_mapper.MODE_SELECT);
	}
	else if(name == "SCALE")
	{
		m_mapper.setEditModeType(m_mapper.MODE_SCALE);
	}
	else if(name == "ROTATE")
	{
		m_mapper.setEditModeType(m_mapper.MODE_ROTATE);
	}
	else if(name == "QUICKCORNER")
	{
		m_mapper.toggleQuickCorner();
	}
    else if(name == "PRECISION")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget; 
		m_mapper.setPrecision(ofToFloat(textinput->getTextString()));
        cout << ofToFloat(textinput->getTextString()) << endl; 
    }
	else if(name == "COORDS")
	{
		ofxUIToggle *toogle = (ofxUIToggle *) e.widget; 
		if(toogle->getValue()){
			m_mapper.enableDrawCoord();
		}else{
			m_mapper.disableDrawCoord();
		}
	}
	else if(name == "SQUARE GRID")
	{
		ofxUIToggle *toogle = (ofxUIToggle *) e.widget; 
		if(toogle->getValue()){
			m_mapper.enableDrawGrid();
		}else{
			m_mapper.disableDrawGrid();
		}
	}
	else if(name == "SIZE")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		scale = slider->getValue();
		m_mapper.scale = scale;
	}
	else if(name == "FADE")
	{
		ofxUIToggle *toogle = (ofxUIToggle *) e.widget; 
		useFade = toogle->getValue();
	}
	
}
//--------------------------------------------------------------
void ofApp::exit()
{
	delete gui1;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(gui1->hasKeyboardFocus())
    {
        return;  
    }
	switch (key) 
	{
		case OF_KEY_LEFT:
		case OF_KEY_UP:
			if(!mappingToogle->getValue()) playlist.nav.activatePreviousOnList(true);
			break;
		case OF_KEY_RIGHT:
		case OF_KEY_DOWN:
			if(!mappingToogle->getValue()) playlist.nav.activateNextOnList(true);
			break;
		case 'f':
			ofToggleFullscreen(); 
			break;

		case 'h':
            gui1->toggleVisible();
			if(gui1->isVisible()){
				playlist.enableDrawUI();
			}else{
				playlist.disableDrawUI();
			}
			break;
            
		default:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if(gui1->isHit(x, y) || playlist.isHit(x, y)){
		m_mapper.disableKeyEvents();
		m_mapper.disableMouseEvents();
	}else{
		m_mapper.enableKeyEvents();
		m_mapper.enableMouseEvents();
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if(guiStartDrag.x!=-1) {
		gui1->setPosition(x - guiStartDrag.x, y - guiStartDrag.y);
		playlist.setPosition(x - guiStartDrag.x + PANEL_WIDTH, y - guiStartDrag.y);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if(gui1->isHit(x, y)){
		if(y < gui1->getRect()->y+30){
			guiStartDrag.x = x - gui1->getRect()->x;
			guiStartDrag.y = y - gui1->getRect()->y;
			return;
		}
	}

	guiStartDrag.x = guiStartDrag.y = -1;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	guiStartDrag.x = guiStartDrag.y = -1;
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