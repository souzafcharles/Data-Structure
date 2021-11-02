#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h" //inclui os Protótipos

struct NO{
    int info; // Elementos dos nós 
    int altura; //Altura da sub-arvore para utilizar em uma função para calcular a altura necessaria para calcular o balanceamento
    struct NO *esq; // Direção indicada a esqueda 
    struct NO *dir; // Direção indicada a esqueda 
};

// Função que cria a áreve AVL
ArvAVL* cria_ArvAVL(){ 
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL)); // cria um ponteiro para árvore, fazendo alocação para estrura da áravore
    if(raiz != NULL) // se a condicao for satisfeita
        *raiz = NULL; // nó especial apontando para null
    return raiz; // retorno o conteudo para quem chamar a funcao no prgrama principal
}

// Função para "Destruir" a árvore
 void libera_NO(struct NO* no){
    if(no == NULL) // verifica se o nó não é nulo
        return; // se for retorna nada 
    libera_NO(no->esq); //caso não, é chama a funcao que ira percorrer recursivamente os nós da esquerda 
    libera_NO(no->dir); //caso não, é chama a funcao que ira percorrer recursivamente os nós da direita 
    free(no); // libera o nó quando a função recursiva retornar
    no = NULL; // eveitar qualquer erro de verificação
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL) // verifica se a raiz não é nula
        return; //se for retorna nada 
    libera_NO(*raiz);// caso não, é chama a funcao que ira percorrer e libera cada nó
    free(raiz);//libera a raiz, liberando a memória alocada quando foi chamada a funcao que cria a árvore
}

//Função Auxiliar que calcula da altura de um nó
int altura_NO(struct NO* no){ //recebe como parâmetro  nó
    if(no == NULL)
        return -1; // se não existe o nó
    else //então
    return no->altura; // retorna o dado da altura 
}

// Calcula o fator de balanceamento de um nó sabendo sua diferença
int fatorBalanceamento_NO(struct NO* no){ 
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
    //                direfença do lado esquerdo com o direito que depois será utilizado para saber se 
    //                a rotação será para lado direito se a diferença for negativa e postiva para esquerda
}

//Função para calcular o maior valor da árvore
int maior(int x, int y){ //recebendo dois parametros
    if(x > y) //verifica se valor x é maior
        return x; //se for retorna x
    else //senao
        return y; //retorna y como maior valor
}

// Função para esvaziar a raiz
int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL) // verifica se árvore foi criada
        return 1; // caso sim retorna 1
    if(*raiz == NULL) // verifica se o nó raiz aponta para nulo
        return 1; // caso sim retorna 1
    return 0; //caso nao exista e retorna 0
}

// Funcao que contabiliza a quantidade de nós da árvore
int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL) // verifica se árvore foi criada
        return 0; // caso sim nao exista e retorna 0
    if (*raiz == NULL)// verifica se o nó raiz aponta para nulo
        return 0;// caso sim nao exists e retorna 0
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq)); // camada recursiva da funcao para sub-arvore da esquerda
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir)); // camada recursiva da funcao para sub-arvore da direita
    return(alt_esq + alt_dir + 1); //soma o tal de nós da esquerda com a da direita mais o nó pai.
}

