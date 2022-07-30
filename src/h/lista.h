#ifndef LISTA_H
#define LISTA_H

typedef struct lista Lista;

typedef struct cel Celula;

// Struct cel contem uma string chave e um ponteiro para proxima celula
struct cel{
    char* chave;
    Celula* prox;
};

// Struct lista contem ponteiros para primeira e ultima celula
struct lista{
    Celula* prim;
    Celula* ult;
};

// Inicia uma lista
Lista* inicia_lista();

// Insere uma celula na lista
void insere_na_lista(Lista* lista, char* string);

// Retira uma celula da lista na posicao informada
void retira_na_lista(Lista* lista, int posicao);

// Imprime uma lista
void imprime_lista(Lista* lista);

// Libera a maemoria alocada para uma lista e seu conteudo
void destroi_lista(Lista* lista);

#endif