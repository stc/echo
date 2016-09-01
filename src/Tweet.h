#pragma once
#include "ofMain.h"
#include "ofxFontStash.h"

class Tweet {
public:
    Tweet(int index, string date, string text, ofVec2f mapPos);
    void drawMapView(ofxFontStash & mTextFont);
    
    string mText;
    string mDate;
    
    ofVec2f mRawPos;
    ofVec2f mMapPos;
    ofVec2f mTimeLinePos;
    ofVec2f mTextPos;
    
    int mMonth = 0;
    int mYear = 0;
    int mDay = 0;
    
    
    //ofxFontStash mTextFont;
    vector<string> splittedText;
    
    float textAlpha = 0;
    int mIndex = 0;
    
    bool mCanPlay = true;
};