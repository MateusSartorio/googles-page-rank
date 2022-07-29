#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../h/lista.h"

typedef struct cel Celula;

struct cel{
    char* chave;
    Celula* prox;
};

struct lista{
    Celula* prim;
    Celula* ult;
};

Lista* inicia_lista(){
    Lista* lista = (Lista*)malloc(sizeof(Lista));

    lista->prim = NULL;
    lista->ult = NULL;

    return lista;
}

void insere_na_lista(Lista* lista, char* string){
    Celula* cont = NULL;
    for(cont = lista->prim; cont!=NULL; cont = cont->prox){
        if(strcmp(cont->chave, string) == 0) return;
    }

    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->chave = string;
    nova->prox = NULL;

    if(lista->ult == NULL) {
        lista->ult = nova;
        lista->prim = nova;
    }
    else {
        lista->ult->prox = nova;
        lista->ult = nova;
    }


}

void retira_na_lista(Lista* lista, int posicao){
    Celula* p = lista->prim;
    Celula* ant;

    for(int i = 0; p!=NULL && i<posicao; i++){
        ant = p;
        p = p->prox;
    }
    
    if(p == NULL) return;

    if(p == lista->prim && p == lista->ult){
        lista->prim = lista->ult = NULL;
    }else if(p == lista->prim){
        lista->prim = p->prox;
    }else if(p == lista->ult){
        lista->ult = ant;
        lista->ult->prox = NULL;
    }else ant->prox = p->prox;
    
    free(p);
}

void imprime_lista(Lista* lista){
    Celula* cont = lista->prim;

    for(cont; cont!=NULL;cont = cont->prox){
        printf("%s ", cont->chave);
    }
}

void destroi_lista(Lista* lista){
    Celula* p = lista->prim;
    Celula* temp;

    while(p!= NULL){
        temp = p->prox;
        free(p);
        p = temp;
    }

    free(lista);
}