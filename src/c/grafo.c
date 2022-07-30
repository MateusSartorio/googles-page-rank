#include "../h/grafo.h"

// Incializa uma lista encadeada de inteiros
static ListInt* init_listint(int index){
    ListInt* li = (ListInt*)malloc(sizeof(ListInt));
    li->index = index;
    li->prox = NULL;
    
    return li;
}

Grafo* init_grafo(char* chave, double pr) {
    Grafo* graf = (Grafo*) malloc(sizeof(Grafo));
    graf->chave = chave;
    graf->pr = pr;
    graf->numAdjacencias = 0;
    graf->entradas = NULL;

    return graf;
}

// Função responsável por verificar se a diferença entre o page rank atual é significantemente menor que a do page rank anterior
static bool e(Grafo** g, double* vetAnt, int n) {
    double cont = 0.0f;
    for(int i = 0; i < n; i++)
        cont += fabs((g[i]->pr - vetAnt[i])) / (double) n;

    if(cont < epsilon)
        return true;

    return false;
}

// Funcao recursiva chamada por page_rank(), que calcula o novo page rank a partir do vetor de page ranks anteriores
static void rec_page_rank(Grafo** g, double* vetAnt, int n) {  
    for(int i = 0; i < n; i++)
        vetAnt[i] = g[i]->pr;

    double cont = 0.0f;
    for(int i = 0; i < n; i++) {
        if(g[i]->numAdjacencias != 0) {
            for(ListInt* j = g[i]->entradas; j; j = j->prox) {
                cont += vetAnt[j->index]/g[j->index]->numAdjacencias;
            }
            cont = ( (1.0f - alfa)/ (double) n ) + alfa*cont;
        }
        else {
            for(ListInt* j = g[i]->entradas; j; j = j->prox) {
                cont += vetAnt[j->index]/g[j->index]->numAdjacencias;
            }
            cont = ( (1.0f - alfa)/ (double) n ) + alfa*vetAnt[i] + alfa*cont;
        }
        g[i]->pr = cont;
        cont = 0.0f;
    }
    if(e(g, vetAnt, n))
        return;
    rec_page_rank(g, vetAnt, n);
}

void page_rank(Grafo** g, int n) {
    double* vetAnt = (double*) malloc(n*sizeof(double));

    for(int i = 0; i < n; i++)
        vetAnt[i] = 1.0f/n;

    rec_page_rank(g, vetAnt, n);
    free(vetAnt);
}

Grafo** le_grafo(FILE* fg, Vetor* vetIndex) {
    Grafo** g = (Grafo**) malloc(vetIndex->tam*sizeof(Grafo*));
    for(int i = 0; i < vetIndex->tam; i++) g[i] = init_grafo(vetIndex->v[i], 1.0f/vetIndex->tam);
    
    for(int i = 0; i < vetIndex->tam; i++) {
        char* linha = NULL;
        size_t size = 0;
        getline(&linha, &size, fg);

        char* influenciado = strtok(linha, " ");
        int posInfluenciado = busca_binaria_string(vetIndex->v, influenciado, 0, vetIndex->tam);
        if(posInfluenciado >= 0) g[posInfluenciado]->numAdjacencias;
        int n = atoi(strtok(NULL, " "));
        g[posInfluenciado]->numAdjacencias = n;

        for(int i = 0; i < n; i++){
            char* influenciador = strtok(NULL, " \n");
            int posInfluenciador = busca_binaria_string(vetIndex->v, influenciador, 0, vetIndex->tam);

            if(!g[posInfluenciador]->entradas){
                g[posInfluenciador]->entradas = init_listint(posInfluenciado);
            }else{
                ListInt* count = g[posInfluenciador]->entradas;
                for(count; count->prox; count = count->prox){}
                count->prox = init_listint(posInfluenciado);
            }
        }
        free(linha);
    }

    return g;
}

void imprime_grafo(Grafo** g, int tam) {
    for(int i = 0; i < tam; i++) {
        printf("%s, pr: %0.16f | ", g[i]->chave, g[i]->pr);
        for(ListInt* temp = g[i]->entradas; temp; temp = temp->prox){
            printf("%s ", g[temp->index]->chave);
        }
        printf("\n");
    }
}

void libera_grafo(Grafo** g, int tam) {
    for(int i = 0; i < tam; i++) {
        ListInt* cont = g[i]->entradas;
        ListInt* temp;
        while(cont) {
            temp = cont->prox;
            free(cont);
            cont = temp;
        }
        free(g[i]);
    }
    free(g);
}