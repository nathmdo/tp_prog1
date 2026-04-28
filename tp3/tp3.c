/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
*/

#include <stdio.h>
#include <stdlib.h> 
#include "racional.h"

#define MAX 100

/* Remove os elementos inválidas do vetor e retorna o novo tamanho. */
int remove_invalidos(struct racional **v, int n)
{
  int j = 0;
  for (int i = 0; i < n; i++) {
    if (v[i] != NULL && valido_r(v[i])) {
      v[j++] = v[i];
    } else {
      destroi_r(&v[i]);
    }
  }
  for (int i = j; i < n; i++) {
    v[i] = NULL;  
  }
  return j;
}

/* Função para ordenar o vetor, selection sort */
void ordena_vetor(struct racional *v[], int n) 
{  
  for(int i=0; i < n - 1; i++){
    int min = i; 
    for(int j = i + 1; j < n; j++){
      if(compara_r(v[j], v[min]) < 0){ 
        min = j; 
      }
    }
    if(min != i){
      struct racional *tmp = v[i];
      v[i] = v[min];
      v[min] = tmp;
    }
  }
}

/* Soma dos elementos do vetor */
struct racional *soma_vetor(struct racional **v, int n)
{
  struct racional *soma = cria_r(0,1);
  struct racional *tmp  = cria_r(0,1);

  if (!soma || !tmp) return NULL;

  for (int i = 0; i < n; i++) {
    if (v[i] && valido_r(v[i])) {
      soma_r(soma, v[i], tmp);

      struct racional *swap = soma;
      soma = tmp;
      tmp = swap;
    }
  }
  destroi_r(&tmp);
  return soma;
}

void imprime_vetor(struct racional **v, int n)
{
  printf("VETOR = ");
  for(int i=0; i<n; i++){
        imprime_r(v[i]);
        if(i < n - 1){
          printf(" ");
        }
  }
  printf("\n");
}

/* programa principal */
int main ()
{
  int n;

  scanf("%d", &n);
  if(n<=0 || n>=MAX) return 0;

  struct racional **vetor = malloc(n * sizeof(struct racional *));
  if(!vetor) return 0; 


  // Inicializar o vetor com ponteiros para N números racionais lidos 
  for(int i=0; i<n; i++){
      long num, den;
      scanf("%ld %ld", &num, &den);
      vetor[i] = cria_r(num, den);
  }

  //imprime o vetor lido
  imprime_vetor(vetor, n);

  //imprime o vetor sem os inválidos
  n = remove_invalidos(vetor, n);
  imprime_vetor(vetor, n);

  //imprime o vetor ordenado em ordem crescente
  ordena_vetor(vetor, n);
  imprime_vetor(vetor, n);

  //imprime a soma de todos os elementos do vetor
  struct racional *resultado = soma_vetor(vetor, n);
  printf("SOMA = ");
  imprime_r(resultado); 
  printf("\n");

  //liberar os racionais apontados pelo vetor
  for (int i = 0; i < n; i++) {
    destroi_r(&vetor[i]);
  }

  imprime_vetor(vetor, n);

  free(vetor);
  vetor = NULL;
  
  destroi_r(&resultado);

  return 0;
}