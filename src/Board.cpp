#include "Board.h"
using namespace std;

Board::Board() {}

Board::Board(stringstream &stream, int width, int height) {
  this->width = width;
  this->height = height;

  int x = 0;
  int y = 0;
  string line;
  while (getline(stream, line, ',')) {
    b[x][y] = (line == ".");
    if (line == "0") {
      playerPosX[Pl1] = x;
      playerPosY[Pl1] = y;
    } else if (line == "1") {
      playerPosX[Pl2] = x;
      playerPosY[Pl2] = y;
    }
    x = (x+1)%16;
    if (x == 0)
      y++;
  }
}

vector<BoardMoves> Board::LegalMoves(int pos[2]) {
  int x = pos[0];
  int y = pos[1];
  vector<BoardMoves> moves;
  if (y > 0  && b[x][y-1]) moves.push_back(UP);
  if (y < height-1 && b[x][y+1]) moves.push_back(DOWN);
  if (x > 0   && b[x-1][y]) moves.push_back(LEFT);
  if (x < width-1 && b[x+1][y]) moves.push_back(RIGHT);
  return moves;
}

void Board::SetWidth(int width) {
  this->width = width;
}

void Board::SetHeight(int height) {
  this->height = height;
}