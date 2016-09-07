#include "BaseView.h"

BaseView::BaseView() {
    mapImg.load("assets/WorldMapBlack.jpg");
}

void BaseView::draw() {
    ofSetColor(255);
    mapImg.draw(0,0);
    
    ofSetColor(0,180);
    ofDrawRectangle(0,ofGetHeight()-160,ofGetWidth(),160);
    
    ofSetColor(0);
    ofDrawLine(0,ofGetHeight()-160,ofGetWidth(),ofGetHeight()-160);
}