#include "ofApp.h"

using namespace PoissonGenerator;

void ofApp::setup() {
    ofSetWindowTitle("NotGalaga");

    // set background color to black, because it's space
    ofSetBackgroundColor(0, 0, 0);
    srand(static_cast<unsigned>(time(0)));

	xbox.setup();
    gamepad = xbox.getGamepadPtr(0);
    deadZone = true;

    game_running_ = true;
    high_score_ = 30000;
    waves_ = 0;

    left_pressed = false;
    right_pressed = false;
    shoot_pressed = false;
    //test = true;

    LoadData();

    // condense below lines into some restartGame method
    player.player_shots_ = 0;
    player.player_lives_ = 3;
    player.alive_ = true;
    player.player_center_.first = kGameWindowWidth / 2;
    player.player_center_.second = kGameWindowHeight - (kGameWindowHeight / 8);

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

	//note that this number will be doubled if the enemy dies while moving
	bee_.enemy_kill_score_ = 40;
    moth_.enemy_kill_score_ = 80;
    boss_.enemy_kill_score_ = 150;

}

//--------------------------------------------------------------
void ofApp::update() {
    /*if (test) {
        std::vector<std::pair<int, int>> vect = CreateRandPath();

        for (std::pair<int, int> cPair : vect) {
            std::cout << cPair.first << std::endl;
            std::cout << cPair.second << std::endl;
        }
		test = false;
	}*/

	gamepad->leftVibration = gamepad->leftTrigger;
    gamepad->rightVibration = gamepad->rightTrigger;

    xbox.update();

    if (game_running_) {
        if (enemies_.empty()) {
            GenerateWave();
        }

        if (player.alive_) {

			// when player shoots with a, the ship will fire sequentially
			// very quickly so it looks like a single shot
			// solution: store when the last shot was shot?
            if ((gamepad->a) && 
				player.player_shots_ < kLegalBulletsMax) {
                ShootBullet(player.player_center_, kPlayerBulletSpeed, true);
			}

            if ((gamepad->dPadLeft || left_pressed) &&
                player.player_center_.first > 0) {
                player.player_center_.first -= kFighterMoveSpeed;
            }

            if ((gamepad->dPadRight || right_pressed) &&
                (player.player_center_.first + kFighterWidth -
                                  1) < kGameWindowWidth) {
                player.player_center_.first += kFighterMoveSpeed;
            }

            // check edges not out of bounds
            int ship_right = player.player_center_.first + kFighterWidth;
            int out_of_bounds_right = ship_right - kGameWindowWidth;

            if (out_of_bounds_right > 0) {
                // std::cout << "out by: " << out_of_bounds << std::endl;
                player.player_center_.first -= out_of_bounds_right;
            }

            int ship_left = player.player_center_.first;

            if (ship_left < 0) {
                // std::cout << "out by: " << ship_left << std::endl;
                player.player_center_.first -= ship_left;
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
            enemies_[i]->enemy_center_.second += kEnemyDefaultMoveSpeed;

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

std::vector<std::pair<int, int>> ofApp::CreateRandPath() {
    std::vector<std::pair<int, int>> to_return;

    DefaultPRNG PRNG;
    int num_points = 100;

    std::vector<Point> points_to_extract =
        generatePoissonPoints(num_points, PRNG);

    int enemy_speed_range = 20;

    for (Point current_point : points_to_extract) {
        // generates a pair of numbers in the range of [-10, 10]
		// note that these numbers are guaranteed in this range because they originate as
		// percentages from -1 to 1
        int xC = current_point.x * 10;
        int yC = current_point.y * 10;

        int x_change = (xC / 2) - (std::rand() % xC);

        int y_change = (yC / 2) - (std::rand() % yC);

        to_return.push_back(std::pair<int, int>(x_change, y_change));
    }

    return to_return;
}

queue<tuple<int, int>> ofApp::GeneratePath() {
    queue<tuple<int, int>> to_return;
    to_return.push(GenerateRandomMove());
    return to_return;
}

tuple<int, int> ofApp::GenerateRandomMove() {
    int enemy_speed_range = 20;

    // generates a pair of numbers in the range of [-10, 10]
    int x_change = (enemy_speed_range / 2) - (std::rand() % enemy_speed_range);

    int y_change = (enemy_speed_range / 2) - (std::rand() % enemy_speed_range);

    return tuple<int, int>(x_change, y_change);
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

void ofApp::ShootBullet(std::pair<int, int> center, int velocity,
                        bool player_shot) {
    // possible streamlining improvement: have this function take in a start
    // point and velocity that way we can reuse for shooting enemy bullets

    Bullet* current_bullet = new Bullet();

    if (player_shot) {
        *current_bullet = player_bullet_;
        current_bullet->bullet_center_ = center;
        current_bullet->bullet_center_.first +=
            kFighterWidth / 2 - (kBulletWidth / 2);
        current_bullet->bullet_center_.second -= kFighterWidth / 8;

        player_bullets_.push_back(current_bullet);
        player.player_shots_++;
        player.player_fire.play();

    } else {
        *current_bullet = enemy_bullet_;
        current_bullet->bullet_center_ = center;
        current_bullet->bullet_center_.first +=
            kEnemyWidth / 2 - (kBulletWidth / 2);

        enemy_bullets_.push_back(current_bullet);
    }

    current_bullet->bullet_velocity_ = velocity;
}

void ofApp::GenerateWave() {
    // note the additional if checks for moths and bees
    // because they form two rows

    int x = kBeeStartX;
    int y = kBeeStartY;
    int separation = 10;

    for (int i = 0; i < kBeeCount; i++) {
        Enemy* curr_bee;

        if (i < kSecondRowBeeIdx) {
            curr_bee = CreateEnemy(x, y, 0);
            x += curr_bee->enemy_width_ + separation;

        } else {
            if (i == kSecondRowBeeIdx) {
                x = kBeeStartX;
                y -= kEnemySpacing;
            }

            curr_bee = CreateEnemy(x, y, 0);
            x += curr_bee->enemy_width_ + separation;
        }
    }

    x = kMothStartX;
    y -= kEnemySpacing;

    for (int i = 0; i < kMothCount; i++) {
        Enemy* curr_moth;

        if (i < kSecondRowMothIdx) {
            curr_moth = CreateEnemy(x, y, 1);
            x += curr_moth->enemy_width_ + separation;

        } else {
            if (i == kSecondRowMothIdx) {
                x = kMothStartX;
                y -= kEnemySpacing;
            }

            curr_moth = CreateEnemy(x, y, 1);
            x += curr_moth->enemy_width_ + separation;
        }
    }

    x = kBossStartX;
    y -= kEnemySpacing;

    for (int i = 0; i < kBossCount; i++) {
        Enemy* curr_boss;

        curr_boss = CreateEnemy(x, y, 2);
        x += curr_boss->enemy_width_ + separation;
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
                score_ += enemies_[j]->enemy_kill_score_;

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
            score_ += 2 * enemies_[j]->enemy_kill_score_;

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
            ofRectangle current_enemy(enemy_center, kBulletWidth,
                                      kBulletHeight);

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
    //ofSetColor(200, 40, 30);
    //ofSetColor(255);
    //xbox.draw();

    DrawSideboard();
    DrawNonPlayerObjects();

    if (!player.alive_) {
        DrawGameDead();

    } else {
        player.fighter_texture_.draw(player.player_center_.first,
                                     player.player_center_.second);
    }
	
	
}

void ofApp::DrawNonPlayerObjects() {
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

Enemy* ofApp::CreateEnemy(int x, int y, int type) {
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
    if (type != 2 && std::rand() % 5 == 0) {
        ShootBullet(current_enemy->enemy_center_, kEnemyBulletSpeed, false);
    }

    return current_enemy;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (player.alive_) {
        if (key == OF_KEY_LEFT) {
            left_pressed = true;
        }

        if (key == OF_KEY_RIGHT) {
            right_pressed = true;
        }

        if (key == OF_KEY_UP) {
            shoot_pressed = true;
        }
    }

    int upper_key = toupper(key);

    if (upper_key == 'R' && !player.alive_) {
        RevivePlayer();
        ReturnToFormation();
    }

    if (upper_key == 'E') {
        GenerateWave();
        // CreateEnemy(player.player_center_.first, bee_.enemy_center_.second,
        // 0);
    }
}

void ofApp::RevivePlayer() {
    player.alive_ = true;
    player.player_center_.first = kGameWindowWidth / 2;

    ofSetColor(255, 255, 255);
    ofSetBackgroundColor(0, 0, 0);
}

void ofApp::ReturnToFormation() {
    for (Enemy* curr_enemy : enemies_) {
        curr_enemy->enemy_center_ = curr_enemy->formation_pos_;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if (key == OF_KEY_LEFT) {
        left_pressed = false;
    }

    if (key == OF_KEY_RIGHT) {
        right_pressed = false;
    }
}
