#ifndef __IBLOCK_H__
#define __IBLOCK_H__
   
#include <iostream>
#include "block.h"

class iBlock : public Block{
public:
	iBlock(int level, char c = 'I');
	Coordinate *newBlockState();
};

#endif