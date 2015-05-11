#include "board.h"


//ctor
Board::Board(Xwindow *xw1, Xwindow *xw2): xw_1(xw1), xw_2(xw2){
	theBoard = new Cell*[NumRows + 3];
	for (int i = 0; i < NumRows + 3; ++i){
		theBoard[i] = new Cell[NumCols];
	}
	for (int i = 0; i < NumRows; ++i){
		for (int j = 0; j < NumCols; ++j){
			theBoard[i][j].setCoords(j*20, 70 + i*20, xw_1, 20, 20);
		}
	}
	for (int i = NumRows; i < NumRows + 3; ++i){
		for (int j = 0; j < NumCols; ++j){
			//theBoard[i][j].setCoords(60 + j*20, 17 + (i -NumRows)*20, xw_2, 20, 20);
			theBoard[i][j].setCoords(265 + j*20, 230 + (i -NumRows)*20, xw_1, 20, 20);

		}
	}
}

//dtor
Board::~Board(){
	clearGrid();
}

void Board::clearGrid(){
	for (int i = 0; i < NumRows + 3; ++i){
		if (theBoard[i]) delete [] theBoard[i]; // deep free
	}
	delete [] theBoard;	
}

void Board::killLine(int l){
	for (int i = 0; i < NumCols; ++i){
		theBoard[l][i].turnOff();
		theBoard[l][i].setTetrominoeType(0);
		theBoard[l][i].setControlled();
		theBoard[l][i].setBlock(NULL);
	}
}

Cell& Board::getCell(int x, int y){
	Cell &c = theBoard[x][y];
	return c;
}

void Board::removeLine(int l){
	for (int i = 0; i < NumCols; ++i){

		// moving the line down
		int t = theBoard[l+1][i].getYCoord(); // storing the original coordinate
		theBoard[l+1][i] = theBoard[l][i]; // move each cell in a line down (call copy ctor)
		theBoard[l+1][i].setYCoord(t); // new y coordinate
		if (theBoard[l][i].getOn()) theBoard[l+1][i].turnOn(); // if the cell above was on, turn the new one on
		
		// killing the current line
		theBoard[l][i].turnOff();
		theBoard[l][i].setBlock(NULL);
		theBoard[l][i].setTetrominoeType(0);
		theBoard[l][i].setControlled();
	}
}

bool Board::isOn(int x, int y){
	return theBoard[y][x].getOn();
}
bool Board::isFree(int x, int y){
	return theBoard[y][x].isFree();
}
bool Board::isOnFreeBlock(int x, int y){
	return(theBoard[y][x].getOn() && theBoard[y][x].isFree());
}

void Board::setBlockFree(Block *b){
	Coordinate *block = b->newBlockState();
	for (int i = 0; i < 4; ++i){
		theBoard[block[i].y][block[i].x].setFree();
	}
}

void Board::turnOnBlock(Block *b){
	Coordinate *block = b->newBlockState();
	for (int i = 0; i < 4; ++i){
		theBoard[block[i].y][block[i].x].setTetrominoeType(b->getTetrominoeType());
		theBoard[block[i].y][block[i].x].setBlock(b);
		theBoard[block[i].y][block[i].x].turnOn();
	}
}

void Board::turnOnNextBlock(Block *b){
	int yCoord = b->getYCoord();
	b->setBlockCoords(0,NumRows);
	Coordinate *block = b->newBlockState();
	for (int i = 0; i < 4; ++i){
		theBoard[block[i].y][block[i].x].setTetrominoeType(b->getTetrominoeType());
		theBoard[block[i].y][block[i].x].setBlock(b);
		theBoard[block[i].y][block[i].x].turnOn();
	}	
	b->setBlockCoords(0,yCoord);
}

void Board::killBlock(Block *b){
	Coordinate *block = b->newBlockState();
	for (int i = 0; i < 4; ++i){
		theBoard[block[i].y][block[i].x].turnOff();
		theBoard[block[i].y][block[i].x].setBlock(NULL);
		theBoard[block[i].y][block[i].x].setTetrominoeType(0);
		theBoard[block[i].y][block[i].x].setControlled();
	}	
}

void Board::killNextBlock(Block *b){
	int yCoord = b->getYCoord();
	b->setBlockCoords(0,NumRows);
	Coordinate *block = b->newBlockState();
	for (int i = 0; i < 4; ++i){
		theBoard[block[i].y][block[i].x].turnOff();
		theBoard[block[i].y][block[i].x].setBlock(NULL);
		theBoard[block[i].y][block[i].x].setTetrominoeType(0);
	}	
	b->setBlockCoords(0,yCoord);
}



std::ostream& operator<<(std::ostream &out, const Board &b){

	for (int i = 0; i < NumCols; ++i) out << "-";
	out << std::endl;

	for (int r = 0; r < NumRows; ++r){
		for (int c = 0; c < NumCols; ++c){
			out << b.theBoard[r][c];
		}
		out << std::endl;
	}
	for (int i = 0; i < NumCols; ++i) out << "-";
	out << std::endl << "Next:" << std::endl;

	for (int r = NumRows; r < NumRows + 3; ++r){
		for (int c = 0; c < NumCols; ++c){
			out << b.theBoard[r][c];
		}
		out << std::endl;
	}
	return out;
}