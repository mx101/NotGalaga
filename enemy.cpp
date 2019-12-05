#include "enemy.h"

using namespace PoissonGenerator;
//Enemy::Enemy() {
//  this->enemy_type_ = 0; 
//  this->dead_ = false;
//  ofLoadImage(this->enemy_texture_, "bee.png");
//}

//Enemy::Enemy(int enemy_type) {
//  this->dead_ = false;
//	
//	// load in images elsewhere and store as a pointer, load when need to
//
//  if (enemy_type == 0) {
//      ofLoadImage(this->enemy_texture_, "bee.png");
//  }
//  this->enemy_type_ = enemy_type;
//
//  if (enemy_type == 1) {
//      ofLoadImage(this->enemy_texture_, "moth.png");
//  }
//
//  if (enemy_type == 2) {
//      ofLoadImage(this->enemy_texture_, "bossGalaga.png");
//  }
//
//  if (enemy_type == 3) {
//      ofLoadImage(this->enemy_texture_, "capturedFighter.png");
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

std::vector<std::pair<int, int>> Enemy::path_plotter() {
  std::vector<std::pair<int, int>> to_return;

  DefaultPRNG PRNG;
  int num_points = 100;

  std::vector<Point> points_to_extract =
      generatePoissonPoints(num_points, PRNG);  

  for (Point current_point : points_to_extract) {
    to_return.push_back(std::pair<int, int>(current_point.x, current_point.y));
  }

  return to_return;
}

