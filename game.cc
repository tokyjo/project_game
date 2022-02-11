#include "game.h"
#include "variable.h"

/* Constructor */
game::game()
{
	initWindow();
	initVariables();
	initializeSprites();
}

/* Destructor */
game::~game(){
	delete window;
}

/* return @void | load the icon of game */
void game::initVariables() {
	icon.loadFromFile("Wall-E.png");
	window->setIcon(50, 50, icon.getPixelsPtr());
	window->setKeyRepeatEnabled(false);
}

/* return @void | init the window */
void game::initWindow() {
	videoMode = sf::VideoMode(SCRWIDTH, SCRHEIGHT);
	window = new sf::RenderWindow(videoMode, "Wall-E Game ");
	window->setFramerateLimit(60);
	window->setKeyRepeatEnabled(false);
}

/* return @void | set the color of bg set the window */
void game::initializeSprites(){
	//Game background
	Color background(247, 232, 177);
	gameBG.setFillColor(background);
	gameBG.setPosition(0, 0);
	gameBG.setSize(Vector2f(SCRWIDTH, SCRHEIGHT));

	//Game Won Sprite
	if (!gameWinTexture.loadFromFile("images/game_win.png"))
		std::cout << "Failed to load game_win spritesheet!" << std::endl;
	gameWinSprite.setTexture(gameWinTexture);
	gameWinSprite.setPosition(Vector2f(0, 0));

	//Game Over Sprite
	if (!gameOverTexture.loadFromFile("images/game_over.png"))
		std::cout << "Failed to load game_over spritesheet!" << std::endl;
	gameOverSprite.setTexture(gameOverTexture);
	gameOverSprite.setPosition(Vector2f(162, 81));
	gameOverSprite.setScale(Vector2f(1.5,1.5));
	
	//Next button
	if (!gameWinNextTexture.loadFromFile("images/next.png"))
		std::cout << "Failed to load next button spritesheet!" << std::endl;
	gameWinNext.setTexture(gameWinNextTexture);
	gameWinNext.setPosition(Vector2f(806, 749));
	gameWinNext.setScale(Vector2f(1.5,1.5));

	//Home button
	if (!gameWinHomeTexture.loadFromFile("images/home_button.png"))
		std::cout << "Failed to load home button spritesheet!" << std::endl;
	gameWinHome.setTexture(gameWinHomeTexture);
	gameWinHome.setPosition(Vector2f(100, 796));
	gameWinHome.setScale(Vector2f(1.5,1.5));
	
	// counter text (in game)
	scoreFont.loadFromFile("Fonts/PKMN RBYGSC.ttf");
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(30);
	scoreText.setPosition(Vector2f(10, 10));
	scoreText.setString("SCORE: " + to_string(score));
	
	//hp text (in game)
	HPFont.loadFromFile("Fonts/PKMN RBYGSC.ttf");
	HPText.setFont(HPFont);
	HPText.setCharacterSize(30);
	HPText.setPosition(Vector2f(10, 50));
	HPText.setString("HP: " + to_string(player.getHP()) + "/" + to_string(player.getMaxHP()));

	//Level text (in game)
	LevelFont.loadFromFile("Fonts/PKMN RBYGSC.ttf");
	LevelText.setFont(LevelFont);
	LevelText.setCharacterSize(30);
	LevelText.setPosition(Vector2f(850, 10));
	LevelText.setString("Level " + to_string(LevelN));
}

/* return @void | set the sprite of a bloc */
void game::init_square(int i, int j, int x, int y, char bg_type, char fg_type){
	BGmap[i][j].setType(bg_type);
	BGmap[i][j].initialize();
	BGmap[i][j].setPosition(x,y);
	FGmap[i][j].setType(fg_type);
	FGmap[i][j].initialize();
	FGmap[i][j].setPosition(x,y);
}

/* return @void | set the player's sprite on the window */
void game::init_player(int i, int j, int x, int y, char bg_type, char fg_type){
	init_square(i,j,x,y,bg_type,fg_type);
	player.setType('@');
	player.initialize();
	player.setPosition(x,y);
	player.setPosX(j);
	player.setPosY(i);
}