//Funcao que rertorna a altura da arvore percorrendo todos os nós
int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL) // verifica se árvore foi criada
        return 0; // caso sim nao exista e retorna 0
    if (*raiz == NULL) // verifica se o nó raiz aponta para nulo
        return 0; // caso sim nao exists e retorna 0
    int alt_esq = altura_ArvAVL(&((*raiz)->esq)); // camada recursiva da funcao para sub-arvore da esquerda
    int alt_dir = altura_ArvAVL(&((*raiz)->dir)); // camada recursiva da funcao para sub-arvore da direita
    if (alt_esq > alt_dir) // define qual altura é maior, se é a sub-arvore da esquerda ou da direita
        return (alt_esq + 1); // se for a esqueda a maior sub-árvore então retorna a altura + o pai
    else
        return(alt_dir + 1); // se for a direita a maior sub-árvore então retorna a altura + o pai
}
// Função para percorrer a árvore AVL
void preOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL) // verifica se a raiz for nula
        return; // caso sim, nao é retornado nada
    if(*raiz != NULL){ // se a raiz for diferente de nulo
        printf("%d\n",(*raiz)->info); // é impresso a informacao da raiz
        printf("No %d: %d\n",(*raiz)->info,fatorBalanceamento_NO(*raiz)); // percorre a raiz imprindo de forma banlaceada os nós
        printf("No %d: %d\n",(*raiz)->info,altura_NO(*raiz)); // coforme altura dos nós
        preOrdem_ArvAVL(&((*raiz)->esq)); // recursivamente percorre os nós da esquerda
        preOrdem_ArvAVL(&((*raiz)->dir)); // recursivamente percorre os nós da direita
    }
}
// Função para percorrer a árvore AVL
void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL) // verifica se a raiz for nula
        return; // caso sim, nao é retornado nada
    if(*raiz != NULL){ // se a raiz for diferente de nulo
        emOrdem_ArvAVL(&((*raiz)->esq)); //percorre a raiz de forma recursiva em direção aos nós da esquerda
        printf("%d\n",(*raiz)->info); // recursivamente percorre os nós da esquerda imprindo as informações
        printf("No %d: H(%d) fb(%d)\n",(*raiz)->info,altura_NO(*raiz),fatorBalanceamento_NO(*raiz)); // tratamento do nós pela altura e balanceamento
        emOrdem_ArvAVL(&((*raiz)->dir)); // recursivamente percorre os nós da direita
    }
}
// Função para percorrer a árvore AVL
void posOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL) // verifica se a raiz for nula
        return; // caso sim, nao é retornado nada
    if(*raiz != NULL){ // se a raiz for diferente de nulo
        posOrdem_ArvAVL(&((*raiz)->esq)); // recursivamente percorre os nós da esquerda
        posOrdem_ArvAVL(&((*raiz)->dir)); // recursivamente percorre os nós da esquerda
        printf("%d\n",(*raiz)->info); // impreme a informação do nó raiz pai
    }
}
// Funcao de busca. 
//Para cada nó pai, todos valores da sub-árvores da esquerda, são menores do que o nó pai.
//Para cada nó pai, todos valores da sub-árvores da direita, são maiores do que o nó pai.
int consulta_ArvAVL(ArvAVL *raiz, int valor){
    if(raiz == NULL) // verifica se a raiz for nula
        return 0; // caso sim, rerorna 0
    struct NO* atual = *raiz; // nó atual recebe nó raiz
    while(atual != NULL){ //enquanto o nó atual for diferente de nulo
        if(valor == atual->info){ //se o valor a ser buscado for igual a informação do nó atual
            return 1; // retorna 1, indicando não existir o valor
        }
        if(valor > atual->info) // se o valor a ser buscado for maior que a informação do nó atual
            atual = atual->dir; // nó atual percorre a sub-árvore da direita
        else
            atual = atual->esq;// senão o nó atual percorre a sub-árvore da esquerda
    }
    return 0; // retornar 0 indicando encontrar o valor
}

//=================================
void RotacaoLL(ArvAVL *A){// Rotação simples girando a  direita em que A é a raiz que foi desbalanceada 
    printf("RotacaoLL\n");
    struct NO *B; // cria o no auxiliar 
    B = (*A)->esq; // cria o auxiliar B que recebe o filho da esquerda 
    (*A)->esq = B->dir; // filho a esquerda recebe o filho a direita 
    B->dir = *A; //filho da direita recebe a raiz A
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1; //1. calculo das novas alturas da arvore 
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;                 //2. onde a maior altura passa a ser entre o filho da esquerda
    *A = B;                                 //3. e da direita somado + 1
} //4. altura do no auxlilar B passa a ser a esquerda. //5. raiz recebe quem está no nó  

