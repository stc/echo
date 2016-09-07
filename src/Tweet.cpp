#include "Tweet.h"

Tweet::Tweet(int index, string date, string text, ofVec2f mapPos, ofColor color) {
    mDate = date;
    mText = text;
    mIndex = index;
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
    mTextPos = ofVec2f(ofRandom(200)-100, ofRandom(300)-150);
    mColor = color;
    
    //mTextFont.setup("fonts/DINBold.ttf", 1.0, 1024, false, 8, 2.0f);
    splittedText = ofSplitString(mText, "http");
}

void Tweet::drawMapView(ofxFontStash & mTextFont) {
    ofPushMatrix();
    ofTranslate(mMapPos);
    ofSetColor(mColor);
    ofSetLineWidth(6);
    ofDrawLine(0,-3,0,3);
    ofSetLineWidth(1);

    ofTranslate(mTextPos);
    if(textAlpha>0) {
        ofSetColor(mColor,textAlpha);
        ofDrawLine(-mTextPos.x,-mTextPos.y,95,50);
        ofSetColor(mColor,textAlpha);
        ofDrawRectangle(-5,-5,180,100);
        ofTranslate(10,0);
        
        ofSetColor(255,textAlpha);
        
        mTextFont.draw(ofToString(mYear) + " / ", 16, 0, 15);
        mTextFont.draw(ofToString(mMonth) + " / ", 16, 40, 15);
        mTextFont.draw(ofToString(mDay), 16, 60, 15);
    
        ofTranslate(0,30);
        ofSetColor(0,textAlpha);
        int numLines = 0;
        bool wordsWereCropped;
        ofRectangle column;
        column = mTextFont.drawMultiLineColumn(	splittedText[0], 16, 0, 0, MAX( 10 ,150), numLines, false, 5, true,	&wordsWereCropped);
        textAlpha-=0.5;
    }
    ofPopMatrix();
}
