#include "ofApp.h"

/*
//TODO: 
 + add map to App
 + add mapPosition to tweets / add displayOnMap function
 
 + select & load multiple bots
 + add displayAsTimeLine function
 
 + add playhead to App
 + add sound + mixer interaction
 + add animation
 
*/

void ofApp::setup(){
    timelines.push_back(new TimeLine());
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
    for(auto timeline : timelines) {
        for(auto tweet : timeline->tweets) {
            tweet->draw();
        }
    }
    
    ofDrawCircle(ofGetFrameNum()%ofGetWidth(),100,50);
}

void ofApp::keyPressed(int key){
    if(!timelines[0]->threadedTwitterQuery.isThreadRunning()) {
        timelines[0]->getTweetsFromTwitter("congressedits", 40);
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
