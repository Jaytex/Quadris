#include "cell.h"

Cell::Cell():  tetrominoeType(0), b(NULL), isOn(false), _free(false){}

Cell::~Cell(){}

void Cell::setTetrominoeType(char c){
	tetrominoeType = c;
}

void Cell::turnOn(){
	isOn = true;
	if (b) b->addCell();
	if (xw) draw();
}

void Cell::turnOff(){
	isOn = false;
	if (b) b->killCell();
	if(xw) erase();
}

bool Cell::getOn(){
	return isOn;
}

char Cell::getTetrominoeType(){
	return tetrominoeType;
}

Block* Cell::getBlock(){
	return b;
}

void Cell::setFree(){
	_free = true;
}

void Cell::setControlled(){
	_free = false;
}

int Cell::getYCoord(){
	return y;
}

bool Cell::isFree(){
	return _free;
}

void Cell::setBlock(Block *blck){
	b = blck;
}

void Cell::setCoords(int xC, int yC, Xwindow *xW, int w, int h){
	x = xC;
	y = yC;
	width = w;
	height = h;
  xw = xW;
} // add xwindow stuff later

void Cell::setYCoord(int yC){
	y = yC;
}

 void Cell::draw(){

  switch(tetrominoeType){
 		    case 'I':
         	xw->fillRectangle(x, y, width, height, Xwindow::Red);     
          	break;
      	case 'J':
         	xw->fillRectangle(x, y, width, height, Xwindow::Orange);  
         	break;
      	case 'L':
         	xw->fillRectangle(x, y, width, height, Xwindow::Yellow);        
           	break;
      	case 'O':
         	xw->fillRectangle(x, y, width, height, Xwindow::Green);           
         	break;
      	case 'S':
         	xw->fillRectangle(x, y, width, height, Xwindow::Blue);
         	break;
      	case 'Z':
         	xw->fillRectangle(x, y, width, height, Xwindow::Cyan);     
         	break;
      	case 'T':
         	xw->fillRectangle(x, y, width, height, Xwindow::Magenta);
           	break;
      	default:
         	xw->fillRectangle(x, y, width, height, 1);
 	}
}

 void Cell::erase(){
 	xw->fillRectangle(x, y, width, height, Xwindow::Black);
 }

std::ostream& operator<<(std::ostream &out, const Cell &c){
	c.isOn ? out << c.tetrominoeType : out << " ";
	return out;
}