#include "Tweet.h"

Tweet::Tweet(int index, string date, string text, ofVec2f mapPos) {
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
    
    mRawPos = ofVec2f(20, index * 30);
    mMapPos = mapPos;
    
    //  should be based on date
    mTimeLinePos = ofVec2f(index, 0);
    
    mTextFont.load("fonts/Tsukushi.ttc",9);
    splittedText = ofSplitString(mText, "http");
}

void Tweet::drawRawView() {
    ofPushMatrix();
    ofTranslate(mRawPos);
    ofSetColor(255,100,0,140);
    mTextFont.drawString(ofToString(mYear), 0, 15);
    mTextFont.drawString(ofToString(mMonth), 40, 15);
    mTextFont.drawString(ofToString(mDay), 80, 15);
    
    ofSetColor(255,140);
    
    mTextFont.drawString(splittedText[0], 0, 30);
    ofPopMatrix();
}

void Tweet::drawMapView(bool showText) {
    ofPushMatrix();
    ofTranslate(mMapPos);
    ofSetColor(255);
    ofDrawCircle(0,0,3);
    
    if(showText) {
        ofTranslate(10,0);
        ofSetColor(255,244,71,200);
        mTextFont.drawString(ofToString(mYear), 0, 15);
        mTextFont.drawString(ofToString(mMonth), 40, 15);
        mTextFont.drawString(ofToString(mDay), 60, 15);
    
        ofSetColor(255,200);
        vector< string > mTxt = ofSplitString(splittedText[0]," ");
        int xoffset = 0;
        int yoffset = 0;
        for(int i=0; i< mTxt.size(); i++) {
            if(i>0) {
                xoffset += mTextFont.getStringBoundingBox(mTxt[i-1], 0, 0).width + 4;
            }
            if(i%3==0) {
                yoffset +=15;
                xoffset = 0;
            }
            mTextFont.drawString(mTxt[i],xoffset,yoffset + 15);
        }
    }
    ofPopMatrix();
}

void Tweet::drawTimeLineView() {
    //...
}