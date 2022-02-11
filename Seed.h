#pragma once 
#include "object.h"

class Seed : public Object{
    private:
        bool _planted = false;
        int  _growth  = 0;
    public:
        Seed();
        //getter
        bool planted() {return this->_planted;};

        //setter
        bool radioactiveSeed(Character [21][21], Character [21][21], int i, int j);
        void plant(Character [21][21], Character [21][21], int i, int j);
        void grow(Character [21][21]); 
};
