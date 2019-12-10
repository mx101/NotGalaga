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

vector<pair<int, int>> Enemy::PathPlotter(pair<int, int> begin, pair<int, int> end) {
	int frame_count = 20;
	pair<int, int> current = begin;
	int x_change = (end.first - begin.first) / frame_count;
	int y_change = (end.second - begin.second) / frame_count;

	vector<pair<int, int>> to_return;

	for (int i = 0; i < frame_count; i++) {
		to_return.push_back({ x_change, y_change });
	}

	return to_return;
}

vector<pair<int, int>> Enemy::GenerateRandomPath() {
	vector<pair<int, int>> to_return;
	int random_steps = 20;

	for (int i = 0; i < random_steps; i++) {
		to_return.push_back(GenerateRandomMove());
	}

	return to_return;
}

pair<int, int> Enemy::GenerateRandomMove() {
	int enemy_speed_range = 20;

	// generates a pair of numbers in the range of [-10, 10]
	int x_change = (enemy_speed_range / 2) - (std::rand() % enemy_speed_range);

	int y_change = (enemy_speed_range / 2) - (std::rand() % enemy_speed_range);

	return pair<int, int>(x_change, y_change);
}