/* return @void | init the map */
void game::initiateLevel(level& currentLevel, int N) {
	gameover=false;
	gameFinished=false;
	score = BASE_SCORE;
	levelWon = false;
	player.setHP(player.getMaxHP());

	setmap('?');
	currentLevel.empty();
	currentLevel.initialize(N);
	LevelText.setString("Level " + to_string(LevelN));

	nb_seeds = currentLevel.getNbSeeds();
	for (int i=0; i<nb_seeds; i++){
		Seed elem;
		seeds.push_back(elem);
	}

	int initialX = 0, initialY = 100;
	for (int i = 0; i < 21; i++) {
		initialX = 50;
		for (int j = 0; j < 21; j++) {
			switch (currentLevel.getContent(i, j)){
				case ' ': init_square(i,j,initialX,initialY,' ','?'); break; //Empty
				case '#': init_square(i,j,initialX,initialY,'#','?'); break; //Wall
				case '.': init_square(i,j,initialX,initialY,'.','?'); break; //Goal
				case '$': init_square(i,j,initialX,initialY,' ','$'); break; //seed
				case '@': init_player(i,j,initialX,initialY,' ','?'); break; //Player
				case '?': init_square(i,j,initialX,initialY,'.','+'); break; //seed on Goal
				case '+': init_player(i,j,initialX,initialY,'.','?'); break; //Player on Goal
				case 'u': init_square(i,j,initialX,initialY,'u','?'); break; // magma
				case 'T': init_square(i,j,initialX,initialY,'T','?'); break; //trash_empty
				default:  //S P A C E
					FGmap[i][j].setType('?');
					FGmap[i][j].initialize();
					FGmap[i][j].setPosition(initialX, initialY);
			}
			initialX += 50;
		}
		initialY += 50;
		initialX = 50;
	}
													
}

/* return true when -next button is pressed or -home button is pressed */
bool game::mousePress(int spriteNo) {
	int mouseX = Mouse::getPosition().x;
	int mouseY = Mouse::getPosition().y;

	Vector2i windowPosition = window->getPosition();

	switch (spriteNo) {
	case 0: //Next Button
		if (mouseX > gameWinNext.getPosition().x + windowPosition.x && mouseX < (gameWinNext.getPosition().x + gameWinNext.getGlobalBounds().width + windowPosition.x)
			&& mouseY > gameWinNext.getPosition().y + windowPosition.y && mouseY < (gameWinNext.getPosition().y + gameWinNext.getGlobalBounds().height + windowPosition.y)) {
			if (Mouse::isButtonPressed(Mouse::Left))
				return true;
		}
		break;
	case 1: //Home Button
		if (mouseX > gameWinHome.getPosition().x + windowPosition.x && mouseX < (gameWinHome.getPosition().x + gameWinHome.getGlobalBounds().width + windowPosition.x)
			&& mouseY > gameWinHome.getPosition().y + windowPosition.y && mouseY < (gameWinHome.getPosition().y + gameWinHome.getGlobalBounds().height + windowPosition.y)) {
			if (Mouse::isButtonPressed(Mouse::Left))
				return true;
		}
		break;
	}
	return false;
}

/* return @void |update the window after the game ended */
void game::endGame(){
	if (gameFinished) {
		window->draw(gameWinSprite);
		window->draw(gameWinHome);
		levelWon = true;
	}
	else if ((gameWin() || levelWon) && !gameFinished) {
		window->draw(gameWinSprite);
		window->draw(gameWinHome);
		window->draw(gameWinNext);
		levelWon = true;
	}
	else if (gameover)
	{
		window->draw(gameOverSprite);
		window->draw(gameWinHome);
	}
}

/* return @void | rendering of all sprites */
void game::render(){
	window-> clear(); //clear window 
	if (status==0){
		menu.draw(*window);
	}
	else{
		/*rendering phases*/
		window->draw(gameBG);
		
		for (int i = 0; i < 21; i++) {
			for (int j = 0; j < 21; j++) {
				BGmap[i][j].draw(*window);
			}
		}
		player.draw(*window);
		nb_seed_passed = 0;
		for (int i = 0; i < 21; i++) {
			for (int j = 0; j < 21; j++) {
				FGmap[i][j].draw(*window);
				if (FGmap[i][j].getType() == 3 || FGmap[i][j].getType() == 6){
					seeds.at(nb_seed_passed).setPosY(i);
					seeds.at(nb_seed_passed).setPosX(j);
					nb_seed_passed++;
				}
			}
		}
		scoreText.setString("Score: " + to_string(score));
		HPText.setString("HP: " + to_string(player.getHP()) + "/" + to_string(player.getMaxHP()));

		window->draw(scoreText);
		window->draw(HPText);
		window->draw(LevelText);

		endGame();
	}
	window->display();
}

