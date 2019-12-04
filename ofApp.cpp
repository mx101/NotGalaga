#include "ofApp.h"

void ofApp::setup() {
    ofSetWindowTitle("NotGalaga");
	
	// set background color to black
    ofSetBackgroundColor(0, 0, 0);
    srand(static_cast<unsigned>(time(0)));
    font.load("arial.ttf", kFontSize);

	left_pressed = false;
    right_pressed = false;
    shoot_pressed = false;

    // load player
    ofLoadImage(player.fighter_texture_, "fighter.png");

    player.player_shots_ = 0;
    player.player_lives_ = 3;
    player.alive_ = true;
    player.player_center_.first = ofGetWidth() / 2;
    player.player_center_.second = ofGetHeight() - (ofGetHeight() / 8);

    ofLoadImage(bullet.bullet_texture_, "bullet.png");

    // load demo bee
    ofLoadImage(demo_bee.enemy_texture_, "bee.png");

    demo_bee.enemy_center_.first = ofGetWidth() / 2;
    demo_bee.enemy_center_.second = ofGetHeight() / 8;

    ofLoadImage(demo_boss.enemy_texture_, "bossGalaga.png");

    demo_boss.enemy_center_.first = ofGetWidth() / 4;
    demo_boss.enemy_center_.second = ofGetHeight() / 3;

    // TODO: load player fire sound
    player.player_fire.load("playerFire.mp3");
}

//--------------------------------------------------------------
void ofApp::update() {
    if (left_pressed) {
        player.player_center_.first -= kFighterMoveSpeed;
        left_pressed = false;
	}

	if (right_pressed) {
        player.player_center_.first += kFighterMoveSpeed;
        right_pressed = false;
    }

	if (shoot_pressed) {
        ShootBullet();
        shoot_pressed = false;
    }

    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->bullet_center_.second -= kBulletSpeed;
        int second = bullets[i]->bullet_center_.second;
        if (second < 0) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            player.player_shots_--;
        }
    }

	for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->enemy_center_.second += kEnemyMoveSpeed;
        if (enemies[i]->enemy_center_.second > ofGetHeight()) {
            enemies[i]->enemy_center_.second = kEnemySpawnHeight;
		}
    }

	CheckEnemyCollisions();
    CheckPlayerCollisions();
}

void ofApp::ShootBullet() {
    if (player.player_shots_ < kLegalBulletsMax) {
        Bullet* current_bullet = new Bullet();
        *current_bullet = bullet;
        current_bullet->bullet_center_ = player.player_center_;
        current_bullet->bullet_center_.first +=
            kFighterWidth / 2 - (kBulletWidth / 2);
        current_bullet->bullet_center_.second -= kFighterWidth / 8;
        bullets.push_back(current_bullet);
        player.player_shots_++;
        player.player_fire.play();
    }
}

void ofApp::CheckEnemyCollisions() {
    // This looks like an O(n^2) operation but bullets will always contain at most 2 elements

	for (int j = 0; j < enemies.size(); j++) {
        int enemy_first = enemies[j]->enemy_center_.first;
        int enemy_second = enemies[j]->enemy_center_.second;
        glm::vec2 enemy_center(enemy_first, enemy_second);
        ofRectangle current_enemy(enemy_center, kEnemyWidth, kEnemyHeight);

        for (int i = 0; i < bullets.size(); i++) {
            int bullet_first = bullets[i]->bullet_center_.first;
            int bullet_second = bullets[i]->bullet_center_.second;
            glm::vec2 bullet_center(bullet_first, bullet_second);
            ofRectangle current_bullet(bullet_center, kBulletWidth, kBulletHeight);

			if (current_enemy.intersects(current_bullet)) {
                delete enemies[j];
                enemies.erase(enemies.begin() + j);

                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                player.player_shots_--;
			}
        }
    }
    
}

void ofApp::CheckPlayerCollisions() {
    for (int j = 0; j < enemies.size(); j++) {
        int enemy_first = enemies[j]->enemy_center_.first;
        int enemy_second = enemies[j]->enemy_center_.second;
        glm::vec2 enemy_center(enemy_first, enemy_second);
        ofRectangle current_enemy(enemy_center, kEnemyWidth, kEnemyHeight);

		int player_first = player.player_center_.first;
        int player_second = player.player_center_.second;
        glm::vec2 player_center(player_first, player_second);
        ofRectangle player_rect(player_center, kFighterWidth, kFighterHeight);

		if (current_enemy.intersects(player_rect)) {
            delete enemies[j];
            enemies.erase(enemies.begin() + j);

			player.player_lives_--;
            player.alive_ = false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    player.fighter_texture_.draw(player.player_center_.first, player.player_center_.second);

    for (int i = 0; i < bullets.size(); i++) {
        int first = bullets[i]->bullet_center_.first;
        int second = bullets[i]->bullet_center_.second;
        bullets[i]->bullet_texture_.draw(first, second);
    }

    for (int i = 0; i < enemies.size(); i++) {
        int first = enemies[i]->enemy_center_.first;
        int second = enemies[i]->enemy_center_.second;
        enemies[i]->enemy_texture_.draw(first, second);
    }
}

void ofApp::CreateEnemy(int x, int y, int type) {
    Enemy* current_enemy = new Enemy();
    *current_enemy = demo_bee;
    current_enemy->enemy_center_.first = x;
    current_enemy->enemy_center_.second = y;
    enemies.push_back(current_enemy);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (player.alive_) {
        if (key == OF_KEY_LEFT && player.player_center_.first > 0) {
            left_pressed = true;
        }

        if (key == OF_KEY_RIGHT &&
            (player.player_center_.first + kFighterWidth) < ofGetWidth()) {
            right_pressed = true;
        }

        if (key == OF_KEY_UP) {
            shoot_pressed = true;
        }
	}
    

    int upper_key = toupper(key);

	if (upper_key == 'R') {
        player.alive_ = true;
    }

    if (upper_key == 'E') {
        CreateEnemy(player.player_center_.first, demo_bee.enemy_center_.second, 1);
    }
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
