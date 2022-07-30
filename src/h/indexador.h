#ifndef INDEXADOR_H
#define INDEXADOR_H

#include "./vetor.h"
#include "./tabela_simbolos.h"

char* append_diretorio(char* diretorio, char* sufixo);
RBT* indexador(Vetor* vetIndex, Vetor* vetStopWords, char* path);
char* to_lower(char* str);
// void 索引器();

#endif