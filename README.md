# Quadris
A derivative (non-realtime version) of the popular game tertis.

Much easier to play, allowing you to take your time before drop a block.

# Installation and Running

1. Pull the repository into a local directory
2. Navigate to the directory in a terminal and type make
3. In the terminal, type ./quadris to run the game
4. Enjoy!

#Commands

To move the blocks, you need to type the commands into the terminal.

Example, to move right, type in "right"

Once you're comfortable with a block's postion, type "drop" to finalize the turn.

The acceptable commands are:
- right
- left
- clockwise
- counterclockwise
- down
- levelup
- leveldown
- drop
- restart


#Extras

1. You only need to type the least unambigous expression to execute a command, e.g. "ri" is sufficient enough to move the block to the right, whereas "r" is not as there are two commands that start with the letter 'r'.
2. You can enter a command line only option by running the game by typing "./quadris -text"
3. You can start the game at any desired level by typing "./quadris -startlevel n" where n is either 0,1,2, or 3.