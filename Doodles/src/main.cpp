#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
#ifdef TARGET_OPENGLES
    ofGLESWindowSettings settings;
    settings.glesVersion = 2;
    settings.width = 1280;
    settings.height = 720;
#else
    ofGLWindowSettings settings;
    settings.setGLVersion(1,5);
    settings.setSize(1280, 720);
#endif
    settings.windowMode = OF_WINDOW;
    ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
