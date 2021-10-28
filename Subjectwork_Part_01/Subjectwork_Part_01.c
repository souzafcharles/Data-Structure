#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

//Structs para as estruturas das musicas ------------------------------------------------------------------
typedef struct musica {//Estrutura para o tipo de dado musica (equivalante ao info dos exemplos da aula)
    int id;
    char titulo[200];
    char artista[200];
    char album[200];
    int duracao; // deve estar em segundos
} Musica;

typedef struct musica_no { //No que liga a lista de musicas duplamente encadeada
    Musica *musica;
    struct musica_no *anterior; //ponteiro para o no anterior da lista duplamente encadeada
    struct musica_no *proximo; //poteiro para o proximo no da lista duplamente encadeada
} Musica_no;

//Structs para as estruturas das playlist ------------------------------------------------------------------
typedef struct playlist_no { //No que liga a playlist do tipo lista circular
    Musica *musica;
    struct playlist_no *proximo;
} Playlist_no;

typedef struct lplaylists_no { //No que liga a lista simples
    int id;
    char nome[200];
    Playlist_no *musicas;
    struct lplaylists_no *proximo; //poteiro para o proximo no da lista circular
} *Lplaylists_no;

//--------------- Funcoes para musica --------------------------------------------------

//Cria um no cabeca para lista de musica
Musica_no *cabeca_lista_musica() { 
    Musica_no *inicio = malloc(sizeof(Musica_no)); //aloca espaço na memoria para o no cabeca inicio
    inicio->proximo = NULL; //no cabeça ira apontar para null
    return inicio;
}

//Funcao para inserir uma musica da lista duplamente encadeada
void insere_musica(Musica_no* lista) {
    Musica_no *novo_no = malloc(sizeof(Musica_no)); //Cria um novo no cabeca para lista duplamente encadeada alocando espaço na memoria
    novo_no->musica = malloc(sizeof(Musica));//Cria novos dados sobre a musicas ligando o novo no da lista a informacao da musica

    system("cls");
    printf("ID: ");
    scanf("%d", &novo_no->musica->id); //Id recebe valor na estrura da musica e o novo no da lista aponta para esse conteudo
    fflush(stdin);
    printf("Titulo: ");
    gets(novo_no->musica->titulo); //Titulo recebe valor na estrura da musica e o novo no da lista aponta para esse conteudo
    printf("Artista: ");
    gets(novo_no->musica->artista); //Artista recebe valor na estrura da musica e o novo no da lista aponta para esse conteudo
    printf("Album: ");
    gets(novo_no->musica->album); //Album recebe valor na estrura da musica e o novo no da lista aponta para esse conteudo
    printf("Duracao(em segundos): ");
    scanf("%d", &novo_no->musica->duracao); //Duração recebe valor referenciado na estrura da musica e o novo no da lista aponta para esse conteudo

    novo_no->proximo = lista->proximo; //novo no ira apontar para o proximo no (apontar para nulo)
    novo_no->anterior = lista; //novo no ira apontar para o no anterior, na primria insersao sera o no cabeça
    if (lista->proximo) { // Se existe um ponteiro lista apontando para proximo 
        lista->proximo->anterior = novo_no; //Entao ponteiro para proximo apontara para novo no entre o no ja existente e o no cabeca
    }
    lista->proximo = novo_no;// Caso nao, pontoeteiro  ira apontar para o anterior que e o no cabeca
    printf("\nMusica Cadastrada!\n");
}

//Funcao para inserir uma musica da lista duplamente encadeada
void imprime_musica(Musica_no *no_inicio) {
    system("cls");
    printf("\t--------------MUSICAS CADASTRADAS--------------\n");

    if (!no_inicio->proximo) { // Se o proximo for null significa que so ha o no cabeca e a lista esta vazia
        printf("A lista de musicas esta vazia!\n\n");
        system("pause"); //mensagem para clicar em qualquer tecla para continuar 
    }
    else {//Caso haja um no 
        Musica_no *inicial = no_inicio->proximo; // o no cabeca tera ponteiro proximo que apontara para o proximo no

        while (inicial) { // enquanto houver no ligado ao no cabeca sera impresso as infomacoes da estrtura musica
            printf("\tID:-------- %d\n", inicial->musica->id);
            printf("\tTitulo:---- %s\n", inicial->musica->titulo);
            printf("\tArtista:--- %s\n", inicial->musica->artista);
            printf("\tAlbum:----- %s\n", inicial->musica->album);
            printf("\tDuracao:--- %.2d:%.2d:%.2d\n", (inicial->musica->duracao / 3600), (inicial->musica->duracao % 3600 / 60),
            (inicial->musica->duracao % 3600 % 60)); // funcao para impremir em formato horas, minutos e segundos: HH:MM:SS.
            printf("\t-------------------------------------------\n");

            inicial = inicial->proximo; // no cabeca ponta para o proximo no
        }
        system("pause"); //mensagem para clicar em qualquer tecla para continuar 
    }
}

