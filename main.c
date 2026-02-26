#include <stdio.h>
#include "game.h"

int parseCol(char c) { return c - 'a'; }
int parseRow(char c) { return 8 - (c - '0'); }

int main() {
    char sc, sr, ec, er;

    initBoard();

    while (1) {
        printBoard();
        printf("Digite movimento (ex: e2 e4): ");

        if (scanf(" %c%c %c%c", &sc, &sr, &ec, &er) != 4)
            break;

        if (movePiece(parseRow(sr), parseCol(sc), parseRow(er), parseCol(ec)))
            printf("Movimento realizado!\n");
        else
            printf("Movimento invalido!\n");
    }

    return 0;
}
