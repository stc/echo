#include "TimeLine.h"

void TimeLine::getTweetsFromTwitter(string username, int limit) {
    mUserName = username;
    string path_to_twurl = "/Library/Ruby/Gems/2.0.0/gems/twurl-0.9.3/bin/";
    string cmd = path_to_twurl + "twurl \"/1.1/statuses/user_timeline.json?screen_name=" + mUserName + "&count=" + ofToString(limit) + "\" > " + ofToDataPath(mUserName) + ".json";
    system(cmd.c_str());
    bool parsingSuccessful = result.open(ofToDataPath(mUserName) + ".json");
    if (parsingSuccessful) {
        canParse = true;
        parseResults();
    } else {
        canParse = false;
    }
}

void TimeLine::displayTweetsFromJSON(int x, int y) {
    if(canParse) {
        if(result.isArray()) {
            ofPushMatrix();
            ofTranslate(x, y);
            ofSetColor(200,200,0);
            ofDrawBitmapString(mUserName, 0, 0);
            
            for(int i=0; i<result.size(); i++) {
                ofSetColor(255,100);
                string date = result[i]["created_at"].asString();
                ofDrawBitmapString(date, 0, 30 * i + 30);
                ofSetColor(255);
                string txt = result[i]["text"].asString();
                string splittxt = txt.substr(0,30);
                ofDrawBitmapString(splittxt, 0, 30 * i + 45);
            }
            ofPopMatrix();
        }
    }
    ofSetColor(255,0,0);
    ofDrawBitmapString(ofToString(int(ofGetFrameRate())), 20, 20);
}

void TimeLine::parseResults() {
    if(result.isArray()) {
        for(int i=0; i<result.size(); i++) {
            string date = result[i]["created_at"].asString();
            string txt = result[i]["text"].asString();
            tweets.push_back(new Tweet(i, date, txt));
        }
    }
}