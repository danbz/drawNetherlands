/*
 Project Title: drawNetherlands : tankers at sea
 Description:
 ©Daniel Buzzo 2019
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */


#include "ofApp.h"

#define sceneWidth 8000
#define sceneDepth 8000

//--------------------------------------------------------------
void ofApp::setup(){

    // cam setup
    cam.setAutoDistance(false);
    ofQuaternion  camOrientation =  ofQuaternion( -0.05, 0.37, 0.18, 0.92);
    cam.setGlobalOrientation(camOrientation);
    cam.setGlobalPosition(85, 10, 85);
    cam.setFarClip(10000);
    ofxLoadCamera(cam,  "ofEasyCamSettings" );
    
    // light setup
    light.setGlobalPosition(0, 500, 2000);
    light.setAreaLight(200, 200);
    light.setAmbientColor(ofColor(55));
    
    ofSetFrameRate(60);
    
    // setup tankers
    int numOfTankers = 10;
    for (int i=0; i<numOfTankers; i++){
        tanker newTanker;
        newTanker.setPosition(0,0,0);
        ofVec3f newPosition;
        newPosition.set(ofRandom(-sceneWidth/2, sceneWidth/2), 1, ofRandom(-sceneDepth/2, sceneDepth/2));
        newTanker.setPosition(newPosition);
        tankers.push_back(newTanker);
    }
    
    windDirection =ofRandom(360);
    windSpeed = ofRandom(1,10);
    ofSetBackgroundColor(21, 31, 63);
}

//--------------------------------------------------------------
void ofApp::update(){
    //float t = ofGetSystemTimeMillis();
    float t = ofGetElapsedTimef();
    windDirection += ofSignedNoise(t)  ;
    cout << windDirection << endl;
    for (int i=0; i<tankers.size(); i++){
        tankers[i].updatePosition();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    light.enable();
    cam.begin();
    for (int i=0; i<tankers.size(); i++){
        ofPushMatrix();
        ofTranslate(tankers[i].getPosition());
        ofRotateYDeg(windDirection);
        tankers[i].draw();
        ofPopMatrix();

    }
    cam.end();
    light.disable();
    ofDisableDepthTest();
    
    if (b_showGui){
        string camPos =   ofToString(cam.getGlobalPosition());
        string camOrient = ofToString(cam.getGlobalOrientation());
        // ofDrawBitmapString( cam.getGlobalPosition() , 10, 10);
        ofDrawBitmapString(ofGetFrameRate(), 10, 10);
        // cout << "pos " << cam.getGlobalPosition() << " orient " << cam.getGlobalOrientation() << endl;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    string camPos, camOrient;
    
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
            
        case 'h':
            cam.reset();
            break;
            
        case 'g':
            b_showGui = !b_showGui;
            break;
            
        case 's':
            cout << "saving cam position" << endl;
            ofxSaveCamera(cam, "ofEasyCamSettings");
            break;
            
        case 'l':
            cout << "loading cam position" << endl;
            ofxLoadCamera(cam,  "ofEasyCamSettings");
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------

tanker::tanker(){
    // tanker constructor
    float size = ofRandom(50,400);
    float width_length_ratio = 0.2;
    int wakeLength = 20;
    rotation =0;
    motion.set(0,0,0);
    tankerHull.set(size*width_length_ratio, size*width_length_ratio, size);
    // tankerHull.set(10, 10, 50);
    
    // setup wake
    for (int i = 0; i< wakeLength; i++){
        ofPoint newPoint;
        newPoint.set(0,0);
        wake.push_back(newPoint);
    }

}

//--------------------------------------------------------------

tanker::~tanker(){
    //tanker destructor
    
}


//--------------------------------------------------------------

void tanker::draw(){
//    ofPushMatrix();
//    ofTranslate(getPosition());
    ofTranslate(0,0,tankerHull.getDepth()*1.5);
    tankerHull.draw();
    ofTranslate(0,0, tankerHull.getDepth()/2);
    ofRotateXDeg(90);
    ofTranslate(0, 0, tankerHull.getHeight()/2);
    for (int i = 0; i< wake.size(); i++){
        ofDrawCircle(wake[i],wake.size()-i);
    }
    //ofPopMatrix();
}
//--------------------------------------------------------------
void tanker::updatePosition(){
    setPosition(getPosition()+motion);
    for (int i=0; i<wake.size()-1; i++){
        wake[i+1]=wake[i];
        wake[i].x=0;
        wake[i].y=i*tankerHull.getDepth()/20;
    }
    
}
//--------------------------------------------------------------

void tanker::setPosition(int x, int y, int z ){
    ofVec3f newPosition;
    newPosition.set(x,y,z);
    setPosition(newPosition);
}

//--------------------------------------------------------------

void tanker::setPosition(ofVec3f newPosition){
    position = newPosition;
}

//--------------------------------------------------------------

ofVec3f tanker::getPosition(){
    return position;
}