/* return @void | set the entire map */
void game::setmap(char type){
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			BGmap[i][j].setType(type);
			BGmap[i][j].initialize();
			FGmap[i][j].setType(type);
			FGmap[i][j].initialize();
		}
	}
}

/* return @void| infinite Loop of the game and treat all the events on the keybard */
void game::gameLoop(){
	level currentLevel;
	Event event;
	while (window->isOpen()) {
		if(!_moving){
			window->pollEvent(event);
			switch (status){
				case 0:
					if (menu.mousePress(*window) || Keyboard::isKeyPressed(Keyboard::Return)) { //Play button pressed or Enter
						status = 1;
						LevelN = 1;
						initiateLevel(currentLevel, LevelN);
					}
					break;
				case 1:
			// game play
				if (BGmap[player.getPosY()][player.getPosX()].getType() == /*uranium*/ 7){ // si le joueur marche sur l'uranium il fait tout de suite demi-tour
					_moving = player.moving();
					if(!_moving){
						undo();
						player.setHurt(true);
						player.takeDamage(10);
					}
				}
				else{
					if (!levelWon && !gameover) {
						if (Keyboard::isKeyPressed(Keyboard::Right)     || Keyboard::isKeyPressed(Keyboard::D))
							move(3);
						else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Q))
							move(2);
						else if (Keyboard::isKeyPressed(Keyboard::Up)   || Keyboard::isKeyPressed(Keyboard::Z))
							move(0);
						else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
							move(1);
						else if (Keyboard::isKeyPressed(Keyboard::U)) //Undo button
							undo();
						else if (Keyboard::isKeyPressed(Keyboard::R)) { //Restart button
							initiateLevel(currentLevel, LevelN);
						}
					}
					else if (mousePress(0)) { //Next Button
						LevelN++;
						gameFinished=false;
						if (LevelN > range) 
							gameFinished = true;

						if (LevelN <= range) {
							levelWon = false;
							initiateLevel(currentLevel, LevelN);
						}
					}
					else if (mousePress(1)) { //Home Button
							gameover=false;
							gameFinished=false;
							levelWon = false;
							status = 0;
							gameWinHome.setPosition(Vector2f(70, 610));
							setmap('+');
					}
				}
				break;
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed){
				window->clear();
				window->close();
			}

			if(player.getHP() == 0 || score <= 0)
				gameover = true;
			if (winClock.getElapsedTime().asSeconds() > 0.3f && !gameFinished && !gameover) {

				if (winPic) {
					Image img;
					img.loadFromFile("images/game_win_2.png");
					gameWinTexture.update(img);
					winPic = false;
					winClock.restart();
				}
				else if (!gameover && !gameFinished) {
					Image img;
					img.loadFromFile("images/game_win.png");
					gameWinTexture.update(img);
					winPic = true;
					winClock.restart();
				}
			}
			else if (gameover)
			{
				Image img;
				img.loadFromFile("images/game_over.png");
				gameOverTexture.update(img);
			}
		}
		_moving = player.update_player();
		for(int i=0; i<nb_seeds; i++){
			if(seeds[i].radioactiveSeed(BGmap,FGmap,seeds[i].getPosY(),seeds[i].getPosX())){
				gameover = true;
				break;
			}
			seeds[i].plant(BGmap,FGmap,seeds[i].getPosY(),seeds[i].getPosX()); // updating the state of the plant/seed on the map
			seeds[i].grow(FGmap);
		}
		render();
	}
}

/* return bool = true if all seed are planted */
bool game::gameWin() {
	int nb_seed_planted = 0;
	for (int i=0; i<nb_seeds; i++){
		if (seeds[i].planted())
			nb_seed_planted++;
	}
	return nb_seed_planted == nb_seeds;
}

