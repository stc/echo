#pragma once
#include "ofMain.h"
#include "ThreadedTwitterObject.h"
#include "ofxJSON.h"
#include "Tweet.h"

class TimeLine {
public:
    TimeLine(int year, int month, int day);
    
    void getTweetsFromTwitter(string username, int limit, ofVec2f mapPos, string userCountry);
    void parseResults();
    void reset();
    void loadTweets();
    void drawTimeLine(int index, ofVec2f p);
    
    bool loading = false;
    bool parsed = false;
    
    string mUserName = "";
    string mUserCountry = "";
    ofxJSONElement result;
    vector<Tweet *> tweets;
    ofFile mFile;
    ThreadedTwitterObject threadedTwitterQuery;
    int index = 0;
    ofVec2f mMapPos;
    ofTrueTypeFont mTextFont;
    
    int cYear;
    int cMonth;
    int cDay;
    
    int getNumDaysInMonth(int year, int month);
    
    string monthNames[12] = {
        "January","February","March","April","May","June","July", "August", "September", "October", "November", "December"
    };

};