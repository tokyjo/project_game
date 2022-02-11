#include "character.h"

Character::Character(){
    _posX = 0;
    _posY = 0;
    _direction = 1;
    _on_goal  = false;
    _moving   = false;
    _cnt_move = 0;
    _hurt     = false;
    _cnt_hurt = 0;
}

void Character::setType(char t){
    switch(t) {
		case ' ': _type = empty;     break; 
        case '#': _type = wall;      break;
		case '.': _type = goal;      break;
        case '$': _type = seed;      break;
        case '@': _type = player;    break;
		case '?': _type = space;     break; // seed on goal 
		case '+': _type = seed_grow; break; // player on goal
        case 'u': _type = uranium;   break; // uranium
        case 't': _type = trash;     break;
    }
}

void Character::initialize() {
	switch (_type) {
		case empty: // empty = floor
				_texture.loadFromFile("sprites/floor.jpg");
				_sprite.setTexture(_texture, true);
				break;

		case wall: // wall
				_texture.loadFromFile("sprites/Wall.png");
				_sprite.setTexture(_texture, true);
				break;

		case goal: //G goal
				_texture.loadFromFile("sprites/Goal.png");
				_sprite.setTexture(_texture, true);
				break;

		case seed: //seed
				_texture.loadFromFile("sprites/seed.png");
				_sprite.setTexture(_texture, true);
				_on_goal = false;
				break;

		case player: // player
				_texture.loadFromFile("sprites/Wall-e.png");
				_sprite.setTexture(_texture, true);
				_sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
				break;

		case space: // space
				 _texture.loadFromFile("sprites/space.png");
				_sprite.setTexture(_texture, true);
				break;

		case seed_grow: // seed_grow
				_texture.loadFromFile("sprites/seed_grow.png"); // growing seed
				_sprite.setTexture(_texture, true);
				_sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
				break;

	    case uranium: // uranium
				_texture.loadFromFile("sprites/uranium.png");
				_sprite.setTexture(_texture, true);
				break;
    
	    case trash: // trash
				_texture.loadFromFile("sprites/trash.png");
				_sprite.setTexture(_texture, true);
				break;
	}
}

bool Character::move(int direction) {
	if (!_moving) {
		_direction = direction;
		_moving    = true;
		_cnt_move  = 0;
		return true;
	}
	return false;
}

bool Character::update_player() {
	const int Dy[4] = { -10, 10, 0, 0 };
	const int Dx[4] = { 0, 0, -10, 10};

	if (_moving && _cnt_move < 5 && _type == 4){
		_sprite.move(Dx[_direction],Dy[_direction]);
		_sprite.setTextureRect(sf::IntRect((_cnt_move % 5)*50, _direction*50, 50, 50));

		if(_hurt || _cnt_hurt != 0){
			_sprite.setColor(sf::Color(255,0,0));
			_cnt_hurt++;
			_hurt = false;
		}
		else
			_sprite.setColor(sf::Color(255,255,255));
		_cnt_move++;

		if(_cnt_hurt == 4)
			_cnt_hurt = 0;
	}
	else if(_cnt_move >= 5){
		_moving = false;
		_cnt_move = 0;
	}
	return _moving;
}

void Character::switcher(int win, int growth) {
	sf::Image temp;
	if (_type == seed && win == 0){
		_on_goal = false;
		if (!temp.loadFromFile("sprites/seed.png"))
			std::cout << "Failed to load seed spritesheet!" << std::endl;
		_texture.update(temp);
	}
	else if (_type == seed_grow && win == 1) {
		_on_goal = true;
		if (!temp.loadFromFile("sprites/seed_grow.png"))
			std::cout << "Failed to load seed_grow spritesheet!" << std::endl;
		sf::Image temp2;
		temp2.create(50,50);
		temp2.copy(temp,0,0,sf::IntRect(growth*48, 0, 50, 50));
		_texture.update(temp2);
	}
}

void Character::draw(sf::RenderWindow& window) {
	window.draw(_sprite);
}