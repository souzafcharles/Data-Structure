/*
Class title: Data Structure
Lecturer: Prof. Dr. Rodrigo Elias Bianchi
Wagner Gaspar's Example adapted by: Charles Fernandes de Souza
Date: September 28, 2021
*/
#include<stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *direita, *esquerda;
}NoArv;

void inserirABB(NoArv **raiz, int numero){
    NoArv *auxiliar = *raiz;
    while(auxiliar){
        if(numero < auxiliar->valor)
            raiz = &auxiliar->esquerda;
        else
            raiz = &auxiliar->direita;
        auxiliar = *raiz;
    }
    auxiliar = malloc(sizeof(NoArv));
    auxiliar->valor = numero;
    auxiliar->esquerda = NULL;
    auxiliar->direita = NULL;
    *raiz = auxiliar;
}

NoArv* buscarABB(NoArv *raiz, int numero){
    while(raiz){
        if(numero < raiz->valor)
            raiz = raiz->esquerda;
        else if(numero > raiz->valor)
            raiz = raiz->direita;
        else
            return raiz;
    }
    return NULL;
}

int altura(NoArv *raiz){
    if(raiz == NULL){
        return -1;
    }
    else{
        int auxiliarEsquerda = altura(raiz->esquerda);
        int auxiliarDireita = altura(raiz->direita);
        if(auxiliarEsquerda > auxiliarDireita)
            return auxiliarEsquerda + 1;
        else
            return auxiliarDireita + 1;
    }
}

int quantidade_nos(NoArv *raiz){
    if(raiz == NULL)
        return 0;
    else
        return 1 + quantidade_nos(raiz->esquerda) + quantidade_nos(raiz->direita);
}

int quantidade_folhas(NoArv *raiz){
    if(raiz == NULL)
        return 0;
    else if(raiz->esquerda == NULL && raiz->direita == NULL)
        return 1;
    else
        return quantidade_folhas(raiz->esquerda) + quantidade_folhas(raiz->direita);
}

NoArv* removerABB(NoArv *raiz, int chave) {
    if(raiz == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else { 
        if(raiz->valor == chave) {
            if(raiz->esquerda == NULL && raiz->direita == NULL) {
                free(raiz);
                printf("Elemento folha removido: %d !\n", chave);
                return NULL;
            }
            else{
                if(raiz->esquerda != NULL && raiz->direita != NULL){
                    NoArv *auxiliar = raiz->esquerda;
                    while(auxiliar->direita != NULL)
                        auxiliar = auxiliar->direita;
                    raiz->valor = auxiliar->valor;
                    auxiliar->valor = chave;
                    printf("Elemento trocado: %d !\n", chave);
                    raiz->esquerda = removerABB(raiz->esquerda, chave);
                    return raiz;
                }
                else{
                    // remover nós que possuem apenas 1 filho
                    NoArv *auxiliar;
                    if(raiz->esquerda != NULL)
                        auxiliar = raiz->esquerda;
                    else
                        auxiliar = raiz->direita;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d !\n", chave);
                    return auxiliar;
                }
            }
        } else {
            if(chave < raiz->valor)
                raiz->esquerda = removerABB(raiz->esquerda, chave);
            else
                raiz->direita = removerABB(raiz->direita, chave);
            return raiz;
        }
    }
}

void imprimirABB(NoArv *raiz){
    if(raiz){
        imprimirABB(raiz->esquerda);
        printf("%d ", raiz->valor);
        imprimirABB(raiz->direita);
    }
}

int main(){
    NoArv *busca, *raiz = NULL;
    int opcao, valor;

    do{
        printf("\n\n--------------------------------- MENU ----------------------------------\n\n");
        printf ("Digite o numero [1] para inserir valores da Arvore Binaria de Busca\n");
        printf ("Digite o numero [2] para imprimir valores da Arvore Binaria de Busca\n");
        printf ("Digite o numero [3] para buscar um valor da Arvore Binaria de Busca\n");
        printf ("Digite o numero [4] para saber a altura da Arvore Binaria de Busca\n");
        printf ("Digite o numero [5] para saber o tamanho da Arvore Binaria de Busca\n");
        printf ("Digite o numero [6] para a quantidade de folhas da Arvore Binaria de Busca\n");
        printf ("Digite o numero [7] para remover um valor da Arvore Binaria de Busca\n");
        printf ("Digite o numero [0] para encerrar\n");
        printf("\nEscolha uma opcao:> ");
        scanf("%d", &opcao);

        switch(opcao){
        case 0:
            printf("\nFim! Volte Sempre!\n");
            printf("\n");
            break;
        case 1:
            printf("\n\tDigite um valor: ");
            scanf("%d", &valor);
            inserirABB(&raiz, valor);
            break;
        case 2:
            printf("\n\tArvore Binaria de Busca:\n\t");
            imprimirABB(raiz);
            printf("\n");
            break;
        case 3:
            printf("\n\tDigite o valor a ser buscado: ");
            scanf("%d", &valor);
            busca = buscarABB(raiz, valor);
            if(busca)
                printf("\n\tValor encontrado: %d\n", busca->valor);
            else
                printf("\n\tValor nao encontrado!\n");
            break;
        case 4:
            printf("\n\tAltura da arvore: %d\n\n", altura(raiz));
            break;
        case 5:
            printf("\n\tQuantidade de nos: %d\n", quantidade_nos(raiz));
            break;
        case 6:
            printf("\n\tQuantidade folhas: %d\n", quantidade_folhas(raiz));
            break;
        case 7:
            printf("\t");
            imprimirABB(raiz);
            printf("\n\tDigite o valor a ser removido: ");
            scanf("%d", &valor);
            raiz = removerABB(raiz, valor);
            break;
        default:
            if(opcao != 0)
                printf("\n\tOpcao invalida!!!\n");
        }
    }while(opcao != 0);
    return 0;
}