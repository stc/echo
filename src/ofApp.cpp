#include "ofApp.h"

void ofApp::setup(){
    for(int i=0; i<5; i++) timelines.push_back(new TimeLine());
    ofVec2f mapPos = ofVec2f(332,190); // washington
    timelines[0]->getTweetsFromTwitter("congressedits", 10, mapPos);
    mapPos = ofVec2f(649,133);
    timelines[1]->getTweetsFromTwitter("berlinEDUedits", 10, mapPos);
    mapPos = ofVec2f(581,132);
    timelines[2]->getTweetsFromTwitter("IrishGovEdits", 10, mapPos);
    mapPos = ofVec2f(860,205);
    timelines[3]->getTweetsFromTwitter("PakistanEdits", 10, mapPos);
    mapPos = ofVec2f(1124,498);
    timelines[4]->getTweetsFromTwitter("AussieParlEdits", 10, mapPos);
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
    //cout << mouseX << " " << mouseY << endl;
}

void ofApp::draw(){
    ofBackground(0);
    baseView.draw();
    
    for(int i=0; i< timelines.size(); i++) {
        if(timelines[i]->tweets.size()>1) {
            bool over = ofVec2f(mouseX,mouseY).distance(timelines[i]->tweets[0]->mMapPos) < 50 ? true : false;
            timelines[i]->tweets[0]->drawMapView(over);
            timelines[i]->drawTimeLine(ofVec2f(20,ofGetHeight()-20 - (i*15)));
        }
    }
}

void ofApp::keyPressed(int key){
    /*
     if(!timelines[0]->threadedTwitterQuery.isThreadRunning()) {
        ofVec2f mapPos = ofVec2f(10,10);
        timelines[0]->getTweetsFromTwitter("congressedits", 40, mapPos);
    }
     */    
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
