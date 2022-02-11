#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>

class level {
	private:
		std::vector<char> grid;
		int  _x;
		int  _y;
		int  _size;
		bool _initialized = false;
		int _nb_seeds;
		
	public:
		level();
		void initialize(int);
		char getContent(int, int);
		void print();
		int  getNbSeeds();
		void empty();
	    void showgriday(); 
};
