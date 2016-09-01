#pragma once
#include "ofMain.h"
#include "ThreadedTwitterObject.h"
#include "ofxJSON.h"
#include "Tweet.h"
#include "ofxFontStash.h"

class TimeLine {
public:
    TimeLine(int index, int year, int month, int day);
    
    void getTweetsFromTwitter(string username, int limit, ofVec2f mapPos, string userCountry);
    void parseResults();
    void reset();
    void loadTweets();
    void drawTimeLine(ofVec2f p, ofxFontStash & mTextFont);
    
    bool loading = false;
    bool parsed = false;
    
    string mUserName = "";
    string mUserCountry = "";
    ofxJSONElement result;
    vector<Tweet *> tweets;
    ofFile mFile;
    ThreadedTwitterObject threadedTwitterQuery;
    int mIndex = 0;
    ofVec2f mMapPos;
    
    int cYear;
    int cMonth;
    int cDay;
    int tlIndex;
    
    ofVec2f mP;
    
    int getNumDaysInMonth(int year, int month);
    
    int tlMin = 0;
    int tlMax = 0;
    
    string monthNames[12] = {
        "January","February","March","April","May","June","July", "August", "September", "October", "November", "December"
    };
    
    float mVolume = 0;
    float getVolume(ofVec2f p);

};