#include "nextblock.h"
#include <iostream>

NextBlock::NextBlock(): tetrominoeType(0), c(0){}

NextBlock::~NextBlock(){ sequence.clear(); }

char NextBlock::getTetrominoeType() { 
	return tetrominoeType; 
}

void NextBlock::setSequence(std::vector<char> seq){
	sequence = seq;
}

// increments the counter to get the next tetrominoe in the sequence
void NextBlock::nextTetrominoe(){
	++c;
	if (c > sequence.size() - 1) reset_c();
}

void NextBlock::reset_c(){
	c = 0;
}

void NextBlock::level_0(){
	tetrominoeType = sequence[c];
}

void NextBlock::level_1(uint32_t x){
	char tet;

	switch(x){
		case 0:
		case 1: tet = 'I'; break;

		case 2:
		case 3: tet = 'J'; break;

		case 4:
		case 5: tet = 'L'; break;

		case 6:
		case 7: tet = 'O'; break;


		case 8: tet = 'S'; break;


		case 9: tet = 'Z'; break;

		case 10:
		case 11: tet = 'T'; break;
	}
	tetrominoeType = tet;
}

void NextBlock::level_2(uint32_t x){
	char tet;

	switch(x){
		case 0: tet = 'I'; break;

		case 1: tet = 'J'; break;

		case 2: tet = 'L'; break;

		case 3: tet = 'O'; break;

		case 4: tet = 'S'; break;

		case 5: tet = 'Z'; break;

		case 6: tet = 'T'; break;
	}
	tetrominoeType = tet;
}

void NextBlock::level_3(uint32_t x){
	char tet;

	switch(x){
		case 0: tet = 'I'; break;

		case 1: tet = 'J'; break;

		case 2: tet = 'L'; break;

		case 3: tet = 'O'; break;

		case 4:
		case 5: tet = 'S'; break;

		case 6:
		case 7: tet = 'Z'; break;

		case 8: tet = 'T'; break;
	}
	tetrominoeType = tet;
}