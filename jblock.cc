#include "jblock.h"
#include <iostream>

jBlock::jBlock(int level, char tetrominoeType):Block(tetrominoeType){ 
	this->tetrominoeType = tetrominoeType; 
	orientation = N;
	xCoord = 0;
	yCoord = 2; // starts on the second row 
	numCells = 0;
	this->level = level;
}

Coordinate* jBlock::newBlockState(){
	int x = xCoord;
	int y = yCoord;

	switch(orientation){
		case N:
			blockCoords[0].x = x;
			blockCoords[0].y = y;	
			blockCoords[1].x = x;
			blockCoords[1].y = y + 1;	
			blockCoords[2].x = x + 1;
			blockCoords[2].y = y + 1;	
			blockCoords[3].x = x + 2;
			blockCoords[3].y = y + 1;
			break;
		case E:
			blockCoords[0].x = x;
			blockCoords[0].y = y - 1;	
			blockCoords[1].x = x + 1;
			blockCoords[1].y = y - 1;
			blockCoords[2].x = x;
			blockCoords[2].y = y;	
			blockCoords[3].x = x;
			blockCoords[3].y = y + 1;
			break;
		case S:
			blockCoords[0].x = x;
			blockCoords[0].y = y;
			blockCoords[1].x = x + 1;
			blockCoords[1].y = y;
			blockCoords[2].x = x + 2;
			blockCoords[2].y = y;
			blockCoords[3].x = x + 2;
			blockCoords[3].y = y + 1;
			break;
		case W:
			blockCoords[0].x = x + 1;
			blockCoords[0].y = y - 1;
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