#include "Tweet.h"

Tweet::Tweet(int index, string date, string text) {
    mDate = date;
    mText = text;
    
    vector< string > str = ofSplitString(mDate, " ");
    mYear = ofToInt(str[5]);
    mDay  = ofToInt(str[2]);
    if(str[1] == "Jan") mMonth = 1;
    if(str[1] == "Feb") mMonth = 2;
    if(str[1] == "Mar") mMonth = 3;
    if(str[1] == "Apr") mMonth = 4;
    if(str[1] == "May") mMonth = 5;
    if(str[1] == "Jun") mMonth = 6;
    if(str[1] == "Jul") mMonth = 7;
    if(str[1] == "Aug") mMonth = 8;
    if(str[1] == "Sep") mMonth = 9;
    if(str[1] == "Oct") mMonth = 10;
    if(str[1] == "Nov") mMonth = 11;
    if(str[1] == "Dec") mMonth = 12;
    
    // should be based on month
    mPos = ofVec2f(20, index * 30);
    
    mTextFont.load("fonts/Tsukushi.ttc",10);
    splittedText = ofSplitString(mText, "http");
}

void Tweet::draw() {
    ofPushMatrix();
    ofTranslate(mPos);
    ofSetColor(255,100,0,140);
    mTextFont.drawString(ofToString(mYear), 0, 15);
    mTextFont.drawString(ofToString(mMonth), 40, 15);
    mTextFont.drawString(ofToString(mDay), 80, 15);
    
    ofSetColor(255,140);
    
    mTextFont.drawString(splittedText[0], 0, 30);
    ofPopMatrix();
}