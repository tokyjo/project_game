#include "menu.h"

Menu::Menu(){
//Title
	if (!mainTitleTexture.loadFromFile("images/title.png"))
	{
		std::cout << "Failed to load main title spritesheet!" << std::endl;
	}
	mainTitle.setTexture(mainTitleTexture, true);
	mainTitle.setPosition(Vector2f(0, 100));

    //background 
	
    if (!BgTexture.loadFromFile("images/Space.png"))
    {
        std::cout <<"Failed to load Bg image spritesheet"<< std::endl;
    }
    menuBG.setTexture(BgTexture,true);
    menuBG.setPosition(Vector2f(0,0));
	
/*
	Color background(0, 29, 61);
	menuBG.setFillColor(background);
	menuBG.setPosition(0, 0);
	menuBG.setSize(Vector2f(1050, 1050));
*/
	//start Button
	if (!startButtonTexture.loadFromFile("images/start_button.png"))
	{
		std::cout << "Failed to load play button spritesheet!" << std::endl;
	}
	startButton.setTexture(startButtonTexture, true);
	startButton.setPosition(Vector2f(363, 600));
	startButton.setScale(Vector2f(2,2));
}

void Menu::draw(RenderWindow& window){
	window.draw(menuBG);
	window.draw(mainTitle);
	window.draw(startButton);
}

bool Menu::mousePress(RenderWindow& window){
    int mouseX = Mouse::getPosition().x;
	int mouseY = Mouse::getPosition().y;
	Vector2i windowPosition = window.getPosition();
    if (mouseX > startButton.getPosition().x + windowPosition.x && mouseX < (startButton.getPosition().x + startButton.getGlobalBounds().width + windowPosition.x)
     && mouseY > startButton.getPosition().y + windowPosition.y && mouseY < (startButton.getPosition().y + startButton.getGlobalBounds().height + windowPosition.y)) {
        if (Mouse::isButtonPressed(Mouse::Left))
            return  true;
    }
    return false;
}