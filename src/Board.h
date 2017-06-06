#ifndef BOARD_h
#define BOARD_h

#include <sstream>
#include <vector>
#include "GameEnums.h"

class Board {
  int width = 16;
  int height = 16;
public:
  int playerPosX[2];
  int playerPosY[2];
  char b[16][16];
  Board();
  Board(std::stringstream &stream, int width, int height);
  void SetWidth(int width);
  void SetHeight(int height);
  std::vector<BoardMoves> LegalMoves(int pos[2]);
};

#endif
