#pragma once
#include "ofMain.h"

class Player {

  public:
    const int kFighterWidth = 48;
	//int player_center;
    std::pair<int, int> player_center;
	
	ofTexture fighter_texture;
    ofTexture captured_fighter_texture; 
	ofSoundPlayer player_fire;
    
	
};