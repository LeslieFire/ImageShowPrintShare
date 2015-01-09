#pragma once

#include "ofMain.h"
#include "ofxThreadedDirLoader.h"
#include "ofxPrint.h"
#include "ofxXmlSettings.h"
#include "ofxFlash.h"
#include "ofxCurl.h"
#include "ofxButtons.h"
#include "ofxOpenCv.h"

enum ButtonID{
	PREVIOUS,
	NEXT,
	PRINT,
	SHARE
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void setupButtons();
		bool isInRange(int x, int y, ofRectangle & t);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void SetToPreviousImage();
		void SetToNextImage();
		void PrintCurrentPicture();
		

private:
		void updateUrl();
		void uploadImage();
		

		ofImage		_bg;
		ofImage		_logo;

		vector<ofImage> assets;
		ofxButtons		_buttons;

		ofDirectory	_directory;
		int			_fileNum;
		int			_imageIndex;
		string		_imageName;
		string		_url;
		ofxFlash	*_QR;

		ofxThreadedImageLoader loader;
		ofxThreadedDirLoader _loader;

		ofImage*	_currentImage;
		ofImage*	_preImage;
		ofImage*	_postImage;

		bool		_bPrinted;
		bool		_bShared;
		bool		_bPressed;

		bool		_bFullscreen;

		ofxXmlSettings xml;

		string		_uploadURL;
		ofxCurl		_curl;
};
