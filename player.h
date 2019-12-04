#pragma once
#include "ofMain.h"

class Player {

 public:
  const int kFighterWidth = 48;
  std::pair<int, int> player_center_;
  int player_shots_;
  bool alive_;
  int player_lives_;
	
  ofTexture fighter_texture_;
  ofSoundPlayer player_fire;
};