#include "iblock.h"
#include <iostream>

iBlock::iBlock(int level, char tetrominoeType):Block(tetrominoeType){ 
	this->tetrominoeType = tetrominoeType; 
	orientation = N;
	xCoord = 0;
	yCoord = 3; // starts on the third row 
	numCells = 0;
	this->level = level;
}

Coordinate* iBlock::newBlockState(){
	int x = xCoord;
	int y = yCoord;

	switch(orientation){
		// same NS orientation
		case N:
		case S:
			blockCoords[0].x = x;
			blockCoords[0].y = y;
			blockCoords[1].x = x + 1;
			blockCoords[1].y = y;
			blockCoords[2].x = x + 2;
			blockCoords[2].y = y;
			blockCoords[3].x = x + 3;
			blockCoords[3].y = y;
			break;
		// same EW orientation
		case E:
		case W:
			blockCoords[0].x = x;
			blockCoords[0].y = y - 3;
			blockCoords[1].x = x;
			blockCoords[1].y = y - 2;
			blockCoords[2].x = x;
			blockCoords[2].y = y - 1;
			blockCoords[3].x = x;
			blockCoords[3].y = y;
			break;
	}
	return blockCoords;
}