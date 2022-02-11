#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <list>

class Character{
    protected:
        enum kind {empty,wall,goal,seed,player,space,seed_grow,uranium,trash};
        kind _type;

        sf::Sprite _sprite;  
        sf::Texture _texture;
        sf::Vector2f _pos; 

        int  _posX;
        int  _posY;
        int  _direction;
        bool _on_goal;

        bool _moving; 
        int  _cnt_move;

        bool _hurt;
        int  _cnt_hurt;
    
    public:
        Character();

        /*getter*/
        sf::Vector2f getPosition() {return _sprite.getPosition();};
        kind getType() {return _type;};
        int  getPosX() {return _posX;};
        int  getPosY() {return _posY;};
        bool moving()  {return _moving;};

        /*setter*/
        void setType(char type);
        void setPosX(int value)  { _posX = value;};
        void setPosY(int value)  { _posY = value;};
        void setHurt(bool state) { _hurt = state;};
        void setPosition(int x, int y) { _sprite.setPosition(x, y);};


        /*functions*/
        void initialize();
        bool move(int direction);
        bool update_player();
        void switcher (int win, int growth);

        /*animation*/
        void draw(sf::RenderWindow&);
};

