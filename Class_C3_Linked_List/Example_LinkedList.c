/*
Class title: Data Structure
Lecturer: Prof. Dr. Rodrigo Elias Bianchi
Example adapted by: Charles Fernandes de Souza
Date: August 24, 2021
*/

#include <stdio.h>
#include <stdlib.h>

struct No {
    int informacao;
    struct No *proximo;
};

typedef struct No No;

void insere(No *ponteiro, int item){
    No *novoNo;
    novoNo = malloc(sizeof(No));
    novoNo->informacao = item;
    novoNo->proximo = ponteiro->proximo;
    ponteiro->proximo = novoNo;
}

void imprime(No *inicio) {
    No *ponteiro;
    ponteiro = inicio;
    while (ponteiro){
        printf("%d ", ponteiro->informacao);
        ponteiro = ponteiro->proximo;
    }
    printf("\n");
}

void imprimeRecursivo(No *ponteiro){
    if(ponteiro){
        printf("%d ", ponteiro->informacao);
        imprimeRecursivo(ponteiro->proximo);
    }
    printf("\n");
}

No *busca(No *inicio, int item){
    No *ponteiro = inicio;
    while (ponteiro && ponteiro->informacao != item){
        ponteiro = ponteiro->proximo;
    }
    return ponteiro;
}

No *buscaRecursivo(No *ponteiro, int item){
    if (!ponteiro || ponteiro->informacao == item) {
        return ponteiro;
    }
    return buscaRecursivo(ponteiro->proximo, item);
}

void remove(No *ponteiro){
    No *ponteiroAcesso;
    ponteiroAcesso = ponteiro->proximo;
    ponteiro->proximo = ponteiroAcesso->proximo;
    free(ponteiroAcesso);
}

int main() {
    struct No {
        int informacao;
        struct No *proximo;
    };

    typedef struct No No;

    No *inicio;
    inicio = malloc(sizeof(No));
    inicio->proximo = NULL;

    insere(inicio, 3);
    insere(inicio, 8);
    insere(inicio, 11);

    imprime(inicio);

    remove(inicio);

    imprimeRecursivo(inicio);

    printf("\n");
    system("pause");
    return 0;
}
