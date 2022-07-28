#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "vetor.h"

typedef struct no_t {
    char* chave;

    int numEntradas;
    No* entradas;

    int numSaidas;
    No* saidas;
} No;

typedef struct grafo_t {
    int tam;
    No** vetNos;
} Grafo;

Grafo* init_grafo();
Grafo** le_grafo(FILE* fg, Vetor* vetIndex);
void imprime_grafo(Grafo** g, int tam);
void libera_grafo(Grafo** g, int tam);

#endif