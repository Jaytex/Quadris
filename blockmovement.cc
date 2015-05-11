#include "blockmovement.h"


BlockMovement::BlockMovement(Board *b): b(b), hasRotatedCW(false), 
										hasRotatedCCW(false), isSafeMovement(true), isSafeRotation(true),
										isFullLine(false), numRemovedLines(0), numRemovedBlocks(0),
										upmostFreeRow(NumRows -1), currBlock(NULL){}

BlockMovement::~BlockMovement(){
	for (std::vector<Block*>::iterator i = bl.begin(); i != bl.end(); ++i){
		if (*i) delete *i;
	}
 	bl.clear();
}

int BlockMovement::getNumRemovedLines(){
	return numRemovedLines;
}

int BlockMovement::getNumRemovedBlocks(){
	return numRemovedBlocks;
}

bool BlockMovement::getSafeMovement(){
	return isSafeMovement;
}

std::vector<int> BlockMovement::getLevelList(){
	return ll;
}

void BlockMovement::resetNumRemovedLines(){
	numRemovedLines = 0;
}

void BlockMovement::setSafeMovement(int movement){
	// can't be NULL
	if (currBlock){
		Coordinate *block = currBlock->getCoordsSafe(); // set b to be a copy of the current block
		// move every cell in the block accordingly
		switch(movement){
			case space:
				break;
			case down:
				for (int i = 0; i < 4; ++i) (block[i].y) += 1; break;// increment y (i.e move down ... wasted time on whether to increment of decrement) 
			case left:
				for (int i = 0; i < 4; ++i) (block[i].x) -= 1;	break;
			case right:
				for (int i = 0; i < 4; ++i) (block[i].x) += 1; break;
			case clockwise:
				currBlock->rotateCW();
				hasRotatedCW = true;
				currBlock->newBlockState();
				delete [] block;
				block = currBlock->getCoordsSafe(); // new block state (post rotation)
				break;
			case counterclockwise:
				currBlock->rotateCCW();
				hasRotatedCCW = true;
				currBlock->newBlockState();
				delete [] block;
				block = currBlock->getCoordsSafe();
				break;	
		}
		// for every cell in a block check if it's safe to move
		for (int i = 0; i < 4; ++i){
	   	    // if cell position is by the side walls
			if (block[i].x > NumCols - 1 || block[i].x < 0 
				// if cell position is at very top or very bottom
				|| block[i].y > NumRows - 1 || block[i].y < 0
				// if it's a free cell that is on (not being controlled by this class)
				|| b->isOnFreeBlock(block[i].x,block[i].y)){
				isSafeMovement = false;
				isSafeRotation = false;
				break;
			}
			else {
				isSafeMovement = true;
				isSafeRotation = true;
			}
		}
		if(hasRotatedCW){
			currBlock->rotateCCW(); // rotate back to original state
			hasRotatedCW = false;
			currBlock->newBlockState();
		}
		else if (hasRotatedCCW){
			currBlock->rotateCW(); // rotate back to original state
			hasRotatedCCW = false;
			currBlock->newBlockState();
		}
		delete [] block;
	}
}

void BlockMovement::pushBlock(){
	bl.push_back(currBlock); // add the active block to the block list
	Coordinate *aBlock = currBlock->getCoords(); // actual block (no copy)
	if (aBlock[0].y < upmostFreeRow){
		upmostFreeRow = aBlock[0].y;
	}
}

void BlockMovement::rotateCW(int x){
	if (x){
		if (currBlock){
			setSafeMovement(clockwise);
			if (isSafeRotation){
				b->killBlock(currBlock);
				for (int i = 0; i < x; ++i){
					setSafeMovement(clockwise);
					if(isSafeRotation) {
						currBlock->rotateCW();
						currBlock->newBlockState();
					} else break;
				}
				b->turnOnBlock(currBlock);
			}
		}
	}
}

