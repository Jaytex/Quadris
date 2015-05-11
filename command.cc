#include "command.h"

Command::Command(): isValCmd(false), num(1), currCmd(""), aCmd(""){

	// Creating the commands and all the non ambigous forms of them

	// Moves a block left
	std::string left[5] = {"lef","left"};		
	// Moves a block right
	std::string right[5] = {"ri","rig","righ","right"};			
	// Moves a block down
	std::string down[5] = {"do","dow","down"};			
	// Rotates block clockwise
	std::string cw[10] = {"cl","clo","cloc","clock","clockw","clockwi","clockwis","clockwise"};		
	// Rotates block counter-clockwise
	std::string ccw[30] = {"co","cou","coun","count","counte","counter","counterc","countercl","counterclo","countercloc","counterclock","counterclockw","counterclockwi","counterclockwis","counterclockwise"};
	// Drops a block (this must be called for a new block to be generated)
	std::string drop[5] = {"dr","dro","drop"};			
	// Increases the level
	std::string lu[5] = {"levelu","levelup"};			
	// Decreases the level
	std::string ld[5] = {"leveld","leveldo", "leveldow" "leveldown"};		
	// Restarts the game
	std::string restart[10] = {"re","res","rest","resta","restar","restart"};	

	entries cmds[] = {
						{0,left,NVAL(left)},
						{1,right,NVAL(right)},
						{2,down,NVAL(down)},
						{3,cw,NVAL(cw)},
						{4,ccw,NVAL(ccw)},
						{5,drop,NVAL(drop)},
						{6,lu,NVAL(lu)},
						{7,ld,NVAL(ld)},
						{8,restart,NVAL(restart)}
	};

	// Initialize our command map
	for (unsigned int i = 0; i < NVAL(cmds); ++i){
			commands.insert(std::make_pair(cmds[i].key,
				// insert vectors for each key 
				std::vector<std::string>(cmds[i].vals, cmds[i].vals+cmds[i].numOfVals)));
	}	
}

Command::~Command(){
	commands.clear(); // clear the contents of the command map
}

// For testing purposes
void Command::verify(){
	for (std::map<int, std::vector<std::string> >::const_iterator i = commands.begin(); i != commands.end(); ++i){
		std::cout << i->first << ": ";
		for (std::vector<std::string>::const_iterator j = i->second.begin(); j != i->second.end(); ++j){
			std::cout << *j << " ";
		}
		std::cout << std::endl;
	}
}
// Returns the list of all the possible non-ambigous forms of a command
std::vector<std::string>  Command::getCmd(int x){
	return commands[x];
}

int Command::getCmdNum(){
	return num;
}

void Command::setCmd(std::string cmd){
	currCmd = cmd;
}

std::string Command::getCmd(){
	return currCmd;
}

std::string Command::getACmd(){
	return aCmd;
}

void Command::setValCmd(){
	stripCmdNum(); // sets aCmd to actual command (without number) and parses the number to num
	// search each vector in the map to see if the command exists
	// if it does then command is valid
	for (unsigned int i = 0; i < 9; ++i){
		std::vector<std::string> v = getCmd(i);
		if(std::find(v.begin(),v.end(),aCmd) != v.end()){
			isValCmd = true; return;
		} else {
			isValCmd = false;
		}
	}
}

bool Command::getValCmd(){
	return isValCmd;
}

// helper function
bool isNum(char n){
	return	(n >= '0' && n <= '9') ? true : false;
}

int parseNum(std::string s){
	std::istringstream iss(s);
	int num;
	iss >> num;
	return num;
}

void Command::stripCmdNum(){
	int cmdLength = currCmd.length();
	std::string n = "";
	
	int i = 0;
	// extract any number until it reaches a non-numeric character
	for(; i < cmdLength; ++i){
		if(isNum(currCmd[i])){
			n += currCmd[i];
		}
		else break;
	}

	if(!i) n = "1"; // only apply the command once if no number specified
	num = parseNum(n);
	aCmd = currCmd.substr(i); // set actual command to command without number
}


