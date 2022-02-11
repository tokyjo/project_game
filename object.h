#pragma once 
#include "character.h"

class Object : public Character{
    private :
        bool _movable = false;

    public:
        /*getter*/
        bool ismovable(){return _movable;};

        /*setter*/
        bool setmove(bool val){ return val;};

};