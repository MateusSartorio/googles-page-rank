#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "lista.h"

#define VERMELHO    true
#define PRETO       false

#define NULL_Value  NULL
#define NULL_Key    NULL

#define Key char*
#define Value Lista*

typedef struct node RBT;

// A arvore rubro negra foi utilizada como tabela de simbolos
// Struct no da arvore rubro negra, contem uma chave, um valor, uma cor e os ponteiros para dois outros nos
struct node {
    Key chave;
    Value val;
    bool cor;
    RBT *e, *d;
};

// Inicializa a arvore rubro negra
RBT* RBT_init();

// Busca uma chave na tabela de simbolos, retorna o valor caso encontre e NULL_Value caso contrario
Value busca(RBT *n, Key key);

// Insere uma chave na tabela de simbolos
RBT* RBT_insere(RBT *h, Key key, char* val);

// Imprime a arvore rubro negra na saida padrao
void RBT_imprime(RBT* h);

// Libera todos os nos da arvore rubro negra
void RBT_libera(RBT* h);

#endif