#include "ofApp.h"

#define BRUSHES 6
#define CONSTRAINT 6
int timer;
int timerthresh;

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
    ofDisableArbTex();
    fbb.allocate(w,h);
    fbb.getTexture().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
    ffb.allocate(w,h);
	ffb.getTexture().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
    //settings
    //ofSetMinMagFilters(GL_NEAREST, GL_NEAREST);
    
    // Clear the FBO's
    // otherwise it will bring some junk with it from the memory
    fbb.begin();
    ofClear(0,0,0,255);
    fbb.end();
    
    ffb.begin();
    ofClear(0,0,0,255);
    ffb.end();
    
    //make the shader
    boss.load("shaders/bossr");
    boss.begin();
    boss.begin();
    boss.setUniform2f("size", w, h);
    boss.setUniform1f("hscale",5);
    boss.setUniform1f("nscale",1);
    boss.setUniform1f("dthresh",0.6f);
    boss.setUniform1f("dfade",0.15f);
    boss.setUniform1f("brightness",1.25f);
    boss.setUniform3f("lightpos",0.8,0.5,3);
    boss.setUniform2f("offset",1,1);
    boss.end();
    tritimer = 0;
    tritimer2 = 0;
    tritimerlimit=30;
    tritimer2limit=45;

    
    bb = new pxBrush*[BRUSHES];
    for (int i = 0;i<BRUSHES;i++){
        bb[i] = new pxBrush(ofVec3f(ofRandomWidth(),ofRandomHeight(),0));
    }
    cc = new pxConstraint*[CONSTRAINT];
    cc[0] = new pxConstraint(bb[0],bb[1],300,0.01);
        cc[1] = new pxConstraint(bb[1],bb[2],200,0.01);
        cc[2] = new pxConstraint(bb[2],bb[3],250,0.01);
        cc[3] = new pxConstraint(bb[3],bb[4],200,0.01);
        cc[4] = new pxConstraint(bb[4],bb[5],200,0.01);
        cc[5] = new pxConstraint(bb[5],bb[0],200,0.01);
    timer = 0;
    timerthresh = 100;

}

//--------------------------------------------------------------
void testApp::update(){
    timer++;
    if(timer>timerthresh){
        bb[int(ofRandom(BRUSHES))]->shift(ofVec3f(ofRandom(-20,20),ofRandom(-20,20),0));
        timer = 0;
        timerthresh = ofRandom(5,100);
    }

    for (int i=0;i<BRUSHES;i++){
        bb[i]->update();
    }
    for (int i=0;i<CONSTRAINT;i++){
        cc[i]->solve();
    }
    tritimer++;
    tritimer2++;
    w = ofGetWidth();
    h = ofGetHeight();
}

//--------------------------------------------------------------
void testApp::draw(){
    ffb.begin();
    //ofSetTextureWrap(GL_REPEAT,GL_REPEAT);
    ofSetColor(255,255,255);
    fbb.draw(-1,0);
    //cam.draw(0,0);
    fbb.getTexture().bind();
    trik2.draw();
    fbb.getTexture().unbind();
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
                trik2.addTexCoord(ofVec2f(xpt,ypt));
                trik2.addColor(ofFloatColor(1,1,1));
            }
        }
        tritimer2=0;
        tritimer2limit= ofRandom(20,200);
        //ofDisableNormalizedTexCoords();
    }
    float xp,yp;
    ofDrawCircle(xp,yp,10);
    for (int i=0;i<BRUSHES;i++){
        ofSetColor(bb[i]->color);
        xp= bb[i]->pos.x;
        yp= bb[i]->pos.y;
        ofDrawCircle(xp,yp,bb[i]->size);
    }
    ofSetColor(255,255,255);
    ffb.end();
    fbb.begin();
    boss.begin();
    ffb.draw(0,0);
    boss.end();
    fbb.end();
    ffb.draw(0,0);
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
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
