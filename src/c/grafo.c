#include "../h/grafo.h"

Grafo* init_grafo(char* chave) {
    Grafo* graf = (Grafo*)malloc(sizeof(Grafo));
    graf->chave = chave;
    graf->adjacencias = NULL;

    return graf;
}

Grafo** le_grafo(FILE* fg, Vetor* vetIndex) {
    Grafo** g = (Grafo**) malloc((vetIndex->tam)*sizeof(Grafo*));
    for(int i = 0; i < (vetIndex->tam); i++) g[i] = init_grafo(vetIndex->v[i]);
    
    for(int i = 0; i < (vetIndex->tam); i++) {
        char* linha = NULL;
        size_t size = 0;
        getline(&linha, &size, fg);

        //g[i] = init_grafo(strtok(linha, " "));
        char* influenciado = strtok(linha, " ");

        int n = atoi(strtok(NULL, " "));
        int m = busca_binaria_string(vetIndex->v, influenciado, 0, vetIndex->tam -1);
        if(m >= 0) g[m]->numSaidas = n;

        int igual = 0;
        for(int j = 0; j < n; j++){
            if(igual == 1) break;
            //insere_na_lista(g[i]->adjacencias, strtok(NULL, " \n"));
            char* chaveAtual = strtok(NULL, " \n");
            int posInfluenciador = busca_binaria_string(vetIndex->v, chaveAtual, 0, vetIndex->tam -1);
            printf("influenciado = %d, influenciador: %d\n", m,posInfluenciador);
            Grafo* cont = NULL;
            for(cont = g[posInfluenciador]; cont!=NULL; cont = cont->adjacencias){
                if(strcmp(cont->chave, influenciado) == 0) igual = 1;
            }
            if(igual != 1)cont = g[m];
        }
    }

    return g;
}

void imprime_grafo(Grafo** g, int tam) {
    for(int i = 0; i < tam; i++){
        printf("Nó: <%s> ", g[i]->chave);
        for(Grafo* cont = g[i]->adjacencias; cont!=NULL; cont = cont->adjacencias){
            printf("%s ", cont->chave);
        }
        putchar('\n');
    }
}

void libera_grafo(Grafo** g, int tam) {
    for(int i = 0; i < tam; i++) {
        free(g[i]->chave);
        //destroi_lista(g[i]->adjacencias);
        free(g[i]);
    }
    free(g);
}