Bitboard based checkers engine. I plan to use some sort of machine learning algorithm for the evaluation function.  

Rough design doc(intended more as a personal reference while the development is in it's initial stages):

1. Bitboard based engine
2. Use machine learning in the evaluation function -- figure out the details. Will probably be a neural network.
3. Bitboards - 3: light, dark, and king.
4. All the bitboards are 64 bit integers
5. What will the directory structure be like?
--- Directory structure:
a) main.cpp
b) moveGenerator.cpp
c) data.hpp
d) board.cpp
e) board.hpp
f) eval.cpp, eval.hpp
g) search.cpp, search.hpp

6. Classes - the board class.

Will contain the data members light, dark and king.
The constructor will initialize them to the required values.
A printing method will be present to print the board.
makeMove()
undoMove()
generateAllMoves() -- function to generate legal moves

main structure -- class board: board() { light = ..., dark = ..., king = ...}
main will initialize a board object.

