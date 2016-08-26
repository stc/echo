#pragma once
#include "ofMain.h"

class Tweet {
public:
    Tweet(int index, string date, string text, ofVec2f mapPos);
    
    void drawRawView();
    void drawMapView(bool showText);
    void drawTimeLineView(ofVec2f p);
    
    string mText;
    string mDate;
    
    ofVec2f mRawPos;
    ofVec2f mMapPos;
    ofVec2f mTimeLinePos;
    
    int mMonth = 0;
    int mYear = 0;
    int mDay = 0;
    
    ofTrueTypeFont mTextFont;
    vector<string> splittedText;
};