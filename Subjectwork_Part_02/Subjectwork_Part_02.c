#include <stdio.h>
#include <stdlib.h>
#define NUM_PESSOAS 7

//------------------------------------- ÁRVORE AVL -------------------------------------
typedef struct pessoa {
int id;
char CPF[12];
char nome[200];
char sobrenome[200];
} pessoa;

typedef struct no{
    pessoa Pessoa;
    struct no *esquerdo, *direito;
    int altura;
}No;

//Função para liberar o nó raiz da árvore
void destruir(No * raiz) {
	free(raiz);
}

//int *ID = 0;
pessoa ler_pessoa(){
    pessoa p;
    printf("\n----------- CADASTRO DE PESSOA -----------");
    fflush(stdin);
    printf("\n\nDigite o CPF da pessoa: ");
    fgets(p.CPF, 11, stdin);
    fflush(stdin);
    printf("\nDigite o nome da pessoa: ");
    fgets(p.nome, 199, stdin);
    fflush(stdin);
    printf("\nDigite o sobrenome da pessoa: ");
    fgets(p.sobrenome, 199, stdin);
    fflush(stdin);
    printf("\nDigite o id: ");
    scanf("%d", &p.id);
    //p.id = ID++;
    return p;
}

void imprimir_pessoa(pessoa p){
    printf("\n---------------------DADOS DA PESSOA -----------------------\n");
    printf("\n ID...........................: %d\n", p.id);
    printf("\n Nome.........................: %s", p.nome);
    printf("\n Sobrenome....................: %s", p.sobrenome);
    printf("\n CPF..........................: %s", p.CPF);
    printf("\n------------------------------------------------------------\n");
}

//Função que cria um novo nó pessoa a ser inserido no nóRetorna: o endereço do nó criado
No* novoNo(pessoa p){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->Pessoa = p;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
    }
    else
        printf("\nERRO ao alocar nó em novoNo!\n");
    return novo;
}

// Retorna o maior dentre dois valores a, b -> altura de dois nós da árvore
int maior(int a, int b){
    return (a > b)? a: b;
}

