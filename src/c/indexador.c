#include "../h/indexador.h"

char* to_lower(char* str) {
    for(int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);

    return str;
}

char* append_diretorio(char* diretorio, char* sufixo){
    size_t necessario = snprintf(NULL, 0, "%s/%s", diretorio, sufixo);
    char* apnd = (char*) malloc(necessario+1);
    sprintf(apnd, "%s/%s", diretorio, sufixo);

    return apnd;
}

RBT* indexador(Vetor* vetIndex, Vetor* vetStopWords, char* path) {
    RBT* tab_sim = RBT_init();
    
    for(int i = 0; i < vetIndex->tam; i++){
        char* filePath = append_diretorio(path, vetIndex->v[i]);
        FILE* fileTemp = fopen(filePath, "r");

        while(1){
            char* linha = NULL;
            size_t size = 0;

            int n = getline(&linha, &size, fileTemp);
            if(n <= 0) {
                free(linha);
                break;
            }
            
            char* temp = strtok(linha, " \t\n");
            char* splits;
            if(temp) splits = temp;

            while(1) {
                if(!temp) break;
                //printf("%s\n", splits);

                if(busca_binaria_string(vetStopWords->v, to_lower(splits), 0, vetStopWords->tam - 1) < 0)
                    tab_sim = RBT_insere(tab_sim, splits, vetIndex->v[i]);

                temp = strtok(NULL, " \t\n");
                if(temp) splits = temp;
            }
            //free(splits);
            free(linha);
        }
        free(filePath);
        fclose(fileTemp);
    }

    return tab_sim;
}