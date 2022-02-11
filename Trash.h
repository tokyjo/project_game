#pragma once 
#include "object.h"

/* Trash will be no poisoned after after all the seeds planted */

class Trash : public Object {
    private:
        bool _poisoned;  

    public:
        void poisonous();
};
