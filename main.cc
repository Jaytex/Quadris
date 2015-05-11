#include "game.h"

int main(int argc, char *argv[]){

	uint32_t seed = maxSeed;
	int n = 0; // the level the game starts at. Defualt set to 0
	std::string sFile; // the script file. Defualt set to sequence.txt
	bool noGraphics = false; // runs graphics by default


	for (int i = 1; i < argc; ++i){

		std::string arg = (std::string)argv[i];

		if (arg == "-seed"){
			++i; // xxx (i.e. -seed xxx)
			std::string t = (std::string)argv[i]; // temp string that stores the seed number (xxx)
			std::istringstream iss(t);
			iss >> seed;
		} 

		else if (arg == "-text"){
			noGraphics = true; // runs text only
		}

		else if (arg == "-scriptfile"){
			++i; // xxx (i.e. -scriptfile xxx)
			std::string t = (std::string)argv[i]; // temp string that stores the script file's name (xxx)
			std::istringstream iss(t);
			iss >> sFile;
		}

		else if (arg == "-startlevel"){
			++i; // n (i.e. -startlevel n)
			std::string t = (std::string)argv[i]; // temp string that stores the lebel number (n)
			std::istringstream iss(t);
			iss >> n; 
		}
	}


	if (noGraphics){
		Game g; // initiate a new game class
		g.turnOffGraphics(); // display text only
		g.setSeed(seed);
		g.setLevel(n);
		if (n == 0) g.setScriptFile(sFile); // script files only during level 0
		g.newGame(); // start a new game 
	}

	else {
		Xwindow xw1(40 * NumCols, 68 + 20 * NumRows);
		Xwindow xw2(1, 1); // was used to display next block initially
		Game g(&xw1, &xw2); // initiate a new game class with an xwindow
		g.setSeed(seed);
		if (n == 0) g.setScriptFile(sFile); // script files only during level 0
		g.newGame(); // start a new game at level n
	}

	return 0;
}