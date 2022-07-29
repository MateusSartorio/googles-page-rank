#include "../h/vetor.h"

static int compare(const void* s1, const void* s2){
    char* c1 = *((char**)s1);
    char* c2 = *((char**)s2);

    return strcmp(c1,c2);
}

Vetor* vetor_strings(FILE* arquivo) {
    Vetor* vetor = (Vetor*)malloc(sizeof(Vetor));
    vetor->v = (char**)malloc(TAM_INIC*sizeof(char*));
    vetor->tam = 0;
    int tamMax = TAM_INIC;
    while(1) {
        if(feof(arquivo)) break;

        fscanf(arquivo, " %m[^\n] ", &vetor->v[vetor->tam]);
        vetor->tam++;

        if(vetor->tam >= tamMax){
            tamMax *= 2;
            vetor->v = (char**)realloc(vetor->v, tamMax*sizeof(char*));
        }
    }
    vetor->v = (char**)realloc(vetor->v, vetor->tam*sizeof(char*));

    qsort(vetor->v, vetor->tam, sizeof(char*), compare);

    return vetor;
}

int busca_binaria_string(char** vet, char* k, int lo, int hi) {
    if(hi < lo)
        return -1;
    
    int mid = lo + (hi-lo)/2;

    int cmp = strcmp(k, vet[mid]);
    if(!cmp)
        return mid;
    else if(cmp < 0)
        return busca_binaria_string(vet, k, lo, mid -1);
    else
        return busca_binaria_string(vet, k, mid + 1, hi);
}

void imprime_vetor(Vetor* vetor) {
    printf("====================================\n");
    printf("O tamanho do vetor eh: %d\n", vetor->tam);
    for(int i = 0; i < vetor->tam; i++)
        printf("%d: %s\n", i, vetor->v[i]);
    printf("====================================\n");
}

void destroi_vetor(Vetor* vetor) {
    for(int i = 0; i < vetor->tam; i++)
        free(vetor->v[i]);
        
    free(vetor->v);
    free(vetor);
}