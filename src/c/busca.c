#include "../h/busca.h"

void processa_consultas(RBT* tab_sim, Vetor* vetorStopwords, Vetor* vetIndex, Grafo** grafo, FILE* fp) {
    while(1) {
        if(feof(fp))
            break;

        char* linha = NULL;
        size_t size = 0;

        getline(&linha, &size, fp);
        char* copiaLinha = strdup(linha);

        to_lower(linha);

        Lista** vetListas = (Lista**) malloc(TAM_INIC*sizeof(Lista*));
        int tamMaxVetListas = TAM_INIC;
        int tamVetListas = 0;
        
        Vetor* vetDocumentos;

        bool naoEncontrado = false;

        char* termo = strtok(linha, " \n");
        while(termo) {
            int k = busca_binaria_string(vetorStopwords->v, termo, 0, vetorStopwords->tam - 1);
            
            if(k < 0) {
                Lista* l = busca(tab_sim, termo);
                if(l) {
                    vetListas[tamVetListas++] = l;
                    if(tamVetListas >= tamMaxVetListas) {
                        vetListas = (Lista**) realloc(vetListas, 2*tamMaxVetListas*sizeof(Lista*));
                        tamMaxVetListas *= 2;
                    }
                }
                else {
                    naoEncontrado = true;
                    break;
                }
            }
            termo = strtok(NULL, " \n");
        }

        if(naoEncontrado) {
            printf("search:%s\n", strtok(linha, "\n"));
            printf("pages:\n");
            printf("pr:\n");
        }else {
            vetDocumentos = gera_vetor_documentos(vetListas, tamVetListas);

            Grafo** vetDocumentosGrafo = organiza_page_rank(grafo, vetIndex, vetDocumentos);

            printf("search:%s\n", strtok(copiaLinha, "\n"));
            printf("pages:");
            for(int i = 0; i < vetDocumentos->tam; i++)
                (i == (vetDocumentos->tam - 1)) ? printf("%s", vetDocumentosGrafo[i]->chave) : printf("%s ", vetDocumentosGrafo[i]->chave);
            printf("\n");

            printf("pr:");
            for(int i = 0; i < vetDocumentos->tam; i++)
                (i == (vetDocumentos->tam - 1)) ? printf("%.16lf", vetDocumentosGrafo[i]->pr) : printf("%.16lf ", vetDocumentosGrafo[i]->pr);
            printf("\n");

            free(vetDocumentosGrafo);
            libera_vetor(vetDocumentos);
        }
        
        free(linha);
        free(copiaLinha);

        free(vetListas);
    }
}

// Função responsável por verificar se a lista de nomes de arquivos da terceira palavra contem o(s) elemento(s) que está contido simultâneamente nas listas da primeira e segunda palavra
// Ao final retornando se os elementos em comum persistem por todas as listas de todas as palavras (que não são stopwords)
static Vetor* rec_gvd(Vetor* igual, Lista** proxima, int posLista, int tamMaxVetLista){
    if(!igual->tam || posLista >= tamMaxVetLista) return igual;

    Vetor* vetDocumentos = (Vetor*) malloc(sizeof(Vetor));
    vetDocumentos->v = (char**) malloc((igual->tam)*sizeof(char*));
    vetDocumentos->tam = 0;

    int tamVetDocs = 0;

    for(int i = 0; i < igual->tam; i++) {
        for(Celula* temp2 = proxima[posLista]->prim; temp2; temp2 = temp2->prox){
            if(!strcmp(igual->v[i],temp2->chave)){
                vetDocumentos->v[vetDocumentos->tam++] = temp2->chave;
            }
        }
    }
    libera_vetor(igual);
    return rec_gvd(vetDocumentos, proxima, posLista+1, tamMaxVetLista);
}

Vetor* gera_vetor_documentos(Lista** vetListas, int tamVetListas) {
    Vetor* vetDocumentos = (Vetor*) malloc(sizeof(Vetor));
    vetDocumentos->v = (char**) malloc(TAM_INIC*sizeof(char*));
    vetDocumentos->tam = 0;

    int tamMaxVetDocs = TAM_INIC;
    
    if(tamVetListas <= 0) {
        printf("Vetor de listas com tamanho invalido - gera_vetor_documentos()\n");
        exit(1);
    }
    else if(tamVetListas == 1) {
        Celula* temp1 = vetListas[0]->prim;
        while(temp1) {
            vetDocumentos->v[vetDocumentos->tam++] = temp1->chave;
            
            if(vetDocumentos->tam >= tamMaxVetDocs) {
                vetDocumentos->v = (char**) realloc(vetDocumentos->v, 2*tamMaxVetDocs*sizeof(char*));
                tamMaxVetDocs *= 2;
            }
                        
            temp1 = temp1->prox;
        }
    }
    else {
        Celula* temp1 = vetListas[0]->prim;
        while(temp1) {
            Celula* temp2 = vetListas[1]->prim;
            while(temp2) {
                if(!strcmp(temp1->chave,temp2->chave)){
                    vetDocumentos->v[vetDocumentos->tam++] = temp1->chave;
                    if(vetDocumentos->tam >= tamMaxVetDocs) {
                        vetDocumentos->v = (char**) realloc(vetDocumentos->v, 2*tamMaxVetDocs*sizeof(char*));
                        tamMaxVetDocs *= 2;
                    }
                }
                temp2 = temp2->prox;
            }
            temp1 = temp1->prox;
        }
        vetDocumentos = rec_gvd(vetDocumentos, vetListas, 2, tamVetListas);
    }

    return vetDocumentos;
}

// Compara dois nos do grafo por page rank
// Caso o modulo da diferenca dos page ranks seja menor que delta, ordena por ordem alfabetica das chavez
static int compara(const void* p1, const void* p2) {
    double delta = 1e-20;

    Grafo* g1 = *((Grafo**) p1);
    Grafo* g2 = *((Grafo**) p2);

    if(fabs((g1->pr - g2->pr)) < delta)
        return strcmp(g1->chave, g2->chave);
    
    return g1->pr > g2->pr ? -1 : 1;
}

// Gera o vetor de paginas comuns a todos os termos da busca, e o organiza em ordem de page rank
Grafo** organiza_page_rank(Grafo** graf, Vetor* vetorIndex, Vetor* vetDocumento) {
    Grafo** grafoPageRank = (Grafo**)malloc((vetDocumento->tam)*sizeof(Grafo*));

    for(int i = 0; i < vetDocumento->tam; i++){
        int posGrafo = busca_binaria_string(vetorIndex->v, vetDocumento->v[i], 0, vetorIndex->tam -1);
        grafoPageRank[i] = graf[posGrafo];
    }

    qsort(grafoPageRank, vetDocumento->tam, sizeof(Grafo*), compara);

    return grafoPageRank;
}