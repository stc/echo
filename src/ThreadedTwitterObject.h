#pragma once
#include "ofThread.h"

class ThreadedTwitterObject: public ofThread {
public:
    ThreadedTwitterObject(): shouldThrowTestException(false), mLimit("10"), mUserName(""){}

    void start(string userName, int limit) {
        mLimit = ofToString(limit);
        mUserName = userName;
        startThread();
    }

    void stop() {
        stopThread();
    }

    void threadedFunction() {
        while(isThreadRunning()) {
            if(lock()) {
                string path_to_twurl = "/Library/Ruby/Gems/2.0.0/gems/twurl-0.9.3/bin/";
                string cmd = path_to_twurl + "twurl \"/1.1/statuses/user_timeline.json?screen_name=congressedits&count=" + mLimit + "\" > " + ofToDataPath(mUserName + ".json");
                system(cmd.c_str());
                
                unlock();
                sleep(1000);

                if(shouldThrowTestException > 0) {
                    shouldThrowTestException = 0;
                    throw Poco::ApplicationException("We just threw a test exception!");
                }
            }
            else {
                ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
            }
            //waitForThread(true,5000);
        }
    }

    void throwTestException() {
        shouldThrowTestException = 1;
    }

protected:
    Poco::AtomicCounter shouldThrowTestException;
    string mLimit;
    string mUserName;
};
