#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lista.h"
#include "vetor.h"

#define alfa 0.85
#define epsilon 1e-6

#define fabs(A) (A > 0 ? A : -A)

typedef struct grafo_t Grafo;
typedef struct list_int_t ListInt;

struct list_int_t{
    int index;
    ListInt* prox;
};

struct grafo_t{
    char* chave;
    double pr;
    int numAdjacencias;
    ListInt* entradas;
};

Grafo* init_grafo(char* chave, double pr);
void page_rank(Grafo** g, int n);
Grafo** le_grafo(FILE* fg, Vetor* vetIndex);
void imprime_grafo(Grafo** g, int tam);
void libera_grafo(Grafo** g, int tam);

#endif