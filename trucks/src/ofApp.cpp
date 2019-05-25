#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int maxVehicles = 1000;
    b_showGui = true;
    
    for (int i=0;i<maxVehicles;i++){
        vehicle newTruck;
        vehicles.push_back(newTruck);
    }
    
    // cam setup
    cam.setAutoDistance(false);
    ofQuaternion  camOrientation =  ofQuaternion( -0.05, 0.37, 0.18, 0.92);
    cam.setGlobalOrientation(camOrientation);
    cam.setGlobalPosition(85, 10, 85);
    
    ofxLoadCamera(cam,  "ofEasyCamSettings");

}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0; i < vehicles.size(); i++){
        vehicles[i].updateLocation();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    
    cam.begin();
    for (int i=0; i < vehicles.size(); i++){
        vehicles[i].draw();
    }
    
    cam.end();
    ofDisableDepthTest();
    
    if (b_showGui){
        string camPos =   ofToString(cam.getGlobalPosition());
        string camOrient = ofToString(cam.getGlobalOrientation());
        ofDrawBitmapString( cam.getGlobalPosition() , 10, 10);
        cout << "pos " << cam.getGlobalPosition() << " orient " << cam.getGlobalOrientation() << endl;
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
    
    box.draw();
    // box.drawWireframe();
    
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

