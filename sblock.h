#ifndef __SBLOCK_H__
#define __SBLOCK_H__

#include "block.h"

class sBlock : public Block{
public:
	sBlock(int level, char tetrominoeType = 'S');
	Coordinate *newBlockState();
};

#endif