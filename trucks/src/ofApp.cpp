#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int maxVehicles = 1000;
    for (int i=0;i<maxVehicles;i++){
        vehicle newTruck;
        vehicles.push_back(newTruck);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0; i < vehicles.size(); i++){
        vehicles[i].updateLocation();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    for (int i=0; i < vehicles.size(); i++){
        vehicles[i].draw();
    }
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------

 vehicle::vehicle(){
    // constructor
     int farClip = -2000;
     int nearClip = 2000;
     int laneWidth = 6;
     float size = 10.0;
     float widthRatio = 0.5;
     float heightratio = 0.7;
     float maxSpeed = 5.0;
     boxColor = ofColor(ofRandom(100)+55);
     box.set(ofRandom(size * widthRatio), ofRandom(size * widthRatio), size);
     box.setPosition(ofRandom(laneWidth) * size, box.getHeight()/2, farClip);
     speed = ofRandom(maxSpeed);
     for (int i =0;i < 6; i ++){
         box.setSideColor(i, boxColor);

     }
 }

//--------------------------------------------------------------

 vehicle::~vehicle(){
    // destructor
}

//--------------------------------------------------------------

void vehicle::draw(){
    ofEnableDepthTest();
    box.draw();
    ofDisableDepthTest();
}

//--------------------------------------------------------------

void vehicle::updateLocation(){
    int farClip = -2000;
    int nearClip = 2000;
    int laneWidth = 6;
    float size = 10.0;
    
    if (box.getPosition().z >nearClip){
        box.setPosition(ofRandom(laneWidth) * size, box.getPosition().y, farClip);
    }
    box.setPosition(box.getPosition().x, box.getPosition().y, box.getPosition().z + speed);
}

//--------------------------------------------------------------

