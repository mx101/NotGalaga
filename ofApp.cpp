#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() { 
	ofSetWindowTitle("NotGalaga");
    srand(static_cast<unsigned>(time(0)));

	font.load("arial.ttf", kFontSize); 
	ofLoadImage(player.fighter_texture, "fighter.png");
    ofLoadImage(player.captured_fighter_texture, "capturedFighter.png");

	player.player_center.first = ofGetWidth() / 2;
    player.player_center.second = ofGetHeight() - (ofGetHeight() / 8);

	//TODO: load player fire sound
	//player.player_fire.load("");
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
    font.drawString("The FitnessGram Pacer test is a multi-stage aerobic", 155, 92);

	player.fighter_texture.draw(player.player_center.first, player.player_center.second);

    //ofNoFill();  // will not fill shapes after this line is called, line is
                 // still a line
    // note there also exists an ofFill() function

    ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() / 2, 50, 25);

    ofDrawLine(ofGetWidth() / 2, 30, 200, 200);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
