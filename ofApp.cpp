#include "ofApp.h"

void ofApp::setup() {
  ofSetWindowTitle("NotGalaga");
  ofSetBackgroundColor(0, 0, 0);
  srand(static_cast<unsigned>(time(0)));
  font.load("arial.ttf", kFontSize); 

  // load player
  ofLoadImage(player.fighter_texture, "fighter.png");

  player.player_center.first = ofGetWidth() / 2;
  player.player_center.second = ofGetHeight() - (ofGetHeight() / 8);

  // load demo bee
  ofLoadImage(demo_bee.texture_, "bee.png");

  demo_bee.enemy_center_.first = ofGetWidth() / 2;
  demo_bee.enemy_center_.second = ofGetHeight() / 8;

  ofLoadImage(demo_boss.texture_, "bossGalaga.png");

  demo_boss.enemy_center_.first = ofGetWidth() / 4;
  demo_boss.enemy_center_.second = ofGetHeight() / 3;
  
  //TODO: load player fire sound
  //player.player_fire.load("");
}

//--------------------------------------------------------------
void ofApp::update() {

  // update the bullets fired
  // check for bullet, enemy collisions
  // check for player, enemy collisions

}

void checkEnemyCollisions() {

}

void checkPlayerCollisions() {

}

//--------------------------------------------------------------
void ofApp::draw() {

  player.fighter_texture.draw(player.player_center.first, player.player_center.second);

  demo_bee.texture_.draw(demo_bee.enemy_center_.first, demo_bee.enemy_center_.second);

  demo_boss.texture_.draw(demo_boss.enemy_center_.first, demo_boss.enemy_center_.second);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == OF_KEY_LEFT) {
    player.player_center.first -= 8;
  }

  if (key == OF_KEY_RIGHT) {
    player.player_center.first += 8;
  }

  // these commands are not supported in the Original Galaga
  /*if (key == OF_KEY_UP) {
    player.player_center.second -= 5;
  }
  if (key == OF_KEY_DOWN) {
    player.player_center.second += 5;
  }*/

}

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
