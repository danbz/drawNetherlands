#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int maxVehicles = 500;
    int maxScenery = 2000;
    b_showGui = false;
    
    for (int i=0;i<maxVehicles;i++){
        vehicle newTruck;
        vehicles.push_back(newTruck);
    }
    
    for (int i=0;i<maxScenery;i++){
        scenery newScenery;
        landscape.push_back(newScenery);
    }
    
    // cam setup
    cam.setAutoDistance(false);
    ofQuaternion  camOrientation =  ofQuaternion( -0.05, 0.37, 0.18, 0.92);
    cam.setGlobalOrientation(camOrientation);
    cam.setGlobalPosition(85, 10, 85);
    
    ofxLoadCamera(cam,  "ofEasyCamSettings" );
    
    // light setup
    light.setGlobalPosition(0, 500, 2000);
    light.setAreaLight(100, 100);
    light.setAmbientColor(ofColor(55));

}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0; i < vehicles.size(); i++){
        vehicles[i].updateLocation();
    }
    for (int i=0; i < landscape.size(); i++){
        landscape[i].updateLocation();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    light.enable();
    
    cam.begin();
    for (int i=0; i < vehicles.size(); i++){
        vehicles[i].draw();
    }
    
    for (int i=0; i < landscape.size(); i++){
        landscape[i].draw();
    }
    
    cam.end();
    light.disable();
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
    // vehicle constructor
    int farClip = -2000;
    int nearClip = 2000;
    int laneWidth = 6;
    float size = 10.0;
    float widthRatio = 0.4;
    float heightRatio = 0.5;
    float maxSpeed = 5.0;
    float minSpeed = 0.25;
    float minWidth = 3;
    float minHeight = 3;
    boxColor = ofColor(ofRandom(150)+55);
    box.set(ofRandom(size * widthRatio)+ minWidth, ofRandom(size * heightRatio)+minHeight, size);
    box.setPosition(ofRandom(laneWidth) * size, box.getHeight()/2, farClip);
    speed = ofRandom(maxSpeed)+minSpeed;
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
    
    if (box.getPosition().z > nearClip){
        box.setPosition(ofRandom(laneWidth) * size, box.getPosition().y, farClip);
    }
    box.setPosition(box.getPosition().x, box.getPosition().y, box.getPosition().z + speed);
}

//--------------------------------------------------------------

scenery::scenery(){
    // scenery constructor
    int farClip = -2000;
    int nearClip = 2000;
    int sceneryLanes = 20;
    float size = 100.0;
    float widthRatio = 0.1;
    float heightRatio = 0.5;
    float speed = 2.0;
    float spread = abs(farClip) + nearClip;
    float minWidth = 3;
    float minHeight = 3;
    float boxbaseColor = ofRandom(50) + 10;
    boxColor = ofColor(boxbaseColor, boxbaseColor + 50, boxbaseColor);
    box.set(ofRandom(size * widthRatio)+ minWidth, ofRandom(size * heightRatio)+minHeight, ofRandom(size)+ 2);
    box.setPosition(- ofRandom(sceneryLanes) * size, box.getHeight()/2, ofRandom(spread));
    for (int i =0;i < 6; i ++){
        box.setSideColor(i, boxColor);
        
    }
}

//--------------------------------------------------------------

scenery::~scenery(){
    // destructor
}

//--------------------------------------------------------------

void scenery::draw(){
    
    box.draw();
    // box.drawWireframe();
    
}

//--------------------------------------------------------------

void scenery::updateLocation(){
    int farClip = -2000;
    int nearClip = 2000;
    int sceneryLanes = 20;
    float size = 100.0;
    
    if (box.getPosition().z <farClip){
        box.setPosition(- ofRandom(sceneryLanes) * size, box.getPosition().y, nearClip);
    }
    box.setPosition(box.getPosition().x, box.getPosition().y, box.getPosition().z - speed);
}

//--------------------------------------------------------------

