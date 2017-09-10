SRC_FILES = board.cpp move.cpp main.cpp

all: anubis_checkers

anubis_checkers: $(SRC_FILES)
	g++ -std=c++11 $(SRC_FILES) -o $@
	
