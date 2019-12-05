#include "ofApp.h"

void ofApp::setup() {
    ofSetWindowTitle("NotGalaga");

    // set background color to black, because it's space
    ofSetBackgroundColor(0, 0, 0);
    srand(static_cast<unsigned>(time(0)));

    game_running_ = true;
    high_score_ = 30000;
    waves_ = 0;

    left_pressed = false;
    right_pressed = false;

	LoadData();

	//condense below lines into some restartGame method
    player.player_shots_ = 0;
    player.player_lives_ = 3;
    player.alive_ = true;
    player.player_center_.first = kGameWindowWidth / 2;
    player.player_center_.second = kGameWindowHeight - (kGameWindowHeight / 8);

	bee_.enemy_center_.first = kGameWindowWidth / 2;
    bee_.enemy_center_.second = kGameWindowHeight / 8;

	moth_.enemy_center_.first = kGameWindowWidth / 4;
    moth_.enemy_center_.second = kGameWindowHeight / 3;

	boss_.enemy_center_.first = kGameWindowWidth / 4;
    boss_.enemy_center_.second = kGameWindowHeight / 3;

    score_ = 0;
}

void ofApp::LoadData() {

	// load font data
	message_font_.load("galaga.ttf", kMessageSize);
    side_font_.load("galaga.ttf", kSideSize);

    // load player
    ofLoadImage(player.fighter_texture_, "fighter.png");
    player.player_fire.load("playerFire.mp3");
    
	// load bullets
	ofLoadImage(player_bullet_.bullet_texture_, "bullet.png");
    ofLoadImage(enemy_bullet_.bullet_texture_, "enemyBullet.png");

    // load enemy data
    ofLoadImage(bee_.enemy_texture_, "bee.png");
    ofLoadImage(boss_.enemy_texture_, "bossGalaga.png");
    ofLoadImage(moth_.enemy_texture_, "moth.png");
}

//--------------------------------------------------------------
void ofApp::update() {
    if (game_running_) {
        if (player.alive_) {
            if (left_pressed) {
                player.player_center_.first -= kFighterMoveSpeed;
            }

            if (right_pressed) {
                player.player_center_.first += kFighterMoveSpeed;
            }
        }

        for (int i = 0; i < player_bullets_.size(); i++) {
            player_bullets_[i]->bullet_center_.second += kPlayerBulletSpeed;
            int second = player_bullets_[i]->bullet_center_.second;

            if (second < 0) {
                delete player_bullets_[i];
                player_bullets_.erase(player_bullets_.begin() + i);
                player.player_shots_--;
            }
        }

        for (int i = 0; i < enemies_.size(); i++) {
            enemies_[i]->enemy_center_.second += kEnemyMoveSpeed;

            if (enemies_[i]->enemy_center_.second > kGameWindowHeight) {
                enemies_[i]->enemy_center_.second = kEnemySpawnHeight;
            }
        }

		for (int i = 0; i < enemy_bullets_.size(); i++) {
            enemy_bullets_[i]->bullet_center_.second += kEnemyBulletSpeed;
            int second = enemy_bullets_[i]->bullet_center_.second;

            if (second > kGameWindowHeight) {
                delete enemy_bullets_[i];
                enemy_bullets_.erase(enemy_bullets_.begin() + i);
            }
        }

        CheckEnemyCollisions();

        if (player.alive_) {
            CheckPlayerCollisions();
        }

    } else {
        DrawScoreboard();
    }
}

void ofApp::DrawScoreboard() {
    // items to display, high score of current session, score of current game
    // option to restart game
    // remember to delete the remaining enemies from memory
}

void ofApp::DrawSideboard() {
    // draw the line of separation between gameplay and sideboard
    glm::vec2 top_border(kGameWindowWidth, 0);
    glm::vec2 bottom_border(kGameWindowWidth, kGameWindowHeight);
    ofDrawLine(top_border, bottom_border);

    string lives_message = "Lives: " + to_string(player.player_lives_);

    int side_life_width = kGameWindowWidth + (kSideboardWidth / 2) -
                          side_font_.stringWidth(lives_message) / 2;

    int side_life_height = (kGameWindowHeight / 2) + kSideboardSpacing;

    side_font_.drawString(lives_message, side_life_width, side_life_height);

    string score_message = "Score: " + to_string(score_);

    int side_score_width = kGameWindowWidth + (kSideboardWidth / 2) -
                           side_font_.stringWidth(score_message) / 2;

    int side_score_height = (kGameWindowHeight / 2) - kSideboardSpacing;

    side_font_.drawString(score_message, side_score_width, side_score_height);

    string wave_message = "Wave: " + to_string(waves_);

    int side_wave_width = kGameWindowWidth + (kSideboardWidth / 2) -
                          side_font_.stringWidth(wave_message) / 2;

    int side_wave_height = (kGameWindowHeight / 2) + (2 * kSideboardSpacing);

    side_font_.drawString(wave_message, side_wave_width, side_wave_height);
}

