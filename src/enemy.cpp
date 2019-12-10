#include "enemy.h"

void Enemy::GenerateNewPath() {
  this->path_.directions = GenerateDefaultPath();
}
vector<pair<int, int>> Enemy::GenerateDefaultPath() {
	vector<pair<int, int>> to_path;

	// default path moves as follows:
	// L L R R R R L L

	to_path.push_back(kLeftMove);
	to_path.push_back(kZeroMove);
	to_path.push_back(kLeftMove);
	to_path.push_back(kZeroMove);
	to_path.push_back(kRightMove);
	to_path.push_back(kZeroMove);
	to_path.push_back(kRightMove);
	to_path.push_back(kZeroMove);
	to_path.push_back(kRightMove);
	to_path.push_back(kZeroMove);
	to_path.push_back(kRightMove);
	to_path.push_back(kZeroMove);
	to_path.push_back(kLeftMove);
	to_path.push_back(kZeroMove);
	to_path.push_back(kLeftMove);
	to_path.push_back(kZeroMove);

	return to_path;
}

