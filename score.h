#ifndef __SCORE_H__
#define __SCORE_H__

#include <iostream>
#include <sstream>
#include "blockmovement.h"
#include "xwindow.h"
#include <vector>

class BlockMovement;

class Score{
	private:
		int currScore, hiScore;
		int level;
		BlockMovement *bm;
		Xwindow *xw;
	public:
		Score(BlockMovement *bm, int level, Xwindow *xw);
		~Score();

		void setScore(int x);
		int getHiScore();
		int getScore();
		void setScore();
		void setHiScore();
		void setBM(BlockMovement *b);
		void setLvl(int level);
		int getLvl();
};

#endif