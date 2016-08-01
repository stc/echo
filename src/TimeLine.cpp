#include "TimeLine.h"

void TimeLine::getTweetsFromTwitter(string username, int limit) {
    mUserName = username;
    threadedTwitterQuery.start(mUserName, limit);
    loading = true;
}

void TimeLine::parseResults() {
    bool parsingSuccessful = result.open(ofToDataPath(mUserName) + ".json");
    if (parsingSuccessful) {
        if(result.isArray()) {
            for(int i=0; i<result.size(); i++) {
                string date = result[i]["created_at"].asString();
                string txt = result[i]["text"].asString();
                tweets.push_back(new Tweet(i, date, txt));
            }
        }
    }
}