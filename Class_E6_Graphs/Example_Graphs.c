/*
Class title: Data Structure
Lecturer: Prof. Dr. Rodrigo Elias Bianchi
Example adapted by: Charles Fernandes de Souza
Date: October 26, 2021
*/

#include<stdio.h>
#include <stdlib.h>

typedef struct No {
    int v;
    struct No *prox;
} No;

typedef struct {
    No **adjacencia;
    int n;
} Grafo;

void inicia_grafo(Grafo *g, int n);

void destroi_grafo(Grafo g);

void insere_aresta(Grafo g, int u, int v);

void remove_aresta(Grafo g, int u, int v);

int tem_aresta(Grafo g, int u, int v);

void imprime_arestas(Grafo g);

void inicia_grafo(Grafo *g, int n) {
    int i;
    g->n = n;
    g->adjacencia = malloc(n * sizeof(No *));
    for (i = 0; i < n; i++)
        g->adjacencia[i] = NULL;
}

void libera_lista(No *lista) {
    if (lista != NULL) {
        libera_lista(lista->prox);
        free(lista);
    }
}

void destroi_grafo(Grafo g) {
    int i;
    for (i = 0; i < g.n; i++)
        libera_lista(g.adjacencia[i]);
    free(g.adjacencia);
}

No* insere_na_lista(No *lista, int v) {
    No *novo = malloc(sizeof(No));
    novo->v = v;
    novo->prox = lista;
    return novo;
}

void insere_aresta(Grafo g, int u, int v) {
    g.adjacencia[v] = insere_na_lista(g.adjacencia[v], u);
    g.adjacencia[u] = insere_na_lista(g.adjacencia[u], v);
}

No * remove_da_lista(No *lista, int v) {
    No *proximo;
    if (lista == NULL)
        return NULL;
    else if (lista->v == v) {
        proximo = lista->prox;
        free(lista);
        return proximo;
    } else {
        lista->prox = remove_da_lista(lista->prox, v);
        return lista;
    }
}

void remove_aresta(Grafo g, int u, int v) {
    g.adjacencia[u] = remove_da_lista(g.adjacencia[u], v);
    g.adjacencia[v] = remove_da_lista(g.adjacencia[v], u);
}

int tem_aresta(Grafo g, int u, int v) {
    No *t;
    for (t = g.adjacencia[u]; t != NULL; t = t->prox) {
        if (t->v == v)
            return 1;
        }
    return 0;
}

void imprime_arestas(Grafo g) {
    int u;
    No *t;
    for (u = 0; u < g.n; u++) {
        for (t = g.adjacencia[u]; t != NULL; t = t->prox)
            printf("{%d,%d}\n", u, t->v);
    }
}

int main(){
    Grafo *ponteiroGrafo = inicia_grafo;
    inicia_grafo(ponteiroGrafo,0);
    inicia_grafo(ponteiroGrafo,1);
    inicia_grafo(ponteiroGrafo,4);
    inicia_grafo(ponteiroGrafo,9);
    inicia_grafo(ponteiroGrafo,7);
    inicia_grafo(ponteiroGrafo,2);
}
