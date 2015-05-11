#include "blocklist.h"

BlockList::BlockList(){}

BlockList::~BlockList(){
	for (std::vector<Block *>::iterator i = blockList.begin(); i != blockList.end(); ++i){
		if (*i) delete *i;
	}
	blockList.clear();
}

std::vector<Block *> BlockList::getBlockList(){ 
	return blockList; 
}

std::vector<int> BlockList::getLevelList() {
	return levelList; 
}

void BlockList::pushBlock(Block *b){
	blockList.push_back(b);
}

void BlockList::pushLevel(int l){
	levelList.push_back(l);
}

void BlockList::clearBlockList(){
	for (std::vector<Block *>::iterator i = blockList.begin(); i != blockList.end(); ++i){
		if(*i){
			delete *i; // calls block's dtor
			*i = NULL;
		}
	}
	blockList.clear();
}
