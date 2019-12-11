#include "enemy.h"

Enemy::Enemy() {
	path_ = EnemyPath();
	enemy_center_ = pair<int, int>();
	formation_pos_ = pair<int, int>();
	enemy_type_ = -1;
	enemy_kill_score_ = 0;
	enemy_width_ = 0;
	time_moved_ = 0;
	shots_to_fire_ = 0;
	shots_to_kill_ = 0;
}

Enemy::Enemy(const Enemy& source) {
	if (source.enemy_type_ == -1) {
		path_.directions.clear();
		path_.in_formation_ = false;
		enemy_center_ = pair<int, int>();
		formation_pos_ = pair<int, int>();
		enemy_type_ = -1;
		enemy_kill_score_ = 0;
		enemy_width_ = 0;
		time_moved_ = 0;
		shots_to_fire_ = 0;
		shots_to_kill_ = 0;
		return;
	}

	this->path_ = source.path_;
	this->enemy_center_ = source.enemy_center_;
	this->formation_pos_ = source.formation_pos_;
	this->enemy_type_ = source.enemy_type_;
	this->enemy_kill_score_ = source.enemy_kill_score_;
	this->enemy_width_ = source.enemy_width_;
	this->time_moved_ = source.time_moved_;
	this->enemy_texture_ = source.enemy_texture_;
	this->shots_to_fire_ = source.shots_to_fire_;
	this->shots_to_kill_ = source.shots_to_kill_;
}

Enemy::Enemy(Enemy&& source) noexcept {
	if (source.enemy_type_ == -1) {
		path_.directions.clear();
		path_.in_formation_ = false;
		enemy_center_ = pair<int, int>();
		formation_pos_ = pair<int, int>();
		enemy_type_ = -1;
		enemy_kill_score_ = 0;
		enemy_width_ = 0;
		time_moved_ = 0;
		shots_to_fire_ = 0;
		shots_to_kill_ = 0;
		return;
	}

	this->path_ = source.path_;
	this->enemy_center_ = source.enemy_center_;
	this->formation_pos_ = source.formation_pos_;
	this->enemy_type_ = source.enemy_type_;
	this->enemy_kill_score_ = source.enemy_kill_score_;
	this->enemy_width_ = source.enemy_width_;
	this->time_moved_ = source.time_moved_;
	this->enemy_texture_ = source.enemy_texture_;
	this->shots_to_fire_ = source.shots_to_fire_;
	this->shots_to_kill_ = source.shots_to_kill_;

	source.path_.directions.clear();
	source.path_.in_formation_ = false;
	source.enemy_center_ = pair<int, int>();
	source.formation_pos_ = pair<int, int>();
	source.enemy_type_ = -1;
	source.enemy_kill_score_ = 0;
	source.enemy_width_ = 0;
	source.time_moved_ = 0;
	source.shots_to_fire_ = 0;
	source.shots_to_kill_ = 0;
}

Enemy::~Enemy() {
	this->path_.directions.clear();
	this->path_.in_formation_ = false;
	this->enemy_center_ = pair<int, int>();
	this->formation_pos_ = pair<int, int>();
	this->enemy_type_ = -1;
	this->enemy_kill_score_ = 0;
	this->enemy_width_ = 0;
	this->time_moved_ = 0;
	this->shots_to_fire_ = 0;
	this->shots_to_kill_ = 0;
}

Enemy& Enemy::operator=(const Enemy& source) {
	if (this != &source) {
		this->path_.directions.clear();
		this->path_.in_formation_ = false;
		this->enemy_center_ = pair<int, int>();
		this->formation_pos_ = pair<int, int>();
		this->enemy_type_ = -1;
		this->enemy_kill_score_ = 0;
		this->enemy_width_ = 0;
		this->time_moved_ = 0;
		this->shots_to_fire_ = 0;
		this->shots_to_kill_ = 0;
	}

	this->path_ = source.path_;
	this->enemy_center_ = source.enemy_center_;
	this->formation_pos_ = source.formation_pos_;
	this->enemy_type_ = source.enemy_type_;
	this->enemy_kill_score_ = source.enemy_kill_score_;
	this->enemy_width_ = source.enemy_width_;
	this->time_moved_ = source.time_moved_;
	this->enemy_texture_ = source.enemy_texture_;
	this->shots_to_fire_ = source.shots_to_fire_;
	this->shots_to_kill_ = source.shots_to_kill_;

	return *this;
}

