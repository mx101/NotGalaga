#pragma once
#include "ofMain.h"

#include <vector>

class Enemy {	
 public:  
  // the pair will be representing a change in x, y
  // this is represented as a queue since some enemies have repeating paths
	const int kNumPathChoices = 10;
	const int kMoveFrames = 20;
	const int kMoveSpeedMax = 6;

  struct EnemyPath {
		EnemyPath() {
			directions = vector<pair<int, int>>();
			in_formation_ = false;
		}

    vector<pair<int, int>> directions;
    bool in_formation_;
  };

	Enemy();
	Enemy(const Enemy& source);
	Enemy(Enemy&& source) noexcept;
	~Enemy();
	Enemy& operator=(Enemy&& source) noexcept;
	Enemy& operator=(const Enemy&);

  void GenerateNewPath();
  vector<pair<int, int>> GenerateDefaultPath();
	vector<pair<int, int>> GenerateDiagPath();
	vector<pair<int, int>> PathPlotter(pair<int, int> begin, pair<int, int> end, int frame_count);
	vector<pair<int, int>> GenerateRandomPath();
	pair<int, int> GenerateRandomMove();


  pair<int, int> kZeroMove = { 0, 0 };
  pair<int, int> kLeftMove = { -10, 0 };
  pair<int, int> kRightMove = { 10, 0 };
	pair<int, int> kDiagDownLeft = { -5, 5 };
	pair<int, int> kDiagDownRight = { 5, 5 };
	 
  EnemyPath path_;
  pair<int, int> enemy_center_;
  pair<int, int> formation_pos_;
  int enemy_type_;
  int enemy_kill_score_;
  int enemy_width_;
	int time_moved_ = 0;

  ofTexture enemy_texture_;
};