#include "TimeLine.h"

void TimeLine::getTweetsFromTwitter(string username, int limit) {
    mUserName = username;
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
    tweets.push_back(new Tweet(index, date, txt));
    index++;
    
    if(index == result.size()) {
        loading = false;
        result.clear();
        index = 0;
    }
}