void ofApp::DrawGameDead() {
    ofImage explosion("explosion.gif");
    explosion.draw(player.player_center_.first, player.player_center_.second);

    string death_message;

    if (player.player_lives_ > 0) {
        death_message = "Life lost! Press R to respawn";
    } else {
        death_message = "Life lost! Game Over";
        game_running_ = false;
    }

    // This is the RGB for Illini Orange
    ofSetColor(232, 74, 39);

    int center_width =
        (kGameWindowWidth / 2) - (message_font_.stringWidth(death_message) / 2);

    int center_height = kGameWindowHeight / 2;

    message_font_.drawString(death_message, center_width, center_height);
}

void ofApp::ShootBullet(std::pair<int, int> center, int velocity, bool player_shot) {
    // possible streamlining improvement: have this function take in a start
    // point and velocity that way we can reuse for shooting enemy bullets

    Bullet* current_bullet = new Bullet();

	if (player_shot) {
        *current_bullet = player_bullet_;
        current_bullet->bullet_center_ = center;
        current_bullet->bullet_center_.first += kFighterWidth / 2 - (kBulletWidth / 2);
        current_bullet->bullet_center_.second -= kFighterWidth / 8;

		player_bullets_.push_back(current_bullet);
        player.player_shots_++;
        player.player_fire.play();

    } else {
        *current_bullet = enemy_bullet_;
        current_bullet->bullet_center_ = center;
        current_bullet->bullet_center_.first += kEnemyWidth / 2 - (kBulletWidth / 2);

		enemy_bullets_.push_back(current_bullet);
	}   

	current_bullet->bullet_velocity_ = velocity;
}

void ofApp::GenerateWave() {
    // load in the first 44 aliens
    // note the additional if checks for moths and bees because they form two
    // rows
    int x = kStartX;
    int y = kStartY;
    int separation = 10;

    for (int i = 0; i < kEnemyCount; i++) {
		// create bees for enemies [0,19]
        Enemy* curr_enemy;

        if (i < kFirstRowMothIdx) {
            if (i < kSecondRowBeeIdx) {
                curr_enemy = CreateEnemy(x, y, 0);
                x += curr_enemy->enemy_width_ + separation;

            } else {
                if (i == kSecondRowBeeIdx) {
                    x = kStartX;
                    y += kEnemySpacing;
				}
                
                curr_enemy = CreateEnemy(x, y, 0);
                x += curr_enemy->enemy_width_ + separation;
            }

			
		// create moths for enemies [20, 35]
        } else if (i < kFirstBossIdx) {
            if (i < kSecondRowMothIdx) {
                curr_enemy = CreateEnemy(x, y, 1);
            } else {
                curr_enemy = CreateEnemy(x, y, 1);
            }

		// create boss galaga for enemies [36, 39]
        } else {
            curr_enemy = CreateEnemy(x, y, 2);
        }


    }

    waves_++;
}

void ofApp::CheckEnemyCollisions() {
    // This looks like an O(n^2) operation but bullets will always contain at
    // most 2 elements

    for (int j = 0; j < enemies_.size(); j++) {
        int enemy_first = enemies_[j]->enemy_center_.first;
        int enemy_second = enemies_[j]->enemy_center_.second;
        glm::vec2 enemy_center(enemy_first, enemy_second);
        ofRectangle current_enemy(enemy_center, kEnemyWidth, kEnemyHeight);

        for (int i = 0; i < player_bullets_.size(); i++) {
            int bullet_first = player_bullets_[i]->bullet_center_.first;
            int bullet_second = player_bullets_[i]->bullet_center_.second;
            glm::vec2 bullet_center(bullet_first, bullet_second);
            ofRectangle current_bullet(bullet_center, kBulletWidth,
                                       kBulletHeight);

            if (current_enemy.intersects(current_bullet)) {
                delete enemies_[j];
                enemies_.erase(enemies_.begin() + j);

                delete player_bullets_[i];
                player_bullets_.erase(player_bullets_.begin() + i);
                player.player_shots_--;
            }
        }
    }
}

