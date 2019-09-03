/*
 Project Title: drawNetherlands : clouds
 Description:
 ©Daniel Buzzo 2019
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#pragma once

#include "ofMain.h"
/* #include "ofxCameraSaveLoad.h" */

class cloud{
    
public:
    ofBoxPrimitive box;
    ofColor boxColor;
    ofPoint location;
    float speed;
    void draw();
    void updateLocation();
    cloud(); // constructor
    ~cloud(); // destructor
};

class scenery{
    
public:
    ofBoxPrimitive box;
    ofColor boxColor;
    ofPoint location;
    float speed;
    void draw();
    void updateLocation();
    void setNewPosition();
    scenery(); // constructor
    ~scenery(); // destructor
};

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
    
    ofEasyCam cam;
    vector<cloud> clouds;
    vector<scenery> landscape;
    bool b_showGui;
    ofLight light;
    ofBoxPrimitive ground;
    int sceneWidth, sceneDepth;
};
