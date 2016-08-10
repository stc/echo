#include "ofApp.h"

void ofApp::setup(){
    timelines.push_back(new TimeLine());
    ofVec2f mapPos = ofVec2f(10,10);
    timelines[0]->getTweetsFromTwitter("congressedits", 40, mapPos);
}

void ofApp::update(){
    for(auto timeline : timelines) {
        ofFile mFile = ofFile(ofToDataPath(timeline->mUserName) + ".json");
        if(mFile.exists() && timeline->loading && !timeline->threadedTwitterQuery.isThreadRunning()) {
            if(!timeline->parsed) {
                timeline->parseResults();
            }else {
                timeline->loadTweets();
            }
        }
    }
}

void ofApp::draw(){
    ofBackground(0);
    baseView.draw();
    
    for(auto timeline : timelines) {
        for(auto tweet : timeline->tweets) {
            tweet->drawRawView();
        }
    }
    
    //ofDrawCircle(ofGetFrameNum()%ofGetWidth(),100,50);
}

void ofApp::keyPressed(int key){
    if(!timelines[0]->threadedTwitterQuery.isThreadRunning()) {
        ofVec2f mapPos = ofVec2f(10,10);
        timelines[0]->getTweetsFromTwitter("congressedits", 40, mapPos);
    }
}

void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
