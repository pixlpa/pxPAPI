#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
#ifdef TARGET_OPENGLES
    ofGLESWindowSettings settings;
    settings.glesVersion = 2;
#else
    ofGLWindowSettings settings;
    settings.setGLVersion(1,5);
#endif
    settings.windowMode = OF_WINDOW;
    settings.setSize(1280, 720);
    ofCreateWindow(settings);
	ofRunApp(new ofApp());

}
