#include <iostream>
#include "block.h"

Block::Block(char tetrominoeType){
	for (int i = 0; i < 4; ++i){
		blockCoords[i].x = 0;
		blockCoords[i].y = 0; 
	}
}

Block::~Block() {}

Coordinate* Block::getCoordsSafe(){
	Coordinate *block = new Coordinate[4];
	for (int i = 0; i < 4; ++i){
		block[i].x = blockCoords[i].x;
		block[i].y = blockCoords[i].y;
	}
	return block;
}

Coordinate* Block::getCoords(){
	return blockCoords;
}

int Block::getLevel(){
	return level;
}

int Block::getNumCells(){
	return numCells;
}

char Block::getTetrominoeType(){
	return tetrominoeType;
}

int Block::getOrientation(){
	return orientation;
}

int Block::getXCoord(){
	return xCoord;
}

int Block::getYCoord(){
	return yCoord;
}

void Block::setOrientation(int o){
	orientation = o;
}

void Block::setBlockCoords(int x, int y){
	xCoord = x;
	yCoord = y;
}

void Block::rotateCW(){
	orientation == W ? orientation = N : ++orientation;
}

void Block::rotateCCW(){
	orientation == N ? orientation = W : --orientation;
}

void Block::moveDown(){
	++yCoord;
}

void Block::moveLeft(){
	--xCoord;
}

void Block::moveRight(){
	++xCoord;
}

void Block::addCell(){
	++numCells;
}

void Block::killCell(){
	--numCells;
}

void Block::levelUp(){
	++level;
}

void Block::levelDown(){
	--level;
}
