#include "testApp.h"


int tritimer;
int tritimer2;
int w;
int h;
ofMesh trik2;

//--------------------------------------------------------------
void testApp::setup(){

	w = ofGetWidth();
	h = ofGetHeight();
    fbfbo.allocate(w,h);
    fbfbo.getTextureReference().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
    fbo.allocate(w,h);
	fbo.getTextureReference().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);    
    //settings
    ofEnableNormalizedTexCoords();
    ofSetMinMagFilters(GL_NEAREST, GL_NEAREST); 
    
    // Clear the FBO's
    // otherwise it will bring some junk with it from the memory
    fbfbo.begin();
    ofClear(0,0,0,255);
    fbfbo.end();
    
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();

    tritimer = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    tritimer++;
    tritimer2++;
    w = ofGetWidth();
    h = ofGetHeight();
    if(tritimer2>45){
        //re-generate the feedback triangles
        float xpt, ypt,xoff,yoff,xtoff,ytoff;
        trik2.clear();
        for(int b = 0;b<5;b++){
            xoff = ofRandomf()*0.1;
            yoff = ofRandomf()*0.1;
            xtoff = ofRandomf()*0.5;
            ytoff = ofRandomf()*0.5;
            for(int i=0;i<3;i++){
                xpt = ofRandomuf()+xtoff;
                ypt = ofRandomuf()+ytoff;
                trik2.addVertex(ofVec3f((xpt+xoff)*w,(ypt+yoff)*h,0));
                trik2.addTexCoord(ofVec2f(xpt,ypt));
                trik2.addColor(ofFloatColor(1,1,1));
            }
        }
        tritimer2=0;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    fbo.begin();
        ofSetTextureWrap(GL_REPEAT,GL_REPEAT);
        fbfbo.draw(0,2);
    //cam.draw(0,0);
        fbfbo.getTextureReference().bind();
        trik2.draw();
        fbfbo.getTextureReference().unbind();

        ofSetColor(255,255,255);
    if(tritimer>30){
        float xpt, ypt,xtoff,ytoff;
        //draw gradient splashes
        ofMesh trik;
        for(int b = 0;b<5;b++){
            xtoff = ofRandomf()*0.5;
            ytoff = ofRandomf()*0.5;
            for(int i=0;i<3;i++){
                xpt = ofRandomuf()*2+xtoff;
                ypt = ofRandomuf()*2+ytoff;
                trik.addVertex(ofVec3f(xpt*w,ypt*h,0));
                trik.addColor(ofFloatColor(float(ofRandomuf()>0.5)*0.4+0.5,float(ofRandomuf()>0.5)*0.4+0.5,float(ofRandomuf()>0.5)*0.4+0.5));
            }
        }
        trik.draw();
        tritimer = 0;
    }
    fbo.end();
    fbfbo.begin();
    fbo.draw(0,0);
    fbfbo.end();
    fbo.draw(0,0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int _w, int _h){
	w = _w;
	h = _h;
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}