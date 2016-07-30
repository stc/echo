#pragma once
#include "ofMain.h"
#include "ofxJSON.h"
#include "Tweet.h"

class TimeLine {
public:
    void displayTweetsFromJSON(int x, int y);
    void getTweetsFromTwitter(string username, int limit);
    void parseResults();
    
    ofxJSONElement result;
    bool canParse = false;
    string mUserName;
    
    vector<Tweet *> tweets;
};