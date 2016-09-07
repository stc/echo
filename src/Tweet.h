#pragma once
#include "ofMain.h"
#include "ofxFontStash.h"

class Tweet {
public:
    Tweet(int index, string date, string text, ofVec2f mapPos, ofColor color);
    void drawMapView(ofxFontStash & mTextFont);
    void drawOriginOnMap();
    
    string mText;
    string mDate;
    
    ofVec2f mRawPos;
    ofVec2f mMapPos;
    ofVec2f mTimeLinePos;
    ofVec2f mTextPos;
    ofVec2f mDirection;
    
    ofColor mColor;
    
    int mMonth = 0;
    int mYear = 0;
    int mDay = 0;
    
    vector<string> splittedText;
    
    float textAlpha = 0;
    int mIndex = 0;
    
    bool mCanPlay = true;
    
    
};