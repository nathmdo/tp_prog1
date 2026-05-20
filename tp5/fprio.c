// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Marcos Castilho, inclui as structs no arquivo.c, Out 2025
// Implementação com lista encadeada simples

#include <stdio.h>
#include <stdlib.h>

// descreve um nodo da fila de prioridades
struct fpnodo_t
{
  void *item ;          // item associado ao nodo
  int   tipo ;          // tipo do item
  int   prio ;          // prioridade do item
  struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades
struct fprio_t
{
  struct fpnodo_t *prim ;   // primeiro nodo da fila
  int num ;         // número de itens na fila
} ;

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria ()
{
  struct fprio_t *f = malloc(sizeof(struct fprio_t));

  if(!f) return NULL;
  f->prim = NULL;
  f->num = 0;

  return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi (struct fprio_t *f)
{
  if(!f) return NULL;

  struct fpnodo_t *atual = f->prim;
  while(atual)
  {
    struct fpnodo_t *aux = atual->prox;
    //libera a memória do dado genérico alocado pelo usuário
    if(atual->item != NULL) free(atual->item);

    free(atual);
    atual = aux;
  }

  free(f);
  return NULL;
}

// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio)
{
  // 1 - Validação de segurança
  if(!f || !item) return -1;

  // 2 - Verificação de item duplicado
  struct fpnodo_t *atual = f->prim;
  while (atual)
  {
    if(atual->item == item) return -1; //Erro: ele já existe na fila
    atual = atual->prox;
  }
  
  // 3 - Criação do novo nodo
  struct fpnodo_t *novo = malloc(sizeof(struct fpnodo_t));
  if(!novo) return -1;
  novo->item = item; 
  novo->tipo = tipo;
  novo->prio = prio;
  novo->prox = NULL;

  // 4 - Busca o lugar certo
  atual = f->prim;
  struct fpnodo_t *ant = NULL;
  while (atual != NULL && atual->prio <= prio)
  {
    ant = atual;
    atual = atual->prox;
  }

  // 5 - Costurar
  if(ant == NULL){
    novo->prox = f->prim;
    f->prim = novo;
  } else {
    novo->prox = atual;
    ant->prox = novo;
  }

  f->num++;
  return f->num; //retorna o num de itens na fila
}

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio)
{
  if(!f || f->prim == NULL || f->num == 0) return NULL;

  struct fpnodo_t *aux = f->prim; //aux segura o primeiro nodo
  void *item_retirado = aux->item;
  
  *tipo = aux->tipo;
  *prio = aux->prio;

  f->prim = aux->prox;
  free(aux);
  f->num--;
  return item_retirado;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho (struct fprio_t *f)
{
  if(!f || f->num < 0) return -1;
  return f->num;
}

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f)
{
  if(!f) return;

  struct fpnodo_t *atual = f->prim; //pq pointer
  while(atual != NULL)
  {
    printf("(%d %d)", atual->tipo, atual->prio);
    if(atual->prox != NULL) printf(" ");
    atual = atual->prox;
  }
}