#pragma once 

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "character.h"
#include "player.h"
#include "object.h"
#include "Seed.h"
#include "menu.h"

#define SCRWIDTH  1050
#define SCRHEIGHT 1050

using namespace std;
using namespace sf;

Menu menu;

const int Dx[4] = {/*up*/ 0, /*down*/0, /*left*/-1, /*right*/1};
const int Dy[4] = {/*up*/-1, /*down*/1, /*left*/ 0, /*right*/0};

int status = 0; // 0 for the main menu and 1 for the game
int LevelN; 
int range = 11;

Character BGmap[21][21], FGmap[21][21]; // foreground background of the game map

bool gameFinished = false, gameover, levelWon = false, nextWasSeed;
int score=0;
int BASE_SCORE = 10000;

Player player;
bool _moving = false;	
int direction = -1;

int nb_seeds;
int nb_seed_passed = 0;
vector<Seed> seeds;
	
Font mainFont, scoreFont, HPFont, LevelFont;

RectangleShape gameBG;
Sprite gameWinSprite, gameOverSprite, gameWinNext, gameWinHome, homeButton, restartButton;
Texture gameWinTexture, gameOverTexture, gameWinNextTexture, gameWinHomeTexture, homeButtonTexture, restartButtonTexture;
Text scoreText,HPText,LevelText;