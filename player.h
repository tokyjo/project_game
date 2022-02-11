#pragma once
#include "character.h"

class Player : public Character{
    private :
        int _HP;
        int _HP_max = 50; 
        
    public :
        Player();
        /*getter*/
        const int getHP()    const {return this->_HP;};
        const int getMaxHP() const {return this->_HP_max;};

        /*setter*/
        void setHP(int value){ _HP = value;};

        /* function */
        void takeDamage(int damage); 
};

Player::Player(){
    _HP    = _HP_max;
}

void Player::takeDamage(int damage){
    if(_HP > damage)  
        _HP -= damage;
    else
        _HP =0; 
}