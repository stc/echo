#pragma once
#include "ofMain.h"

class Tweet {
public:
    Tweet(int index, string date, string text);
    void draw();
    string mText;
    string mDate;
    ofVec2f mPos;
    
    int mMonth;
    int mYear;
    int mDay;
    
    ofTrueTypeFont mTextFont;
    vector<string> splittedText;
};