void ofApp::CheckPlayerCollisions() {
    int player_first = player.player_center_.first;
    int player_second = player.player_center_.second;
    glm::vec2 player_center(player_first, player_second);
    ofRectangle player_rect(player_center, kFighterWidth, kFighterHeight);

    // check physical player/enemy collision
    for (int j = 0; j < enemies_.size(); j++) {
        int enemy_first = enemies_[j]->enemy_center_.first;
        int enemy_second = enemies_[j]->enemy_center_.second;
        glm::vec2 enemy_center(enemy_first, enemy_second);
        ofRectangle current_enemy(enemy_center, kEnemyWidth, kEnemyHeight);

        if (current_enemy.intersects(player_rect)) {
            delete enemies_[j];
            enemies_.erase(enemies_.begin() + j);

            player.player_lives_--;
            player.alive_ = false;
        }
    }

    // if player is alive after direct player/enemy collision check,
    // check for enemy bullet collision with player
    if (player.alive_) {
        for (int i = 0; i < enemy_bullets_.size(); i++) {
            int enemy_first = enemy_bullets_[i]->bullet_center_.first;
            int enemy_second = enemy_bullets_[i]->bullet_center_.second;
            glm::vec2 enemy_center(enemy_first, enemy_second);
            ofRectangle current_enemy(enemy_center, kBulletWidth, kBulletHeight);

			if (current_enemy.intersects(player_rect)) {
                delete enemy_bullets_[i];
                enemy_bullets_.erase(enemy_bullets_.begin() + i);

                player.player_lives_--;
                player.alive_ = false;
            }
		}
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    DrawSideboard();

    if (!player.alive_) {
        // add additional state here for whether the player is out of lives
        // if (player.player_lives_ > 0) {
        DrawGameDead();
        //} else {
        //}
    } else {
        player.fighter_texture_.draw(player.player_center_.first,
                                     player.player_center_.second);

        for (int i = 0; i < player_bullets_.size(); i++) {
            int first = player_bullets_[i]->bullet_center_.first;
            int second = player_bullets_[i]->bullet_center_.second;
            player_bullets_[i]->bullet_texture_.draw(first, second);
        }

        for (int i = 0; i < enemies_.size(); i++) {
            int first = enemies_[i]->enemy_center_.first;
            int second = enemies_[i]->enemy_center_.second;
            enemies_[i]->enemy_texture_.draw(first, second);
        }

		for (int i = 0; i < enemy_bullets_.size(); i++) {
            int first = enemy_bullets_[i]->bullet_center_.first;
            int second = enemy_bullets_[i]->bullet_center_.second;
            enemy_bullets_[i]->bullet_texture_.draw(first, second);
        }
    }
}

Enemy * ofApp::CreateEnemy(int x, int y, int type) {
	
    Enemy* current_enemy = new Enemy();
    if (type == 0) {
        *current_enemy = bee_; 
	} else if (type == 1) {
        *current_enemy = moth_;
    } else if (type == 2) {
        *current_enemy = boss_;
	}
        
	current_enemy->enemy_center_.first = x;
    current_enemy->enemy_center_.second = y;
    current_enemy->formation_pos_.first = x;
    current_enemy->formation_pos_.second = y;
    enemies_.push_back(current_enemy);
    current_enemy->enemy_width_ = kEnemyWidth;

	// use wave number mod something else to determine if an enemy should shoot
    if (std::rand() % 5 == 0) {
        ShootBullet(current_enemy->enemy_center_, kEnemyBulletSpeed, false);
	}
	

	return current_enemy;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (player.alive_) {
        if (key == OF_KEY_LEFT && player.player_center_.first > 0) {
            left_pressed = true;
        }

        if (key == OF_KEY_RIGHT &&
            (player.player_center_.first + kFighterWidth) < kGameWindowWidth) {
            right_pressed = true;
        }

        if (key == OF_KEY_UP && player.player_shots_ < kLegalBulletsMax) {
            ShootBullet(player.player_center_, kPlayerBulletSpeed, true);
        }
    }

    int upper_key = toupper(key);

    if (upper_key == 'R' && !player.alive_) {
        RevivePlayer();
    }

    if (upper_key == 'E') {
        GenerateWave();
		//CreateEnemy(player.player_center_.first, bee_.enemy_center_.second, 0);
    }
}

void ofApp::RevivePlayer() {
    player.alive_ = true;
    player.player_center_.first = kGameWindowWidth / 2;

    ofSetColor(255, 255, 255);
    ofSetBackgroundColor(0, 0, 0);
}

void ofApp::ReturnToFormation() {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if (key == OF_KEY_LEFT) {
		left_pressed = false;
	}

	if (key == OF_KEY_RIGHT) {
		right_pressed = false;
	}
}

////--------------------------------------------------------------
//void ofApp::mouseMoved(int x, int y) {}
//
////--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button) {}
//
////--------------------------------------------------------------
//void ofApp::mousePressed(int x, int y, int button) {}
//
////--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button) {}
//
////--------------------------------------------------------------
//void ofApp::mouseEntered(int x, int y) {}
//
////--------------------------------------------------------------
//void ofApp::mouseExited(int x, int y) {}
//
////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h) {}
//
////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg) {}
//
////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo) {}
