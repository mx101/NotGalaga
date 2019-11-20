#pragma once
#include "ofMain.h"
#include "PoissonGenerator.h"

#include <vector>

class Enemy {	
 public:
  /*Enemy();
  Enemy(int enemy_type);*/

  std::vector<std::pair<int, int>> path_plotter();  
  //static void generate_enemies(std::vector<Enemy> *enemies);

  /*const int kEnemyCount = 44;
  const int kFirstBeeIdx = 0;
  const int kFirstMothIdx = 20;
  const int kFirstBossIdx = 40;*/


  std::pair<int, int> enemy_center_;
  int enemy_type_;
  bool dead_;

  ofTexture texture_;
};