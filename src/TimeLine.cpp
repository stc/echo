#include "TimeLine.h"

TimeLine::TimeLine(int year, int month, int day) {
    mTextFont.load("fonts/DINBold.ttf",9);
    cYear = year;
    cMonth = month;
    cDay = day;
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
    string date = result[index]["created_at"].asString();
    string txt = result[index]["text"].asString();
    tweets.push_back(new Tweet(index, date, txt, mMapPos));
    index++;
    
    if(index == result.size()) {
        loading = false;
        result.clear();
        index = 0;
    }
}

void TimeLine::drawTimeLine(int index, ofVec2f p) {
    ofSetColor(255,244,71);
    mTextFont.drawString(mUserName + " (" + mUserCountry + ")",p.x,p.y);
    
    ofSetColor(100);
    ofDrawLine(p.x + 140, p.y, ofGetWidth()-100,p.y);
    
    // Important! Works only in 2016 with the following code:
    
    int tmpDateIndex = cDay;
    int dayIndex = 0;
    int monthIndex;
    
    int timeLineOffset = ofGetWidth() / 2;
    
    
    if(index == 0) {
        mTextFont.drawString(monthNames[cMonth-1], 16 + timeLineOffset, ofGetHeight()-120);
        mTextFont.drawString(monthNames[cMonth-2], 16 + 150, ofGetHeight()-120);
        ofSetColor(100);
        ofDrawLine(16 + timeLineOffset, ofGetHeight()-100, 16 + timeLineOffset, ofGetHeight());
        ofDrawLine(16 + 150, ofGetHeight()-100, 16 + 150, ofGetHeight());
    }
    
    for(int i=0; i<200; i++) {
        if(tmpDateIndex>=1) {
            dayIndex = cDay -i;
            monthIndex = cMonth;
            
            if(i<tweets.size()) {
                if(tweets[i]->mYear == cYear) {
                    if(tweets[i]->mMonth == monthIndex) {
                        int x = tweets[i]->mDay * 16 + timeLineOffset;
                        ofSetColor(255,244,71);
                        ofDrawRectangle(x, p.y-2,4,4);
                    }
                }
            }
            
        }else {
            dayIndex = getNumDaysInMonth(cYear, cMonth-1) - i + cDay;
            monthIndex = cMonth-1;
            
            if(i<tweets.size()) {
                
                if(tweets[i]->mYear == cYear) {
                    if(tweets[i]->mMonth == monthIndex) {
                        int x = ((tweets[i]->mDay-getNumDaysInMonth(cYear, cMonth-1)) * 16 + timeLineOffset);
                        ofSetColor(255,244,71);
                        ofDrawRectangle(x, p.y-2,4,4);
                    }
                }
            }
        }
        tmpDateIndex--;
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




