#pragma once
#include "ofMain.h"

#include <vector>

class Enemy {	
 public:  
  // the pair will be representing a change in x, y
  // this is represented as a queue since some enemies have repeating paths
	const int kNumPathChoices = 16;
	const int kPathChoiceDefault = 10;
	const int kPathChoice1 = 12;
	const int kPathChoice2 = 14;
	const int kMoveFrames = 40;
	const int kMoveSpeedMax = 4;

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

  void GenerateNewPath(bool all_move);
	vector<pair<int, int>> GenerateFlyIn(int wave_number);
  vector<pair<int, int>> GenerateDefaultPath();
	vector<pair<int, int>> GenerateDiagPath();
	vector<pair<int, int>> PathPlotter(pair<int, int> begin, pair<int, int> end, int frame_count);
	vector<pair<int, int>> GenerateRandomPath();
	vector<pair<int, int>> GenerateSwirlPath();
	pair<int, int> GenerateRandomMove();
	vector<pair<int, int>> GenerateLeftCurve();
	vector<pair<int, int>> GenerateRightCurve();
	void ReturnToFormation();

  pair<int, int> kZeroMove = { 0, 0 };
  pair<int, int> kLeftMove = { -10, 0 };
  pair<int, int> kRightMove = { 10, 0 };
	pair<int, int> kDiagDownLeft = { -3, 3 };
	pair<int, int> kDiagDownRight = { 3, 3 };
	 
  EnemyPath path_;
  pair<int, int> enemy_center_;
  pair<int, int> formation_pos_;
  int enemy_type_;
  int enemy_kill_score_;
  int enemy_width_;
	int time_moved_ = 0;
	int shots_to_kill_;
	int shots_to_fire_;

  ofTexture enemy_texture_;
};