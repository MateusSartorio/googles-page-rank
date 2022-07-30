#ifndef BUSCA_H
#define BUSCA_H

#include "vetor.h"
#include "grafo.h"
#include "indexador.h"
#include "lista.h"

// Função responsável pela leitura da busca (na entrada padrão) e o processamento da mesma
void processa_consultas(RBT* tab_sim, Vetor* vetorStopwords, Vetor* vetIndex, Grafo** grafo, FILE* fp);

// Função que gera um vetor que gera um vetor que contém todos os arquivos que contém todas as palavras de busca
Vetor* gera_vetor_documentos(Lista** vetListas, int tamVetListas);

// Função que organiza as chaves em ordem de page rank decresente
Grafo** organiza_page_rank(Grafo** graf, Vetor* vetorIndex, Vetor* vetDocumento);

#endif