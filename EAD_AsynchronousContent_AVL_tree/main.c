#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

int main(){
    ArvAVL* avl;
    int res,i;
    int N = 10, dados[10] = {1,2,3,10,4,5,9,7,8,6}; //busca a chave 10

    avl = cria_ArvAVL(); //chamada da função para criação da árvore

    for(i=0;i<N;i++){
        printf("========================\n");
        printf("Inserindo: %d\n",dados[i]);
        res = insere_ArvAVL(avl,dados[i]); //chamada da função para insersão 
        printf("\n\n");
    }

    printf("\nAVL tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    remove_ArvAVL(avl,6); //remoção de nó passando chave 6
    printf("\nAVL tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    remove_ArvAVL(avl,7); //remoção de nó passando chave 7
    printf("\nAVL tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    remove_ArvAVL(avl,4); //remoção de nó passando chave 4
    printf("\nAVL tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    libera_ArvAVL(avl);

    getchar();
    return 0;
}
