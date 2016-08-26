#include "TimeLine.h"

TimeLine::TimeLine() {
    mTextFont.load("fonts/Tsukushi.ttc",9);
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
    for(int i=0; i<tweets.size(); i++) {
        tweets[i]->drawTimeLineView(ofVec2f(p.x + 200 + i*10,p.y));
    }
}
