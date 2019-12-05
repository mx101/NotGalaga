## CS 126 Project Proposal 
### Michael Xiang
For my final project, I intend on recreating a classic arcade game in the style of [__*Galaga*__](https://en.wikipedia.org/wiki/Galaga). It is a classic "fixed shooter" game where the player must defeat waves of space bugs and avoid incoming projectiles. My influence for completing this project is based from childhood nostalgia as this was my favorite arcade game to play growing up.

I currently plan on using an external math libraries like this [Poisson point generator](https://github.com/corporateshark/poisson-disk-generator) and [matplotlib](https://github.com/lava/matplotlib-cpp) to plot out possible creative enemy paths for __*Galaga*__.

The current timeline for this project (detailed more specifically by week below) covers the key gameplay functionalities of __*Galaga*__. This includes player movement/shooting, enemy movement (paths)/shooting, enemy types, player [kidnapping/rescuing](https://youtu.be/bnGl9P2TVUc?t=43), a scoreboard, incrementing wave difficulty, etc.

To elaborate more on certain aspects, the program will keep track of player score per enemy killed. Once the player loses a set number of "lives", the game will display the scoreboard. If the current score beats at least the lowest of the top 3 scores, the application will prompt the user to input a 3 letter nickname to map their score to and add this to the scoreboard. Currently, I plan on storing this scoreboard to an independent text file and loading in past score data each time the game ends.

Some stretch goals I would want to implement if this project is finished ahead of schedule would be a full arcade machine. I don't believe it would be hard to make a "selection screen" but rather most of the extra time would be dedicated to creating/replicating more games. Some additional games to implement could be: [__*Space Invaders*__](https://en.wikipedia.org/wiki/Space_Invaders), Chess, Checkers, [__*Missile Command*__](https://en.wikipedia.org/wiki/Missile_Command)
### Timeline
- #### Week 1
  - [X] Create graphical elements for __*Galaga*__
    - [X] Player Ship
    - [X] Enemy Space Bugs
    - [X] Player projectiles
    - [X] Enemy projectiles
    - [X] Player/Enemy death
    - [X] Score/Life Display
  - [X] Start main __*Galaga*__ game engine
    - [X] Player movement
    - [X] Player shooting
- #### Week 2
  - [X] Continue game engine
    - [X] Enemy movement
    - [X] Enemy shooting (only for some enemy types)
    - [X] Collision handling
    - [X] Player lives
- #### Week 3
  - [ ] Continue game engine
	- [X] Implement wave creation
	- [?] Start more advanced enemy movement/paths
    - [?] Start wave difficulty handling (should be slightly exponential)
	  - Some ideas for this could be:
	    - more shooting
		- more random movement paths
  - [?] Scoreboard display at end of game
  - [ ] Add any other application text output needed i.e. *"Fighter Captured"*, *"Game Over"*, *"Game Start"*, etc.
- #### Week 4
  - [ ] Player kidnapping/rescue
  - [ ] Finish anything pushed back from previous weeks
  - [ ] Complete additional testing, if need be
- #### Stretch Goals
  - [ ] Create more arcade games, refer to above list
