/*
Class title: Data Structure
Lecturer: Prof. Dr. Rodrigo Elias Bianchi
Example adapted by: Charles Fernandes de Souza
Date: October 26, 2021
*/

#include<stdio.h>
#include <stdlib.h>
#define true 1;
#define false 0;

typedef struct adjacencia{
    int vertice; 
    int peso; 
    struct adjacencia *proximo; 
}Adjacencia;

typedef struct vertice{
    Adjacencia *noCabeca;  
}Vertice;

typedef struct grafo{
    int vertices; 
    int arestas; 
    Vertice *ponteiroAdjacencia; 
}Grafo;

Grafo *insereGrafo(int valorVertice){
    int index;
    Grafo *ponteiroGrafo = (Grafo*)malloc(sizeof(Grafo)); 
    ponteiroGrafo->vertices = valorVertice; 
    ponteiroGrafo->arestas = 0;  
    ponteiroGrafo->ponteiroAdjacencia = (Vertice*)malloc(valorVertice*sizeof(Vertice));
    for(index= 0;index < valorVertice; index++){
        ponteiroGrafo->ponteiroAdjacencia[index].noCabeca = NULL; 
    }
    return ponteiroGrafo;
}

Adjacencia *insereAdjacencia(int valorVertice,int peso){
    Adjacencia *ponteiroAdjacencia = (Adjacencia*)malloc(sizeof(Adjacencia));
    ponteiroAdjacencia->vertice = valorVertice;  
    ponteiroAdjacencia->peso = peso;  
    ponteiroAdjacencia->proximo = NULL;
    return ponteiroAdjacencia; 
}

int insereAresta(Grafo* valorGrafo, int valorIncial, int valorFinal,int peso){
    if(valorGrafo == NULL)
    {
        return false;
    }
    if(valorFinal < 0 || valorFinal >= valorGrafo->vertices){ 
        return false;
    }
    if(valorIncial < 0 || valorIncial >= valorGrafo->vertices){ 
        return false;
    }
    Adjacencia *nova = insereAdjacencia(valorFinal,peso);

    nova->proximo = valorGrafo->ponteiroAdjacencia[valorIncial].noCabeca;  
    valorGrafo->ponteiroAdjacencia[valorIncial].noCabeca = nova; 
    valorGrafo->arestas++; 
}

void imprimiGrafo(Grafo *ponteiroGrafo){
    if(ponteiroGrafo != NULL){
        int i;
        for(i = 0; i < ponteiroGrafo->vertices; i++){
            printf("Valor %d | ",i); 
            Adjacencia *adj = ponteiroGrafo->ponteiroAdjacencia[i].noCabeca;
            while(adj != NULL){
                printf("Valor %d | Peso %d | ",adj->vertice,adj->peso); 
                adj = adj->proximo; 
            }
            printf("\n");
        }
    }
    return false;
}

int main(){
    Grafo *ponteiroGrafo = insereGrafo(5);
    insereAresta(ponteiroGrafo,0,1,2);
    insereAresta(ponteiroGrafo,1,2,4);
    insereAresta(ponteiroGrafo,2,4,6);
    insereAresta(ponteiroGrafo,3,1,8);
    insereAresta(ponteiroGrafo,4,3,9);
    imprimiGrafo(ponteiroGrafo);
}