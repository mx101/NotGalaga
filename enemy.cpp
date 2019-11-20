#include "enemy.h"

//Enemy::Enemy() {
//  this->enemy_type_ = 0; 
//  this->dead_ = false;
//  ofLoadImage(this->texture_, "bee.png");
//}

//Enemy::Enemy(int enemy_type) {
//  this->enemy_type_ = enemy_type;
//  this->dead_ = false;
//
//  if (enemy_type == 0) {
//    ofLoadImage(this->texture_, "bee.png");
//  }
//
//  if (enemy_type == 1) {
//    ofLoadImage(this->texture_, "moth.png");
//  }
//
//  if (enemy_type == 2) {
//    ofLoadImage(this->texture_, "bossGalaga.png");
//  }
//
//  if (enemy_type == 3) {
//    ofLoadImage(this->texture_, "capturedFighter.png");
//  }
//}

//void Enemy::generate_enemies(std::vector<Enemy> *enemies) {
//  // load in the first 44 aliens
//
//  for (int i = 0; i < kEnemyCount; i++) {
//    if (i < kFirstMothIdx) {
//      enemies->push_back(Enemy(0));
//    } else if (i < kFirstBossIdx) {
//      enemies->push_back(Enemy(1));
//    } else {
//      enemies->push_back(Enemy(2));
//    }
//  }
//}

//std::vector<std::pair<int, int>> Enemy::path_plotter() {
//  std::vector<std::pair<int, int>> to_return;
//
//  return to_return;
//}