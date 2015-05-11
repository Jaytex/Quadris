#ifndef __OBLOCK_H__
#define __OBLOCK_H__

#include "block.h"

class oBlock : public Block{
public:
	oBlock(int level, char c = 'O');
	Coordinate *newBlockState();
};

#endif