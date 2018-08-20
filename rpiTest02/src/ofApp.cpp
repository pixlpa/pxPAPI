#include "ofApp.h"


int tritimer;
int tritimerlimit;
int tritimer2;
int tritimer2limit;
int w;
int h;
ofMesh trik2;

//--------------------------------------------------------------
void testApp::setup(){

	w = ofGetWidth();
	h = ofGetHeight();
    fbfbo.allocate(w,h);
    fbfbo.getTexture().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
    fbo.allocate(w,h);
	fbo.getTexture().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
    
    // Clear the FBO's
    // otherwise it will bring some junk with it from the memory
    fbfbo.begin();
    ofClear(0,0,0,255);
    fbfbo.end();
    
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();

    tritimer = 0;
    tritimer2 = 0;
    tritimerlimit=160;
    tritimer2limit=395;
    
}

//--------------------------------------------------------------
void testApp::update(){
    tritimer++;
    tritimer2++;
    w = ofGetWidth();
    h = ofGetHeight();
}

//--------------------------------------------------------------
void testApp::draw(){
    fbo.begin();
        fbfbo.draw(-1,0);
    //cam.draw(0,0);
        fbfbo.getTexture().bind();
        trik2.draw();
        fbfbo.getTexture().unbind();
        
        ofSetColor(255,255,255);
    if(tritimer>tritimerlimit){
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
                trik.addColor(ofFloatColor(float(ofRandomuf()>0.5)*0.6+0.4,float(ofRandomuf()>0.5)*0.5+0.5,float(ofRandomuf()>0.5)*0.7+0.3));
            }
        }
        trik.draw();
        tritimer = 0;
        tritimerlimit= ofRandom(20,200);
    }
    
    if(tritimer2>45){
        //re-generate the feedback triangles
        float xpt, ypt,xoff,yoff,xtoff,ytoff;
        trik2.clear();
        //ofEnableNormalizedTexCoords();
        for(int b = 0;b<5;b++){
            xoff = ofRandomf()*0.1;
            yoff = ofRandomf()*0.1;
            xtoff = ofRandomf()*0.5;
            ytoff = ofRandomf()*0.5;
            for(int i=0;i<3;i++){
                xpt = ofRandomuf()+xtoff;
                ypt = ofRandomuf()+ytoff;
                trik2.addVertex(ofVec3f((xpt+xoff)*w,(ypt+yoff)*h,0));
                trik2.addTexCoord(ofVec2f(xpt*w,ypt*h));
                trik2.addColor(ofFloatColor(1,1,1));
            }
        }
        tritimer2=0;
        tritimer2limit= ofRandom(20,200);
        //ofDisableNormalizedTexCoords();
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
