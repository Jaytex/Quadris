CXX = g++
CXXFLAGS = -Wall -MMD -g -L/usr/include/X11
EXEC = quadris
OBJECTS = main.o  command.o block.o blocklist.o score.o blockmovement.o iblock.o jblock.o lblock.o nextblock.o oblock.o sblock.o tblock.o zblock.o cell.o board.o game.o xwindow.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -lX11 -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS ${EXEC} ${DEPENDS}