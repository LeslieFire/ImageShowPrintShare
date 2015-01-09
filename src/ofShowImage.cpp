#include "ofShowImage.h"

ofEvent<ofShowImageEvent> ofShowImageEvent::events;

ofShowImage::ofShowImage(){
	_imageIndex = -1;
}




ofShowImage::~ofShowImage(){
	waitForThread(true);
    stopThread();
}

