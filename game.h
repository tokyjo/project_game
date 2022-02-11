#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "level.h"

using namespace sf;

class game {
    private:
        /*variable window */
        VideoMode videoMode;
    	RenderWindow *window;

        Font font; 
    	Clock winClock;
        Image icon;

    	bool winPic = true;
    	
    public:
        game();
        ~game();

        /*init*/
        void initVariables();
        void initWindow();
        void initializeSprites(); 
        void init_square(int i, int j, int x, int y, char bg_type, char fg_type);
        void init_player(int i, int j, int x, int y, char bg_type, char fg_type);
        void initiateLevel(level&, int);
        void setmap(char type);

        /* move */
        bool PossibleMove(int dir);
        void verticalMove(int dir);
        void horizontalMove(int dir);
        void move(int dir);
        void undo();
        
        bool NextIsSeed(int dir);
        bool gameWin();
        bool mousePress(int spriteNo);

        /***********/
        void render();
        void gameLoop();
        void endGame();
};