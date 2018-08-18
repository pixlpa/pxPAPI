#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    ofEnableNormalizedTexCoords();
    time = 0;
    w = ofGetWidth();
    h = ofGetHeight();
    
    fbo1.allocate(w, h);
    fbo2.allocate(w, h);

    filler.load("shaders/heightflow");
    boss.load("shaders/bossr");
    boss.begin();
    boss.setUniform2f("size", w, h);
    boss.setUniform1f("hscale",50);
    boss.setUniform1f("nscale",1);
    boss.setUniform1f("dthresh",0.65f);
    boss.setUniform1f("dfade",-0.04f);
    boss.setUniform1f("brightness",0.1f);
    boss.setUniform3f("lightpos",0,0,2);
    boss.setUniform2f("offset",4,4);
    boss.end();
    
    filler.begin();
    filler.setUniform2f("size", w, h);
    filler.setUniform1f("power",1.1f);
    filler.setUniform1f( "offset",1.5f);
    filler.setUniform1f( "bright",1.0058f);
    filler.setUniform1f( "dark",0.0045f);
    filler.setUniform1f("contrast",1.006f);
    filler.setUniform1f("warp",5.0f);
    filler.setUniform2f("shift",0.0f,-1.0f);
    filler.setUniform1f("mixin",0.01f);
    filler.setUniform1f("aspect",w/h);
    filler.setUniform1f("time",time);
    filler.end();
    
    fbo1.begin();
    ofClear(255,0,0,255);
    fbo1.end();
    fbo2.begin();
    ofClear(0,0,0,255);
    ofSetColor(10,10,10);
    ofDrawCircle(w,h,100);
    fbo2.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    time += 0.03;
    w = ofGetWidth();
    h = ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofBackground(200);
    
    fbo1.begin();
    filler.begin();
    filler.setUniform2f("size", w, h);
    filler.setUniform1f("time",time);
    fbo2.draw(0,0);
    filler.end();
    fbo1.end();
    
    fbo2.begin();
    boss.begin();
    boss.setUniform2f("size", w, h);
    fbo1.draw(0,0);
    boss.end();
    //ofDrawCircle(w,h,100);
    fbo2.end();
    fbo2.draw(0,0,w,h);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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

