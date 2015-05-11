#ifndef __ZBLOCK_H__
#define __ZBLOCK_H__

#include "block.h"

class zBlock : public Block{
public:
	zBlock(int level, char c = 'Z');
	Coordinate *newBlockState();
};

#endif