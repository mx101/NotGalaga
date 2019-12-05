## DEV LOG
### Week 1
#### 11/19/19
- 1:30pm - First setup of project, basic files for running the program created. Still need to add matplotlib.h somewhere

- 3:15pm - Attended lecture, added some notes for openFrameworks

- 5:45pm - Ate dinner, back now. Added in player fighter/captured fighter textures, now adding this into the setup of the game

- 6:00pm - Player texture now loads in at the start of the game in the bottom center of the window

- 6:20pm - First major proof of life: player ship can now move around the screen

- 6:44pm - Background color of window is now black. Started Enemy class, adding necessary member variables

- 7:00pm - Added constructors to Enemy class, 0 represents a bee, 1 represents a moth, 2 represents a boss Galaga. Also added the pngs for these textures in the bin/data folder

- 7:20pm - Formatting adjusted to be more consistent

- 8:30pm - Took a short break. Running into compiler errors when pushing back onto the enemies vector

- 9:00pm - Attempted fix for generating the enemies vector, not working :(, will move on and come back to this at a later time

- 9:30pm - Not entirely sure why some things seem to be messing with the compiler but I'd guess it's an issue with the way openFrameworks compiles its part of the project

- 10:00pm - Program compiles with addition of PoissonGenerator.h

- 11:00pm - Been trying to setup Catch2 to function properly, wrote function of path_plotter() that returns a vector of std::pairs representing points. This function still needs to be tested. A test case was written located in the tests.cpp folder for path_plotter()

## Week 2
### Plan for this week:
Implement player shooting and enemy movement at the very least.
### 11/22/19
- 12:00pm - Likely planning on switching over to ofxUnitTests if Catch2 does not cooperate soon.

### 12/3/19
- 9:00pm - Added a new bullet class. This is planned to be used for handling player projectiles, could also may be used for enemy projectiles.

- 9:30pm - Planning more necessary functions, added checkPlayerCollisions and checkEnemyCollisions

#### 12/4/19
- 3:00am - Started bullet handling, will provide an update once this reaches a point at which it is reasonable to provide an update on.

- 3:20am - Found galaga bullet sprite online, loading this onto a default "bullet" Bullet var in ofApp.h 

- 3:30am - Player can now shoot bullets! Right now, the player can shoot as fast as the keyboard takes in input because of player_shots_ being a negative value once the first player bullet moves off screen.

- 3:40am - Fix applied to bullet count. Player can now only have two bullets on screen at a time.

- 4:00am - Working on enemy/bullet collision now.

- 4:20am - Enemy/Bullet collision is functioning. If the bullet ofRectangle and enemy ofRectangle intersect, both are deleted.

- 4:30am - Some play testing at the current stage.

- 4:35am - Created generic CreateEnemy helper function. Takes in an x, y, and type to create an enemy in the game.

- 4:50am - Added bounds on player movement (player can no longer move off screen)

- 5:00am - Working on Player/Enemy Collision now, centered player bullet

- 5:15am - Player/Enemy Collision functions, player still not implemented to "die" when colliding with Enemy object. Added some more functionality with player lives and player alive bool.

- 5:30am - Enemies now reappear after going off the screen at the bottom

- 5:40am - Attempting to implement multiple key press recognition

- 5:50am - So far unable to get multiple keys, posted on Piazza. However, I have added a ShootBullet() function for readability purposes.

- 6:00am - Added constants to lessen number of magic numbers. 

- 6:05am - Added player shooting sound effect

- 6:20am - Added enemy bullet image. Also, we are now differentiating between enemy bullets and player bullets

- 11:00am - Added drawGameDead function that prints out a simple life lost message in the window when the player ship dies.

- 11:20am - Extended window size and restricted actual game play area to make room for Score, life display

- 11:25am - Added RevivePlayer() function to improve readability for ofApp::keyPressed()

- 7:00pm - Added some notes and predicted variables/functions