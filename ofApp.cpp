#include "ofApp.h"

void ofApp::setup() {
    ofSetWindowTitle("NotGalaga");
	
	// set background color to black, because it's space
    ofSetBackgroundColor(0, 0, 0);
    srand(static_cast<unsigned>(time(0)));

	game_running_ = true;

    message_font_.load("galaga.ttf", kMessageSize);
    side_font_.load("galaga.ttf", kSideSize);

	left_pressed = false;
    right_pressed = false;
    shoot_pressed = false;

    // load player
    ofLoadImage(player.fighter_texture_, "fighter.png");

    player.player_shots_ = 0;
    player.player_lives_ = 3;
    player.alive_ = true;
    player.player_center_.first = kGameWindowWidth / 2;
    player.player_center_.second = kGameWindowHeight - (kGameWindowHeight / 8);
    
	score_ = 0;

    ofLoadImage(player_bullet.bullet_texture_, "bullet.png");

	ofLoadImage(enemy_bullet.bullet_texture_, "enemyBullet.png");

    // load demo bee
    ofLoadImage(demo_bee.enemy_texture_, "bee.png");

    demo_bee.enemy_center_.first = kGameWindowWidth / 2;
    demo_bee.enemy_center_.second = kGameWindowHeight / 8;

    ofLoadImage(demo_boss.enemy_texture_, "bossGalaga.png");

    demo_boss.enemy_center_.first = kGameWindowWidth / 4;
    demo_boss.enemy_center_.second = kGameWindowHeight / 3;

    // TODO: load player fire sound
    player.player_fire.load("playerFire.mp3");
}

//--------------------------------------------------------------
void ofApp::update() {
    if (game_running_) {
        if (player.alive_) {
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
        }

        for (int i = 0; i < player_bullets.size(); i++) {
            player_bullets[i]->bullet_center_.second -= kBulletSpeed;
            int second = player_bullets[i]->bullet_center_.second;
            if (second < 0) {
                delete player_bullets[i];
                player_bullets.erase(player_bullets.begin() + i);
                player.player_shots_--;
            }
        }

        for (int i = 0; i < enemies.size(); i++) {
            enemies[i]->enemy_center_.second += kEnemyMoveSpeed;
            if (enemies[i]->enemy_center_.second > kGameWindowHeight) {
                enemies[i]->enemy_center_.second = kEnemySpawnHeight;
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

	// implement wave number display
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
    
    ofSetColor(232, 74, 39);
	
	int center_width = (kGameWindowWidth / 2) -
                       (message_font_.stringWidth(death_message) / 2);

	int center_height = kGameWindowHeight / 2;

    message_font_.drawString(death_message, center_width,
                                 center_height);
}

void ofApp::ShootBullet() {
	//possible streamlining improvement: have this function take in a start point and velocity
	//that way we can reuse for shooting enemy bullets
    
    Bullet* current_bullet = new Bullet();
    *current_bullet = player_bullet;
    current_bullet->bullet_center_ = player.player_center_;
    current_bullet->bullet_center_.first +=
        kFighterWidth / 2 - (kBulletWidth / 2);
    current_bullet->bullet_center_.second -= kFighterWidth / 8;
    player_bullets.push_back(current_bullet);
    player.player_shots_++;
    player.player_fire.play();
}

void ofApp::CheckEnemyCollisions() {
    // This looks like an O(n^2) operation but bullets will always contain at most 2 elements

	for (int j = 0; j < enemies.size(); j++) {
        int enemy_first = enemies[j]->enemy_center_.first;
        int enemy_second = enemies[j]->enemy_center_.second;
        glm::vec2 enemy_center(enemy_first, enemy_second);
        ofRectangle current_enemy(enemy_center, kEnemyWidth, kEnemyHeight);

        for (int i = 0; i < player_bullets.size(); i++) {
            int bullet_first = player_bullets[i]->bullet_center_.first;
            int bullet_second = player_bullets[i]->bullet_center_.second;
            glm::vec2 bullet_center(bullet_first, bullet_second);
            ofRectangle current_bullet(bullet_center, kBulletWidth, kBulletHeight);

			if (current_enemy.intersects(current_bullet)) {
                delete enemies[j];
                enemies.erase(enemies.begin() + j);

                delete player_bullets[i];
                player_bullets.erase(player_bullets.begin() + i);
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
            
			//add some more logic here for player death

			player.player_lives_--;
            player.alive_ = false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    DrawSideboard();

	if (!player.alive_) {
        // add additional state here for whether the player is out of lives
        //if (player.player_lives_ > 0) {
            DrawGameDead();
        //} else {
        //}
	} else {
        player.fighter_texture_.draw(player.player_center_.first,
                                     player.player_center_.second);

        for (int i = 0; i < player_bullets.size(); i++) {
            int first = player_bullets[i]->bullet_center_.first;
            int second = player_bullets[i]->bullet_center_.second;
            player_bullets[i]->bullet_texture_.draw(first, second);
        }

        for (int i = 0; i < enemies.size(); i++) {
            int first = enemies[i]->enemy_center_.first;
            int second = enemies[i]->enemy_center_.second;
            enemies[i]->enemy_texture_.draw(first, second);
        }
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
            (player.player_center_.first + kFighterWidth) < kGameWindowWidth) {
            right_pressed = true;
        }

        if (key == OF_KEY_UP && player.player_shots_ < kLegalBulletsMax) {
            shoot_pressed = true;
        }
	}
    

    int upper_key = toupper(key);

	if (upper_key == 'R' && !player.alive_) {
        RevivePlayer();
    }

    if (upper_key == 'E') {
        CreateEnemy(player.player_center_.first, demo_bee.enemy_center_.second, 1);
    }
}

void ofApp::RevivePlayer() {
    player.alive_ = true;
    player.player_center_.first = kGameWindowWidth / 2;
	
    ofSetColor(255, 255, 255);
    ofSetBackgroundColor(0, 0, 0);
}

void ofApp::ReturnToFormation() {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) { 
	/*if (key == OF_KEY_LEFT) {
        left_pressed = false;
    }

    if (key == OF_KEY_RIGHT) {
        right_pressed = false;
    }

    if (key == OF_KEY_UP) {
        shoot_pressed = false;
    }*/
}

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
