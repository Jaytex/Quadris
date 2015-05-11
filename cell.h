#ifndef __CELL_H__
#define __CELL_H__

#include <iostream>
#include "block.h"
#include "xwindow.h"

 class Cell{

 	private:
 		char tetrominoeType; // The type of tetrominoe
 		Block *b; // The block the cell belongs to
 		bool isOn; // cell's status
 		Xwindow *xw;
 		int x,y, width, height; // x and y coordinates , width heigh for graphics
 		bool _free;
	
 	public:
 		Cell();
 		~Cell();

 		void setTetrominoeType(char tetrominoeType);
 		void turnOn(); // cell is alive
 		void turnOff(); // cell is dead
 		void setFree(); // cell is no longer being controlled
 		void setControlled();

 		// Accessor methods
 		bool getOn();
 		char getTetrominoeType();
 		Block *getBlock();
 		int getYCoord();
 		bool isFree();

 		// Mutator methods
 		void setBlock(Block *b); // lets cell know which block it belongs to
 		void setCoords(int x, int y, Xwindow *xW, int w, int h);
 		void setYCoord(int y); // for removing lines and keeping track of cell's line
 								// no need for setXCoord since the Col remains the same
 		
 		// Graphics
 		void draw();
 		void erase();
 	
 	friend std::ostream& operator<<(std::ostream &out, const Cell &c);
 };

#endif