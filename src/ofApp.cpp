#include "ofApp.h"

/*
//TODO: 
 --- process dates in tweets
 + add displayAsTimeLine function 
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
    timelines[0]->getTweetsFromTwitter("congressedits", 40);
}

void ofApp::update(){}

void ofApp::draw(){
    ofBackground(0);
    for(auto timeline : timelines) {
        for(auto tweet : timeline->tweets) {
            tweet->draw();
        }
    }
}

void ofApp::keyPressed(int key){}
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
