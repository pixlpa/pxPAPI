#pragma once

#include "ofMain.h"
class pxBrush{
public:
    ofVec3f pos;
    ofVec3f ppos;
    ofColor color;
    ofColor tcolor;
    float size;
    float tsize;
    int timer;
    int timerthresh;
    float gravity;
    
    pxBrush(){
        init();
    }
    
    pxBrush(ofVec3f _pos){
        init();
        pos = _pos;
        ppos = _pos;
    }
    void init(){
        pos = ofVec3f(0,0,0);           //Current Position
        ppos = ofVec3f(0,0,0);          //Previous Position
        gravity = 0.00;
        timer = 0;
        timerthresh = 50;
        color = ofColor(0,0,0);
        size = 10;
    }
    void update(){
        solve();
        doTimer();
        doColor();
    }
    void solve(){
        ofVec3f savepos = pos;
        pos.y += gravity;
        pos = pos*2-ppos;
        if (pos.x<20) pos.x = 20;
        else if (pos.x>(ofGetWidth()-20)) pos.x = ofGetWidth()-20;
        if (pos.y<20) pos.y = 20;
        else if (pos.y>(ofGetHeight()-50)) pos.y = ofGetHeight()-50;
        ppos = savepos;
    }
    void shift(ofVec3f _shift){
        pos += _shift;
    }
    void doTimer(){
        timer++;
        if(timer>timerthresh){
            tcolor = ofColor(float(ofRandomuf()>0.5)*255,float(ofRandomuf()>0.5)*255,float(ofRandomuf()>0.5)*255);
            tsize = ofRandom(3,100);
            timer = 0;
            timerthresh = ofRandom(10, 200);
        }
    }
    void doColor(){
        color.lerp(tcolor,0.05);
        size =ofLerp(size,tsize,0.08);
        
    }
};

class pxConstraint{
public:
    pxConstraint(pxBrush* _pta,pxBrush* _ptb,float _distance,float _strength){
        pta = _pta;
        ptb = _ptb;
        rest = _distance;
        strength = _strength;
    }
    
    void solve(){
        float rstsq = rest*rest;
        ofVec3f dab = ptb->pos-pta->pos;
        float delta = dab.length();
        delta = (rest-delta)/delta;
        //dab *= rstsq/(dab*dab+rstsq)-0.5;
        pta->shift(-dab*delta*strength);
        ptb->shift(dab*delta*strength);
    }
    float strength;
    float rest;
    pxBrush* pta;
    pxBrush* ptb;
};


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void doConstraint(pxBrush* pta,pxBrush* ptb,float restlength,float strength);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    pxConstraint** cc;
    pxBrush** bb;
    ofFbo fbb;
    ofFbo ffb;
};
