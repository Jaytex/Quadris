#include "oblock.h"
#include <iostream>

oBlock::oBlock(int level, char tetrominoeType):Block(tetrominoeType){ 
	this->tetrominoeType = tetrominoeType; 
	orientation = N;
	xCoord = 0;
	yCoord = 2; // starts on the third row 
	numCells = 0;
	this->level = level;
}

Coordinate* oBlock::newBlockState(){
	int x = xCoord;
	int y = yCoord;

	switch(orientation){
		// same coordinates no matter orientation
		case N:
		case S:
		case E:
		case W:
			blockCoords[0].x = x;
			blockCoords[0].y = y ;
			blockCoords[1].x = x + 1;
			blockCoords[1].y = y;
			blockCoords[2].x = x;
			blockCoords[2].y = y + 1;
			blockCoords[3].x = x + 1;
			blockCoords[3].y = y + 1;
			break;
	}
	return blockCoords;
}