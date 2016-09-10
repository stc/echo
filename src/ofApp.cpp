#include "ofApp.h"

void ofApp::setup(){
    if(checkInternetConnection()) {
        mOnline = true;
    } else {
        mOnline = false;
    }
    
    mNetworkError.load("assets/NetworkError.png");
    
    int ticksPerBuffer = 8; // 8 * 64 = buffer len of 512
    ofSoundStreamSetup(2, 0, this, 44100, ofxPd::blockSize()*ticksPerBuffer, 3);

    soda.init();
    soda.clear();
    soda.createSampler("s","sounds/bleep.wav",10);
    soda.save();
    
    soda.pd.openPatch("lib/bg.pd");
    soda.pd.sendFloat("vol", mOutputVolume);
    
    mTextFont.setup("fonts/DINBold.ttf", 1.0, 1024, false, 8, 2.0f);
    
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    cYear  = now->tm_year + 1900;
    cMonth = now->tm_mon + 1;
    cDay   =  now->tm_mday;
    
    for(int i=0; i<7; i++) {
        cTweets.push_back(-1);
        timelines.push_back(new TimeLine(i, cYear, cMonth, cDay));
    }
    
    cNotes.push_back(0.5);
    cNotes.push_back(0.6);
    cNotes.push_back(0.75);
    cNotes.push_back(0.9);
    cNotes.push_back(1);
    cNotes.push_back(1.2);
    cNotes.push_back(1.5);
    
    for(int i=0; i<5; i++) tunerAverage.push_back(0);
    
    ofVec2f mapPos = ofVec2f(332,190);
    timelines[0]->getTweetsFromTwitter("congressedits", 200, mapPos, "US");
    mapPos = ofVec2f(649,133);
    timelines[1]->getTweetsFromTwitter("bundesedit", 200, mapPos, "DE");
    mapPos = ofVec2f(351,500);
    timelines[2]->getTweetsFromTwitter("BotDetectorCamb", 200, mapPos, "CL");
    mapPos = ofVec2f(616,140);
    timelines[3]->getTweetsFromTwitter("euroedit", 200, mapPos, "BE");
    mapPos = ofVec2f(705,182);
    timelines[4]->getTweetsFromTwitter("TBMMedits", 200, mapPos, "TUR");
    mapPos = ofVec2f(170,140);
    timelines[5]->getTweetsFromTwitter("gccaedits", 200, mapPos, "CAN");
    mapPos = ofVec2f(666,152);
    timelines[6]->getTweetsFromTwitter("_EchoBot", 200, mapPos, "H");
    
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
            timelines[i]->tweets[0]->drawOriginOnMap();
        }
    }
    for(int i=0; i< timelines.size(); i++) {
        if(timelines[i]->tweets.size()>0) {
            timelines[i]->drawTimeLine(ofVec2f(20,ofGetHeight()-20 - (i*15)), mTextFont);
            getSequence(timelines[i]);
            
            if(cTweets[i]>=0 && cTweets[i] <= timelines[i]->tweets.size()) {
                timelines[i]->tweets[cTweets[i]]->drawMapView(mTextFont);
            }
        }
    }
    
    if(!mOnline) {
        ofSetColor(255);
        mNetworkError.draw(ofGetWidth()/2-mNetworkError.getWidth()/2, ofGetHeight()/2-mNetworkError.getHeight()/2);
    }
    
    drawProcessTuner();
    
    if(mRotateAlpha<255) mRotateAlpha += 0.1;
    
    ofSetColor(255,mRotateAlpha * 0.5);
    if(mPlayMode) mTextFont.draw("ROTATE TO LISTEN TWEETS >>> ", 30, ofGetWidth()-400, ofGetHeight()/2-15 + sin(ofGetFrameNum()* 0.01) * 15);
    
    /*
    ofSetColor(255);
    ofDrawBitmapString("fps > " + ofToString(int(ofGetFrameRate())), 20,20);
    ofSetColor(255,0,0);
    ofDrawBitmapString("encoder > " + ofToString(mTunerValue), 20,40);
    */
}

void ofApp::drawProcessTuner() {
    if(mCanMoveTuner) {
        //  avoid extreme values from sensor
        if(mTunerValue > -2 && mTunerValue < 2) {
            // filter out short wrong values
            tunerAvgCounter++;
            if(tunerAvgCounter>4) tunerAvgCounter = 0;
            tunerAverage[tunerAvgCounter] = mTunerValue;
            mRotateAlpha = 0;
            float sum = 0;
            for(int i=0;i<tunerAverage.size(); i++) {
                sum += tunerAverage[i];
            }
            if((sum >= 5 || sum <= -5)) {
                mTunerTarget = mTunerPos + mTunerValue * -30;
            }
        }
        
        if(mTunerTarget<timelines[0]->tlMin) {
            mTunerTarget = timelines[0]->tlMax;
            mTunerPos = timelines[0]->tlMax;
        }else if(mTunerTarget > timelines[0]->tlMax) {
            mTunerTarget = timelines[0]->tlMin;
            mTunerPos = timelines[0]->tlMin;
        }
        mCanMoveTuner = false;
    }
    
    float d = mTunerTarget - mTunerPos;
    mTunerPos += d * mTunerEasing;
    
    // drawing
    if(mTunerSwitch == 0) {
        mPlayMode = true;
        ofSetColor(255,100 + mTriggerAlpha);
    } else {
        mPlayMode = false;
        ofSetColor(255,30);
    }
    
    if(mTriggerAlpha > 0) mTriggerAlpha -= 8;
    
    if(mPlayMode) {
        ofSetLineWidth(10);
        ofDrawLine(mTunerPos,ofGetHeight()-160,mTunerPos,ofGetHeight());
        ofSetLineWidth(1);
    } else {
        ofSetColor(0,100);
        ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
        float vol = ofMap(mTunerTarget, timelines[0]->tlMin, timelines[0]->tlMax, 0, 1);
        ofSetColor(255);
        mTextFont.draw("Volume >>> " + ofToString(vol),40, 80, 80);
        mOutputVolume = vol;
        soda.pd.sendFloat("vol", vol);
        
        mTextFont.draw("Echo: A listening machine for tracking governmental wikipedia edits",30, 80, 200);
        mTextFont.draw("@_EchoBot: A Twitter bot (tracking edits from the Hungarian Government)",30, 80, 240);
        mTextFont.draw("Binaura: makers of what you see now",30, 80, 280);
        mTextFont.draw("Freedom: a state of mind",30, 80, 320);
    }
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
        if(mPlayMode) playHead = mTunerPos;
    }

    for(auto tweet : t->tweets) {
        if(tweet->mTimeLinePos.x > 0) {
            if(ofVec2f(playHead,t->mP.y).distance(tweet->mTimeLinePos) <2) {
                tweet->textAlpha = 255;
                cTweets[t->tlIndex] = tweet->mIndex;
                if(tweet->mCanPlay) {
                    soda.set("s")->shift(cNotes[t->tlIndex], false);
                    soda.set("s")->volume(mOutputVolume);
                    tweet->mCanPlay = false;
                    mTriggerAlpha = 150;
                }
                return tweet->mIndex;
            } else {
                tweet->mCanPlay = true;
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

void ofApp::audioReceived(float * input, int bufferSize, int nChannels) {
    soda.audioReceived(input, bufferSize, nChannels);
}

void ofApp::audioRequested(float * output, int bufferSize, int nChannels) {
    soda.audioRequested(output, bufferSize, nChannels);
}

