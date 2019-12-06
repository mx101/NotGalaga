#pragma once
#include "ofMain.h"
#include "PoissonGenerator.h"

#include <vector>

class Enemy {	
 public:  
  // the pair will be representing a change in x, y
  // this is represented as a queue since some enemies have repeating paths
  queue<pair<int, int>> path_;
  pair<int, int> enemy_center_;
  pair<int, int> formation_pos_;
  int enemy_type_;
  int enemy_kill_score_;
  bool dead_;
  bool in_formation_;
  int enemy_width_;

  ofTexture enemy_texture_;
};