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

- 7:30pm - Renamed kFontSize to kMessageSize and also added another ofTrueTypeFont kScoreSize for displaying the score text on the side

- 7:45pm - We have a line of separation between the scoreboard and gameplay area now!

- 8:30pm - Changed font to a Galaga-esque one instead of Arial. DrawScoreboard() renamed to DrawSideboard() and partially implemented to show lives.

- 11:00pm - Made some fixes to game logic, player cannot die/move/shoot when dead, also centered life count in sideboard

- 11:10pm - Added score display in sideboard

- 11:30pm - Added additional logic for player death, also loaded player death gif

- 11:40pm - Added different update logic for if player has lives or no

- 11:50pm - Noted some more needed items for DrawScoreboard()

### 12/5/19
- 12:00am - Changed so that the bee, moth, and boss galaga images are all loaded in setup(), some additional notes/comments in other areas

- 12:25am - Started Wave Generator function in ofApp

- 12:35am - Basic function structure created for above method. Now just need the math for what coordinate to start spawning.

- 12:45am - Added basic wave number display to sideboard

- 12:55am - Adjusted some variable names to be consistent in style

- 1:15am - Streamlined ShootBullet() function to create a bullet for either a player or enemy bullet

- 1:30am - Enemies can now shoot, their bullets are currently invisible... whoops

- 1:35am - Enemy bullets are no longer invisible

- 11:30am - Started Wave generation system. Currently activates on single key press and spawns in a line of bees

- 11:45am - Playing around with std::rand() to determine if an enemy should shoot or no

- 11:55am - Slight tangent to include XInput header

- 12:00pm - Logic fix in Generate Wave so enemies now actually spawn in rows

- 12:05pm - Different enemy types now spawn

- 12:40pm - Added ability to move and shoot

- 12:45pm - Adjusted player movement speed

- 12:50pm - Condensed some setup() lines into a LoadData() function that calls most of the load functions for oF objects

- 1:30pm - Finishing GenerateWave() function

- 1:45pm - Fixed bug that caused enemies to have massive hitboxes

- 2:15pm - Fixed literal edge case of player fighter extending past the game window on the right side

- 2:20pm - Fixed player fighter extending past game window on left side

- 2:50pm - Planning out complex enemy move generation

- 7:10pm - Completed GenerateMove() which returns a tuple representing a change in x and y

### 12/6/19
- 1:30am - Finally functioning controller support! Currently, the controller controls a test sphere

- 1:45am - Controller can now move and shoot player fighter

- 1:55am - Removed controller testing sphere and controller display information

- 2:30am - Condensed some code in ofApp::draw() into a DrawNonPlayerObjects() function to improve readability

- 2:45am - Added enemy kill score variable. Killing an enemy will actually increase the player's score now

- 2:50am - Deleted the unnecessary CreateRandPath function that utilized the Poisson Generator library

- 3:02am - Making some design improvements to GenerateWave()

- 3:05am - Moved/Deleted some unnecessary constants

- 3:10am - Running into a weird vector out of bounds error when attempting to add theme music 

- 3:15am - Successfully added theme music, bug occurred when ofSoundPlayer for theme music was loaded before the xbox controller was created in setup()

- 3:25am - Condensed update code into helper functions to improve readability

- 3:35am - Changed GeneratePath() and GenerateRandomMove() to deal with pairs instead of tuples to stay consistent with rest of project

- 4:00am - Started enemy movement based on a queue of direction changes

- 4:15am - Added vibration on death

- 4:20am - Added specific widths depending if enemy is a bee/moth/boss

- 4:30am - Added pseudotimer, currently primarily used for limiting shooting speed. In the future, implement into enemy movement, possibly make some EnemyMove() function that takes in whether the enemy movement should wait or not?

- 4:55am - Implemented pseudotimer in player death vibration

- 5:10am - Now storing enemy path in an inner struct to the Enemy class

- 5:30am - Doing some file organization to fix GitHub Issue #2

- 5:35am - Added RestartGame function to improve readability in setup() and add ability for player to play again after losing all lives

- 5:45am - Adjusted some spacing on the sideboard

- 6:15am - Added clock for enemy default move so it is a recognizable shift in enemy position instead of an incredibly fast teleport between multiple locations

- 6:25am - Keeping track of shots fired by the player and shots landed 

- 6:30am - Changes to earning score, specifically about whether the enemy is in formation or not

- 6:45am - Made some adjustments to enemy spawn coordinates

- 7:00am - Created PathPlotter() function that creates a queue based on a default frame_count in which we want the enemy to travel from point A to point B in.

### 12/9/19
- 11:15pm - Adding fixes to PathPlotter(), making this an enemy class function instead of ofApp along with GenerateDefaultPath

### 12/10/19
- 12:40am - Moved over rest of path functions to enemy class, start fixing and refining

- 1:20am - Big 5 implemented for enemy class so that C++ won't argue with the compiler, tested and game still functions properly

- 1:35am - Fixed whitespacing for ofApp.cpp

- 10:10am - Starting Diagonal downwards movement for enemy units

- 10:30am - Diagonal movement works for enemy units. TODO: Make sure enemy units end up at their starting position, make this diag movement less weird.

- 11:10am - Various changes, adjusted enemy size to be more similar to the actual game. Also changed PathPlotter() to be more flexible as a path vector creator.

- 1:30pm - Modifying when an enemy will shoot

- 4:00pm - Started GenerateSwirlPath, bug fixed in PathPlotter

- 4:20pm - GenerateRightCurve and GenerateLeftCurve tested and functioning

- 7:45pm - Added additional controller inputs and final scoreboard display

- 8:15pm - Added shots fired and shots hit to scoreboard

- 9:20pm - Implemented ReturnToFormation so enemies return to their original position after running out of moves

- 11:00pm - Started implementing enemy fly in, if have time, set the enemies' default path movement to a private member var of ofApp whenever the enemies are in formation so that all the enemies will move together.

### 12/11/19
- 12:00am - DrawSideboard now prints onto an ofRectangle to hide the incoming enemies on the right side

- 12:15am - FlyIn works now but it's messing with the Enemy formation positions.

- 12:30am - Enemy fly in no longer messes with the enemies' formation positions. This was fixed by adjusting ReturnToFormation()'s tolerance for instant teleportation from == 0 to <= 1

- 10:45am - Trying new function CheckAllReady(), O(# of enemies) runtime, to bind all enemies to a single default path movement

- 11:10am - Player given ability to press start to start the next wave, the other implementation for wave start would be setting a timer but this feels like a better design choice to me. Also, CheckAllReady() does not seem to have a noticeable effect on runtime

- 7:10pm - Enemies now all move together when in formation. Bug that now exists is formation entirely stops moving when waiting for enemies to return to formation
