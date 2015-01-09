#include "ofApp.h"

void ofApp::setupButtons(){
	_loader.loadImageFromDirectory(assets, "Assets");

	_buttons.SetButton(PREVIOUS, &assets.at(0));
	_buttons.SetButton(PREVIOUS, &assets.at(1), 1);

	_buttons.SetButton(NEXT, &assets.at(2));
	_buttons.SetButton(NEXT, &assets.at(3), 1);

	_buttons.SetButton(PRINT, &assets.at(4));
	_buttons.SetButton(PRINT, &assets.at(5), 1);

	_buttons.SetButton(SHARE, &assets.at(6));
	_buttons.SetButton(SHARE, &assets.at(7), 1);

	_buttons.setup("buttons");
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofLogToFile("runner.log");

	_imageName= "";
	_url = "http://115.159.0.222/imageShow.php?name=";
	_uploadURL = "http://115.159.0.222/imageShowUpdate.php";

	_bPrinted = false;
	_bShared = false;
	_bPressed= false;
	_bFullscreen = true;
	ofSetFullscreen(_bFullscreen);

	_QR = NULL;

	_bg.loadImage("beijing.png");
	_logo.loadImage("logo.png");

	setupButtons();
	
	_currentImage = new ofImage();
	_preImage = new ofImage();
	_postImage = new ofImage();

	
	if (xml.loadFile("urlXml.xml")){
	}else {
		ofLogNotice() << "Fail to load url.xml. Produce a new url.xml file" ;
		xml.setValue("URL", _url);

		xml.saveFile("urlXml.xml");
	}


	_fileNum = _directory.listDir("images");
	if (_fileNum > 0){
		_imageIndex = _fileNum - 1;
		updateUrl();

		loader.loadFromDisk(*_currentImage, _directory.getPath(_imageIndex));
		if (_imageIndex - 1 >= 0){
			loader.loadFromDisk(*_preImage, _directory.getPath(_imageIndex-1));
		}
	}	

}

void ofApp::updateUrl(){
	
	_imageName = _directory.getFile(_imageIndex).getFileName();
	xml.setValue("URL", _url + _imageName);

	xml.saveFile("urlXml.xml");

	ofLogNotice() << "Update Url : " + _url + _imageName;
	if(_QR != NULL){
		_QR->Stop();
		delete _QR;
		_QR = NULL;
	}
	if (_QR == NULL){
		_QR = new ofxFlash();
		_QR->setup("as-QR-code.swf", 210,210);
		_QR->Play(); 
	}
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofEnableAlphaBlending();
	_bg.draw(0, 0);

	ofSetRectMode(OF_RECTMODE_CENTER);
	if (_imageIndex != -1 && _currentImage->isAllocated()){
			float pro =  (float)_currentImage->getWidth()*(768.0f / (float)_currentImage->getHeight());
			_currentImage->draw(683, 384, pro, 768);
			
	}
	ofSetRectMode(OF_RECTMODE_CORNER);

	_buttons.draw();

	ofSetRectMode(OF_RECTMODE_CENTER);
	if (_bShared){
		if (_QR != NULL){
			_QR->draw(1296,650, 210, 210);
		}
	}
	ofSetRectMode(OF_RECTMODE_CORNER);

	//_logo.draw(0, 346, 832, 426);
	ofDisableAlphaBlending();

	gui.draw();
}

void ofApp::exit(){

	if (_QR != NULL){
		_QR->Stop();
		delete _QR;
		_QR = NULL;
	}
	if (_currentImage != NULL){
		delete _currentImage;
	}
	if (_preImage != NULL){
		delete _preImage;
	}
	if (_postImage != NULL){
		delete _postImage;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'q' || key == OF_KEY_LEFT){
		SetToPreviousImage();
	}else if (key == 'e' || key == OF_KEY_RIGHT){
		SetToNextImage();
	}else if (key == 'p'){
		PrintCurrentPicture();
	}else if (key == 's'){
		uploadImage();
	}else if (key == 'f'){
		_bFullscreen = !_bFullscreen;
		ofSetFullscreen(_bFullscreen);
	}
}

