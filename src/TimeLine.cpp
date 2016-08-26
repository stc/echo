#include "TimeLine.h"

TimeLine::TimeLine(int year, int month, int day) {
    mTextFont.load("fonts/Tsukushi.ttc",9);
    cYear = year;
    cMonth = month;
    cDay = day;
}

void TimeLine::getTweetsFromTwitter(string username, int limit, ofVec2f mapPos) {
    mUserName = username;
    mMapPos = mapPos;
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

void TimeLine::drawTimeLine(ofVec2f p) {
    ofSetColor(255,244,71,200);
    mTextFont.drawString(mUserName,p.x,p.y);
    
    // works only in 2016 now!!
    int tmpDateIndex = cDay;
    int dayIndex = 0;
    int monthIndex;
    ofSetColor(255,244,71,100);
    
    for(int i=0; i<30; i++) {
        if(tmpDateIndex>=1) {
            dayIndex = cDay -i;
            monthIndex = cMonth;
            
            if(i<tweets.size()) {
                if(tweets[i]->mYear == cYear) {
                    if(tweets[i]->mMonth == monthIndex) {
                        int x = tweets[i]->mDay * 15 + 300;
                        ofDrawBitmapString(ofToString(tweets[i]->mDay),x, p.y-10);
                        ofDrawCircle(x, p.y,3);
                    }
                }
            }
            
        }else {
            dayIndex = getNumDaysInMonth(2016, cMonth-1) - i + cDay;
            monthIndex = cMonth-1;
            
            if(i<tweets.size()) {
                if(tweets[i]->mYear == cYear) {
                    if(tweets[i]->mMonth == monthIndex) {
                        int x = (tweets[i]->mDay * 15 + 300) - (cDay+1) * 15;
                        ofDrawBitmapString(ofToString(tweets[i]->mDay),x, p.y-10);
                        ofDrawCircle(x, p.y,3);
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




