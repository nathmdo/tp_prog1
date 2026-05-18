#include <stdio.h>
#include <stdlib.h>
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

/*
 * Cria e retorna uma nova lista.
 * Retorna NULL em caso de erro de alocação.
*/
struct lista *lista_cria (){
    struct lista *list = malloc(sizeof(struct lista));
    if(list == NULL) return NULL;

    list->ini = malloc(sizeof(struct nodo)); 
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
void lista_destroi (struct lista **lista){ 
    if(!lista || !(*lista)) return;
    
    struct nodo *atual = (*lista)->ini->prox;
    while (atual){
        struct nodo *tmp = atual; 
        atual = atual->prox; 
        free(tmp); 
    }
    
    free((*lista)->ini); 
    free(*lista); 
    *lista = NULL; 
}

/*
 * Insere chave no inicio da lista.
 */
int lista_insere_inicio (struct lista *lista, int chave){
     if(!lista) return 0;
    struct nodo *novo = malloc(sizeof(struct nodo)); 
    if(!novo) return 0;
    novo->chave = chave; 
    novo->prox = lista->ini->prox; 
    lista->ini->prox = novo;
    lista->tamanho++;
    return 1;
}

/*
 * Insere chave no final da lista.
 */
int lista_insere_fim (struct lista *lista, int chave){
    if(!lista) return 0;
    
    struct nodo *novo = malloc(sizeof(struct nodo)); 
    if(!novo) return 0;
    novo->chave = chave; 
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
 * Insere chave em ordem na lista. 
 */
int lista_insere_ordenado (struct lista *lista, int chave){ 
    if(!lista) return 0;
    struct nodo *novo = malloc(sizeof(struct nodo)); 
    if(!novo) return 0;
    novo->chave = chave;

    struct nodo *aux = lista->ini;

    while(aux->prox != NULL && aux->prox->chave < chave){
        aux = aux->prox;
    }

    novo->prox = aux->prox;
    aux->prox = novo;

    lista->tamanho++;

    return 1;
}

/*
 * Remove o elemento do inicio da lista e o retorna
 * no parametro chave. 
 */
int lista_remove_inicio (struct lista *lista, int *chave){
    if(!lista || lista->ini->prox == NULL) return 0;

    struct nodo *aux = lista->ini->prox; 
    *chave = aux->chave; 

    lista->ini->prox = aux->prox;

    free(aux);
    lista->tamanho--; 
    return 1;
}

/*
 * Remove o elemento do final da lista e o retorna
 * no parametro chave. 
 */
int lista_remove_fim (struct lista *lista, int *chave){
    if(!lista || lista->ini->prox == NULL) return 0; 

    if(lista->ini->prox->prox == NULL){ 
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

    lista->tamanho--; 
    return 1;
}

/*
 * Remove o elemento chave da lista mantendo-a ordenada.
 */
int lista_remove_ordenado (struct lista *lista, int chave){
    if(!lista) return 0;

    struct nodo *aux;
    aux = lista->ini;  

    while(aux->prox->chave != chave){
        aux = aux->prox;
    }
    struct nodo *rem = aux->prox; 
    aux->prox = rem->prox;       
    free(rem);                   
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
    return lista->tamanho;
}

/*
  Retorna 1 se o elemento chave esta presente na lista,
  caso contrário retorna 0.
*/
int lista_pertence (struct lista *lista, int chave){
    if(lista == NULL || lista_vazia(lista)) return 0;

    int x = 0;
    lista_inicia_iterador(lista);
    while(lista_incrementa_iterador(lista, &x)){
        if(x == chave) return 1;
    }
    return 0;
}

/* Inicializa ptr usado na funcao incrementa_iterador. */
void lista_inicia_iterador (struct lista *lista){
    if(lista != NULL){
        lista->ptr = lista->ini->prox; 
    }
}

/* Devolve no parametro *chave o elemento apontado e incrementa o iterador. */
int lista_incrementa_iterador (struct lista *lista, int *chave){
    if(lista == NULL || lista->ptr == NULL ) return 0;
    *chave = lista->ptr->chave; 
    lista->ptr = lista->ptr->prox; 
    return 1;
}
