#include "ofApp.h"

void ofApp::setup() {
    ofSetWindowTitle("NotGalaga");
    ofSetBackgroundColor(0, 0, 0);
    srand(static_cast<unsigned>(time(0)));
    font.load("arial.ttf", kFontSize);

    // load player
    ofLoadImage(player.fighter_texture_, "fighter.png");

	player.player_shots_ = 0;
    player.player_center_.first = ofGetWidth() / 2;
    player.player_center_.second = ofGetHeight() - (ofGetHeight() / 8);

	ofLoadImage(bullet.bullet_texture_, "bullet.png");

    // load demo bee
    ofLoadImage(demo_bee.texture_, "bee.png");

    demo_bee.enemy_center_.first = ofGetWidth() / 2;
    demo_bee.enemy_center_.second = ofGetHeight() / 8;

    ofLoadImage(demo_boss.texture_, "bossGalaga.png");

    demo_boss.enemy_center_.first = ofGetWidth() / 4;
    demo_boss.enemy_center_.second = ofGetHeight() / 3;

    // TODO: load player fire sound
    // player.player_fire.load("");
}

//--------------------------------------------------------------
void ofApp::update() {
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->bullet_center_.second -= 16;
        int second = bullets[i]->bullet_center_.second;
        if (second < 0) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            player.player_shots_--;
		}
    }
    // update the bullets fired
    // check for bullet, enemy collisions
    // check for player, enemy collisions
}

void ofApp::checkEnemyCollisions() {}

void ofApp::checkPlayerCollisions() {}

//--------------------------------------------------------------
void ofApp::draw() {
    player.fighter_texture_.draw(player.player_center_.first,
                                 player.player_center_.second);

    demo_bee.texture_.draw(demo_bee.enemy_center_.first,
                           demo_bee.enemy_center_.second);

    demo_boss.texture_.draw(demo_boss.enemy_center_.first,
                            demo_boss.enemy_center_.second);

    for (int i = 0; i < bullets.size(); i++) {
        int first = bullets[i]->bullet_center_.first;
        int second = bullets[i]->bullet_center_.second;
        bullets[i]->bullet_texture_.draw(first, second);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == OF_KEY_LEFT) {
        player.player_center_.first -= 8;
    }

    if (key == OF_KEY_RIGHT) {
        player.player_center_.first += 8;
    }

    if (key == OF_KEY_UP) {
        if (player.player_shots_ < 2) {
            //bullets.push_back();
            Bullet* current_bullet = new Bullet();
            *current_bullet = bullet;
            current_bullet->bullet_center_ = player.player_center_;
            current_bullet->bullet_center_.second += player.kFighterWidth / 2;
            bullets.push_back(current_bullet);
            player.player_shots_++;
		}
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
