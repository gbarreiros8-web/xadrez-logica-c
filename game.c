#include <stdio.h>
#include <stdlib.h>
#include "game.h"

Piece board[SIZE][SIZE];
char currentPlayer = 'W';

void initBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = (Piece){' ', ' '};

    for (int i = 0; i < SIZE; i++) {
        board[1][i] = (Piece){'P', 'B'};
        board[6][i] = (Piece){'P', 'W'};
    }

    board[0][0] = board[0][7] = (Piece){'R', 'B'};
    board[7][0] = board[7][7] = (Piece){'R', 'W'};

    board[0][1] = board[0][6] = (Piece){'N', 'B'};
    board[7][1] = board[7][6] = (Piece){'N', 'W'};

    board[0][2] = board[0][5] = (Piece){'B', 'B'};
    board[7][2] = board[7][5] = (Piece){'B', 'W'};

    board[0][3] = (Piece){'Q', 'B'};
    board[7][3] = (Piece){'Q', 'W'};

    board[0][4] = (Piece){'K', 'B'};
    board[7][4] = (Piece){'K', 'W'};
}

void printBoard() {
    printf("\nTurno: %s\n", currentPlayer == 'W' ? "Brancas" : "Pretas");

    for (int i = 0; i < SIZE; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j].type == ' ')
                printf(". ");
            else
                printf("%c ", board[i][j].type);
        }
        printf("\n");
    }
    printf("  a b c d e f g h\n");
}

int isPathClear(int sr, int sc, int er, int ec) {
    int dr = (er - sr) ? (er - sr)/abs(er - sr) : 0;
    int dc = (ec - sc) ? (ec - sc)/abs(ec - sc) : 0;

    sr += dr;
    sc += dc;

    while (sr != er || sc != ec) {
        if (board[sr][sc].type != ' ')
            return 0;
        sr += dr;
        sc += dc;
    }
    return 1;
}

int isValidMove(Piece p, int sr, int sc, int er, int ec) {
    int dr = er - sr;
    int dc = ec - sc;

    if (er < 0 || er >= SIZE || ec < 0 || ec >= SIZE)
        return 0;

    if (board[er][ec].color == p.color)
        return 0;

    switch (p.type) {
        case 'P':
            if (p.color == 'W')
                return (dr == -1 && dc == 0);
            else
                return (dr == 1 && dc == 0);

        case 'R':
            if (sr == er || sc == ec)
                return isPathClear(sr, sc, er, ec);
            break;

        case 'N':
            return (dr*dr + dc*dc) == 5;

        case 'B':
            if (abs(dr) == abs(dc))
                return isPathClear(sr, sc, er, ec);
            break;

        case 'Q':
            if (sr == er || sc == ec || abs(dr) == abs(dc))
                return isPathClear(sr, sc, er, ec);
            break;

        case 'K':
            return abs(dr) <= 1 && abs(dc) <= 1;
    }

    return 0;
}

int movePiece(int sr, int sc, int er, int ec) {
    Piece p = board[sr][sc];

    if (p.type == ' ' || p.color != currentPlayer)
        return 0;

    if (isValidMove(p, sr, sc, er, ec)) {
        board[er][ec] = p;
        board[sr][sc] = (Piece){' ', ' '};

        currentPlayer = (currentPlayer == 'W') ? 'B' : 'W';
        return 1;
    }

    return 0;
}
