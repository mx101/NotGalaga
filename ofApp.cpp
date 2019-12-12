#include "ofApp.h"

void ofApp::setup() {
  ofSetWindowTitle("NotGalaga");

  // set background color to black, because it's space
  ofSetBackgroundColor(0, 0, 0);
  srand(static_cast<unsigned>(time(0)));

  xbox.setup();
  gamepad = xbox.getGamepadPtr(0);
  deadZone = true;

  LoadData();
	RestartGame();
}

void ofApp::RestartGame() {
	game_running_ = true;
	high_score_ = kDefaultHighScore;
	waves_ = 1;
	timer_ = 0;
	time_last_shot = 0;
	time_last_paused = 0;
	shots_fired_ = 0;
	shots_hit_ = 0;
	all_in_form_ = false;

	left_pressed = false;
	right_pressed = false;
	shoot_pressed = false;

	player.player_shots_ = 0;
	player.player_lives_ = 3;
	player.alive_ = true;
	player.player_center_.first = kGameWindowWidth / 2;
	player.player_center_.second = kGameWindowHeight - (kGameWindowHeight / 8);

	score_ = 0;
}

void ofApp::LoadData() {
  theme_music_.load("theme.mp3");
  theme_music_.play();

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
	ofLoadImage(boss_damaged_.enemy_texture_, "bossGalagaHit.png");

  // note that this number will be doubled if the enemy dies while moving
  bee_.enemy_kill_score_ = 40;
	moth_.enemy_kill_score_ = 80;
  boss_.enemy_kill_score_ = 0;
	boss_damaged_.enemy_kill_score_ = 150;
}

//--------------------------------------------------------------
void ofApp::update() {
	timer_++;

  xbox.update();

  if (game_running_) {
    if (enemies_.empty() && gamepad->start) {
      GenerateWave();
    }

		CheckAllReady();

    UpdatePlayerObjects();

    UpdateEnemyObjects();

    CheckEnemyCollisions();

    if (player.alive_) {
      CheckPlayerCollisions();
		}
		else {
			DeathVibration();
		}

  } else {
    DeathVibration();
  }

	// weird bugs with vibration continuing, press Down to turn off vibration
	if (gamepad->dPadDown) {
		gamepad->rightVibration = 0;
		gamepad->leftVibration = 0;
	}
}

void ofApp::DeathVibration() {
  int pause_elapsed = abs(timer_ - time_last_paused);
  if (pause_elapsed < kGeneralTime) {
    gamepad->leftVibration = float(1.0);
    gamepad->rightVibration = float(1.0);
  } else {
    gamepad->rightVibration = 0;
    gamepad->leftVibration = 0;
  }
}

void ofApp::CheckAllReady() {
	for (size_t i = 0; i < enemies_.size(); i++) {
		if (enemies_[i]->enemy_center_ != enemies_[i]->formation_pos_) {
			all_in_form_ = false;
			return;
		}
	}

	all_in_form_ = true;
}

