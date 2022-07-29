#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./src/h/vetor.h"
#include "./src/h/grafo.h"
#include "./src/h/indexador.h"

int main(int argc, char** argv) {
    char* dir = argv[1];

    char* index = append_diretorio(dir, "index.txt");
    char* stopwords = append_diretorio(dir, "stopwords.txt");
    char* graph = append_diretorio(dir, "graph.txt");
    char* pages = append_diretorio(dir, "pages");

    // printf("%s\n", index);
    // printf("%s\n", stopwords);
    // printf("%s\n", graph);

    FILE* fi = fopen(index, "r");
    FILE* fs = fopen(stopwords, "r");
    FILE* fg = fopen(graph, "r");

    if(!fi || !fs || !fg) {
        printf("Erro na abertura dos arquivos!\n");
        exit(1);
    }

    Vetor* vetorIndex = vetor_strings(fi);
    //imprime_vetor(vetorIndex);

    Vetor* vetorStopwords = vetor_strings(fs);
    // imprime_vetor(vetorStopwords);

    Grafo** g = le_grafo(fg, vetorIndex);
    page_rank(g,vetorIndex->tam);
    // imprime_grafo(g, vetorIndex->tam);

    RBT* tab_sim = indexador(vetorIndex, vetorStopwords, pages);
    //RBT_imprime(tab_sim);

    while(1) {
        char* linha;
        size_t size = 0;

        getline(&linha, &size, stdin);
        if(feof(stdin))
            break;
        
        printf("%s\n", linha);


        free(linha);
    }

    RBT_libera(tab_sim);
    libera_grafo(g, vetorIndex->tam);
    destroi_vetor(vetorIndex);
    destroi_vetor(vetorStopwords);

    fclose(fi);
    fclose(fs);
    fclose(fg);
        
    free(index);
    free(stopwords);
    free(graph);
    free(pages);

    return 0;
}