//Funcao para buscar uma musica pelo ID na lista duplamente encadeada
Musica *busca_musica(Musica_no* lista, int id_buscado) { //
    Musica_no *procurado = lista->proximo;
    while (procurado && procurado->musica->id != id_buscado){ //enquanto a condicao for diferente o id buscado
        procurado = procurado->proximo; // o ponteiro caminha para o proximo no
    }
    return procurado->musica; //retorna a informacao 
}

//Funcao para remover uma musica eliminando as referencias nas listas 
void remove_musica(Musica_no* musicas, Lplaylists_no playlists) {
    int musica_id; 
    Lplaylists_no lista_de_playlists = playlists->proximo; //Acessa a lista simplemente ligada

    system("cls");
    printf("Informe o ID da musica a ser apagada:\n");
    scanf("%d", &musica_id); // armazena o id para remocao

    while(lista_de_playlists != NULL) { //Enquanto a lista de playlist for diferente de nulo....
        Playlist_no *no_atual, *proximo_no; // ira acessar o no com a musica a ser excluida o proximo no
        no_atual = lista_de_playlists->musicas; // acessa o conteudo do no 
        proximo_no = no_atual->proximo; // no aponta para o endereco do proximo no 

        while(proximo_no->musica != NULL && proximo_no->musica->id != musica_id) { //enquanto existir a musica e o id da musica não for encontrado...
            no_atual = proximo_no; // acessar o conteudo do no
            proximo_no = proximo_no->proximo; //no ira percorrer ate proximo no 
        }
        if(proximo_no->musica != NULL) {//conteudo existe...
            no_atual->proximo = proximo_no->proximo; //no ira percorrer o proximo apontando até o ultimo no que aponta para nulo
            free(proximo_no); // libera o no excluido da memoria 
        }

        lista_de_playlists = lista_de_playlists->proximo; //no ira apontar para o proximo no (apontar para nulo)
    }

    //Funcao para remover da lista de musicas
    Musica_no *atual, *proximo;
    atual = musicas;
    proximo = atual->proximo;

    while(proximo != NULL && proximo->musica->id != musica_id) { // consicao para encontrar a musica
        atual = proximo; //acessa a o item
        proximo = proximo->proximo; // ponteiro vai percorrer ate  oitem
    }
    if(proximo != NULL) { // se o item nao tiver conteudo nulo
        atual->proximo = proximo->proximo; //o ponteiro vai percorrer os nos e apontar para item ao lado do removido
        free(proximo->musica); //libera o ponteiro da musica que aponta para lista
        free(proximo); // Libera a musica removida
        printf("Musica removida!\n");
        system("pause"); //mensagem para clicar em qualquer tecla para continuar 
    }
    else {
        printf("Musica nao cadastrada!");
        system("pause"); //mensagem para clicar em qualquer tecla para continuar 
    }
}

//--------------- Funcoes para playlist --------------------------------------------------

//Cria um no cabeca para lista circular de playlist 
Playlist_no *cabeca_lista_circular_playlist (){ //Cria uma cabeca de lista circular encadeada de playlist
    Playlist_no *inicio = malloc(sizeof(Playlist_no)); //Cria um novo no cabeca para lista circular alocando espaço na memoria
    inicio->proximo = inicio; //Cria novos dados sobre a musicas ligando o novo no da lista a informacao da musica
    return inicio;
}

//Cria um no cabeca para lista simplesmente encadeada de playlist 
Lplaylists_no cabeca_lista_simples_playlist() { //Cria uma cabeca de lista simplesmente encadeada de playlist
    Lplaylists_no inicio = (Lplaylists_no) malloc(sizeof(Lplaylists_no)); //aloca espaço na memoria para o no cabeca inicio
    inicio->proximo = NULL; //no cabeça ira apontar para null
    return inicio;
}

