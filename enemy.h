#pragma once
#include "matplotlibcpp.h"
#include "ofMain.h"

class Enemy {	
 public:
  Enemy();
  Enemy(int enemy_type);

  std::pair<int, int> enemy_center_;
  int enemy_type_;
  bool dead_;

  ofTexture texture_;
};