CXX=g++
CFLAGS=-I. --std=c++11
DEPS=board.hpp move.hpp
OBJ=board.o move.o main.o

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

anubis_checkers: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	rm board.o move.o main.o
