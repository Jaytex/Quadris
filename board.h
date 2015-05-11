#ifndef __BOARD_H__
#define __BOARD_H__

 #include <iostream>
 #include "score.h"
 #include "cell.h"
 #include "block.h"
 #include "xwindow.h"

// Forward Delcarations


const int NumRows = 18;
const int NumCols = 10;

class Board{

	private:
		Cell **theBoard; // 15 X 10 board of Cells
		Xwindow *xw_1, *xw_2; // one for the next block
	
	public:
		Board(Xwindow *xw1, Xwindow *xw2);
		~Board();

		void clearGrid();

		
		Cell& getCell(int x, int y);
	

		bool isOn(int x, int y);
		bool isFree(int x, int y);
		bool isOnFreeBlock(int x, int y);
		void killLine(int l); // kills every cell on a line
		void removeLine(int l); // delete line and moves everything above it down

		void killBlock(Block *b);
		void killNextBlock(Block *b);
		void turnOnBlock(Block *b);
		void turnOnNextBlock(Block *b);
		void setBlockFree(Block *b);
		

		friend std::ostream& operator<<(std::ostream &out, const Board &b);
};



#endif