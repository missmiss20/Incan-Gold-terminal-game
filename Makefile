CXX=clang++

CXXFLAGS = -std=c++11 -Wall -Wextra -Werror

BINARIES = player.o adventure.o 

rungame: ${BINARIES} main.o
	${CXX} ${CXXFLAGS} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o
