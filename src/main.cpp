#include "ofMain.h"
#include "ofApp.h"

#if _DEBUG

#else
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

//========================================================================
int main( ){
	ofSetupOpenGL(1366,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
