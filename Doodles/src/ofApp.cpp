#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    //ofEnableNormalizedTexCoords();
    time = 0;
    w = ofGetWidth();
    h = ofGetHeight();
    
    fbo1.allocate(1280,720);
    fbo2.allocate(1280,720);
    noisefbo.allocate(1280,720);

    filler.load("shaders/heightflow");
    boss.load("shaders/bossr");
    noisy.load("shaders/noisegen");
    boss.begin();
    boss.setUniform2f("size", 1280, 720);
    boss.setUniform1f("hscale",30);
    boss.setUniform1f("nscale",1);
    boss.setUniform1f("dthresh",0.5f);
    boss.setUniform1f("dfade",0.05f);
    boss.setUniform1f("brightness",0.78f);
    boss.setUniform3f("lightpos",0.665,0.15,3);
    boss.setUniform2f("offset",1,1);
    boss.end();
    
    filler.begin();
    filler.setUniform2f("size", 1280, 720);
    filler.setUniform1f("power",1.7f);
    filler.setUniform1f( "offset",2);
    filler.setUniform1f( "bright",1.0043f);
    filler.setUniform1f( "dark",0.004f);
    filler.setUniform1f("contrast",1.007f);
    filler.setUniform1f("warp",5.0f);
    filler.setUniform2f("shift",1.2f,0);
    filler.setUniform1f("mixin",0.0098f);
    filler.setUniform1f("aspect",w/h);
    filler.setUniform1f("time",time);
    filler.end();
    
    fbo1.begin();
    ofClear(255,0,0,255);
    fbo1.end();
    fbo2.begin();
    ofClear(0,0,0,255);
    ofSetColor(20,80,200);
    ofDrawCircle(1024,600,100);
    fbo2.end();
    
    noisefbo.begin();
    noisy.begin();
    noisy.setUniform2f("size",1280,720);
    fbo1.draw(0,0);
    noisy.end();
    noisefbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    time += 0.03;
    w = ofGetWidth();
    h = ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255,254,253);
    ofBackground(200);
    
    fbo1.begin();
    filler.begin();
    //filler.setUniform2f("size", w, h);
    filler.setUniform1f("time",time);
    filler.setUniformTexture("tex1",noisefbo.getTexture(),1);
    fbo2.draw(0,0);
    filler.end();
    fbo1.end();
    
    fbo2.begin();
    boss.begin();
    //boss.setUniform2f("size", w, h);
    fbo1.draw(0,0);
    boss.end();
    //ofDrawCircle(640,360,100);
    fbo2.end();
    fbo2.draw(0,0);
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