void BlockMovement::rotateCCW(int x){
	if (x){
		if (currBlock){
			setSafeMovement(counterclockwise);
			if (isSafeRotation){
				b->killBlock(currBlock);
				for (int i = 0; i < x; ++i){
					setSafeMovement(counterclockwise);
					if(isSafeRotation) {
						currBlock->rotateCCW();
						currBlock->newBlockState();
					} else break;
				}
				b->turnOnBlock(currBlock);
			}
		}
	}	
}

void BlockMovement::moveDown(int x){
	if (x){
		if (currBlock){
			setSafeMovement(down);
			if (isSafeMovement){
				b->killBlock(currBlock);
				for (int i = 0; i < x; ++i){
					setSafeMovement(down);
					if(isSafeMovement) {
						currBlock->moveDown();
						currBlock->newBlockState();
					} else break;
				}
				b->turnOnBlock(currBlock);
			}
		}
	}	
}

void BlockMovement::moveLeft(int x){
	if (x){
		if (currBlock){
			setSafeMovement(left);
			if (isSafeMovement){
				b->killBlock(currBlock);
				for (int i = 0; i < x; ++i){
					setSafeMovement(left);
					if(isSafeMovement) {
						currBlock->moveLeft();
						currBlock->newBlockState();
					} else break;
				}
				b->turnOnBlock(currBlock);
			}
		}
	}
}

void BlockMovement::moveRight(int x){
	if (x){
		if (currBlock){
			setSafeMovement(right);
			if (isSafeMovement){
				b->killBlock(currBlock);
				for (int i = 0; i < x; ++i){
					setSafeMovement(right);
					if(isSafeMovement) {
						currBlock->moveRight();
						currBlock->newBlockState();
					} else break;
				}
				b->turnOnBlock(currBlock);
			}
		}
	}
}

void BlockMovement::dropBlock(){
	if (currBlock){
		setSafeMovement(down);
		if (isSafeMovement){
			b->killBlock(currBlock);
			for (int i = 0; i < NumRows; ++i){
				setSafeMovement(down);
				if(isSafeMovement) {
					currBlock->moveDown();
					currBlock->newBlockState();
				} else break;
			}
			b->turnOnBlock(currBlock);
		}
	}
}

void BlockMovement::setIsFullLine(int l){
	for (int i = 0; i < NumCols; ++i){
		if (!(b->isOn(i, l))){
			isFullLine = false; 
			return; // there is an off cell
		}
	}
	isFullLine = true;
}

void BlockMovement::killFullLine(){

	for (int i = NumRows - 1; i >= upmostFreeRow; --i){
		setIsFullLine(i + numRemovedLines);
		if(isFullLine){
			b->killLine(i + numRemovedLines);
			++numRemovedLines;
			for (int l = (i + numRemovedLines) - 2; l >= upmostFreeRow; --l)
				b->removeLine(l);
		}
	}

	for (std::vector<Block *>::iterator i = bl.begin(); i != bl.end(); ++i){
		if(*i){
			// if every cell in a block is off, then the block got removed
			if((*i)->getNumCells() == 0){
				++numRemovedBlocks;
				ll.push_back((*i)->getLevel()); // push the removed block's level onto the level's list
			}
		}	
	}

	if(numRemovedBlocks){
		for (unsigned int i = 0; i < bl.size(); ++i){
			if(bl[i]){
				if(bl[i]->getNumCells() == 0){
					delete bl[i];
					bl[i] = NULL;
				}
			}
		}
	}
	numRemovedBlocks = 0;
}

void BlockMovement::clearBlockList(){
	for (std::vector<Block*>::iterator i = bl.begin(); i != bl.end(); ++i){
		if (*i){
			delete *i;
			*i = NULL;
		}
	}
	bl.clear();
}

void BlockMovement::clearLevelList(){
	ll.clear();
}

void BlockMovement::clearBoundryBlock(){
	for (int i = upmostFreeRow; i < NumRows; ++i){
		for (int j = 0; j < NumCols; ++j){
			// if a cell is on, turn it off
			if(b->getCell(i,j).getOn()) b->getCell(i,j).turnOff();
			b->getCell(i,j).setBlock(NULL);
			b->getCell(i,j).setTetrominoeType(0);
			b->getCell(i,j).setControlled();
		}
	}
}