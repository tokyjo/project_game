#include "Seed.h"

/*Constructor*/
Seed::Seed() {
    _planted = false;
    _growth  = 0;
}

/* return true if the seed become infected because placed on uranium, */
bool Seed::radioactiveSeed(Character BGmap[21][21], Character FGmap[21][21], int i, int j) {
	if (BGmap[i][j].getType() == /*uranium*/ 7 && FGmap[i][j].getType() == /*seed*/ 3)
		return true;
	else
		return false;
}

/* return @void | update the state of the plant/seed on the map */
void Seed::plant(Character BGmap[21][21], Character FGmap[21][21], int i, int j) {
	if (BGmap[i][j].getType() == /*goal*/ 2 && FGmap[i][j].getType() == /*seed*/ 3) {
		FGmap[i][j].setType('+'); // become a growing plant
		FGmap[i][j].switcher(1,0); // seed => seed_grow
		_planted = true;
	}
	else if (BGmap[i][j].getType() != /*goal*/ 2 && FGmap[i][j].getType() == /*seed_grow*/ 6) {
		FGmap[i][j].setType('$'); // become a seed (again)
		FGmap[i][j].switcher(0,0); // seed_grow => seed
		_growth = 0;
		_planted = false;
	}
	else if (BGmap[i][j].getType() == /*goal*/ 2 && FGmap[i][j].getType() ==/*seed_grow*/ 6) {
		_planted = true;
	}
	else if (BGmap[i][j].getType() != /*goal*/ 2 && FGmap[i][j].getType() == /*seed*/ 3) {
		_growth = 0;
		_planted = false;
	}
}

/* return @void | animation of the seed */ 
void Seed::grow(Character FGmap[21][21]) {
	if(_planted){
		FGmap[getPosY()][getPosX()].switcher(1,_growth);
		if(_growth < 6)
			_growth++;
	}
}