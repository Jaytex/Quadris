#ifndef __NEXTBLOCK_H__
#define __NEXTBLOCK_H__

#include <sstream>
#include <vector>
#include "prng.h"



class NextBlock{

	private:
		char tetrominoeType;
		std::vector<char> sequence; // sequence that stores the tetrominoe's for level 0
		unsigned int c; // counter for our position in the sequence
		
	public:
		NextBlock();
		~NextBlock();

		// Accessor methods
		char getTetrominoeType();


		// Mutator method
		void setSequence(std::vector<char> seq);
		void nextTetrominoe(); // gets the next tetrominoe in the sequence
		void reset_c(); // reset the counter after reaching end of sequence

		void level_0(); // generate the new block at level 0
		void level_1(uint32_t x); // generate the new block at level 1
		void level_2(uint32_t x); // generate the new block at level 2
		void level_3(uint32_t x); // generate the new block at level 3

};

#endif