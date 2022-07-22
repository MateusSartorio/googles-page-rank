#ifndef INDEXADOR_H
#define INDEXADOR_H

#include "./vetor.h"
#include "./tabela_simbolos.h"

char* append_diretorio(char* diretorio, char* sufixo);
RBT* indexador(Vetor* vetIndex, char* path);
// void 索引器();

#endif