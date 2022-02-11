#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "level.h"

using namespace std;

/*Constructor*/
level::level() {
	_x = 21; //Default _size
	_y = 21; //Default _size
	for (int i = 0; i < _x; i++) {
		for (int j = 0; j < _y; j++) {
			grid.push_back(-1);
		}
	}
	_size = grid.size();
}

/* @return void | Load a map from the text file */
void level::initialize(int levelNo) {
	ifstream fd;
	fd.open("levels/" + to_string(levelNo) + ".txt");
	if (fd.fail()) {
		cerr << "Error opening level # " << levelNo << ". Check if file is corrupted\n";
	}
	int nb_seeds;
	fd >> nb_seeds;
	_nb_seeds = nb_seeds;
	char c;
	fd.get(c);
	if (c == '\n')
		fd.get(c);
	for (int i = 0; i < _x; i++) {
		if (c == '\n')
			fd.get(c);
		for (int j = 0; j < _y; j++) {
            grid.at(i*_y +j) = c ;
			fd.get(c);
			if (c == '\n')
				fd.get(c);
		}
	}
	_initialized = true;
	fd.close();
}

/* return @char | getter for the type of one element */
char level::getContent(int i, int j) {
	return grid[i * _y + j];
}

/* return @void | print the map */
void level::print() {
	for (int i = 0; i < _x; i++) {
		for (int j = 0; j < _y; j++) {
			cout << setw(2);
			cout << grid[i*_y + j] << " ";
		}
		cout << endl;
	}
}

/* @getter for the number of seed */
int level::getNbSeeds(){
	return _nb_seeds;
}

/* return void | empty the map */
void level::empty() {
	for (int i = 0; i < _y; i++) {
		for (int j = 0; j < _x; j++) {
			grid.push_back(-1);
		}
	}
	_size = grid.size();
}