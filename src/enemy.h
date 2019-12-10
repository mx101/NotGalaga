#pragma once
#include "ofMain.h"

#include <vector>

class Enemy {	
 public:  
  // the pair will be representing a change in x, y
  // this is represented as a queue since some enemies have repeating paths
  struct EnemyPath {
    vector<pair<int, int>> directions;
    bool in_formation_;
  };

  void GenerateNewPath();
  vector<pair<int, int>> GenerateDefaultPath();

  pair<int, int> kZeroMove = { 0, 0 };
  pair<int, int> kLeftMove = { -10, 0 };
  pair<int, int> kRightMove = { 10, 0 };
	 
  EnemyPath path_;
  pair<int, int> enemy_center_;
  pair<int, int> formation_pos_;
  int enemy_type_;
  int enemy_kill_score_;
  int enemy_width_;

  ofTexture enemy_texture_;
};