void RotacaoRR(ArvAVL *A){//Rotação simples a griando a esquerda em que A é a raiz que foi desbalanceada 
    printf("RotacaoRR\n");
    struct NO *B; // cria o no auxiliar 
    B = (*A)->dir; // cria o auxiliar B que recebe o filho da direita
    (*A)->dir = B->esq; // filho a direita recebe o filho a esquerda
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1; //1. calculo das novas alturas da arvore
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1; //2. onde a maior altura passa a ser entre o filho da direita
    (*A) = B;                                        //e da esqueda somado + 1
    //4. altura do no auxlilar B passa a ser a direita. //5. raiz recebe quem está no nó 
}

void RotacaoLR(ArvAVL *A){//Função para implementar com duas rotações simples
    RotacaoRR(&(*A)->esq); //aplico uma rotação no filho da esquerda
    RotacaoLL(A); // aplico uma rotação na raiz
}

void RotacaoRL(ArvAVL *A){//Função para implementar com duas rotações simple
    RotacaoLL(&(*A)->dir);//aplico uma rotação no filho da direita
    RotacaoRR(A); //aplico uma rotação na raiz
}

int insere_ArvAVL(ArvAVL *raiz, int valor){
    int res; //pegar as respostas das chamadas das funções
    if(*raiz == NULL){ //primeiro caso armove vazia ou já cheguei no folha
        struct NO *novo; // nvoo nó auxliar
        novo = (struct NO*)malloc(sizeof(struct NO)); //aloca memoria para novo nó
        if(novo == NULL) // verifica se deu certo a alocação
            return 0;

        novo->info = valor; //coloca o valor a ser inserido no novo nó
        novo->altura = 0; // coloca altura do nó para 0 pois ele vai ser a folha ou a raiz
        novo->esq = NULL; // filhos como nulos 
        novo->dir = NULL; // filhos como nulos 
        *raiz = novo; // raiz pode ser uma folha 
        return 1; // retorna 1 confirmando a inserção 
    }

    struct NO *atual = *raiz; // cria o no atual para receber o conteudo da raiz
    if(valor < atual->info){ // verificação se é menor
        if((res = insere_ArvAVL(&(atual->esq), valor)) == 1){ // caso sim insersção na arvore do lado esquerdo 
            if(fatorBalanceamento_NO(atual) >= 2){ // balancemento caso a inserção ocorrer e for igual a 2
                if(valor < (*raiz)->esq->info ){ //verfica o tipo de rotação necessaria para o balanceamento
                    RotacaoLL(raiz); // chama rotação LL
                }else{
                    RotacaoLR(raiz); // ou chama rotação LR
                }
            }
        }
    }else{ //se não foi  menor
        if(valor > atual->info){ //então é maior
            if((res = insere_ArvAVL(&(atual->dir), valor)) == 1){ // caso sim insersção na arvore do lado direito 
                if(fatorBalanceamento_NO(atual) >= 2){ // balancemento caso a inserção ocorrer e for igual a 2
                    if((*raiz)->dir->info < valor){ //verfica o tipo de rotação necessaria para o balanceamento
                        RotacaoRR(raiz); // chama rotação LL
                    }else{
                        RotacaoRL(raiz); // ou chama rotação LR
                    }
                }
            }
        }else{ // se não é menor e nem maior, então são iguais não sendo inserido na arvore
            printf("Valor duplicado!!\n");
            return 0;
        }
    }
    // recalculo da altura do nó atual com valores da altura do no da esqueda e direita acrescentado de 1
    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

//função responsável por fazer a remoção de um nó com dois filhos
struct NO* procuraMenor(struct NO* atual){ //procura pelo nó mais a esquerda
    struct NO *no1 = atual; //nó 1 recebe o no atual
    struct NO *no2 = atual->esq; // nó 2 receven o atual e da esquerda
    while(no2 != NULL){ //enquanto nó 2 for diferente de nulo
        no1 = no2;      //é percorrido o trajeto 
        no2 = no2->esq; // mais a esquerda, sempre armazenando o último nó até que nó 2 for igual a nulo
    }
    return no1; //assim nó 1 é o último valor mais a esquerda da sub-árvore da direita
}

//função responsável pela busca do nó a ser removido
int remove_ArvAVL(ArvAVL *raiz, int valor){
	if(*raiz == NULL){// Se o conteúdo do nó da raiz e nulo, então valor não existe
	    printf("valor não existe!!\n");
	    return 0;
	}

    int res; // funcão recursiva
	if(valor < (*raiz)->info){ // Se o valor for menor que a inforção guardada na raiz
	    if((res = remove_ArvAVL(&(*raiz)->esq,valor)) == 1){ //Será chamada a funcao remove para sub-árvore da esquerda
            if(fatorBalanceamento_NO(*raiz) >= 2){//caso a condição seja suficiente, será calculado o fator de balanceamento do nó raiz, sendo este >= 2 é necessário balancear.
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))//verificação se há necessidade de balancamento da árevore da direita, comparando as alturas dos filhos da direita e da esquerda
                    RotacaoRR(raiz); //conforme resultado da caompação das aluras dos filhos,
                else                 //será chamado a função para rotacao
                    RotacaoRL(raiz);
            }
	    }
	}

	if((*raiz)->info < valor){//se o valor da raiz fosse menor que o valor procurado, 
	    if((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1){//será chamada a funcao remove para sub-árvore da direita
            if(fatorBalanceamento_NO(*raiz) >= 2){//caso a condição seja suficiente, será calculado o fator de balanceamento do nó raiz, sendo este >= 2 é necessário balancear.
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )//verificação se há necessidade de balancamento da árevore da esquerda, comparando as alturas dos filhos da direita e da esquerda
                    RotacaoLL(raiz); //conforme resultado da caompação das aluras dos filhos,
                else                   //será chamado a função para rotacao
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->info == valor){ //se o valor procurado nao for maior ou menor que o no raiz, então ele pode ser igual a raiz
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// Verifica quando filhos há, e se nó tem 1 filho ou nenhum
			struct NO *oldNode = (*raiz);
			if((*raiz)->esq != NULL) //verifica quais filhos serao nulos
                *raiz = (*raiz)->esq; //caso positivo a raiz recebe o filho da esquerda
            else                      // ou 
                *raiz = (*raiz)->dir; //a raiz recebe o filho da direita
			free(oldNode); //libera o nó
		}else { //coso nenhum dos dois filhos sejam null, então o nó tem 2 filhos, então substitui pelo nó mais a esquerda da sub-árvore da direira
			struct NO* temp = procuraMenor((*raiz)->dir);//chamda da funcao procuraMenor, que entao o menor valor do nó estar em temp
			(*raiz)->info = temp->info;//copia as informacõe spara o nó raiz
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);//chamada da funcao de remoção de forma recursiva para tratar os nós do lado direito removendo o nó
            if(fatorBalanceamento_NO(*raiz) >= 2){ //caso a condição seja suficiente, será calculado o fator de balanceamento do nó raiz, sendo este >= 2 é necessário balancear.
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq)) //verificação se há necessidade de balancamento da árevore da esquerda, comparando as alturas dos filhos da direita e da esquerda
					RotacaoLL(raiz); //conforme resultado da caompação das aluras dos filhos,
				else                 //será chamado a função para rotacao
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL) //se o nó raiz for igual a nulo
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1; //realoca os nós da arvore o máximo uma rotação
		return 1;
	}

	(*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1; //realoca os nós da arvore o máximo uma rotação (simples ou dupla) 
	return res; // retorna o valor da firnação recursiva
}