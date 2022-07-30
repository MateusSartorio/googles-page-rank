#ifndef VETOR_H
#define VETOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tamanho inicial da alocacao do vetor de strings
#define TAM_INIC 2

// Struct vetor de strings que contém um vetor interno e seu tamamnho
typedef struct vetor_t {
    int tam;
    char** v;
} Vetor;

// Gera vetor de strings
Vetor* vetor_strings(FILE* arquivo);

// Faz busca binaria em um vetor de strings ordenado
int busca_binaria_string(char** vet, char* k, int lo, int hi);

// Imprime vetor da saida padrao
void imprime_vetor(Vetor* vetor);

// Desaloca memoria do vetor e de todos os seus elementos
void destroi_vetor(Vetor* vetor);

// Desaloca memoria do vetor, mas nao de seus elementos
void libera_vetor(Vetor* vetor);

#endif