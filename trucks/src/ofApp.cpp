/*
 Project Title: drawNetherlands : trucks
 Description:
 ©Daniel Buzzo 2019
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */


#include "ofApp.h"

#define sceneWidth 4000
#define laneWidth 6
#define truckSize 10

//--------------------------------------------------------------
void ofApp::setup(){
    int maxVehicles = 500;
    int maxScenery = 1000;
    //sceneWidth = sceneDepth = 4000;
    roadWidth = laneWidth * truckSize * 2 + truckSize;
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
    light.setAreaLight(200, 200);
    light.setAmbientColor(ofColor(55));
    
    ofSetFrameRate(60);
    
    ground.set( sceneWidth,  sceneWidth, 1 );
    ground.setPosition( -sceneWidth/2, 0, 0 );
    ground.rotateDeg(90, 1, 0, 0);
    ofColor groundColor = (155, ofRandom(100)+155, 155);
    for (int i =0;i < 6; i ++){
        ground.setSideColor(i, groundColor);
        
    }
    road.set( sceneWidth, roadWidth, 2);
    road.setPosition( 0, -2 , 0 );
    road.rotateDeg( 90, 1, 0, 0 );
    road.rotateDeg( 90, 0, 1, 0 );
    ofColor roadColor = (75);
    for (int i =0;i < 6; i ++){
        road.setSideColor(i, roadColor);
        
    }
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
    
    ground.draw();
    road.draw();
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
    int farClip = -sceneWidth/2;
    int nearClip = sceneWidth/2;
    float widthRatio = 0.4;
    float heightRatio = 0.5;
    float maxSpeed = 2.2;
    float minSpeed = 0.1;
    float minWidth = 3;
    float minHeight = 3;
    boxColor = ofColor(ofRandom(150)+55);
    if (ofRandom(500) > 499){
       boxColor = ofColor(ofRandom(200)+55, 50, 50); // random red vehicle as 1 in 1000
        maxSpeed = 2.5; // make it fast
        minSpeed = 1.5;
    }
    box.set(ofRandom(truckSize * widthRatio)+ minWidth, ofRandom(truckSize * heightRatio)+minHeight, truckSize);
    box.setPosition(ofRandom(laneWidth) * truckSize, box.getHeight()/2, farClip);
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
    int farClip = -sceneWidth/2;
    int nearClip = sceneWidth/2;
    if (box.getPosition().z > nearClip){
        box.setPosition(ofRandom(laneWidth) * truckSize, box.getPosition().y, farClip);
    }
    box.setPosition(box.getPosition().x, box.getPosition().y, box.getPosition().z + speed);
}

//--------------------------------------------------------------

scenery::scenery(){
    // scenery constructor
    speed = 1.0;
//    int farClip = -2000;
//    int nearClip = 2000;
//    int sceneryLanes = 20;
//    float size = 100.0;
//    float widthRatio = 0.1;
//    float heightRatio = 0.5;
//    float spread = abs(farClip) + nearClip;
//    float minWidth = 3;
//    float minHeight = 3;
//    float boxbaseColor = ofRandom(50) + 10;
//    float colorOffset = 1;
//    float xPosition = ofRandom(sceneryLanes) * size;
//    boxColor = ofColor(boxbaseColor, boxbaseColor + ofRandom(colorOffset), boxbaseColor);
//    box.set(ofRandom(size * widthRatio)+ minWidth, ofRandom(size * heightRatio)+minHeight * ofRandom(xPosition/20.0), ofRandom(size)+ 2 * ofRandom(xPosition/20.0));
//    box.setPosition(- xPosition, box.getHeight()/2, ofRandom(spread));
//    for (int i =0;i < 6; i ++){
//        box.setSideColor(i, boxColor);
//
//    }
    setNewPosition();
}

//--------------------------------------------------------------

scenery::~scenery(){
    // destructor
}

//--------------------------------------------------------------

void scenery::draw(){
    
    box.draw();
   // box.drawWireframe();
   // box.drawVertices();
    
}

//--------------------------------------------------------------

void scenery::updateLocation(){
    int farClip = -sceneWidth/2;
    int nearClip = sceneWidth/2;
    int sceneryLanes = 20;
    float size = 100.0;
    
    if (box.getPosition().z <farClip){
        setNewPosition();
    }
    box.setPosition(box.getPosition().x, box.getPosition().y, box.getPosition().z - speed);
}

//--------------------------------------------------------------

void scenery::setNewPosition(){
    
    int farClip = -sceneWidth/2;
    int nearClip = sceneWidth/2;
    int sceneryLanes = 40;
    float size = 80.0;
    float widthRatio = 0.1;
    float heightRatio = 0.4;
    float spread = abs(farClip) + nearClip;
    float minWidth = 3;
    float minHeight = 3;
    float boxbaseColor = ofRandom(50) + 20;
    float colorOffset = 20;
    float xPosition = ofRandom(sceneryLanes) * size;
    boxColor = ofColor(boxbaseColor, boxbaseColor + ofRandom(colorOffset), boxbaseColor);
    box.set(ofRandom(size * widthRatio)+ minWidth, ofRandom(size * heightRatio)+minHeight * ofRandom(xPosition/20.0), ofRandom(size)+ 2 * ofRandom(xPosition/20.0));
    box.setPosition(- xPosition, box.getHeight()/2, ofRandom(spread)+spread/2);
    for (int i =0;i < 6; i ++){
        box.setSideColor(i, boxColor);
        
    }
}

//--------------------------------------------------------------
    
