#pragma once
#include "ofMain.h"
#include "ThreadedTwitterObject.h"
#include "ofxJSON.h"
#include "Tweet.h"

class TimeLine {
public:
    void getTweetsFromTwitter(string username, int limit);
    void parseResults();
    void reset();
    void loadTweets();
    bool loading = false;
    bool parsed;
    string mUserName;
    ofxJSONElement result;
    vector<Tweet *> tweets;
    ofFile mFile;
    ThreadedTwitterObject threadedTwitterQuery;
    int index;
};