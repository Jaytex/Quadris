#ifndef __COMMAND_H
#define __COMMAND_H
   
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>

// Template to calculate the size of an array
template<typename T, std::size_t N> std::size_t NVAL(T (&)[N]) { return N; }


// A struct for storing the entries in the vector (Helps with initialization purposes)
struct entries{
	int key;
	std::string *vals;
	size_t numOfVals;
};

class Command{

	private:
		bool isValCmd;
		int num; 
		std::string currCmd; 
		std::string aCmd; // current command and actual command (i.e. without number prefix)

		// A map from a key to a vector
		std::map<int, std::vector<std::string> > commands;	// (key, value)

																	// (0, left)
																	// (1, right)
																	// (2, down)
																	// (3, clockwise)
																	// (4, counterclockwise)
																	// (5, drop)
																	// (6, levelup)
																	// (7, leveldown)
																	// (8, restart)
	
	public:
		Command();
		~Command();

		void verify(); // test that everything was inserted into commands properly

		// Accessor Methods

		int getCmdNum(); // Gets the number in front of the command
		bool getValCmd();
		std::string getACmd(); // Gets actual command without number
		std::string getCmd(); // Gets the curent command
		std::vector<std::string>  getCmd(int x); // Gets the command

		// Mutator Methods
		void setCmd(std::string cmd); // sets the current command to cmd (including the number)					  
		void setValCmd(); // searches if commands map actual command is valid, if so sets valCmd to true
						  //*** setCmd(std::string) MUST be called >= 1 before running ***
		void stripCmdNum(); // removes the number from currCmd and puts it into aCmd
							//*** setCmd(std::string) MUST be called >= 1 before running ***
};

#endif