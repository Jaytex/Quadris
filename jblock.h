#ifndef __JBLOCK_H__
#define __JBLOCK_H__

#include "block.h"

class jBlock : public Block{
public:
	jBlock(int level, char c = 'J');
	Coordinate *newBlockState();
};

#endif