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
        cTweets.push_back(-1);
        timelines.push_back(new TimeLine(i, cYear, cMonth, cDay));
        tunerAverage.push_back(0);
    }
    

    ofVec2f mapPos = ofVec2f(332,190);
    timelines[0]->getTweetsFromTwitter("congressedits", 200, mapPos, "US");
    mapPos = ofVec2f(649,133);
    timelines[1]->getTweetsFromTwitter("berlinEDUedits", 200, mapPos, "DE");
    mapPos = ofVec2f(581,132);
    timelines[2]->getTweetsFromTwitter("IrishGovEdits", 200, mapPos, "IR");
    mapPos = ofVec2f(860,205);
    timelines[3]->getTweetsFromTwitter("PakistanEdits", 200, mapPos, "PK");
    mapPos = ofVec2f(1124,498);
    timelines[4]->getTweetsFromTwitter("AussieParlEdits", 200, mapPos, "AUS");
    
    ofBackground(0);
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
    #ifdef TARGET_LINUX_ARM
        //  read from file that is updated by python, reading RPI's GPIO values
        try {
            vector < string > linesRot;
            ofBuffer buffer = ofBufferFromFile(ofToDataPath("python/rot.txt"));
            for (auto line : buffer.getLines()){
                linesRot.push_back(line);
            }
            if(linesRot.size() > 1) {
                if(ofToInt(linesRot[1])!=pTunerVal) {
                    mTunerValue = ofToInt(linesRot[0]);
                    pTunerVal = ofToInt(linesRot[1]);
                    mCanMoveTuner = true;
                }
            }
        } catch(...) {
            // couldn't read from file
        }
    
        try {
            vector < string > linesSwitch;
            ofBuffer mbuffer = ofBufferFromFile(ofToDataPath("python/switch.txt"));
            for (auto line : mbuffer.getLines()){
                linesSwitch.push_back(line);
            }
            if(linesSwitch.size() > 0) {
                mTunerSwitch = ofToInt(linesSwitch[0]);
            }
        } catch(...) {
            // couldn't read from file
        }
    #endif
}

void ofApp::draw(){
    baseView.draw();
    for(int i=0; i< timelines.size(); i++) {
        if(timelines[i]->tweets.size()>0) {
            timelines[i]->tweets[0]->drawMapView();
            timelines[i]->drawTimeLine(ofVec2f(20,ofGetHeight()-20 - (i*15)));
            getSequence(timelines[i]);
            if(cTweets[i]>=0 && cTweets[i] <= timelines[i]->tweets.size()) timelines[i]->tweets[cTweets[i]]->drawMapView();
        }
    }
    
    if(!mOnline) {
        ofSetColor(255);
        mNetworkError.draw(ofGetWidth()/2-mNetworkError.getWidth()/2, ofGetHeight()/2-mNetworkError.getHeight()/2);
    }
    
    drawTuner();
    
    ofSetColor(255);
    ofDrawBitmapString("fps > " + ofToString(int(ofGetFrameRate())), 20,20);
    ofSetColor(255,0,0);
    ofDrawBitmapString("encoder > " + ofToString(mTunerValue), 20,40);
}

void ofApp::drawTuner() {
    if(mCanMoveTuner) {
        //  avoid extreme values from sensor
        if(mTunerValue > -2 && mTunerValue < 2) {
            // filter out short wrong values
            tunerAvgCounter++;
            if(tunerAvgCounter>4) tunerAvgCounter = 0;
            tunerAverage[tunerAvgCounter] = mTunerValue;
            float sum = 0;
            for(int i=0;i<tunerAverage.size(); i++) {
                sum += tunerAverage[i];
            }
            if((sum >= 5 || sum <= -5)) {
                mTunerTarget = mTunerPos + mTunerValue * -30;
            }
        }
        if(mTunerTarget<0) {
            mTunerTarget = ofGetWidth();
            mTunerPos = ofGetWidth();
        }else if(mTunerTarget > ofGetWidth()) {
            mTunerTarget = 0;
            mTunerPos = 0;
        }
        mCanMoveTuner = false;
    }
    
    float d = mTunerTarget - mTunerPos;
    mTunerPos += d * mTunerEasing;
    if(mTunerSwitch == 0) {
        ofSetColor(255,100);
    } else {
        ofSetColor(255,30);
    }
    ofSetLineWidth(10);
    ofDrawLine(mTunerPos,0,mTunerPos,ofGetHeight()-150);
    ofSetLineWidth(1);
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
    if(t->tlIndex == 0) {
        ofSetColor(255);
        ofDrawLine(playHead,ofGetHeight()-100,playHead,ofGetHeight());
        
        if(playHead >= t->tlMax) {
            playHead = t->tlMin;
            for(int i=0; i< timelines.size(); i++ ) cTweets[i] = -1;
            for(auto tweet : t->tweets) tweet->textAlpha = 0;
        }
        playHead+=1;
    }

    for(auto tweet : t->tweets) {
        if(tweet->mTimeLinePos.x > 0) {
            if(ofVec2f(playHead,t->mP.y).distance(tweet->mTimeLinePos) <2) {
                tweet->textAlpha = 255;
                cTweets[t->tlIndex] = tweet->mIndex;
                return tweet->mIndex;
            }
        }
    }
}

void ofApp::keyPressed(int key){
    // control tuner with keys (for testing)
    if(key == OF_KEY_RIGHT) {
        mTunerValue = -1;
        mCanMoveTuner = true;
    }
    if(key == OF_KEY_LEFT) {
        mTunerValue = 1;
        mCanMoveTuner = true;
    }
    if(key == '0') {
        mTunerSwitch = 0;
    }
    if(key == '1') {
        mTunerSwitch = 1;
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
