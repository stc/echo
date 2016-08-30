#include "Tweet.h"

Tweet::Tweet(int index, string date, string text, ofVec2f mapPos) {
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
    //mTextPos = ofVec2f(0,0);
    
    mTextFont.load("fonts/DINBold.ttf",9);
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

void Tweet::drawMapView() {
    ofPushMatrix();
    ofTranslate(mMapPos);
    ofSetColor(255);
    ofDrawLine(-3,0,3,0);
    ofDrawLine(0,-3,0,3);
    
    ofTranslate(mTextPos);
    if(textAlpha>0) {
        ofSetColor(255,100);
        ofDrawLine(-mTextPos.x,-mTextPos.y,95,50);
        ofTranslate(10,0);
        
        ofSetColor(255,244,71,255);
        mTextFont.drawString(ofToString(mYear) + " / ", 0, 15);
        mTextFont.drawString(ofToString(mMonth) + " / ", 40, 15);
        mTextFont.drawString(ofToString(mDay), 60, 15);
    
        
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
            ofSetColor(0);
            ofDrawRectangle(xoffset,yoffset,mTextFont.getStringBoundingBox(mTxt[i], 0, 0).width + 15,20);
            ofSetColor(255,255);
           mTextFont.drawString(mTxt[i],xoffset,yoffset + 15);
        }
        textAlpha-=1;
    }
    ofPopMatrix();
}

void Tweet::drawTimeLineView(ofVec2f p) {
    ofSetColor(255,244,71);
    ofDrawRectangle(p.x, p.y-2,4,4);
    ofSetColor(255,alpha);
    ofDrawRectangle(p.x-2, p.y-4,6,8);
    if(alpha>0) alpha-=5;
    mTimeLinePos = ofVec2f(p.x,p.y);
}
