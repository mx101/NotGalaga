#pragma once
#include "ofMain.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

//some enums to represent game state
enum GameState { IN_PROGRESS = 0, PAUSED, FINISHED };

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  void drawGameDead();

  void ShootBullet();

  void CheckEnemyCollisions();
  void CheckPlayerCollisions();

  void CreateEnemy(int x, int y, int type);

  const int kGameWindowWidth = 800;
  const int kGameWindowHeight = 1000;

  ofTrueTypeFont font;
  const int kFontSize = 24;


  bool left_pressed;
  bool right_pressed;
  bool shoot_pressed;


  // still to be used
  const int kEnemyCount = 44;
  const int kFirstBeeIdx = 0;
  const int kFirstMothIdx = 20;
  const int kFirstBossIdx = 40;
  
  Player player;
  const int kFighterWidth = 48;
  const int kFighterHeight = 48;
  const int kFighterMoveSpeed = 8;

  Bullet player_bullet;
  const int kBulletWidth = 10;
  const int kBulletHeight = 14;
  const int kBulletSpeed = 16;
  vector<Bullet*> player_bullets;
  const int kLegalBulletsMax = 2;

  Bullet enemy_bullet;
  vector<Bullet*> enemy_bullets;

  vector<Enemy*> enemies;
  Enemy demo_bee;
  Enemy demo_boss;
  const int kEnemyWidth = 40;
  const int kEnemyHeight = 40;
  const int kEnemyMoveSpeed = 4;
  const int kEnemySpawnHeight = -20;

  
};
