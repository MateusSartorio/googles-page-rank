#ifndef INDEXADOR_H
#define INDEXADOR_H

#include "./vetor.h"
#include "./tabela_simbolos.h"

// Função auxiliar para concatenar um diretório a outro
char* append_diretorio(char* diretorio, char* sufixo);

// Função responsável pela criação da tabela de símbolos que usaremos para a busca
// Cada nó da arvore terá a chave e o valor será uma lista de todos os nomes dos arquivos que contém a "chave" (palavra)
RBT* indexador(Vetor* vetIndex, Vetor* vetStopWords, char* path);

// Função que converte uma string para conter somente caracteres minúsculos
// Escolhido arbitrariamente para padronização, poderia ser to_upper
char* to_lower(char* str);

#endif