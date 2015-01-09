#pragma once

#include "ofMain.h"


// this is not a very exciting example yet
// but ofThread provides the basis for ofNetwork and other
// operations that require threading.
//
// please be careful - threading problems are notoriously hard
// to debug and working with threads can be quite difficult

//static ofEvent <ofxTimeOut> events;
class ofShowImageEvent: public ofEventArgs
{
public:
	
	bool imageIndex(){return _imageIndex;}
	void setImageIndex(int index){_imageIndex = index;}
	
	ofShowImageEvent():_imageIndex(-1){}

	static ofEvent <ofShowImageEvent> events;
private:
	bool _imageIndex;
};

class ofShowImage : public ofThread{

	public:
		ofShowImage();
		~ofShowImage();

		void start(){
            startThread(true, false);   // blocking, verbose
        }
        void stop(){
			waitForThread(true);
            stopThread();
        }
protected:

		//--------------------------
		void threadedFunction(){

			while( isThreadRunning() != 0 ){
				ofSleepMillis(1 * 1000);
				if( lock() ){
					int num = _directory.listDir("images");
					if (_fileNum != num){
						
						_fileNum = num;
						_imageIndex = _fileNum - 1;

						cout << "file number : " << _fileNum <<endl;

						ofShowImageEvent event;
						event.setImageIndex(_imageIndex);

						ofNotifyEvent(ofShowImageEvent::events, event);
					}
					unlock();
				}
			}
		}

	private:
		ofDirectory	_directory;

		int			_fileNum;
		int			_imageIndex;
		
};

