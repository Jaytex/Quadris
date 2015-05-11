#include "game.h"

//ctor
Game::Game(Xwindow *xw1, Xwindow *xw2):level(0),  
		currSeed(maxSeed), graphicsOn(false), 
		endGame(false),  restart(false), done(false), newState(true), 
  		xw1(xw1), xw2(xw2), b(Board(xw1, xw2)), bm(BlockMovement(&b)), s(Score(&bm, level, xw1)),
  		nextBlock(NULL), xxx("sequence.txt"){}

//dtor
Game::~Game(){
	if (bm.currBlock) delete bm.currBlock;
	if (nextBlock) delete nextBlock;
	sequence.clear();
}

// runs a new game of Quadris
void Game::newGame(){
	if (xw1) drawGame();
	prng.seed(currSeed);
	int p; // probability
	int numOfDrops = 0;

	while (true){
		if (done) break; 
		if (endGame) killGame();
		switch(level){
			case 0:
				genCurrBlock(0);
				break;
			case 1:
				p = prng() % 12;
				genCurrBlock(p);
				break;
			case 2:
				p = prng() % 7;
				genCurrBlock(p);
				break;
			case 3:
				p = prng() % 9;
				genCurrBlock(p);
		} 
		b.turnOnBlock(bm.currBlock);
		std::string _cmd;

		while(true){

			if (newState || restart || endGame){
				switch(level){
					case 0:
						genNextBlock(0);
						break;
					case 1:
						p = prng() % 12;
						genNextBlock(p);
						break;
					case 2:
						p = prng() % 7;
						genNextBlock(p);
						break;
					case 3:
						p = prng() % 9;
						genNextBlock(p);
					}

					b.turnOnNextBlock(nextBlock);
					printGame();
					newState = false;
					restart = false;
					endGame = false;
			}

			if (numOfDrops){
				_cmd = "drop";
				--numOfDrops;
			}
			else if (!(std::cin >> _cmd)){ 
				done = true; 
				break;
			}

			cmd.setCmd(_cmd);
			cmd.setValCmd();
			bool valCmd = cmd.getValCmd();
			int num = cmd.getCmdNum(); // the number before a command
			std::vector<std::string> v;
			if (valCmd) {

				std::string aCmd = cmd.getCmd(); // command without number
				// left
				v = cmd.getCmd(0);
				if (std::find(v.begin(), v.end(), aCmd) != v.end()){
					bm.moveLeft(num);
					printGame();
				}
				// right
				v = cmd.getCmd(1);
				if (std::find(v.begin(), v.end(), aCmd) != v.end()){
					bm.moveRight(num);
					printGame();
				}
				// down
				v = cmd.getCmd(2);
				if (std::find(v.begin(), v.end(), aCmd) != v.end()){
					bm.moveDown(num);
					printGame();
				}
				// clockwise
				v = cmd.getCmd(3);
				if (std::find(v.begin(), v.end(), aCmd) != v.end()){
					bm.rotateCW(num);
					printGame();
				}
				// counterclockwise
				v = cmd.getCmd(4);
				if (std::find(v.begin(), v.end(), aCmd) != v.end()){
					bm.rotateCCW(num);
					printGame();
				}
				// drop
				v = cmd.getCmd(5);
				if (std::find(v.begin(), v.end(), aCmd) != v.end()){ // A LOT OF EDITING LEFT
					if (num){
						bm.dropBlock();
						b.setBlockFree(bm.currBlock);
						bm.pushBlock();
						bm.killFullLine();
						s.setScore();
						s.setHiScore();
						b.killNextBlock(nextBlock);
						nextBlock->newBlockState();
						bm.currBlock = nextBlock;
						bm.setSafeMovement(space);
						if (bm.getSafeMovement()){ 
							b.turnOnBlock(bm.currBlock);
						}
						else {
							endGame = true; // no space to generate a new game
							break;
						}
						newState = true;
						if (num - 1)  numOfDrops = num - 1;
					} else 
						printGame();
				}
				// levelup
				v = cmd.getCmd(6);
				if (std::find(v.begin(), v.end(), aCmd) != v.end()){
					levelUp(num);
					printGame();
				}
				// leveldown
				v = cmd.getCmd(7);
				if (std::find(v.begin(), v.end(), aCmd) != v.end()){
					levelDown(num);
					printGame();
				}
				// restart
				v = cmd.getCmd(8);
				if (std::find(v.begin(), v.end(), aCmd) != v.end()){
					restart = true;
					killGame();
					break;
				}
			}

			// if user issues non valid command
			else if (!valCmd){
				std::cout << "No such Command!" << std::endl;
			}
		}

		sequence.clear();
	}
}

