#include "TimeLine.h"

TimeLine::TimeLine(int index, int year, int month, int day) {
    cYear = year;
    cMonth = month;
    cDay = day;
    
    tlIndex = index;
    
    colorPalette.push_back(ofColor(254, 237, 181));
    colorPalette.push_back(ofColor(254, 202, 161));
    colorPalette.push_back(ofColor(253, 141, 139));
    colorPalette.push_back(ofColor(117, 102, 132));
    colorPalette.push_back(ofColor(30,  167, 179));
    colorPalette.push_back(ofColor(75,  216, 156));
    colorPalette.push_back(ofColor(147, 248, 138));
    mColor = colorPalette[tlIndex];
}

void TimeLine::getTweetsFromTwitter(string username, int limit, ofVec2f mapPos, string userCountry) {
    mUserName = username;
    mMapPos = mapPos;
    mUserCountry = userCountry;
    threadedTwitterQuery.start(mUserName, limit);
    loading = true;
    parsed = false;
}

void TimeLine::reset() {
    mFile = ofFile(ofToDataPath(mUserName) + ".json");
    if(mFile.exists()) {
        mFile.remove();
    }
    result.clear();
    tweets.clear();
}

void TimeLine::parseResults() {
    bool parsingSuccessful = result.open(ofToDataPath(mUserName) + ".json");
    if (parsingSuccessful) {
        if(result.isArray()) {
            tweets.clear();
            parsed = true;
        }
    }
}

void TimeLine::loadTweets() {
    string date = result[mIndex]["created_at"].asString();
    string txt = result[mIndex]["text"].asString();
    tweets.push_back(new Tweet(mIndex, date, txt, mMapPos, mColor));
    mIndex++;
    
    if(mIndex == result.size()) {
        loading = false;
        result.clear();
        mIndex = 0;
    }
}

void TimeLine::drawTimeLine(ofVec2f p, ofxFontStash & mTextFont) {
    mP = p;
    ofSetColor(mColor);
    mTextFont.draw(mUserName + " (" + mUserCountry + ")",16, p.x, p.y);
    
    tlMin = 16 + 150;
    tlMax = tlMax = ofGetWidth()-100;

    ofSetColor(100);
    ofDrawLine(tlMin - 10, p.y, tlMax,p.y);
    
    // Important! Works only in 2016 with the following code:
    int dayIndex = 0;
    int monthIndex;
    int timeLineOffset = ofGetWidth() / 2;
    
    // check if this is the first timeline
    if(tlIndex == 0) {
        ofSetColor(255);
        mTextFont.draw("Twitter Bot Names ", 16, 20, ofGetHeight()-135);
        ofSetColor(100);
        mTextFont.draw(monthNames[cMonth-1], 16, 16 + timeLineOffset, ofGetHeight()-135);
        mTextFont.draw(monthNames[cMonth-2], 16, 16 + 150, ofGetHeight()-135);
        ofDrawLine(16 + timeLineOffset, ofGetHeight()-120, 16 + timeLineOffset, ofGetHeight());
        ofDrawLine(16 + 140, ofGetHeight()-120, 16 + 140, ofGetHeight());
        
        ofSetColor(80);
        for(int i=0; i< getNumDaysInMonth(cYear, cMonth-1); i++) {
            mTextFont.draw(ofToString(i+1), 12, tlMin - 8 + i*16, ofGetHeight()-120);
        }
        for(int i=0; i< getNumDaysInMonth(cYear, cMonth); i++) {
            mTextFont.draw(ofToString(i+1), 12, 16 + timeLineOffset + i*16, ofGetHeight()-120);
        }
    }

    ofSetColor(mColor);
    for(int i=0; i<200; i++) {
        dayIndex = cDay -i;
        monthIndex = cMonth;
        
        if(i<tweets.size()) {
            if(tweets[i]->mYear == cYear) {
                if(tweets[i]->mMonth == monthIndex) {
                    int x = tweets[i]->mDay * 16 + timeLineOffset;
                    tweets[i]->mTimeLinePos = ofVec2f(x,p.y);
                    ofSetLineWidth(6);
                    ofDrawLine(x,p.y-3,x,p.y+3);
                    ofSetLineWidth(1);
                }
            }
        }
    }
    for(int i=0; i<200; i++){
        dayIndex = getNumDaysInMonth(cYear, cMonth-1) - i + cDay;
        monthIndex = cMonth-1;
        
        if(i<tweets.size()) {
            if(tweets[i]->mYear == cYear) {
                if(tweets[i]->mMonth == monthIndex) {
                    int x = ((tweets[i]->mDay-getNumDaysInMonth(cYear, cMonth-1)) * 16 + timeLineOffset);
                    tweets[i]->mTimeLinePos = ofVec2f(x,p.y);
                    
                    ofSetLineWidth(6);
                    ofDrawLine(x,p.y-3,x,p.y+3);
                    ofSetLineWidth(1);
                }
            }
        }
    }
}

int TimeLine::getNumDaysInMonth(int year, int month) {
    int days;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        days = 30;
    } else if (month == 2) {
        bool leapyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (leapyear == 0) {
            days = 28;
        } else {
            days = 29;
        }
    } else {
        days = 31;
    }
    return days;
}

float TimeLine::getVolume(ofVec2f p) {
    float d = p.distance(mMapPos);
    if(d < 100) {
        mVolume = (100 - d) / 100.;
    }else {
        mVolume = 0;
    }
    
    return mVolume;
}




