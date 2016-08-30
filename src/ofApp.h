#pragma once
#include "ofMain.h"
#include "TimeLine.h"
#include "BaseView.h"
#include "Tweet.h"

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
    
        bool mOnline;
        ofImage mNetworkError;
    
        int cYear;
        int cMonth;
        int cDay;
};
