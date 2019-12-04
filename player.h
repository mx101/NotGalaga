#pragma once
#include "ofMain.h"

class Player {

 public:
  const int kFighterWidth = 48;
  std::pair<int, int> player_center_;
	
  ofTexture fighter_texture_;
  ofSoundPlayer player_fire;
    
  int player_shots_;
};