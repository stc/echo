#include "BaseView.h"

BaseView::BaseView() {
    mapImg.load("assets/WorldMap.png");
}

void BaseView::draw() {
    ofSetColor(255,50);
    mapImg.draw(0,0);
    
    ofSetColor(0,180);
    ofDrawRectangle(0,ofGetHeight()-150,ofGetWidth(),150);
}