/*
 Project Title: drawNetherlands : clouds
 Description:
 ©Daniel Buzzo 2019
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */


#include "ofApp.h"

#define sceneWidth 8000
#define sceneDepth 8000
#define laneWidth 6
#define cloudSize 400
#define cloudCeiling 500

//--------------------------------------------------------------
void ofApp::setup(){
    int maxClouds = 1000;
    int maxScenery = 4000;
    b_showGui = false;
    
    for (int i=0;i<maxClouds;i++){
        cloud newCloud;
        ofVec3f newCloudPosition;
        newCloudPosition.set(ofRandom(-sceneWidth/2, sceneWidth/2), cloudCeiling, ofRandom(-sceneDepth/2, sceneDepth/2));
        newCloud.setPosition(newCloudPosition);
        clouds.push_back(newCloud);
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
    float maxSpeed = 0.1;
    float minSpeed = 0.01;
    
    speed = ofRandom(maxSpeed)+minSpeed;
    // new cloud routine
    float cloud_subRatio = 0.9;
    float min_width = 10;
    float max_width = 60;
    float min_height= 10;
    float max_height = 20;
    float min_depth = 20;
    float max_depth = 60.0;
    float subBoxLevels = 5;
    float pos_x = 0;
    float pos_y = 0;
    float pos_z = 0;
    float width = ofRandom(min_width, max_width);
    float height = ofRandom(min_height, max_height);
    float depth = ofRandom(min_depth, max_depth);
    // create parent box
    ofBoxPrimitive newBox;
    newBox.setMode(OF_PRIMITIVE_TRIANGLES);
    newBox.set(width, height, depth);
    //newBox.setGlobalPosition( - ofRandom(sceneDepth) , cloudCeiling+ ofRandom(-cloudCeiling/10.0, cloudCeiling/10.0), farClip);
    ofColor boxColor = ofColor(180, 180, ofRandom(55)+180); // pale blue-ish
    for (int i =0;i < 6; i ++){
        newBox.setSideColor(i, boxColor);
    }
    cloudMesh.append(newBox.getMesh());
    
    for (int i=0;i<subBoxLevels; i++){ // create sub boxes
        ofBoxPrimitive newBox;
        newBox.setResolution(1);
        ofMesh newMesh;
        ofVec3f transformVector;
        float ratio = ofRandom(cloud_subRatio);
        newBox.set(width * ratio, height * ratio, depth * ratio);
        int corner = ofRandom(5);
        switch (corner) {
            case 0: //  sub box on south side of parent
                transformVector = *new ofVec3f(pos_x , pos_y  , pos_z  + depth/2 + depth * ratio /2);
                break;
            case 1: // sub box on north side of parent
                transformVector = *new ofVec3f(pos_x , pos_y  , pos_z - depth/2 - depth * ratio /2);
                break;
            case 2: // sub box on east side of parent
                transformVector = *new ofVec3f(pos_x + (width/2) + width * (ratio /2), pos_y  , pos_z) ;
                break;
            case 3: // sub box on west side of parent
                transformVector = *new ofVec3f(pos_x - (width/2) - width * (ratio /2), pos_y  , pos_z) ;
                break;
            case 4: // sub box on top side of parent
                transformVector = *new ofVec3f(pos_x , pos_y + height/2 + height * ratio /2  , pos_z) ;
                break;
            case 5: // sub box on bottom side of parent
                transformVector = *new ofVec3f(pos_x , pos_y + height/2 - height * ratio /2  , pos_z) ;
                break;
                
            default:
                break;
                
        }
        boxColor = ofColor(200, 200, ofRandom(55)+200); // pale blue-ish
        for (int i =0;i < 6; i ++){
            newBox.setSideColor(i, boxColor);
        }
        newMesh=newBox.getMesh();
        for (int x=0; x< newMesh.getNumVertices();x++){
            newMesh.getVertices()[x] += transformVector;
        }
        cloudMesh.append(newMesh);
    }
    cloudVboMesh=cloudMesh;
}

//--------------------------------------------------------------

cloud::~cloud(){
    // cloud destructor
}

//--------------------------------------------------------------

void cloud::draw(){
  
    ofPushMatrix();
    ofTranslate(getPosition());
   cloudMesh.draw();
    //cloudVboMesh.draw();
    ofPopMatrix();

}

//--------------------------------------------------------------

void cloud::setPosition(ofVec3f newPosition){
    cloudPosition = newPosition;
}
//--------------------------------------------------------------
void cloud::setPosition(float x, float y, float z ){
    ofVec3f newPosition;
    newPosition.set(x,y,z);
    setPosition(newPosition);
}
//--------------------------------------------------------------
ofVec3f cloud::getPosition(){
    return cloudPosition;
}

//--------------------------------------------------------------

void cloud::updateLocation(){
    int farClip = -sceneWidth/2;
    int nearClip = sceneWidth/2;
    if (getPosition().z > nearClip){
        setPosition( - ofRandom(-sceneDepth/2, sceneDepth/2), getPosition().y, farClip);
    }
    setPosition(getPosition().x, getPosition().y, getPosition().z + speed);
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
    float xPosition =  ofRandom(-sceneDepth/2, sceneDepth/2);
    boxColor = ofColor(boxbaseColor, boxbaseColor + ofRandom(colorOffset), boxbaseColor);
    box.set(ofRandom(size * widthRatio)+ minWidth, ofRandom(size * heightRatio)+minHeight, ofRandom(size)+ 2 );
    box.setPosition(- xPosition, box.getHeight()/2, ofRandom(spread)+spread/2);
    for (int i =0;i < 6; i ++){
        box.setSideColor(i, boxColor);
        
    }
}

//--------------------------------------------------------------