Enemy& Enemy::operator=(Enemy&& source) noexcept {
	if (source.enemy_type_ == -1) {
		this->path_.directions.clear();
		this->path_.in_formation_ = false;
		this->enemy_center_ = pair<int, int>();
		this->formation_pos_ = pair<int, int>();
		this->enemy_type_ = -1;
		this->enemy_kill_score_ = 0;
		this->enemy_width_ = 0;
		this->time_moved_ = 0;
		this->shots_to_kill_ = 0;
		this->shots_to_fire_ = 0;
		return *this;
	}

	this->path_ = source.path_;
	this->enemy_center_ = source.enemy_center_;
	this->formation_pos_ = source.formation_pos_;
	this->enemy_type_ = source.enemy_type_;
	this->enemy_kill_score_ = source.enemy_kill_score_;
	this->enemy_width_ = source.enemy_width_;
	this->time_moved_ = source.time_moved_;
	this->enemy_texture_ = source.enemy_texture_;
	this->shots_to_fire_ = source.shots_to_fire_;
	this->shots_to_kill_ = source.shots_to_kill_;

	// reset source's elements
	source.path_.directions.clear();
	source.path_.in_formation_ = false;
	source.enemy_center_ = pair<int, int>();
	source.formation_pos_ = pair<int, int>();
	source.enemy_type_ = -1;
	source.enemy_kill_score_ = 0;
	source.enemy_width_ = 0;
	source.time_moved_ = 0;
	source.shots_to_fire_ = 0;
	source.shots_to_kill_ = 0;

	return *this;
}


void Enemy::GenerateNewPath() {
	int selection = std::rand() % kNumPathChoices;
	
	//weight the default path so we hopefully don't have an extraordinary number of enemies flying at the player at once
	// if have time, implement continuous enemy movement if there are only a few enemies left on screen
  
	if (selection < kNumPathChoices) {
		std::cout << "swirl" << std::endl;
		this->path_.directions = GenerateSwirlPath();
		this->path_.in_formation_ = false;
		// save for defaultpath
		//this->path_.in_formation_ = true;
	} else if (selection == 6) {
		//these are all set for testing purposes
		int vertical_offset = 50;
		pair<int, int> new_end = { this->enemy_center_.first + 20, ofGetHeight() + vertical_offset };
		this->path_.directions = PathPlotter(this->enemy_center_, new_end, 100);
		this->path_.in_formation_ = false;
	} else {
		this->path_.directions = GenerateDiagPath();
		this->path_.in_formation_ = false;
	}
}

