#include <stdio.h>
#include "lista.h"

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    //o iterador foi projetado para percorrer a lista e ler valores, não para manipular ponteiros internos.
    int tamanho;

};
/* ---------------------------------------------------------------------- */

/*************    lista->ini->chave é o nodo cabeça, o primeiro elemento real é lista->ini->prox  ************************ */

/*
 * Cria e retorna uma nova lista.
 * Retorna NULL em caso de erro de alocação.
*/
struct lista *lista_cria (){
    struct lista *list = malloc(sizeof(struct lista));
    if(list == NULL) return NULL;

    list->ini = malloc(sizeof(struct nodo)); //inicia o ponteiro do ini
    if(list->ini == NULL){
        free(list);
        return NULL;
    }

    list->ini->prox = NULL;
    list->ptr = NULL;
    list->tamanho = 0;

    return list;
}

/* Desaloca toda memoria da lista e faz lista receber NULL. */
void lista_destroi (struct lista **lista){ //recebe um ponteiro para ponteiro
    //lista: endereço da variável 
    //*lista: a lista de verdade
    //verifica se o ponteiro é válido e se a lista existe
    if(!lista || !(*lista)) return;
    
    struct nodo *atual = (*lista)->ini->prox;
    while (atual){
        struct nodo *tmp = atual; //guarda o nodo atual para liberar depois
        atual = atual->prox; //avança para o próximo
        free(tmp); //libera o antigo
    }
    
    free((*lista)->ini); // libera o nodo cabeça (ini)
    free(*lista); //libera a struct em si
    *lista = NULL; //aterra o ponteiro    
}

/*
 * Insere chave no inicio da lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_inicio (struct lista *lista, int chave){
     if(!lista) return 0;
    struct nodo *novo = malloc(sizeof(struct nodo)); //cria um novo nodo
    if(!novo) return 0;
    novo->chave = chave; //a chave do novo recebe a chave passada
    novo->prox = lista->ini->prox; //o nodo aponta para o inicio da lista
    lista->ini->prox = novo; //pq prox? não aponta para o ponteiro do inicio mas
    //q está apontando para o proximo item???
    lista->tamanho++;
    return 1;
}

/*
 * Insere chave no final da lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_fim (struct lista *lista, int chave){
    if(!lista) return 0;
    
    struct nodo *novo = malloc(sizeof(struct nodo)); //cria um novo nodo
    if(!novo) return 0;
    novo->chave = chave; //a chave do novo recebe a chave passada
    novo->prox = NULL;

    struct nodo *atual = lista->ini;
    while(atual->prox != NULL){
        atual = atual->prox;
    }
    atual->prox = novo;
    lista->tamanho++;
    return 1;
}

/*
 * Insere chave em ordem na lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_ordenado (struct lista *lista, int chave){ 
    if(!lista) return 0;
    struct nodo *novo = malloc(sizeof(struct nodo)); //cria um novo nodo
    if(!novo) return 0;
    novo->chave = chave;

    struct nodo *aux = lista->ini;

    //procura a pos correta
    while(aux->prox != NULL && aux->prox->chave < chave){
        aux = aux->prox;
    }

    //encaixa o novo
    novo->prox = aux->prox;
    aux->prox = novo;

    lista->tamanho++;

    return 1;
}

/*
 * Remove o elemento do inicio da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_inicio (struct lista *lista, int *chave){
    if(!lista || lista->ini->prox == NULL) return 0;

    struct nodo *aux = lista->ini->prox; //guarda o nodo que será removido
    *chave = aux->chave; //retorna na chave, o elemento retirado

    lista->ini->prox = aux->prox; //o inicio aponta para o prox

    free(aux);
    lista->tamanho--; //ajusta o tamanho
    return 1;
}

/*
 * Remove o elemento do final da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_fim (struct lista *lista, int *chave){
    if(!lista || lista->ini->prox == NULL) return 0; //se null ou se lista vazia

    //Talvez não precise disso
    //ver se tem vazamento de memória
    if(lista->ini->prox->prox == NULL){ //Se a lista só tiver 1 elemento
        struct nodo *rem = lista->ini->prox;
        *chave = rem->chave;
        free(rem);
        lista->ini->prox = NULL;
        lista->tamanho--;
        return 1;
    }

    struct nodo *atual = lista->ini;
    while (atual->prox->prox != NULL){
        atual = atual->prox;
    }

    *chave = atual->prox->chave;
    free(atual->prox);
    atual->prox = NULL;

    lista->tamanho--; //ajusta o tamanho
    return 1;

    /*Versão diferente:
    struct nodo *ant = lista->ini;
    struct nodo *atual = lista->ini->prox;

    while (atual->prox) {
        ant = atual;
        atual = atual->prox;
    }

    *chave = atual->chave;
    ant->prox = NULL;

    free(atual);
    lista->tamanho--;

    return 1;
    */
}

/*
 * Remove o elemento chave da lista mantendo-a ordenada.
 * A função considera que a cheve esta presente na lista, quem chama
 * esta funcao deve garantir isso.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_ordenado (struct lista *lista, int chave){ /****************************************************************** */
    if(!lista) return 0;

    struct nodo *aux;
    aux = lista->ini;  

    while(aux->prox->chave != chave){
        aux = aux->prox;
    }
    struct nodo *rem = aux->prox; //nó a ser removida
    aux->prox = rem->prox;       //anterior aponta para o próximo do removido
    free(rem);                   //libera a memória
    lista->tamanho--;
    return 1;
}

/*
  Retorna 1 se a lista está vazia e 0 caso contrário.
*/
int lista_vazia (struct lista *lista){
    return (lista == NULL || lista->tamanho == 0);
}

/*
  Retorna o numero de elementos da lista
*/
int lista_tamanho (struct lista *lista){
    //if(!lista) return -1;
    return lista->tamanho;
}

/*
  Retorna 1 se o elemento chave esta presente na lista,
  caso contrário retorna 0.
*/
int lista_pertence (struct lista *lista, int chave){ //escolher apenas 1 ******************************************************************
    if(lista == NULL || lista_vazia(lista)) return 0;


    //com o aux
    struct nodo *aux;
    aux = lista->ini->prox;

    while(aux != NULL){
        if(aux->chave == chave) return 1;
        aux = aux->prox;
    }

    /*com o iterador ***
    int x = 0;
    lista_inicia_iterador(lista);
    while(lista_incrementa_iterador(lista, &x)){
        if(x == chave) return 1;
    }*/
    return 0;
}

/*
 * Inicializa ptr usado na funcao incrementa_iterador.
 * A funcao main deve garantir que a lista nao eh vazia.
*/
//o iterador permite andar na lista sem precisar mexer na estrutura dela
void lista_inicia_iterador (struct lista *lista){
    if(lista != NULL){
        lista->ptr = lista->ini->prox; //aponta para o primeiro elemento
    }
}

/*
 * Devolve no parametro *chave o elemento apontado e incrementa o iterador.
 * A funcao retorna 0 caso o iterador ultrapasse o ultimo elemento, ou retorna
 * 1 caso o iterador aponte para um elemento valido (dentro da lista).
*/
int lista_incrementa_iterador (struct lista *lista, int *chave){
    if(lista == NULL || lista->ptr == NULL ) return 0;
    *chave = lista->ptr->chave; //devolve a chave atual
    lista->ptr = lista->ptr->prox; //incrementa o iterador apontando para o próximo

    return 1;
}
