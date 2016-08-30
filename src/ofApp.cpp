#include "ofApp.h"

void ofApp::setup(){
    if(checkInternetConnection()) {
        mOnline = true;
    } else {
        mOnline = false;
    }
    
    mNetworkError.load("assets/NetworkError.png");
    
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    cYear  = now->tm_year + 1900;
    cMonth = now->tm_mon + 1;
    cDay   =  now->tm_mday;
    
    for(int i=0; i<5; i++) {
        timelines.push_back(new TimeLine(i, cYear, cMonth, cDay));
    }
    ofVec2f mapPos = ofVec2f(332,190); // washington
    timelines[0]->getTweetsFromTwitter("congressedits", 200, mapPos, "US");
    mapPos = ofVec2f(649,133);
    timelines[1]->getTweetsFromTwitter("berlinEDUedits", 200, mapPos, "DE");
    mapPos = ofVec2f(581,132);
    timelines[2]->getTweetsFromTwitter("IrishGovEdits", 200, mapPos, "IR");
    mapPos = ofVec2f(860,205);
    timelines[3]->getTweetsFromTwitter("PakistanEdits", 200, mapPos, "PK");
    mapPos = ofVec2f(1124,498);
    timelines[4]->getTweetsFromTwitter("AussieParlEdits", 200, mapPos, "AUS");
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
    
    for(int i=0; i< timelines.size(); i++) {
        if(timelines[i]->tweets.size()>1) {
            timelines[i]->drawTimeLine(ofVec2f(20,ofGetHeight()-20 - (i*15)));
            int cTweet = getSequence(timelines[i]);
            //for(int j=0; j< timelines[i]->tweets.size(); j++) {
            if(cTweet>0 && cTweet < timelines[i]->tweets.size()) timelines[i]->tweets[cTweet]->drawMapView();
            //}
        }
    }
    
    if(!mOnline) {
        ofSetColor(255);
        mNetworkError.draw(ofGetWidth()/2-mNetworkError.getWidth()/2, ofGetHeight()/2-mNetworkError.getHeight()/2);
    }
    
    ofSetColor(255);
    ofDrawBitmapString(ofToString(int(ofGetFrameRate())), 20,20);
}

bool ofApp::checkInternetConnection() {
    int status = system("ping -c 2 google.com");
    int ping_ret;
    if (-1 != status) {
        ping_ret = WEXITSTATUS(status);
        if(ping_ret==0)
            return true;
        else
            return false;
    }
}

int ofApp::getSequence(TimeLine * t) {
    if(playHead > t->tlMax) playHead = t->tlMin;
    playHead+=0.05;
    
    if(t->tlIndex == 0) {
        ofSetColor(255);
        ofDrawLine(playHead,ofGetHeight()-100,playHead,ofGetHeight());
    }
    
    for(auto tweet : t->tweets) {
        if(tweet->mTimeLinePos.x > 0) {
            if(ofVec2f(playHead,t->mP.y).distance(tweet->mTimeLinePos) <2) {
                tweet->alpha = 255;
                tweet->textAlpha = 255;
                return tweet->mIndex;
            }
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
