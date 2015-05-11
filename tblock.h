#ifndef __TBLOCK_H__
#define __TBLOCK_H__

#include "block.h"

class tBlock : public Block{
public:
	tBlock(int level, char c = 'T');
	Coordinate *newBlockState();
};

#endif