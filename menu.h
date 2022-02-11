#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Menu {
	private:
		Sprite startButton, mainTitle,menuBG;
		Texture startButtonTexture, mainTitleTexture, BgTexture;
	public:
		Menu();
		void draw(RenderWindow&);
		bool mousePress(RenderWindow&);
};