#include "enemy.h"
/**
	// Copy constructor
	template<typename ElementType>
	LinkedList<ElementType>::LinkedList(const LinkedList<ElementType> &source) {
		if (source.empty()) {
			this->clear();
			return;
		}

		this->head_ = new LinkedListNode(source.head_->data_);
		LinkedListNode *curr_node = source.head_->next_;
		LinkedListNode *previous = this->head_;
		this->length_ = source.length_;

		while (curr_node != nullptr) {
			previous->next_ = new LinkedListNode(curr_node->data_);
			previous = previous->next_;
			curr_node = curr_node->next_;
		}
	}


*/

Enemy::Enemy() {
	path_ = EnemyPath();
	enemy_center_ = pair<int, int>();
	formation_pos_ = pair<int, int>();
	enemy_type_ = -1;
	enemy_kill_score_ = 0;
	enemy_width_ = 0;
	time_moved_ = 0;
	shots_to_fire_ = 0;
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

	source.path_.directions.clear();
	source.path_.in_formation_ = false;
	source.enemy_center_ = pair<int, int>();
	source.formation_pos_ = pair<int, int>();
	source.enemy_type_ = -1;
	source.enemy_kill_score_ = 0;
	source.enemy_width_ = 0;
	source.time_moved_ = 0;
	source.shots_to_fire_ = 0;
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

	return *this;
}


void Enemy::GenerateNewPath() {
	int selection = std::rand() % kNumPathChoices;
	
	//weight the default path so we hopefully don't have an extraordinary number of enemies flying at the player at once
	// if have time, implement continuous enemy movement if there are only a few enemies left on screen
  
	if (selection < 6) {
		this->path_.directions = GenerateDefaultPath();
		this->path_.in_formation_ = true;
	} else {
		//these are all set for minimum testing purposes
		int vertical_offset = 50;
		pair<int, int> new_end = { this->enemy_center_.first + 20, ofGetHeight() + vertical_offset };
		this->path_.directions = PathPlotter(this->enemy_center_, new_end, 100);
		this->path_.in_formation_ = false;
	}
	
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

	float ratio = float(x_change) / (float(x_change) + float(y_change));
	int x_move = kMoveSpeedMax * ratio;
	int y_move = kMoveSpeedMax - x_move;

	vector<pair<int, int>> to_return;

	for (int i = 0; i < frame_count; i++) {
		to_return.push_back({ x_move, y_move });
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