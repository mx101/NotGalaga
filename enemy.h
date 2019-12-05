#pragma once
#include "ofMain.h"
#include "PoissonGenerator.h"

#include <vector>

class Enemy {	
 public:
  //Enemy();
  //Enemy(int enemy_type);

  std::vector<std::pair<int, int>> path_plotter();  
  //static void generate_enemies(std::vector<Enemy> *enemies);

  /*const int kEnemyCount = 44;
  const int kFirstBeeIdx = 0;
  const int kFirstMothIdx = 20;
  const int kFirstBossIdx = 40;*/

  // the pair will be representing a change in x, y
  // this is represented as a queue since some enemies have repeating paths
  std::queue<std::pair<int, int>> path_;
  std::pair<int, int> enemy_center_;
  std::pair<int, int> formation_pos_;
  int enemy_type_;
  int enemy_score_;
  bool dead_;
  int enemy_width_;


  ofTexture enemy_texture_;
};