//  Retorna a altura de um nó ou -1 caso ele seja null
int alturaDoNo(No *no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

//   Calcula e retorna o fator de balanceamento de um nó
int fatorDeBalanceamento(No *no){
    if(no)
        return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
    else
        return 0;
}

// --------- ROTAÇÕES ---------------------------

// Função para a rotação à esquerda
No* rotacaoEsquerda(No *r){
    No *y, *f;

    y = r->direito;
    f = y->esquerdo;

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

// Função para a rotação à direita
No* rotacaoDireita(No *r){
    No *y, *f;

    y = r->esquerdo;
    f = y->direito;

    y->direito = r;
    r->esquerdo = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

No* rotacaoEsquerdaDireita(No *r){
    r->esquerdo = rotacaoEsquerda(r->esquerdo);
    return rotacaoDireita(r);
}

No* rotacaoDireitaEsquerda(No *r){
    r->direito = rotacaoDireita(r->direito);
    return rotacaoEsquerda(r);
}

//Função para realizar o balanceamento da árvore após uma inserção ou remoção
//Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
No* balancear(No *raiz){
    int fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotação à direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotação dupla à esquerda
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotação dupla à direita
    else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}

//Insere um novo nó na árvore raiz -> raiz da árvore no pessoa a ser inserido
//Retorno: endereço do novo nó ou nova raiz após o balanceamento
No* inserir(No *raiz, pessoa p){
    if(raiz == NULL) // árvore vazia
        return novoNo(p);
    else{ // inserção será à esquerda ou à direita
        if(p.id < raiz->Pessoa.id)
            raiz->esquerdo = inserir(raiz->esquerdo, p);
        else if(p.id > raiz->Pessoa.id)
            raiz->direito = inserir(raiz->direito, p);
        else
            printf("\nInsercao nao realizada!\nO elemento %d ja existe!\n", p);
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    // verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

// Função para percorrer os nós para impressão
void imprimir(No *raiz){
    int i;
    if(raiz){
        imprimir(raiz->esquerdo);
        imprimir_pessoa(raiz->Pessoa);
        imprimir(raiz->direito);
    }
}
// Função para remover um nó da Árvore binária balanceada.
// Pode ser necessário rebalancear a árvore e a raiz pode ser alterada por isso precisa retornar a raiz
No* remover(No *raiz, int chave) {
    if(raiz == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else { // procura o nó a remover
        if(raiz->Pessoa.id == chave) {
            // remove nós folhas (nós sem filhos)
            if(raiz->esquerdo == NULL && raiz->direito == NULL) {
                free(raiz);
                printf("Elemento folha removido: %d !\n", chave);
                return NULL;
            }
            else{
                // remover nós que possuem 2 filhos
                if(raiz->esquerdo != NULL && raiz->direito != NULL){
                    pessoa p;
                    No *aux = raiz->esquerdo;
                    while(aux->direito != NULL)
                        aux = aux->direito;
                    p = raiz->Pessoa;
                    raiz->Pessoa = aux->Pessoa;
                    aux->Pessoa = p;
                    raiz->esquerdo = remover(raiz->esquerdo, chave);
                    return raiz;
                }
                else{
                    // remover nós que possuem apenas 1 filho
                    No *aux;
                    if(raiz->esquerdo != NULL)
                        aux = raiz->esquerdo;
                    else
                        aux = raiz->direito;
                    free(raiz);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->Pessoa.id)
                raiz->esquerdo = remover(raiz->esquerdo, chave);
            else
                raiz->direito = remover(raiz->direito, chave);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

        // verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);

        return raiz;
    }
}

//--------------------------------------- GRÁFOS ---------------------------------------
// Dados da matriz de adjacência como uma variável global
int M[NUM_PESSOAS][NUM_PESSOAS];

// Função que inicializa a matriz de adjacência. 
// De incio, não há relações de amizade, com isso todas as posições da matriz são zeradas.
void inicializar_rede() {
    for (int i = 0; i < NUM_PESSOAS; i++) {
        for (int j = 0; j < NUM_PESSOAS; j++) {
        M[i][j] = 0;
        }
    }
}

//Função para marcar duas pessoas de forma simétrica como amigas na matriz de adjacência.
void adicionar_amizade(int i, int j) {
    M[i][j] = 1;
    M[j][i] = 1;
}

// Função que retorna um número aleatório de tipo ponto flutuante entre 0 e 1...
//gerado pela função rand() é definido pela constante RAND_MAX, que por sua vez é definida na biblioteca stdlib.h
float random_float() {
    return (float)rand() / (float)RAND_MAX;
}

// Função para preencher o grapo e  criar uma rede social a partir dos valores dos ID das pessoas. 
// Assim, para cada par de pessoas (i,j), será  gerado um número aleatório de tipo ponto flutuante r entre 0 e 1 (ex: 0.2345). 
// Caso r seja menor que P, então deve-se criar uma amizade entre as pessoas ni e nj. 
// Exemplo: se P=0.8, para o par de pessoas n0 e n1, se o número r gerado for 0.5412, então você deve criar uma amizade entre essas pessoas. 
// Exemplo consultado em: https://homepages.dcc.ufmg.br/~cunha/teaching/20152/aeds1/pratica8.html
void preencheRedeSocial(No *raiz, int P) {
    float r;
    inicializar_rede();
    for (int i = 0; i < NUM_PESSOAS; i++) {
        for (int j = i + 1; j < NUM_PESSOAS; j++) {
        r = random_float();
        if(r < P)
            adicionar_amizade(i, j);
        }
    }
}

//Função que imprimi todos os amigos de uma pessoa.
No* tem_amizade(No *raiz, int v) {
    int tem_amizade = 0;
    printf("\n Quantidade de amizades: ");
    for (int j = 0; j < NUM_PESSOAS; j++) {
        if (M[v][j] == 1) {
            raiz = tem_amizade++;
            printf("%d ",j);
        }
    }
  return raiz;
}

//Função para retornar o número imprimir os amigos dos amigos.
No* numAmigosEmComum(No *raiz, int v, int u) {
    int amigo_comum = 0;
    printf("\nAmigos dos amigos (em Comum): ");
    for (int j = 0; j < NUM_PESSOAS; j++) {
        if (M[v][j] == 1 && M[u][j] == 1) {
            raiz = amigo_comum++;
            printf("%d ",j);
        }
    }
    return raiz;
}

int main(){
    int opcao, valor, outro, quantidade;
    No *raiz = NULL;

    do{
        printf("\n\n--------------------------------- MENU ----------------------------------\n\n");
        printf ("Digite o numero [1] para inserir valores na AVL\n");
        printf ("Digite o numero [2] para imprimir valores da AVL\n");
        printf ("Digite o numero [3] para remover valor da AVL\n");
        printf ("Digite o numero [4] para adcionar pessoa na rede social\n");
        printf ("Digite o numero [5] para imprimir numero de amigos\n");
        printf ("Digite o numero [6] para imprimir numero de amigo de amigos\n");
        printf ("Digite o numero [0] para encerrar\n");
        printf("\nEscolha uma opcao:> ");
        scanf("%d", &opcao);

        switch(opcao){
        case 0:
            printf("\nFim! Volte Sempre!\n");
            printf("\n");
            break;
        case 1:
            raiz = inserir(raiz, ler_pessoa());
            break;
        case 2:
            imprimir(raiz);
            break;
        case 3:
            printf("\nDigite o id  a ser removido: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        case 4:
            printf("\nDigite o id a ser inserido na Rede Social: ");
            scanf("%d", &valor);
            preencheRedeSocial(raiz, valor);
            break;
         case 5:
            printf("\nDigite o id da pessoa: ");
            scanf("%d", &valor);
            quantidade = tem_amizade(raiz, valor);
            printf("\nNumero de amigos: %d\n", quantidade);
            break;
         case 6:
            printf("\nDigite o id da pessoa 01: ");
            scanf("%d", &valor);
            printf("\nDigite o id da pessoa 02: ");
            scanf("%d", &outro);
            quantidade = numAmigosEmComum(raiz, valor, outro);
            printf("\nNumero de amigos em comum: %d\n", quantidade);
            break;
        default:
            printf("\nOpcao invalida!!!\n");
            break;
        }

    }while(opcao != 0);

    return 0;
}