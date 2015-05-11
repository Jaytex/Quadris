#ifndef __LBLOCK_H__
#define __LBLOCK_H__

#include "block.h"

class lBlock : public Block{
public:
	lBlock(int level, char c = 'L');
	Coordinate *newBlockState();
};

#endif