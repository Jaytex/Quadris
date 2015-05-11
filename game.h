#ifndef __GAME_H__
#define __GAME_H__

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "prng.h"
#include "cell.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
#include "score.h"
#include "command.h"
#include "board.h"
#include "block.h"
#include "blocklist.h"
#include "blockmovement.h"
#include "nextblock.h"




const uint32_t maxSeed = 362436069;

class Game{

	private:
		int level; 
		int currSeed;
		bool graphicsOn;
		bool endGame; // is the game over
		bool restart; // has game been restarted
		bool done;
		bool newState; // state of board after block has been dropped or new game
		
	
		//BlockList *bl;
		PRNG prng;
		std::string scriptFile;
		std::vector<char> sequence; // A list of characters from the scriptfile
		Xwindow *xw1, *xw2;
		Board b;
		Command cmd;
		BlockMovement bm;
		Score s;
		Block *nextBlock;
		NextBlock genBlock;
		std::string xxx;

	protected:

	public:
		Game(Xwindow *xw1 = NULL, Xwindow *xw2 = NULL);
		~Game();

		// Game Engine
		void newGame(); // starts a new game of quadris
		void printGame(); // prints the game layout	
		void drawGame();	
		void turnOffGraphics() { graphicsOn = false; }
		void readScriptFile(std::string s);
		void killGame(); // kills current game and resests values
		void genCurrBlock(uint32_t x);
		void genNextBlock(uint32_t x); // generates a new block. Probabililty variant depending on level
		void levelUp(int x = 1);
		void levelDown(int x = 1);

		
		// Accessor Methods
		std::vector<char> getSequence();
		Board getBoard(){ return b; }
		int getScore(){ return s.getScore(); }
		int getHiScore(){ return s.getHiScore(); }
		Score getScorePointer() { return s; }


		// Mutator Methods
		void setSeed(uint32_t x) { currSeed = x; }
		void setScriptFile(std::string s = "sequence.txt"){ scriptFile = s; }
		void setLevel(int x = 0) { level = x; }
};

#endif