void Enemy::ReturnToFormation() {
	int frames_needed_x = abs(this->enemy_center_.first - this->formation_pos_.first) / kMoveSpeedMax;
	int frames_needed_y = abs(this->enemy_center_.second - this->formation_pos_.second) / kMoveSpeedMax;
	int frames_needed = max(frames_needed_x, frames_needed_y);

	if (frames_needed == 0) {
		this->enemy_center_ = formation_pos_;
	} else {
		this->path_.directions = PathPlotter(this->enemy_center_, this->formation_pos_, frames_needed);
	}

	this->path_.directions.push_back({0, 0});
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

vector<pair<int, int>> Enemy::PathPlotter(pair<int, int> begin, pair<int, int> end, int frame_count) {
	pair<int, int> current = begin;
	int x_change = (end.first - begin.first) / frame_count;
	int y_change = (end.second - begin.second) / frame_count;

	vector<pair<int, int>> to_return;

	for (int i = 0; i < frame_count; i++) {
		to_return.push_back({ x_change, y_change });
	}

	return to_return;
}

vector<pair<int, int>> Enemy::GenerateDiagPath() {
	vector<pair<int, int>> to_return;

	for (int i = 0; i < kMoveFrames; i++) {
		if (i % 2 == 0) {
			to_return.push_back(kDiagDownLeft);
			to_return.push_back(kDiagDownLeft);
			to_return.push_back(kDiagDownLeft);
			to_return.push_back(kDiagDownLeft);
			to_return.push_back(kDiagDownLeft);
			to_return.push_back(kDiagDownLeft);
			to_return.push_back(kDiagDownLeft);
			to_return.push_back(kDiagDownLeft);
		} else {
			to_return.push_back(kDiagDownRight);
			to_return.push_back(kDiagDownRight);
			to_return.push_back(kDiagDownRight);
			to_return.push_back(kDiagDownRight);
			to_return.push_back(kDiagDownRight);
			to_return.push_back(kDiagDownRight);
			to_return.push_back(kDiagDownRight);
			to_return.push_back(kDiagDownRight);
		}
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

vector<pair<int, int>> Enemy::GenerateSwirlPath() {
	vector<pair<int, int>> to_return;

	int iter_count = 10;

	for (int i = 0; i < iter_count; i++) {
		if (std::rand() % 2 == 0) {
			std::cout << "left" << std::endl;
			vector<pair<int, int>> left_curve = GenerateLeftCurve();
			to_return.insert(to_return.end(), left_curve.begin(), left_curve.end());
		} else {
			std::cout << "right" << std::endl;
			vector<pair<int, int>> right_curve = GenerateRightCurve();
			to_return.insert(to_return.end(), right_curve.begin(), right_curve.end());
		}
	}

	return to_return;
}

vector<pair<int, int>> Enemy::GenerateLeftCurve() {
	int move_frames = 10;
	int down_shift = 40;
	int side_shift = 30;

	vector<pair<int, int>> right_arm;
	vector<pair<int, int>> middle_arm;
	vector<pair<int, int>> left_arm;

	pair<int, int> right_end = { this->enemy_center_.first + side_shift, 
		this->enemy_center_.second + down_shift };
	
	pair<int, int> middle_end = { right_end.first,
		right_end.second + (down_shift / 2) };

	pair<int, int> left_end = { middle_end.first - side_shift,
		middle_end.second + down_shift };

	right_arm = PathPlotter(this->enemy_center_, right_end, move_frames);
	middle_arm = PathPlotter(right_end, middle_end, move_frames);
	left_arm = PathPlotter(middle_end, left_end, move_frames);

	vector<pair<int, int>> left_curve = right_arm;
	left_curve.insert(left_curve.end(), middle_arm.begin(), middle_arm.end());
	left_curve.insert(left_curve.end(), left_arm.begin(), left_arm.end());

	return left_curve;
}

vector<pair<int, int>> Enemy::GenerateRightCurve() {
	int move_frames = 10;
	int down_shift = 40;
	int side_shift = 30;

	vector<pair<int, int>> right_arm;
	vector<pair<int, int>> middle_arm;
	vector<pair<int, int>> left_arm;

	pair<int, int> left_end = { this->enemy_center_.first - side_shift,
		this->enemy_center_.second + down_shift };

	pair<int, int> middle_end = { left_end.first,
		left_end.second + (down_shift / 2) };

	pair<int, int> right_end = { middle_end.first + side_shift,
		middle_end.second + down_shift };

	right_arm = PathPlotter(this->enemy_center_, left_end, move_frames);
	middle_arm = PathPlotter(left_end, middle_end, move_frames);
	left_arm = PathPlotter(middle_end, right_end, move_frames);

	vector<pair<int, int>> right_curve = left_arm;
	right_curve.insert(right_curve.end(), middle_arm.begin(), middle_arm.end());
	right_curve.insert(right_curve.end(), right_arm.begin(), right_arm.end());

	return right_curve;
}