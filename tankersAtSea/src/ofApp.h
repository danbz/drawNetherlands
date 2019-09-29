/*
 Project Title: drawNetherlands : tankers at sea
 Description:
 ©Daniel Buzzo 2019
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#pragma once

#include "ofMain.h"
#include "ofxCameraSaveLoad.h"

class tanker{
    ofVec3f position;
    ofVec3f motion;
    float rotation;
public:
    ofBoxPrimitive tankerHull;
    ofVec3f getPosition();
    void setPosition(ofVec3f position);
    void setPosition(int x, int y, int z);
    void draw();
    void updatePosition();
    tanker(); // constructor
    ~tanker(); // destructor
    
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
	
		
    ofEasyCam cam;
    ofLight light;
    bool b_showGui;
    vector<tanker>tankers;
    float windDirection;
    float windSpeed;

};
