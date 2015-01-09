#include "ofxButtons.h"

//--------------------------------class ofxButtons -----------------------
ofxButtons::ofxButtons(void)
{
	void addListener();
}


ofxButtons::~ofxButtons(void)
{
	void removeListener();
}

void ofxButtons::setup(const string & name){
	ofLogNotice() << "ofxButton::Setup of " + name; 

	gui.addPage(name).setXMLName(name + ".xml");
	gui.addTitle("Buttons");

	map<int, button>::iterator it = _buttons.begin();
	map<int, button>::iterator itend = _buttons.end();

	for ( ; it != itend; ++it){
		gui.addSlider(ofToString(it->first) + " X ", it->second._pos.x, 0, ofGetWidth());
		gui.addSlider(ofToString(it->first) + " Y ", it->second._pos.y, 0, ofGetHeight());
	}

	gui.loadFromXML();
	gui.setDefaultKeys(true);
}

void ofxButtons::setPosition(const int& btnName, const ofPoint &pos){

	map<int, button>::iterator it = _buttons.find(btnName);
	if (it != _buttons.end()){
		if (ofDist(it->second._pos.x, it->second._pos.y, pos.x, pos.y)>20){
			it->second._pos = pos;
		}
	}else{
		ofLogVerbose() << "Not found button : " + btnName;
	}
}

void ofxButtons::SetButton(const int &name, ofImage *b, int id){
	ofLogNotice() << "ofxButton::Set Button : " + ofToString(name);
	_buttons[name]._img[id] = b;
}

void ofxButtons::draw(){

	map<int, button>::iterator it = _buttons.begin();
	map<int, button>::iterator itend = _buttons.end();

	for (; it != itend; ++it){
		// draw every enabled buttons
		if(it->second._enabled){
			it->second._img[it->second._id]->draw(it->second._pos.x, it->second._pos.y);
		}
	}
}

void ofxButtons::draw(int btnId){
	//ofEnableAlphaBlending();
	map<int, button>::iterator it = _buttons.find(btnId);
	ofSetRectMode(OF_RECTMODE_CENTER);
	if (it != _buttons.end()){
		it->second._img[it->second._id]->draw(it->second._pos.x, it->second._pos.y);
	}
	ofSetRectMode(OF_RECTMODE_CORNER);
	//ofDisableAlphaBlending();
}

ofRectangle ofxButtons::getButtonArea(int btnId){
	return ofRectangle(_buttons[btnId]._pos.x, 
					   _buttons[btnId]._pos.y,
					   _buttons[btnId]._img[_buttons[btnId]._id]->getWidth(),
					   _buttons[btnId]._img[_buttons[btnId]._id]->getHeight());
}

void ofxButtons::changeButtonState(int btnId){
	_buttons[btnId]._id  = (_buttons[btnId]._id + 1) % 2;
}


void ofxButtons::mousePressed(ofMouseEventArgs &e)
{
}
void ofxButtons::mouseReleased(ofMouseEventArgs &e){
	
}

void ofxButtons::addListener()
{
	ofAddListener(ofEvents().mousePressed, this, &ofxButtons::mousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &ofxButtons::mouseReleased);
}
void ofxButtons::removeListener()
{
	ofRemoveListener(ofEvents().mousePressed, this, &ofxButtons::mousePressed);
	ofRemoveListener(ofEvents().mouseReleased, this, &ofxButtons::mouseReleased);
}