void ofApp::UpdatePlayerObjects() {
  if (player.alive_) {
    // when player shoots with a, the ship will fire sequentially
    // very quickly so it looks like a single shot
    // solution: store when the last shot was shot?
    if ((gamepad->a || gamepad->b) && 
				player.player_shots_ < kLegalBulletsMax && abs(time_last_shot - timer_) > kReloadTime) {
      time_last_shot = timer_;
	  	ShootBullet(player.player_center_, kPlayerBulletSpeed, true);
			shots_fired_++;
    }

    if ((gamepad->dPadLeft || left_pressed) &&
				player.player_center_.first > 0) {
      player.player_center_.first -= kFighterMoveSpeed;
    }

    if ((gamepad->dPadRight || right_pressed) &&
        (player.player_center_.first + kFighterWidth - 1) < kGameWindowWidth) {
      player.player_center_.first += kFighterMoveSpeed;
    }

    // check edges not out of bounds
    int ship_right = player.player_center_.first + kFighterWidth;
    int out_of_bounds_right = ship_right - kGameWindowWidth;

    if (out_of_bounds_right > 0) {
      player.player_center_.first -= out_of_bounds_right;
    }

    int ship_left = player.player_center_.first;

    if (ship_left < 0) {
      player.player_center_.first -= ship_left;
    }
	} else if (player.player_lives_ > 0) {
		if (gamepad->start) {
			RevivePlayer();
		}
	} else {
		if (gamepad->back) {
			RevivePlayer();
			RestartGame();
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
}

void ofApp::UpdateEnemyObjects() {	
	for (int i = 0; i < enemies_.size(); i++) {
	  bool should_move = (enemies_[i]->time_moved_ - timer_) % kGeneralTime == 0;

		// if the enemy is not in formation, the timer should not affect their movement
		if (!enemies_[i]->path_.in_formation_) {
			should_move = true;
		}

		if (enemies_[i]->path_.directions.empty()) {
			if (!player.alive_) {
				if (all_in_form_) {
					enemies_[i]->path_.directions = enemies_[i]->GenerateDefaultPath();
					enemies_[i]->path_.in_formation_ = true;
				} else {
					enemies_[i]->ReturnToFormation();
					enemies_[i]->path_.in_formation_ = true;
				}
			} else if (all_in_form_) { // enemies_[i]->path_.in_formation_) {
				enemies_[i]->GenerateNewPath();
			} else {
				enemies_[i]->ReturnToFormation();
				enemies_[i]->path_.in_formation_ = true;
			}

			// use enemy's shot count and a random low probability to determine if enemy should shoot
			bool should_shoot = (std::rand() % 8 < 1) && enemies_[i]->shots_to_fire_ != 0;

			// if do enemy fly in, the shooting can be moved to as the enemies fly in
			if (enemies_[i]->enemy_type_ != 2 && should_shoot) {
				ShootBullet(enemies_[i]->enemy_center_, kEnemyBulletSpeed, false);
				enemies_[i]->shots_to_fire_--;
			}
		}

		if (should_move) {
			pair<int, int> current_move = enemies_[i]->path_.directions.front();

			enemies_[i]->enemy_center_.first += current_move.first;
			enemies_[i]->enemy_center_.second += current_move.second;

		  enemies_[i]->path_.directions.erase(enemies_[i]->path_.directions.begin());

			if (enemies_[i]->enemy_center_.second > kGameWindowHeight) {
				enemies_[i]->enemy_center_.second = kEnemySpawnHeight;
			}

			enemies_[i]->time_moved_ = timer_;
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
}

void ofApp::DrawScoreboard() {
	int scoreboard_spacing = 40;
	float accuracy = (float(shots_hit_) / float(shots_fired_)) * 100;
	string shots_hit_message = "Accuracy: " + to_string(accuracy) + "%";

	int side_hit_width = (kGameWindowWidth / 2) -
		(message_font_.stringWidth(shots_hit_message) / 2);

	int side_hit_height = kGameWindowHeight / 2;

	side_font_.drawString(shots_hit_message, side_hit_width, side_hit_height);

	string shots_fired_message = "Shots Fired: " + to_string(shots_fired_);

	int side_fired_width = (kGameWindowWidth / 2) -
		(message_font_.stringWidth(shots_fired_message) / 2);

	int side_fired_height = (kGameWindowHeight / 2) + scoreboard_spacing;

	side_font_.drawString(shots_fired_message, side_fired_width, side_fired_height);

  // items to display, high score of current session, score of current game
  // option to restart game
  // remember to delete the remaining enemies from memory
}

void ofApp::DrawSideboard() {
  // draw the line of separation between gameplay and sideboard
  glm::vec2 top_border(kGameWindowWidth, 0);
  glm::vec2 bottom_border(kGameWindowWidth, kGameWindowHeight);
  ofDrawLine(top_border, bottom_border);

	ofSetColor(0, 0, 0);
	ofDrawRectangle(top_border, kSideboardWidth, kGameWindowHeight);
	ofSetColor(255, 255, 255);

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

  string wave_message = "Wave: " + to_string(waves_ - 1);

  int side_wave_width = kGameWindowWidth + (kSideboardWidth / 2) -
                    side_font_.stringWidth(wave_message) / 2;

  int side_wave_height = (kGameWindowHeight / 2) + (3 * kSideboardSpacing);

  side_font_.drawString(wave_message, side_wave_width, side_wave_height);

	string high_message = "High Score:";

	int side_high_width = kGameWindowWidth + (kSideboardWidth / 2) -
		                side_font_.stringWidth(high_message) / 2;

	int side_high_height = (kGameWindowHeight / 2) - (5 * kSideboardSpacing);

	side_font_.drawString(high_message, side_high_width, side_high_height);

	string highS_message = to_string(high_score_);

	int side_highS_width = kGameWindowWidth + (kSideboardWidth / 2) -
	                 	side_font_.stringWidth(highS_message) / 2;

	int side_highS_height = (kGameWindowHeight / 2) - (4 * kSideboardSpacing);

	side_font_.drawString(highS_message, side_highS_width, side_highS_height);
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
        kBeeMothHeight / 2 - (kBulletWidth / 2);

    enemy_bullets_.push_back(current_bullet);
  }

  current_bullet->bullet_velocity_ = velocity;
}

void ofApp::GenerateWave() {
  int second_row_bee = 10;
  int second_row_moth = 8;
  // note the additional if checks for moths and bees
  // because they form two rows

  int x = kBeeStartX;
  int y = kBeeStartY;
  int separation = 10;

  for (int i = 0; i < kBeeCount; i++) {
    Enemy* curr_bee;

    if (i == second_row_bee) {
      x = kBeeStartX;
      y -= kEnemySpacing;
    }

    curr_bee = CreateEnemy(x, y, 0);
    curr_bee->formation_pos_ = std::pair<int, int>(x, y);
		curr_bee->enemy_center_ = kLeftSpawn;
		curr_bee->path_.directions = curr_bee->GenerateFlyIn(std::rand() % kWaveCount);
		curr_bee->shots_to_fire_ = 1;

    x += curr_bee->enemy_width_ + separation;
  }

  x = kMothStartX;
  y -= kEnemySpacing;

  for (int i = 0; i < kMothCount; i++) {
    Enemy* curr_moth;

    if (i == second_row_moth) {
      x = kMothStartX;
      y -= kEnemySpacing;
    }

    curr_moth = CreateEnemy(x, y, 1);
    curr_moth->formation_pos_ = std::pair<int, int>(x, y);
		curr_moth->enemy_center_ = kRightSpawn;
		curr_moth->path_.directions = curr_moth->GenerateFlyIn(std::rand() % kWaveCount);
		curr_moth->shots_to_fire_ = 2;

    x += curr_moth->enemy_width_ + separation;
  }

  x = kBossStartX;
  y -= kEnemySpacing;

  for (int i = 0; i < kBossCount; i++) {
    Enemy* curr_boss;

    curr_boss = CreateEnemy(x, y, 2);
    curr_boss->formation_pos_ = std::pair<int, int>(x, y);
		curr_boss->enemy_center_ = kRightSpawn;
		curr_boss->path_.directions = curr_boss->GenerateFlyIn(std::rand() % kWaveCount);
		curr_boss->shots_to_fire_ = 0;

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
    ofRectangle current_enemy(enemy_center, enemies_[j]->enemy_width_,
                            enemies_[j]->enemy_width_);

    for (int i = 0; i < player_bullets_.size(); i++) {
      int bullet_first = player_bullets_[i]->bullet_center_.first;
      int bullet_second = player_bullets_[i]->bullet_center_.second;
      glm::vec2 bullet_center(bullet_first, bullet_second);
      ofRectangle current_bullet(bullet_center, kBulletWidth,
                                       kBulletHeight);

      if (current_enemy.intersects(current_bullet)) {
		  	if (enemies_[j]->path_.in_formation_) {
					score_ += enemies_[j]->enemy_kill_score_;
				} else {
					// player earns double the points for killing an alien 
					// while not in formation
					score_ += 2 * enemies_[j]->enemy_kill_score_;
				}

				/*if (enemies_[j]->enemy_type_ == 2) {
					std::cout << "damaged" << std::endl;
					*(enemies_[j]) = boss_damaged_;
					enemies_[j]->enemy_type_ = 3;
				} else {*/
					delete enemies_[j];
					enemies_.erase(enemies_.begin() + j);
				//}
        
        delete player_bullets_[i];
        player_bullets_.erase(player_bullets_.begin() + i);
        player.player_shots_--;
				shots_hit_++;
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
    ofRectangle current_enemy(enemy_center, enemies_[j]->enemy_width_,
                              enemies_[j]->enemy_width_);

    if (current_enemy.intersects(player_rect)) {
      score_ += 2 * enemies_[j]->enemy_kill_score_;

      delete enemies_[j];
      enemies_.erase(enemies_.begin() + j);

      player.player_lives_--;
      player.alive_ = false;
      time_last_paused = timer_;
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
        time_last_paused = timer_;
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  /*ofSetColor(200, 40, 30);
   ofSetColor(255);
   xbox.draw();*/

  DrawNonPlayerObjects();

  if (!player.alive_) {
		if (player.player_lives_ > 0) {
			DrawGameDead();
		} else {
			DrawScoreboard();
		}
	} else {
		player.fighter_texture_.draw(player.player_center_.first,
			player.player_center_.second);
	}

	DrawSideboard();
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
		current_enemy->enemy_width_ = kBeeMothWidth;
		current_enemy->enemy_type_ = 0;
	
	} else if (type == 1) {
  
		*current_enemy = moth_;
  	current_enemy->enemy_width_ = kBeeMothWidth;
		current_enemy->enemy_type_ = 1;

	} else if (type == 2) {
  
		*current_enemy = boss_;
  	current_enemy->enemy_width_ = kBossWidth;
		current_enemy->enemy_type_ = 2;

	}

	current_enemy->enemy_center_.first = x;
	current_enemy->enemy_center_.second = y;
	current_enemy->formation_pos_.first = x;
	current_enemy->formation_pos_.second = y;
  
	current_enemy->path_.in_formation_ = false;
	enemies_.push_back(current_enemy);

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
  }

  if (upper_key == 'E') {
    GenerateWave();
  }
}

void ofApp::RevivePlayer() {
  player.alive_ = true;
  player.player_center_.first = kGameWindowWidth / 2;

  ofSetColor(255, 255, 255);
  ofSetBackgroundColor(0, 0, 0);
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
