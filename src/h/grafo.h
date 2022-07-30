#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lista.h"
#include "vetor.h"

// Constantes utilizadas no calculo do page rank
#define alfa 0.85
#define epsilon 1e-6

// Funcao de macro que calcula o valor absoluto de um numero em ponto flutuante
#define fabs(A) (A > 0 ? A : -A)

typedef struct grafo_t Grafo;
typedef struct list_int_t ListInt;

// Lista utilizada para representar os elementos de entrada de cada no
struct list_int_t {
    int index;
    ListInt* prox;
};

// Cada struct grafo corresponde a um no do grafo
// Cada no possui uma chave, o page rank, a quantidade de elementos de saida e a lista de elementos de entrada
struct grafo_t{
    char* chave;
    double pr;
    int numAdjacencias;
    ListInt* entradas;
};

// Inicializa um nó de grafo com uma chave e um valor de page rank
Grafo* init_grafo(char* chave, double pr);

// Calcula os valores de page rank de cada arquivo (recursivamente) até que o valor se estabilize
void page_rank(Grafo** g, int n);

// Le o arquivo graph.txt e constroi o grafo
// A lista de adjacencias de cada aponta para as conexoes que chegam no no
Grafo** le_grafo(FILE* fg, Vetor* vetIndex);

// Imprime grafo na saida padrao
void imprime_grafo(Grafo** g, int tam);

// Desaloca memoria alocada para o grafo e todos os seus nos
void libera_grafo(Grafo** g, int tam);

#endif