#pragma once
#include "ofMain.h"
#include "TimeLine.h"
#include "BaseView.h"
#include "Tweet.h"
#include "ofxSodaLib.h"
#include "ofxFontStash.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        vector< TimeLine * > timelines;
        BaseView baseView;
        bool checkInternetConnection();
    
        int getSequence(TimeLine * t);
        float playHead = 0;
        bool mPlayMode = true;
    
        vector< int > cTweets;
        vector< float > cNotes;
    
        bool mOnline;
        ofImage mNetworkError;
    
        int cYear;
        int cMonth;
        int cDay;
    
        int mTunerValue = 0;
        float mTunerTarget;
        float mTunerPos;
        float mTunerEasing = 0.05;
        int pTunerVal;
        void drawProcessTuner();
        bool mCanMoveTuner = false;
        int mTunerSwitch = 0;
        int pmTunerSwitch = 0;
        vector<int> tunerAverage;
        int tunerAvgCounter = 0;
        int mTriggerAlpha = 0;
        long mTunerSwitchTime;
        long mTunerSwitchCounter = 0;
    
        long mTunerRotateTime;
        long mTunerRotateCounter = 0;
    
        float mOutputVolume = 0.45;
        float mRotateAlpha = 255;
    
        float infoAlpha = 0;
    
        ofxFontStash mTextFont;
    
        ofxSodaLib soda;
        void audioReceived(float * input, int bufferSize, int nChannels);
        void audioRequested(float * input, int bufferSize, int nChannels);
};
