#include "ofApp.h"

/*
//TODO: 
 --- process dates in tweets
 --- threaded loader
 + add displayAsTimeLine function 
 + async JSON reading
 + add map to App
 + add mapPosition to tweets / add displayOnMap function
 + add playhead to App
 + add sound + mixer interaction
 + add fonts
 + add animation
*/

void ofApp::setup(){
    string name = "_stc";
    timelines.push_back(new TimeLine());
}

void ofApp::update(){
    for(auto timeline : timelines) {
        if(timeline->loading && !timeline->threadedTwitterQuery.isThreadRunning()) {
            timeline->parseResults();
            timeline->loading = false;
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
    
    ofDrawCircle(ofGetFrameNum(),100,50);
}

void ofApp::keyPressed(int key){
    timelines[0]->getTweetsFromTwitter("congressedits", 40);
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
