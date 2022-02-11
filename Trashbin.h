#pragma once 
#include "object.h"

class Trashbin : public Object {
    private:
        bool _hidden = true;
        bool _empty = true; 
        bool _poisonous;  

    public:
        bool ravel();
        void poisonous();
};