void ofApp::SetToPreviousImage(){

	if (_imageIndex - 1 >= 0){
		_imageIndex--;

		ofImage*	temp = _postImage;
		_postImage = _currentImage;
		_currentImage = _preImage;
		_preImage = temp;

		updateUrl();
		if (_imageIndex > 0){
			_preImage->loadImage(_directory.getPath(_imageIndex-1));
			//loader.loadFromDisk(*_preImage, _directory.getPath(_imageIndex-1));
		}

		_bPrinted = false;
		_bShared = false;
	}
}
void ofApp::SetToNextImage(){

	if (_imageIndex < _fileNum - 1){
		_imageIndex++;

		ofImage*	temp = _preImage;
		_preImage = _currentImage;
		_currentImage = _postImage;
		_postImage = temp;

		updateUrl();
		if (_imageIndex < _fileNum - 1){
			_postImage->loadImage(_directory.getPath(_imageIndex+1));
			//loader.loadFromDisk(*_postImage, _directory.getPath(_imageIndex+1));
		}

		_bPrinted = false;
		_bShared = false;
	}
}

void ofApp::PrintCurrentPicture(){

	if (_imageIndex != -1 && !_bPrinted){
		_bPrinted = true;

		ofImage _ToPrint;

		/*ofFbo m_Fbo;
		m_Fbo.allocate(_currentImage->getWidth(), _currentImage->getHeight(), GL_RGBA);
		m_Fbo.begin();
			ofClear(255, 255, 255, 0);
			ofEnableAlphaBlending();

			_currentImage->draw(0, 0);
			_logo.draw(0, _currentImage->getHeight() - _logo.getHeight(),
						_logo.getWidth(), _logo.getHeight());

			ofDisableAlphaBlending();
		m_Fbo.end();
		
		ofPixels temp;

		m_Fbo.readToPixels(temp);
		_ToPrint.setFromPixels(temp);
		_ToPrint.setImageType(OF_IMAGE_COLOR);
		_ToPrint.saveImage("print/" + _imageName);*/

		// math stuff
		float height = _currentImage->getHeight();
		float width =  (float)_currentImage->getHeight()*(3403.0f / 2456.0f);
		float var = _currentImage->getWidth() - width;
		float x = 0;
		float y = 0;
		if (var >= 0){
			x = var / 2.0f;
		}else {
			width = _currentImage->getWidth();
		}

		_ToPrint.cropFrom(*_currentImage, x, y, width, height);
		_ToPrint.saveImage("print/" + _imageName);
		PrintPicture((LPCSTR)ofToDataPath("print/" + _imageName).c_str());
	}
}

void ofApp::uploadImage(){
	
	if (_imageIndex != -1 && !_bShared ){
		_currentImage->resize(1152, 768);
		_currentImage->saveImage("uploads/"+ _imageName);

		ofxCurlForm* httpForm = _curl.createForm(_uploadURL);
		httpForm->addInput("file", ofToDataPath("uploads/"+_imageName));
		ofxCurlForm temp = httpForm->post();

		ofLogNotice() << "Upload image : " + _uploadURL +" + "+ _imageName;

		ofLogNotice() << temp.getPostResponseAsString();

		_bShared = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (!_bPressed){
		if (isInRange(x, y, _buttons.getButtonArea(PREVIOUS))){
			_bPressed = true;
			_buttons.changeButtonState(PREVIOUS);
		} else
		if (isInRange(x, y, _buttons.getButtonArea(NEXT))){
			_bPressed = true;
			_buttons.changeButtonState(NEXT);
		} else
		if (isInRange(x, y, _buttons.getButtonArea(PRINT))){
			_bPressed = true;
			_buttons.changeButtonState(PRINT);
		} else
		if (isInRange(x, y, _buttons.getButtonArea(SHARE))){
			_bPressed = true;
			_buttons.changeButtonState(SHARE);
		}	
	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (_bPressed){
		if (isInRange(x, y, _buttons.getButtonArea(PREVIOUS))){
			_bPressed = false;
			_buttons.changeButtonState(PREVIOUS);
			SetToPreviousImage();
		} else
		if (isInRange(x, y, _buttons.getButtonArea(NEXT))){
			_bPressed = false;
			_buttons.changeButtonState(NEXT);
			SetToNextImage();
		} else
		if (isInRange(x, y, _buttons.getButtonArea(PRINT))){
			_bPressed = false;
			_buttons.changeButtonState(PRINT);
			PrintCurrentPicture();
		} else
		if (isInRange(x, y, _buttons.getButtonArea(SHARE))){
			_bPressed = false;
			_buttons.changeButtonState(SHARE);
			uploadImage();
		}	
	}
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
bool ofApp::isInRange(int x, int y, ofRectangle & t){
	if ( ofInRange(x, t.getMinX(), t.getMaxX())
		&& ofInRange(y, t.getMinY(), t.getMaxY())){
		return true;
	}
	return false;
}