//Funcao para inserir dados playlist de musicas
void insere_playlist (Lplaylists_no lista_de_playlists, Playlist_no *playlist) {
    Lplaylists_no novo_no = (Lplaylists_no)malloc(sizeof(Lplaylists_no)); //Cria um novo no cabeca para lista duplamente encadeada alocando espaço na memoria
    novo_no->musicas = malloc(sizeof(Playlist_no));
    system("cls");
    printf("ID da playlist: ");
    scanf("%d", &novo_no->id); //Id recebe valor na estrura da lista circular e o novo no da lista aponta para esse conteudo
    fflush(stdin);
    printf("Nome da playlist: ");
    gets(novo_no->nome); //Nome recebe valor na estrura da lista circular e o novo no da lista aponta para esse conteudo
    novo_no->musicas = playlist; //novo no ira apontar para playlist
    novo_no->proximo = lista_de_playlists->proximo; //novo no ira apontar para o proximo no (apontar para nulo)
    lista_de_playlists->proximo = novo_no; //Pontoeteiro  ira apontar para o anterior que e o no cabeca
}

//Funcao pra preenchar os dados da playlist
void preenche_playlist(Lplaylists_no lista_de_playlist, Musica_no* lista_de_musicas) {
    char entrada_id[100];
    char *id;
    int ids_informados[100]; // vetor de ids
    int indice = 0; //interador
    int numero_de_ids = 0; //contador

    Playlist_no *nova_playlist = cabeca_lista_circular_playlist(); //Cria playlist para lista circular com no cabeca

    //Coleta de dados pelo usuario que ira indicar os ids das musica para compor a playlist
    fflush(stdin);
    printf("Informe os ID's das musicas para incluir na playlist:\n");
    gets(entrada_id);
    id = strtok (entrada_id, " "); //Extrai o primeiro id pela funcao strtok que devolve um ponteiro para a próxima palavra na string apontada por endereçoStrOrigem.

    while (id != NULL) { //Enquanto o valor do id for diferente de null...
        ids_informados[indice++] = atoi(id); //... Adiciona o id no vetor de ids
        id = strtok(NULL, " "); // Função para quando o valor for nulo pela função strtok que devolve um ponteiro para a próxima palavra na string apontada por endereçoStrOrigem.
        numero_de_ids++; //interacao
    }

    // Interação para preencher a playlist com os id das musicas selecionados
    for(indice = 0; indice < numero_de_ids; indice++) {
        Playlist_no *novo_no_playlist = malloc(sizeof(Playlist_no)); //Cria um novo no cabeca para lista circular encadeada alocando espaço na memoria
        novo_no_playlist->musica = busca_musica(lista_de_musicas,ids_informados[indice]); // funcao para buscar musica e incluir no novo no da playlist
        novo_no_playlist->proximo = nova_playlist->proximo; //novo no ira apontar para o proximo no (apontar para nulo)
        nova_playlist->proximo = novo_no_playlist; //Pontoeteiro  ira apontar para o anterior que e o no cabeca
    }
    insere_playlist(lista_de_playlist, nova_playlist); //chamada da funcao
    printf("\nPlaylist Criada!\n");
}

void imprime_playlists(Lplaylists_no no_cabeca) {
    system("cls");
    printf("--------------PLAYLISTS CADASTRADAS--------------\n");

    if(!no_cabeca->proximo) { // Se o proximo for null significa que so ha o no cabeca e a lista esta vazia
        printf("Nenhuma playlist cadastrada!");
    }
    else{//Caso haja um no
        Lplaylists_no inicial = no_cabeca->proximo; // o no cabeca tera ponteiro proximo que apontara para o proximo no

        while(inicial != NULL) { // enquanto houver no ligado ao no cabeca sera impresso as infomacoes da estrtura da playlist
            printf("ID:----------------- %d\n", inicial->id);
            printf("Nome da playlist:--- %s\n", inicial->nome);

            printf("\n---------------- Musicas:---------------\n");
            Playlist_no *playlist = inicial->musicas->proximo;
            while(playlist->musica != NULL) {
                printf("Titulo:--------- %s\n", playlist->musica->titulo);
                playlist = playlist->proximo;
            }
            printf("-------------------------------------------\n");
            inicial = inicial->proximo; // no cabeca ponta para o proximo no
        }
        system("pause"); //mensagem para clicar em qualquer tecla para continuar 
    }
}

