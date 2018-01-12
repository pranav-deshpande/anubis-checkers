/*
Anubis - Checkers Game
Copyright (C) 2017-2018 Pranav Deshpande

This file is a part of Anubis.

Anubis is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

Anubis is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Anubis. If not, see <http://www.gnu.org/licenses/>.
*/

#include "board.hpp"

void board::generateAllMoves(std::vector<Move> &moves) {
  moves.clear();
  generateCaptureMoves(moves);
  // Hence, if they do not exist, only then do we generate normal moves
  if(moves.empty()) {
    generateNonCaptureMoves(moves);
  }
}

void board::generateCaptureMoves(std::vector<Move> &moves) {
  uint64_t tempLight, tempDark, tempLightKing, tempDarkKing, tempKing, block;
  block = light | dark;
  tempDarkKing = dark & king;
  tempLightKing = light & king;

  for(int i = 0; i < 64; i++) {
    if ( side == LIGHT && ((1ULL << i) & light) ) {
      int start = i;
      int cap1 = start+7;
      int cap2 = start+9;
      int end1 = start+14;
      int end2 = start+18;

      tempLight = light, tempDark = dark, tempKing = king;
      if ( ((1ULL << cap1) & dark) && !((1ULL << end1) & block) ) {
        // avoid "wrapping"
        if( start % 8 != 0 && start % 8 != 1) {
          tempLight = tempLight & (~(1ULL << start)); //zero that square
          tempDark  = tempDark  & (~(1ULL << cap1 )); //remove the dark piece
          tempLight = tempLight | (1ULL << end1); //one at the new pos now
          Move move(tempLight, tempDark, tempKing);
          moves.push_back(move);
        }
      }

      tempLight = light, tempDark = dark, tempKing = king;
      if ( ((1ULL << cap2) & dark) && !((1ULL << end2) & block) ) {
        // avoid "wrapping"
        if(start % 8 != 7 && start % 8 != 6) {
            tempLight = tempLight & (~(1ULL << start)); //zero that square
            tempDark  = tempDark  & (~(1ULL << cap2 )); //remove the dark piece
            tempLight = tempLight | (1ULL << end2); //one at the new pos now
            Move move(tempLight, tempDark, tempKing);
            moves.push_back(move);
        }
      }
    }

    if ( side == DARK && ((1ULL << i) & dark) ) {
      int start = i;
      int cap1 = start-9;
      int cap2 = start-7;
      int end1 = start-18;
      int end2 = start-14;

      tempLight = light, tempDark = dark, tempKing = king;
      if ( ((1ULL << cap1) & light) && !((1ULL << end1) & block) ) {
        // avoid "wrapping"
        if(start % 8 != 0 && start % 8 != 1) {
          tempDark = tempDark & (~(1ULL << start)); //zero that square
          tempLight = tempLight & (~(1ULL << cap1)); //remove the light piece
          tempDark = tempDark | (1ULL << end1); //one at the new pos now
          Move move(tempLight, tempDark, tempKing);
          moves.push_back(move);
        }
      }

      tempLight = light, tempDark = dark, tempKing = king;
      if ( ((1ULL << cap2) & light) && !((1ULL << end2) & block) ) {
        // avoid "wrapping"
        if(start % 8 != 7 && start % 8 != 6) {
          tempDark = tempDark & (~(1ULL << start)); //zero that square
          tempLight = tempLight & (~(1ULL << cap2)); //remove the light piece
          tempDark = tempDark | (1ULL << end2); //one at the new pos now
          Move move(tempLight, tempDark, tempKing);
          moves.push_back(move);
        }
      }
    }
  }
// this function ends here.
}

void board::generateNonCaptureMoves(std::vector<Move> &moves) {
  uint64_t tempLight, tempDark, tempLightKing, tempDarkKing, tempKing, block;
  uint64_t lightKing, darkKing;
  block = light | dark;
  lightKing = light & king;
  darkKing  = dark & king;

  for(int i = 0; i < 64; i++) {
    if ( side == LIGHT && ((1ULL << i) & light) ) {
      int start = i;
      int end1 = start+7;
      int end2 = start+9;

      // If 7 is added to start, it causes "curling up"
      tempLight = light, tempDark = dark, tempKing = king;
      if ( !((1ULL << end1) & block) ) {
        if (start % 8 != 0) {
          tempLight = tempLight & (~(1ULL << start)); //zero that square
          tempLight = tempLight | (1ULL << end1); //one at the new pos now
          Move move(tempLight, tempDark, tempKing);
          moves.push_back(move);
        }
      }

      // If 9 is added to start, it causes "curling up"
      tempLight = light, tempDark = dark, tempKing = king;
      if ( !((1ULL << end2) & block) ) {
        if (start % 8 != 7) {
          tempLight = tempLight & (~(1ULL << start)); //zero that square
          tempLight = tempLight | (1ULL << end2); //one at the new pos now
          Move move(tempLight, tempDark, tempKing);
          moves.push_back(move);
        }
      }
    }

    // Normal move generation for dark
    if (side == DARK && ((1ULL << i) & dark) ) {
      int start = i;
      int end1 = start-9;
      int end2 = start-7;

      // If 9 is subracted from the start, it causes "curling up"
      tempLight = light, tempDark = dark, tempKing = king;
      if ( !((1ULL << end1) & block) ) {
          if (start % 8 != 0) {
          tempDark = tempDark & (~(1ULL << start)); //zero that square
          tempDark = tempDark | (1ULL << end1); //one at the new pos now
          Move move(tempLight, tempDark, tempKing);
          moves.push_back(move);
        }
      }

      // If 7 is subtracted from the start, it causes "curling up"
      tempLight = light, tempDark = dark, tempKing = king;
      if ( !((1ULL << end2) & block) ) {
        if (start % 8 != 7) {
          tempDark = tempDark & (~(1ULL << start)); //zero that square
          tempDark = tempDark | (1ULL << end2); //one at the new pos now
          Move move(tempLight, tempDark, tempKing);
          moves.push_back(move);
        }
      }
    }
  }

}
