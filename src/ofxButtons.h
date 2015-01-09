#pragma once

#include "ofxSimpleGuiToo.h"
#include "ofMain.h"

class button{

public:

	button():_pos(ofPoint(0, 0, 0)), 
		_enabled(true), _id(0){
			_img[0] = NULL;
			_img[1] = NULL; 

	}

	ofImage		*_img[2];	// two state
	
	ofPoint		_pos;
	bool		_enabled;

	int			_id;
	string		_title;
};

class ofxButtons
{
public:
	
	ofxButtons(void);
	virtual ~ofxButtons(void);

	void mousePressed(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);

	void addListener();
	void removeListener();

	/*
	* set position configure page
	*/
	void setup(const string & name);

	// used for openNI hand
	void setPosition(const int& btnName, const ofPoint &pos);

	void draw();
	void draw(int btnId);

	ofRectangle getButtonArea(int btnId);
	void changeButtonState(int btnId);

	void SetButton(const int &name, ofImage *b, int id = 0);
	map<int,button> &buttons(){return _buttons;}

private:
	map<int, button> _buttons;
};

