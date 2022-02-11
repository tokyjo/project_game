# Wall-e The last hope
This Game is built in C++ and SFML  and developed by MERKACHE Mohammed and RAVEONJATO Faly.

# Goal
The goal of this game is to plant all the seed to a designated place in order to rebuild the environment of the planet.

# Features
This game was based on a sokobox game which we added new features and can be further developed:
-Animated characters
-new traits to the characters
-new challenges with new rules
-One can add new level just by adding a text file in the level folder 

# Inside The Game 
Keyboard:
-Enter: Begin the Game
-Escape : Close the Game

-R: Reset the curret level
-U: Undo the last move
*moving
-Z / Up
-S / Down
-Q / Left
-D / Right

# Create a map
If you ever want an existing map :  http://aide.sokobox.free.fr/Fichiers/niveaux1.html
 Structure of the map : 21*21
-The first caracter in the file should be the number of seed and then the map itself.
-Outside map : '*' 
-Wall        : '#'
-player      : '@'
-empty       : ' '
-goal        : '.'
-uranium     : 'u'
-seed        : '$'

# Game Rules: 
-Plant all the seed 
-If you step on the a radioactive part , you lost some hit point
-If a seed is placed on the a radioactive part, it's game over
-If the score or the HP reach 0, it's game over too

