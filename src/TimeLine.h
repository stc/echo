#pragma once
#include "ofMain.h"
#include "ThreadedTwitterObject.h"
#include "ofxJSON.h"
#include "Tweet.h"

class TimeLine {
public:
    TimeLine();
    
    void getTweetsFromTwitter(string username, int limit, ofVec2f mapPos);
    void parseResults();
    void reset();
    void loadTweets();
    void drawTimeLine(ofVec2f p);
    
    bool loading = false;
    bool parsed = false;
    
    string mUserName = "";
    ofxJSONElement result;
    vector<Tweet *> tweets;
    ofFile mFile;
    ThreadedTwitterObject threadedTwitterQuery;
    int index = 0;
    ofVec2f mMapPos;
    ofTrueTypeFont mTextFont;
};