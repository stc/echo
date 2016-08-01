#pragma once
#include "ofMain.h"
#include "ThreadedTwitterObject.h"
#include "ofxJSON.h"
#include "Tweet.h"

class TimeLine {
public:
    void getTweetsFromTwitter(string username, int limit);
    void parseResults();
    void removeFile();
    bool loading = false;
    string mUserName;
    ofxJSONElement result;
    vector<Tweet *> tweets;
    ofFile mFile;
    ThreadedTwitterObject threadedTwitterQuery;
};