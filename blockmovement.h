#ifndef __BLOCKMOVEMENT_H__
#define __BLOCKMOVEMENT_H__ 

#include <iostream>
#include "board.h"
#include "block.h"
#include "cell.h"
#include <vector>



#define down 1
#define left 2
#define right 3
#define clockwise 4
#define counterclockwise 5
#define space 100

class Board;
class BlockMovement{
	private:
		Board *b; // the board the block is on
		//BlockList *bl; // block list for storing dropped blocks
		std::vector<Block *> bl;
		std::vector<int> ll;
		bool hasRotatedCW; // true if block has rotated
		bool hasRotatedCCW; // true if block has rotated
		
		bool isSafeMovement;
		bool isSafeRotation;
		bool isFullLine;
		int numRemovedLines; // number of lines cleared after a drop
		int numRemovedBlocks;
		int upmostFreeRow;
	public:
		BlockMovement(Board *b);
		~BlockMovement();
	
		Block *currBlock; // the block in question (i.e the block that's undergoing the movements)
						  // public because accessed by Game class
		
		// Accessor Methods
		int getNumRemovedLines();
		int getNumRemovedBlocks();
		bool getSafeMovement();
		std::vector<int> getLevelList();

		void resetNumRemovedLines();
		void setSafeMovement(int movement);
		void pushBlock();

		// rotates a block - Utkarsh
		void rotateCW(int x = 1);
		// rotates a block counterclockwise - Utkarsh
		void rotateCCW(int x = 1);

		void moveDown(int x = 1); // defualt to run 1 time
		void moveLeft(int x = 1);
		void moveRight(int x = 1);
		void dropBlock();
		void setIsFullLine(int);
		void killFullLine();

		void clearBlockList();
		void clearLevelList();
		void clearBoundryBlock(); // clears a block any block by the walls or bottom
};

		

#endif



