#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <iostream>
   
// block orientations
const int N = 0;
const int E = 1;
const int S = 2;
const int W = 3;


// struct to store the coordinates of a block
struct Coordinate {
	int x,y;
};

class Block{

	protected:
		Coordinate blockCoords[4]; 
		int xCoord; // block's x coordinate
		int yCoord; // block's y coordinate
		int orientation; // The direction the block is facing post rotation (Jay: Similar to the drone's ns,ew idea)
		int level; // The level of the block when it's generated
		char tetrominoeType; // Block's character (only for text version, graphical will be distinguised by colour)
		int numCells; // The number of cells on in a block


	public:
		Block(char tetrominoeType);
		virtual ~Block();
		virtual Coordinate *newBlockState() = 0; // ABSTRACTION YO!


		// Accessor methods
		Coordinate *getCoordsSafe(); // return a copy of the block's coordinates
		Coordinate *getCoords();
		int getLevel();
		int getNumCells();
		char getTetrominoeType();
		int getOrientation();
		int getXCoord();
		int getYCoord();

		// Mutator methods

		void setOrientation(int o); // Change the orientation of a block post rotation
		void setBlockCoords(int x, int y);


		// Misc.

		void rotateCW();
		void rotateCCW();
		void moveDown();
		void moveLeft();
		void moveRight();


		void addCell();
		void killCell();
		void levelUp();
		void levelDown();





};

#endif