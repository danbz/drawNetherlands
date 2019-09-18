/*
 Project Title: drawNetherlands : clouds
 Description:
 ©Daniel Buzzo 2019
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */


#include "ofApp.h"

#define sceneWidth 4000
#define sceneDepth 2000
#define laneWidth 6
#define cloudSize 100
#define cloudCeiling 500

//--------------------------------------------------------------
void ofApp::setup(){
    int maxClouds = 100;
    int maxScenery = 100;
    //sceneWidth = sceneDepth = 4000;
    b_showGui = false;
    
    for (int i=0;i<maxClouds;i++){
        cloud newCloud;
        clouds.push_back(newCloud);
    }
    setCloudParents();
    
    for (int i=0;i<maxScenery;i++){
        scenery newScenery;
        landscape.push_back(newScenery);
    }
    
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
    
    ground.set( sceneWidth,  sceneWidth, 1 );
    ground.setPosition( -sceneWidth/2, 0, 0 );
    ground.rotateDeg(90, 1, 0, 0);
    ofColor groundColor = (175, ofRandom(80)+175, 175);
    for (int i =0;i < 6; i ++){
        ground.setSideColor(i, groundColor);
        
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0; i < clouds.size(); i++){
        clouds[i].updateLocation();
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
    
    // ground.draw();
    //road.draw();
    for (int i=0; i < clouds.size(); i++){
        clouds[i].draw();
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

cloud::cloud(){
    // cloud constructor
    int farClip = -sceneWidth/2;
    int nearClip = sceneWidth/2;
    float widthRatio = 0.6;
    float heightRatio = 0.5;
    float maxSpeed = 0.5;
    float minSpeed = 0.01;
//    float minWidth = 10;
//    float minHeight = 3;
    
    speed = ofRandom(maxSpeed)+minSpeed;
    
    // new cloud routine
    float cloud_subRatio = 0.9;
    float min_width = 10;
    float max_width = 40;
    float min_height= 10;
    float max_height = 20;
    float min_depth = 20;
    float max_depth = 40.0;
    float sky_width =0;
    float sky_depth =0;
    float subBoxLevels = 4;
    float pos_x = ofRandom(-sky_width/2, sky_width/2);
    float pos_y = 0;
    float pos_z = ofRandom(-sky_depth/2, sky_depth/2);
    float width = ofRandom(min_width, max_width);
    float height = ofRandom(min_height, max_height);
    float depth = ofRandom(min_depth, max_depth);
    // create parent box
    cout << "parent of subBox  is " << subBox.getParent()  << endl;
    parentBox.set(width, height, depth);
    parentBox.setGlobalPosition( - ofRandom(sceneDepth) , cloudCeiling+ ofRandom(-cloudCeiling/10.0, cloudCeiling/10.0), farClip);
    ofColor boxColor = ofColor(100, 100, ofRandom(55)+200); // pale blue-ish
    for (int i =0;i < 6; i ++){
        parentBox.setSideColor(i, boxColor);
    }
    // boxes.push_back(parentBox); // push parent box to vector of all boxes
    cout << "constructed parent box " << endl;
    
    for (int i=0;i<subBoxLevels; i++){
        // create sub boxes
        ofBoxPrimitive newBox;
        
        float ratio = ofRandom(cloud_subRatio);
        newBox.set(width * ratio, height * ratio, depth * ratio);
        int corner = ofRandom(5);
        switch (corner) {
            case 0: //  sub box on north side of parent
                newBox.move(pos_x , pos_y  , pos_z - depth + depth * ratio /2);
                break;
            case 1: // sub box on south side of parent
                newBox.move(pos_x , pos_y  , pos_z + depth - depth * ratio /2);
                break;
            case 2: // sub box on east side of parent
                newBox.move(pos_x + width - width * ratio /2, pos_y  , pos_z) ;
                break;
            case 3: // sub box on west side of parent
                newBox.move(pos_x - width + width * ratio /2, pos_y  , pos_z) ;
                break;
            case 4: // sub box on top side of parent
                newBox.move(pos_x , pos_y + height - height * ratio /2  , pos_z) ;
                break;
            case 5: // sub box on bottom side of parent
                newBox.move(pos_x , pos_y - height + height * ratio /2  , pos_z) ;
                break;
    
            default:
                break;
        }
         boxColor = ofColor(200, 200, ofRandom(55)+200); // pale blue-ish
       // boxColor = ofColor(200, 0, 0); // red debug
        for (int i =0;i < 6; i ++){
            newBox.setSideColor(i, boxColor);
        }
        boxes.push_back(newBox);
    }
}

//--------------------------------------------------------------

cloud::~cloud(){
    // cloud destructor
}

//--------------------------------------------------------------

void cloud::draw(){
    // box.draw();
    // box.drawWireframe();
    parentBox.drawWireframe();
    for (int i=0; i<boxes.size(); i++){
        boxes[i].drawWireframe();
        // cout << "draw box " << endl;
    }
}

//--------------------------------------------------------------

void cloud::updateLocation(){
    int farClip = -sceneWidth/2;
    int nearClip = sceneWidth/2;
//    if (box.getPosition().z > nearClip){
//        box.setPosition( - ofRandom(sceneDepth), box.getPosition().y, farClip);
//    }
//    box.setPosition(box.getPosition().x, box.getPosition().y, box.getPosition().z + speed);
    
//    if (boxes[0].getGlobalPosition().z > nearClip){
//        boxes[0].move( - ofRandom(sceneDepth), box.getGlobalPosition().y, farClip);
//    }
//    boxes[0].move(0, 0, speed);
    
//    if (parentBox.getGlobalPosition().z > nearClip){
//        parentBox.move( - ofRandom(sceneDepth), parentBox.getGlobalPosition().y, farClip);
//    }
    parentBox.move(0, 0, speed);
}

//--------------------------------------------------------------
void cloud::setCloudParent(){
    // set parent for all sub boxes
    for (int i=0; i< boxes.size(); i++){
        boxes[i].setParent(parentBox);
        cout << "set parent for subbox " << i << endl;
    }
}
//--------------------------------------------------------------


scenery::scenery(){
    // scenery constructor
    speed = 1.0;
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
    float size = 500.0;
    float widthRatio = 1;
    float heightRatio = 0.1;
    float spread = abs(farClip) + nearClip;
    float minWidth = 3;
    float minHeight = 0.1;
    float boxbaseColor = ofRandom(50) + 20;
    float colorOffset = 20;
    float xPosition =  ofRandom(sceneDepth);
    boxColor = ofColor(boxbaseColor, boxbaseColor + ofRandom(colorOffset), boxbaseColor);
    box.set(ofRandom(size * widthRatio)+ minWidth, ofRandom(size * heightRatio)+minHeight, ofRandom(size)+ 2 );
    box.setPosition(- xPosition, box.getHeight()/2, ofRandom(spread)+spread/2);
    for (int i =0;i < 6; i ++){
        box.setSideColor(i, boxColor);
        
    }
}

//--------------------------------------------------------------

void ofApp::setCloudParents(){
    for (int j =0; j < clouds.size(); j++){
        clouds[j].setCloudParent();
       
    }
    
}
