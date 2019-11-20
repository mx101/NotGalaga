#pragma once
#include "ofMain.h"

#include <vector>

class Enemy {	
 public:
  Enemy(int enemy_type);

  std::vector<std::pair<int, int>> path_plotter();  

  std::pair<int, int> enemy_center_;
  int enemy_type_;
  bool dead_;

  ofTexture texture_;
};