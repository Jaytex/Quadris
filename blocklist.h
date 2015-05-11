#ifndef __BLOCKLIST_H__
#define __BLOCKLIST_H__

#include <iostream>
#include <vector>
#include "block.h"

// Forward Declarations
class Block;

class BlockList{

	private:
		std::vector<Block *> blockList; // stores all the dropped blocks
		std::vector<int> levelList; // levels of blocks removed 

	public:
		BlockList();
		~BlockList();

		//Accessor methods
		std::vector<Block *> getBlockList();
		std::vector<int> getLevelList();

		void pushBlock(Block *b);
		void pushLevel(int l);

		void clearBlockList();

};

 #endif