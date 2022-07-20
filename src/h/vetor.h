#ifndef VETOR_H
#define VETOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_INIC 2

typedef struct vetor_t {
    int tam;
    char** v;
} Vetor;

Vetor* vetor_strings(FILE* arquivo);
void imprime_vetor(Vetor* vetor);
void destroi_vetor(Vetor* vetor);

#endif