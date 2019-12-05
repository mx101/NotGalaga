#pragma once
#include "ofMain.h"

class Bullet {
   public:
    ofTexture bullet_texture_;
    std::pair<int, int> bullet_center_;
    int bullet_velocity_;
	
};