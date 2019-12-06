#pragma once
#include "ofMain.h"
#include "src/player.h"
#include "src/enemy.h"
#include "src/bullet.h"
#include <Windows.h>
#include <Xinput.h>
#include "lib/ofxXboxController.h"
#include <tuple>

//some enums to represent game state
enum GameState { IN_PROGRESS = 0, PAUSED, FINISHED };

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

  void RestartGame();
  void LoadData();

  void keyPressed(int key);
  void keyReleased(int key);

  void DeathVibration();
  void UpdatePlayerObjects();
  void UpdateEnemyObjects();

  void DrawSideboard();
  void DrawScoreboard();
  void DrawNonPlayerObjects();

  void DrawGameDead();
  void RevivePlayer();

  void ShootBullet(std::pair<int, int> center, int velocity, bool player_shot);

  void GenerateWave();
  void ReturnToFormation(); // currently instantly teleports enemies to starting position

  queue<pair<int, int>> GenerateDefaultPath();
  queue<pair<int, int>> GeneratePath();
  pair<int, int> GenerateRandomMove();  // returns a single move in the form of
                                        // (delta x, delta y)

  pair<int, int> kZeroMove = {0, 0};
  pair<int, int> kLeftMove = {-10, 0};
  pair<int, int> kRightMove = {10, 0};

  void CheckEnemyCollisions();
  void CheckPlayerCollisions();

  Enemy * CreateEnemy(int x, int y, int type);

  bool game_running_;
  int high_score_;
  int waves_;
  int timer_;

  //Xbox controller support
  ofxXboxController xbox;
  bool deadZone;
  Gamepad* gamepad;

  ofSoundPlayer theme_music_;


  const int kGameWindowWidth = 800;
  const int kGameWindowHeight = 1000;
  const int kSideboardWidth = 300;
  const int kOffset = 50;


  ofTrueTypeFont message_font_;
  ofTrueTypeFont side_font_;
  const int kMessageSize = 16;
  const int kSideSize = 20;
  const int kSideboardSpacing = 30;


  bool left_pressed;
  bool right_pressed; 
  bool shoot_pressed;


  Player player;
  int score_;
  const int kFighterWidth = 48;
  const int kFighterHeight = 48;
  const int kFighterMoveSpeed = 5;



  Bullet player_bullet_;
  const int kBulletWidth = 10;
  const int kBulletHeight = 14;
  const int kPlayerBulletSpeed = -16;
  vector<Bullet*> player_bullets_;
  const int kLegalBulletsMax = 2;

  const int kReloadTime = 15;
  const int kPauseTime = 10;
  int time_last_shot;
  int time_last_paused;
  

  Bullet enemy_bullet_;
  vector<Bullet*> enemy_bullets_;
  const int kEnemyBulletSpeed = 10;

  vector<Enemy*> enemies_;
  Enemy bee_;
  Enemy boss_;
  Enemy moth_;

  const int kBeeMothWidth = 40;
  const int kBeeMothHeight = 40;
  const int kBossWidth = 60;
  const int kEnemySpacing = 60;
  const int kEnemyDefaultMoveSpeed = 2;
  const int kEnemySpawnHeight = -20;
  const int kBeeStartX = 20;  // change kStartX and kStartY
  const int kBeeStartY = 250;
  const int kMothStartX = 70;
  const int kBossStartX = 170;
  const int kBeeCount = 20;  // 20 bees total
  const int kMothCount = 16;  // 16 moths total
  const int kBossCount = 4;  // 4 boss galaga total
  
};
