#include "Bot.h"
using namespace std;

unsigned int Bot::countGeral = 0;

Bot::Bot() : board() {
  struct timeval time;
  gettimeofday(&time,NULL);
  srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
  countGeral = 0;
}

void Bot::MakeMove(BoardMoves boardMove) {
  switch (boardMove) {
    case UP:    printf("up\n"); break;
    case DOWN:  printf("down\n"); break;
    case LEFT:  printf("left\n"); break;
    case RIGHT: printf("right\n"); break;
  }
}

void Bot::Move(int time) {
  countGeral = 0;
  int pos[2] = {posX, posY};
  vector<BoardMoves> moves = board.LegalMoves(pos);
  if(moves.size() == 0){
    MakeMove(UP);
    return;
  }
  unsigned int finalDirection = 0;
  unsigned int dirs[4] = {0, 0, 0, 0};
  for (int i = 0; i < moves.size(); i++) {
    dirs[i] = TryMove(moves[i], posX, posY);
  }
  finalDirection = maxMoves(dirs);

  MakeMove(moves[finalDirection]);
}

unsigned int Bot::TryMove(BoardMoves boardMove, int x, int y) {
  unsigned int count = 0;
  int dx = 0;
  int dy = 0;
  switch (boardMove) {
    case UP:    dy = -1; break;
    case DOWN:  dy = 1; break;
    case LEFT:  dx = -1; break;
    case RIGHT: dx = 1; break;
  }
  int xCur = x+dx;
  int yCur = y+dy;
  while (yCur > 0 && xCur > 0 && yCur < height && xCur < width && board.b[xCur][yCur] ) {
    count++;
    xCur += dx;
    yCur += dy;
  }
  countGeral++;
  if (countGeral <= 1) {
    int pos[2] = {xCur-dx, yCur-dy};
    vector<BoardMoves> moves = board.LegalMoves(pos);

    unsigned int finalDirection = 0;
    unsigned int dirs[4] = {0, 0, 0, 0};
    for (int i = 0; i < moves.size(); i++) {
      dirs[i] = TryMove(moves[i], xCur-dx, yCur-dy);
    }
    finalDirection = maxMoves(dirs);  
    count += dirs[finalDirection];
  }
  return count;
}

unsigned int Bot::maxMoves(unsigned int* dirs) {
  unsigned int max = 0;
  unsigned int index = 0;
  for (int i = 0; i < 4; i++) {
    if (dirs[i] > max) {
      max = dirs[i];
      index = i;
    }
  }
  return index;
}

void Bot::Round(int time) {  };
void Bot::Update(Board board) {
  this->board = board;
  this->posX = board.playerPosX[playerId];
  this->posY = board.playerPosY[playerId];
}

void Bot::Timebank(int time) { };
void Bot::TimePerMove(int time) { };
void Bot::YourBot(string name) { };
void Bot::YourBotId(Player playerId) { this->playerId = playerId; };
void Bot::FieldWidth(int width) { this->width = width; board.SetWidth(width); };
void Bot::FieldHeight(int height) { this->height = height; board.SetHeight(height); };
void Bot::PlayerNames(string player1, string player2) { };
