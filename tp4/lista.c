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
    int tamanho;

};
/* ---------------------------------------------------------------------- */

/*************    lista->ini->chave é o nodo cabeça, o primeiro elemento real é lista->ini->prox  ************************ */

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

int lista_remove_ordenado (struct lista *lista, int chave){
}

int lista_vazia (struct lista *lista){
    if(lista->tamanho == 0) return 1;
        return 0;
        //ou
        //if(lista->ini == NULL) return 1;
        //return 0;
}

int lista_tamanho (struct lista *lista){
    //if(!lista) return -1;

        return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave){
}

void lista_inicia_iterador (struct lista *lista){
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
}
