## CS 126 Project Proposal 
### Michael Xiang
For my final project, I intend on recreating a classic arcade game in the style of [__*Galaga*__](https://en.wikipedia.org/wiki/Galaga). It is a classic "fixed shooter" game where the player must defeat waves of space bugs and avoid incoming projectiles. My influence for completing this project is based from childhood nostalgia as this was my favorite arcade game to play growing up.

I currently plan on using the [ofxBox2d](https://github.com/vanderlin/ofxBox2d) external library to work as a 2D physics engine for handling collision and physical object generation in my game. Additionally, *ofxBox2d* can provide the gravity needed for enemy projectiles. Along with this, I plan to use external math libraries like this [Poisson point generator](https://github.com/corporateshark/poisson-disk-generator) and [matplotlib](https://github.com/lava/matplotlib-cpp) to plot out possible enemy paths for __*Galaga*__.

The current timeline for this project (detailed more specifically by week below) covers the key gameplay functionalities of __*Galaga*__. This includes player movement/shooting, enemy movement (paths)/shooting, enemy types, player [kidnapping/rescuing](https://youtu.be/bnGl9P2TVUc?t=43), a scoreboard, incrementing wave difficulty, etc.

To elaborate more on certain aspects, the program will keep track of player score per enemy killed. Once the player loses a set number of "lives", the game will display the scoreboard. If the current score beats at least the lowest of the top 3 scores, the application will prompt the user to input a 3 letter nickname to map their score to and add this to the scoreboard. Currently, I plan on storing this scoreboard to an independent text file and loading in past score data each time the game ends.

Some stretch goals I would want to implement if this project is finished ahead of schedule would be a full arcade machine. I don't believe it would be hard to make a "selection screen" but rather most of the extra time would be dedicated to creating/replicating more games. Some additional games to implement could be: [__*Space Invaders*__](https://en.wikipedia.org/wiki/Space_Invaders), Chess, Checkers, [__*Missile Command*__](https://en.wikipedia.org/wiki/Missile_Command)
### Timeline
- #### Week 1
  - [ ] Create graphical elements for __*Galaga*__
    - [X] Player Ship
    - [ ] Enemy Space Bugs
    - [ ] Player projectiles
    - [ ] Enemy projectiles
    - [ ] Player/Enemy death
    - [ ] Score/Life Display
    - [ ] Background stars (optional)
  - [ ] Start main __*Galaga*__ game engine
    - [X] Player movement
    - [ ] Player shooting
- #### Week 2
  - [ ] Continue game engine
    - [ ] Enemy movement
    - [ ] Enemy shooting (only for some enemy types)
    - [ ] Collision handling
    - [ ] Start more advanced enemy movement/paths (not an absolute priority)
- #### Week 3
  - [ ] Continue game engine
    - [ ] Player kidnapping/rescue
    - [ ] Player lives
    - [ ] Start wave difficulty handling (should be slightly exponential)
  - [ ] Scoreboard display at end of game
  - [ ] Add any other application text output needed i.e. *"Fighter Captured"*, *"Game Over"*, *"Game Start"*, etc.
- #### Week 4
  - [ ] Finish anything that was pushed back from previous weeks
  - [ ] Complete additional testing, if need be
- #### Stretch Goals
  - [ ] Create more arcade games, refer to above list
________
## Previous draft:
For my final project, I intend on creating a retro-arcade machine. The users will be able to select between an assortment of games (2 minimum) in a "main menu" screen. The two minimum I plan on having in my "arcade machine" are two that I grew up playing: __*Galaga*__ and __*Tank Wars*__.

[__*Galaga*__](https://en.wikipedia.org/wiki/Galaga) is a classic "fixed shooter" game where the player must defeat waves of enemies and avoid incoming projectiles.

__*Tank Wars*__ is an "artillery strategy" game. A few popular examples of this type are [Worms](https://en.wikipedia.org/wiki/Worms_\(series\)) and the more recent [Shellshock Live](https://www.shellshocklive.com/). Players face off against each other, either taking turns or shooting simultaneously attempting to hit opponents with their projectiles.

I currently plan on using the [ofxBox2d](https://github.com/vanderlin/ofxBox2d) external library to work as a 2D physics engine for handling collision and physical object generation in both my games. Additionally, *ofxBox2d* can provide the gravity needed for my artillery tank game. Along with this, I plan to use external math libraries like this [Poisson point generator](https://github.com/corporateshark/poisson-disk-generator) and [matplotlib](https://github.com/lava/matplotlib-cpp) to plot out possible enemy paths for __*Galaga*__.

Some current stretch goals I plan to implement if time allows include a "scoreboard" page where you can view past high scores of the games played. If the scores beat the previous 3 highest scores of each game, the application should prompt the user to input a 3 letter "nickname" to hold their score for. Currently, I plan on storing this to an independent text file and loading in past score data whenever the "scoreboard" page is accessed by the user.
### Timeline
- #### Week 1
  - [ ] Create a menu GUI
  - [ ] Allow navigation between "pages" in the menu (these can direct to nothing for now)
  - [ ] Create graphical elements for both games
- #### Week 2
  - [ ] Start main __*Galaga*__ game engine
  - [ ] Complete collision handling
  - [ ] Generate enemy paths
  - [ ] Link this to the menu page so that moving left/right and selecting one of the options will move you into __*Galaga*__
- #### Week 3
  - [ ] Complete __*Galaga*__ player shooting and movement
  - [ ] Start main __*Tank Wars*__ game engine
  - [ ] Adjust collision handling from __*Galaga*__ to also function for __*Tank Wars*__ if possible
  - [ ] Generate player movement and shooting
  - [ ] Link this to the menu page so that moving left/right and selecting one of the options will move you into __*Artillery Game*__
- #### Week 4
  - [ ] Complete anything additional for __*Tank Wars*__, add additional weapon types?
  - [ ] Complete additional testing, if need be
- #### Stretch Goals
  - [ ] Implement *Scoreboard* page
  - [ ] Create more arcade games
    - Other ideas: *Space Invaders*, Chess, Checkers, *Missile Command*
    
### Notes:
- Perhaps it is too ambitious to plan multiple games and would be better to instead focus on one?