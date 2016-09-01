#pragma once
#include "ofMain.h"
#include "TimeLine.h"
#include "BaseView.h"
#include "Tweet.h"
#include "ofxSodaLib.h"

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
    
        vector< int > cTweets;
        vector< float > cVolumes;
    
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
        void drawTuner();
        bool mCanMoveTuner = false;
        int mTunerSwitch = 0;
        vector<int> tunerAverage;
        int tunerAvgCounter = 0;
    
        ofxSodaLib soda;
        void audioReceived(float * input, int bufferSize, int nChannels);
        void audioRequested(float * input, int bufferSize, int nChannels);
};
