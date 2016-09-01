#include "BaseView.h"

BaseView::BaseView() {
    mapImg.load("assets/WorldMap.jpg");
}

void BaseView::draw() {
    ofSetColor(255);
    mapImg.draw(0,0);
    
    ofSetColor(0,180);
    ofDrawRectangle(0,ofGetHeight()-150,ofGetWidth(),150);
    
    ofSetColor(150);
    ofDrawLine(0,ofGetHeight()-150,ofGetWidth(),ofGetHeight()-150);
}