/* return @bool | true if the two blocs in front of the player is free */
bool game::PossibleMove(int dir) {
	int x1 = player.getPosX()+Dx[dir];
	int y1 = player.getPosY()+Dy[dir];
	int x2 = player.getPosX()+2*Dx[dir];
	int y2 = player.getPosY()+2*Dy[dir];

	if ((BGmap[y1][x1].getType() == /*wall*/1) || //Next is wall
		(FGmap[y1][x1].getType() == /*seed_grow*/3 && FGmap[y2][x2].getType() == /*seed_grow*/6) || // seed front of a planted seed
		(FGmap[y1][x1].getType() == /*seed_grow*/6 && FGmap[y2][x2].getType() == /*seed_grow*/6) || // planted seed front of a planted seed
		(FGmap[y1][x1].getType() == /*seed_grow*/6 && FGmap[y2][x2].getType() == /*seed*/     3) || // planted seed front of a seed
		(FGmap[y1][x1].getType() == /*seed*/     3 && FGmap[y2][x2].getType() == /*seed*/     3) || // seed front of a seed
		(FGmap[y1][x1].getType() == /*seed*/     3 && BGmap[y2][x2].getType() == /*wall*/     1) || // seed, front of a wall
		(FGmap[y1][x1].getType() == /*seed_grow*/6 && BGmap[y2][x2].getType() == /*wall*/     1))   // planted seed front of a wall
		return false;
	return true;
}

/*@return bool | true if the bloc in front of the player is a seed */
bool game::NextIsSeed(int dir) {
	int x1 = player.getPosX() + Dx[dir];
	int y1 = player.getPosY() + Dy[dir];
	return (FGmap[y1][x1].getType() == 3 || FGmap[y1][x1].getType() == 6);	
}

/* return @void | update the player position on the map when he go up or down */
void game::verticalMove(int dir){
    if (PossibleMove(dir)){                
        if (player.move(dir)) {
            if (NextIsSeed(dir)) {
                swap(FGmap[player.getPosY() +dir*2- 1][player.getPosX()], FGmap[player.getPosY() +dir*4 - 2][player.getPosX()]);
                FGmap[player.getPosY() +dir*2- 1][player.getPosX()].setType(5);
                nextWasSeed = true;
            }
            else
                nextWasSeed = false;
            direction = dir;
            player.setPosY(player.getPosY()+dir*2-1);
        }
        score-=10;
    }
} 

/* return @void | update the player position on the map when he go left or right */
void game::horizontalMove(int dir){
    if (PossibleMove(dir+2)) {
        if (player.move(dir+2)) {
            if (NextIsSeed(dir+2)) {
                swap(FGmap[player.getPosY()][player.getPosX() +dir*2- 1], FGmap[player.getPosY()][player.getPosX() +dir*4- 2]);
                FGmap[player.getPosY()][player.getPosX() + dir*2- 1].setType(5);
                nextWasSeed = true;
            }
            else
                nextWasSeed = false;
            direction = dir+2;
            player.setPosX(player.getPosX() +2*dir-1);
            
        }
        score-=10;
    }
}

/* return @void | move the player on the map using verticalMove() and horizontalMove() */
void game::move(int dir) {
    switch (dir) {
        case 0: //Up
            verticalMove(0);
            break;
        case 1: //Down
            verticalMove(1);
            break;
        case 2: //Left
            horizontalMove(0);
            break;
        case 3: //Right
            horizontalMove(1);
            break;
    }
}

/* return @void | update the player position on the map when he undo his last move */
void game::undo() {
	switch (direction) {
		case 0: //Up
			if (player.move(1)) {
				if (nextWasSeed) {
					swap(FGmap[player.getPosY()][player.getPosX()], FGmap[player.getPosY() - 1][player.getPosX()]);
				}
				player.setPosY(player.getPosY()+1);
			}
			break;
		case 1: //Down
			if (player.move(0)) {
				if (nextWasSeed) {
					swap(FGmap[player.getPosY()][player.getPosX()], FGmap[player.getPosY() + 1][player.getPosX()]);
				}
			}
			player.setPosY(player.getPosY()-1);
			break;
		case 2: //Left
			if (player.move(3)) {
				if (nextWasSeed) {
					swap(FGmap[player.getPosY()][player.getPosX()], FGmap[player.getPosY()][player.getPosX() - 1]);
				}
			}
			player.setPosX(player.getPosX()+1);
			break;
		case 3:
			if (player.move(2)) {
				if (nextWasSeed) {
					swap(FGmap[player.getPosY()][player.getPosX()], FGmap[player.getPosY()][player.getPosX() + 1]);
				}
			}
			player.setPosX(player.getPosX()-1);
			break;
	}
	score-=5; // pénalité
	nextWasSeed = false;
	direction = -1;
}