void Game::levelUp(int x){
	if (x){
		for (int i = 0; i < x; ++i){
			if (level < 3){
				++level;
				bm.currBlock->levelUp();
				nextBlock->levelUp();
				s.setLvl(level);
			}
		}
		if (xw1){
			std::ostringstream _oss, oss;
			_oss << level;
			std::string s = "Level: "+ _oss.str();
			int l = level - 1;
			oss << l;
			std::string _s = "Level: "+ oss.str();
			xw1->fillRectangle(110,16, _s.length()*7, 12, Xwindow::White);
			xw1->drawString(110, 27, s, 0);
		}
	}
}

void Game::levelDown(int x){
	if (x){
		for (int i = 0; i < x; ++i){
			if (level > 0){
				--level;
				bm.currBlock->levelDown();
				nextBlock->levelDown();
				s.setLvl(level);
			}
		}
		if (xw1){
			std::ostringstream _oss, oss;
			_oss << level;
			std::string s = "Level: "+ _oss.str();
			int l = level + 1;
			oss << l;
			std::string _s = "Level: "+ oss.str();
			xw1->fillRectangle(110,16, _s.length()*7, 12, Xwindow::White);
			xw1->drawString(110, 27, s, 0);
		}
	}	
}

void Game::readScriptFile(std::string s){
 	char tetrominoeType;
 	std::ifstream scriptfile(s.c_str());
 	if (!scriptfile.fail()){
 		while( scriptfile >> tetrominoeType){
 			sequence.push_back(tetrominoeType); // adds the tetrominoeType to the sequence
 		}
 	}	
}

std::vector<char> Game::getSequence(){
 	return sequence;
}

void Game::genCurrBlock(uint32_t x){
	genNextBlock(x);
	bm.currBlock = nextBlock;
	nextBlock = NULL;
}
void Game::genNextBlock(uint32_t x){

 	char tetrominoeType;

 	switch (level){
 		case 0:
 			setScriptFile();
 			readScriptFile(scriptFile); // default file is sequence.txt
 			genBlock.setSequence(sequence);
 			genBlock.level_0();
 			tetrominoeType = genBlock.getTetrominoeType(); // set the generated block's tetrominoe 
 			break;
 		case 1:
 			genBlock.level_1(x); // using prng
			tetrominoeType = genBlock.getTetrominoeType(); // set the generated block's tetrominoe 
 			break;	
 		case 2:
  			genBlock.level_2(x); // using prng
			tetrominoeType = genBlock.getTetrominoeType(); // set the generated block's tetrominoe 
 			break;
 		case 3:
  			genBlock.level_3(x); // using prng
			tetrominoeType = genBlock.getTetrominoeType(); // set the generated block's tetrominoe 
 			
 	}

 	// Determine which block type to generate
 	switch(tetrominoeType){
 		case 'I':
 			nextBlock = new iBlock(level); break;
 		case 'J':
 			nextBlock = new jBlock(level); break;
 		case 'L':
 			nextBlock = new lBlock(level); break;
 		case 'O':
 			nextBlock = new oBlock(level); break;
  		case 'S':
 			nextBlock = new sBlock(level); break;
 		case 'Z':
 			nextBlock = new zBlock(level); break;
 		case 'T':
 			nextBlock = new tBlock(level); 
 	}
 	if (level == 0)	genBlock.nextTetrominoe(); // next character in the sequence
}

 // prints the game's layout
void Game::printGame(){
 	std::cout << "Level:      " << s.getLvl() << std::endl;
 	std::cout << "Score:      " << getScore() << std::endl;
 	std::cout << "Hi Score    "	<< getHiScore() << std::endl;
 	std:: cout << b;
}

void Game::drawGame(){
	xw1->fillRectangle(0, 0, NumCols*20, 67, Xwindow::White); 
	xw2->fillRectangle(0,0, 0, 0, Xwindow::Black);
    xw1->fillRectangle(210, 67, NumCols*22, NumRows*22, Xwindow::Black); // fill the grid black 
    xw1->fillRectangle(210, 0, 3, NumRows*24, Xwindow::Black);
    xw1->fillRectangle(199, 0, 3, NumRows*24, Xwindow::Black);
    xw1->fillRectangle(0 , 68, NumCols*20, NumRows*21, Xwindow::Black);
    xw1->drawString(10, 27, "Score: 0", 1);
    xw1->drawString(10, 48, "Hi Score: 0", 1);
    xw1->drawString(110, 27, "Level: 0", 1);
    xw1->drawString(260, 48, "NextBlock:");
    xw2->drawString(5,10,"Next Block:");
}

void Game::killGame(){

	if (bm.currBlock){
		b.killBlock(bm.currBlock);
		if (restart) delete bm.currBlock;
	}

 	if (nextBlock){
 		b.killNextBlock(nextBlock);
 		delete nextBlock;
 	}

 	sequence.clear(); // remove all element in the list
 	bm.clearLevelList();
 	bm.clearBlockList();
 	bm.clearBoundryBlock();
 	genBlock.reset_c();
 	s.setScore(0);
 	s.setScore();
}