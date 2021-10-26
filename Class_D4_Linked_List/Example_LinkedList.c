/*
Class title: Data Structure
Lecturer: Prof. Dr. Rodrigo Elias Bianchi
Example adapted by: Charles Fernandes de Souza
Date: August 31, 2021
*/

#include <stdio.h>
#include <stdlib.h>

struct NoDuplo {
    int informacao;
    struct NoDuplo *anterior;
    struct NoDuplo *proximo;
};
typedef struct NoDuplo NoD;

void insere(NoD *ponteiro, int item) {
    NoD *novoNo;
    novoNo = malloc(sizeof(NoD));
    novoNo->informacao = item;
    novoNo->proximo = ponteiro->proximo;
    novoNo->anterior = ponteiro;
    if (ponteiro->proximo) ponteiro->proximo->anterior = novoNo;
    ponteiro->proximo = novoNo;
}


void imprime(NoD *inicio) {
    NoD *ponteiro;
    ponteiro = inicio;
    while (ponteiro){
        printf("%d ", ponteiro->informacao);
        ponteiro = ponteiro->proximo;
    }
    printf("\n");
}

void imprimeRecursivo(NoD *ponteiro){
    if(ponteiro){
        printf("%d ", ponteiro->informacao);
        imprimeRecursivo(ponteiro->proximo);
    }
    printf("\n");
}

No *busca(NoD *inicio, int item) {
    NoD *ponteiro = inicio;
    while (ponteiro && ponteiro->informacao != item)
        ponteiro = ponteiro->proximo;
    return ponteiro;
}

No *buscaRecursivo(NoD *ponteiro, int item){
    if (!ponteiro || ponteiro->informacao == item) {
        return ponteiro;
    }
    return buscaRecursivo(ponteiro->proximo, item);
}

void remove(NoD *ponteiroAcesso) {
    NoD *ponteiro = ponteiroAcesso->anterior;
    ponteiro->prox = ponteiroAcesso->proximo;
    if (ponteiroAcesso->proximo) ponteiroAcesso->proximo->anterior = ponteiro;
    free(ponteiroAcesso);
}


int main() {

    struct NoDuplo {
        int informacao;
        struct NoDuplo *anterior;
        struct NoDuplo *proximo;
    };
    typedef struct NoDuplo NoD;;

    NoD *inicio;
    inicio = malloc(sizeof(NoD));
    inicio->proximo = NULL;
    inicio->anterior = NULL;

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