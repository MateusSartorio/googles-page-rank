#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./src/h/busca.h"

int main(int argc, char** argv) {
    char* dir = argv[1];

    char* index = append_diretorio(dir, "index.txt");
    char* stopwords = append_diretorio(dir, "stopwords.txt");
    char* graph = append_diretorio(dir, "graph.txt");
    char* pages = append_diretorio(dir, "pages");

    FILE* fi = fopen(index, "r");
    FILE* fs = fopen(stopwords, "r");
    FILE* fg = fopen(graph, "r");

    FILE* fp = fopen("./entrada/searches.txt", "r");

    if(!fi || !fs || !fg) {
        printf("Erro na abertura dos arquivos!\n");
        exit(1);
    }

    Vetor* vetorIndex = vetor_strings(fi);

    Vetor* vetorStopwords = vetor_strings(fs);

    Grafo** g = le_grafo(fg, vetorIndex);
    page_rank(g,vetorIndex->tam);

    RBT* tab_sim = indexador(vetorIndex, vetorStopwords, pages);

    processa_consultas(tab_sim, vetorStopwords, vetorIndex, g, fp);
    // processa_consultas(tab_sim, vetorStopwords, vetorIndex, g, stdin);

    RBT_libera(tab_sim);
    libera_grafo(g, vetorIndex->tam);
    destroi_vetor(vetorIndex);
    destroi_vetor(vetorStopwords);

    fclose(fi);
    fclose(fs);
    fclose(fg);

    fclose(fp);
        
    free(index);
    free(stopwords);
    free(graph);
    free(pages);

    return 0;
}