#ifndef GAME_H
#define GAME_H

#define SIZE 8

typedef struct {
    char type;   // P R N B Q K
    char color;  // W ou B
} Piece;

void initBoard();
void printBoard();
int movePiece(int sr, int sc, int er, int ec);
int isValidMove(Piece p, int sr, int sc, int er, int ec);
int isPathClear(int sr, int sc, int er, int ec);

#endif
