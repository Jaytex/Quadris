#include "score.h"

Score::Score(BlockMovement *bm, int level, Xwindow *xw): currScore(0), hiScore(0), level(level), bm(bm), xw(xw){}

Score::~Score(){}


void Score::setScore(int x){ 
	currScore = x;	 // adds x to current score.
}

int Score::getHiScore(){ // returns hiScore.
	return hiScore; 
}

int Score::getScore(){ // returns currentScore.
	return currScore; 
}

void Score::setScore(){ 
	int numRemovedLines = bm->getNumRemovedLines();
	int blockScores = 0;
	std::vector<int> t = bm->getLevelList();
	int _score = currScore;
	for (unsigned int i = 0; i < t.size(); ++i){
		blockScores += (t[i] + 1)*(t[i] + 1);
	}
	if (numRemovedLines){
		currScore += (level + numRemovedLines)*(level + numRemovedLines) + blockScores;
	}
	bm->clearLevelList();
	t.clear();
	bm->resetNumRemovedLines();
	if (xw){
		std::ostringstream _oss, oss;
		_oss << currScore;
		std::string s = "Score: "+ _oss.str();
		oss << _score;
		std::string _s = "Score: "+ oss.str();
		xw->fillRectangle(10,16, _s.length()*7, 12, Xwindow::White);
		xw->drawString(10, 27, s, 0);
	}
	//setHiScore();	// update high score if necessary.
}

void Score::setHiScore(){
	int _hiScore = hiScore;
	if (currScore >= hiScore){
		hiScore = currScore;
		if (xw){
			std::ostringstream _oss, oss;
			_oss << hiScore;
			std::string s = "Hi Score: "+ _oss.str();
			oss << _hiScore;
			std::string _s = "Hi Score: "+ oss.str();
			xw->fillRectangle(10,37, _s.length()*7, 12, Xwindow::White);
			xw->drawString(10, 48, s, 0);
		}
	}
}

void Score::setBM(BlockMovement *bm){
	this->bm = bm;
}

void Score::setLvl(int level){
	this->level = level;
}

int Score::getLvl(){
	return level;
}