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

int lista_insere_inicio (struct lista *lista, int chave){
}

int lista_insere_fim (struct lista *lista, int chave){
}

int lista_insere_ordenado (struct lista *lista, int chave){
}

int lista_remove_inicio (struct lista *lista, int *chave){
}

int lista_remove_fim (struct lista *lista, int *chave){
}

int lista_remove_ordenado (struct lista *lista, int chave){
}

int lista_vazia (struct lista *lista){
}

int lista_tamanho (struct lista *lista){
}

int lista_pertence (struct lista *lista, int chave){
}

void lista_inicia_iterador (struct lista *lista){
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
}
