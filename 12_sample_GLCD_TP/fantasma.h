#ifndef FANTASMA_H
#define FANTASMA_H

#include <stdbool.h>

extern int X_fan;
extern int Y_fan;
extern int bad;
extern int hits;
extern int wait;
extern int In_Box;
extern int Tempo_blu;

#define MAX_QUEUE_SIZE 100


typedef struct {
    int x, y;
    int cost;
    int priority;
} Node;


void Fantasma_render();
int  Fantasma_canGO(int X, int Y);
void Fantasma_moveTO(int X, int Y);
void Fantasma_clear();


int heuristic(int x1, int y1, int x2, int y2);
int Fantasma_Compute_nextPOS();
int Fantasma_Escape();


// Dichiarazioni delle funzioni per la gestione della coda
void push(Node n);
Node pop();
bool isEmpty();
bool isInBounds(int x, int y, int N_colonne, int N_righe);

#endif // FANTASMA_H