// Funcao shuffle que altera aleatoriamente a ordem das músicas dentro de uma playlist:
//Consultado https://www.programming-idioms.org/idiom/10/shuffle-a-list/1995/c
void shuffle(Lplaylists_no playlists, Musica_no* lista_musicas){
    
    int id;
    int indice = 0; //contador
    int lista_de_ids[50]; //vetor com os ids

    fflush(stdin);
    if(!playlists->proximo){
        printf("Nenhuma playlist cadastrada!");
    }
    else {

        Lplaylists_no no_da_lista = playlists->proximo;
        system("cls");
        printf("Informe o ID da playlist que queira embralhar as musicas:\n");
        scanf("%d", &id); //Recebe qual o id da playlist a ser embaralhada

        while(no_da_lista != NULL && no_da_lista->id != id){// Ira procurar pelo id na lista de playlists...
            no_da_lista = no_da_lista->proximo; //... percorrendo os proximos nos ate encontrar 
        }

        if (no_da_lista != NULL) {// Se o nao existir, ira mapeiar os ids das musicas e os colocara em uma lista
            Playlist_no *playlist = no_da_lista->musicas->proximo; //no com dados para proxima musica
            Playlist_no *playlist_auxliar = playlist; //no auxiliar para manipulacao da playlist
            while(playlist->musica != NULL) { //Enquanto o valor do no for diferente de null...
                lista_de_ids[indice++] = playlist->musica->id; //Adiciona o id no vetor de ids
                playlist = playlist->proximo; //novo no ira apontar para o proximo no (apontar para nulo)
            }

            //Função para substituir as musicas
            while (playlist_auxliar->musica != NULL) {//Para cada no da playlist direreente de null...
                int id_aleatorio;
                int indice_aleatorio = rand() % indice; //Um dos indices do vetor de ids sera escolhido de forma aleatoria
                id_aleatorio = lista_de_ids[indice_aleatorio]; //Um elemento aleatorio sera escolhido do vetor de ids

                Musica_no *musicas = lista_musicas->proximo; //acessa a lista de musica

                while(musicas != NULL && (musicas->musica->id != id_aleatorio)) {//O elemento sera procurado na lista geral de musicas cadastradas
                    musicas = musicas->proximo;
                }
                playlist_auxliar->musica = musicas->musica; // A musica sera atribuida ao no da playlist


                // Interacao para remover o id ja selecionado do vetor
                for(int i = indice_aleatorio; i < indice; i++) {
                     lista_de_ids[i] = lista_de_ids[i + 1];
                }
                indice--; //Decrementa o vetor

                playlist_auxliar = playlist_auxliar->proximo; //no ira apontar para o proximo no (apontar para nulo)
            }

        printf("Musicas da playlist embaralhados!\n");
        system("pause"); //mensagem para clicar em qualquer tecla para continuar
        }
    }
}

//--------------------------------Funcao Principal--------------------------------------
int main(void) {
    setlocale(LC_ALL, "Portuguese");
    srand(time(0));

    Musica_no* lista_de_musicas = cabeca_lista_musica(); //Variavel lista_de_musicas recebe uma função no cabeca para a lista duplamente encadeada
    Lplaylists_no lista_de_playlists = cabeca_lista_simples_playlist(); //Variavel lista_de_playlist recebe uma função no cabeca para a lista simplesmente encadeada

    int opcao = 10; // recebe 1 para diferenciar de 0


    while (opcao!=0){
        
	printf("\n\n------------- MENU MUSICA PLAYER --------------\n\n");
        printf ("Digite o numero [1] para inserir musica\n");
        printf ("Digite o numero [2] para listar musicas\n");
        printf ("Digite o numero [3] para criar uma playlist\n");
        printf ("Digite o numero [4] para mostrar playlist \n");
        printf ("Digite o numero [5] para shuffle da playlist\n");
        printf ("Digite o numero [6] para remover uma musica\n");
        printf ("Digite o numero [0] para encerrar o programa\n");
        printf("\nEscolha uma opcao: "); 
		scanf("%d", &opcao);

        switch(opcao){
            case 1:{
                insere_musica(lista_de_musicas);  //envia a lista de musica
                break;
            }
            case 2:{
                imprime_musica(lista_de_musicas); //envia a lista de musica
                break;
            }
            case 3:{
                preenche_playlist(lista_de_playlists, lista_de_musicas); //envia a lista de musica e a lista de playlist
                break;
            }
            case 4: {
                imprime_playlists(lista_de_playlists); //envia a lista de playlist
                break;
            }
            case 5: {
                shuffle(lista_de_playlists, lista_de_musicas); //envia a lista de musica e a lista de playlist
                break;
            }
            case 6: {
                remove_musica(lista_de_musicas, lista_de_playlists); //envia a lista de musica e a lista de playlist
                break;
            }
        }
    }
    printf("\n--------------- PROGRAMA ENCERRADO ---------------\n\n");
    system("pause"); //mensagem para clicar em qualquer tecla para continuar e encerrar
    return 0;
}
