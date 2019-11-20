#include "enemy.h"

Enemy::Enemy() {

}

Enemy::Enemy(int enemy_type) { 
  this->enemy_type_ = enemy_type;
  this->dead_ = false;
	
  if (enemy_type == 0) {
    ofLoadImage(this->texture_, "bee.png");
  }

  if (enemy_type == 1) {
    ofLoadImage(this->texture_, "moth.png");
  }

  if (enemy_type == 2) {
    ofLoadImage(this->texture_, "bossGalaga.png");
  }
}