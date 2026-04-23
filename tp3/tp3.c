/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h> //malloc
#include "racional.h"

#define MAX 100

//Remove os elementos inválidas do vetor e retorna o novo tamanho.
int remove_invalidos(struct racional **v, int n){ //**V pois v[i] é struct *   */
  int novo_n = 0;
  for(int i=0; i<n; i++){
    if(v[i] != NULL){
      v[novo_n] = v[i];
      novo_n++;
    }
  }
  return novo_n;
}

void ordena_vetor(struct racional *v[], int n) //*v[] equivalente a **v
{  
  // v é um ponteiro para vetor[0]
  for(int i=0; i < n - 1; i++){
    int min = i; //assume que o menor está na pos i
    for(int j = i + 1; j < n; j++){
      if(compara_r(v[j], v[min]) < 0){ //compara retorna -1 se r1 for menor
        min = j; //achou um menor, atualiza o índice
      }
    }
    //troca v[i] com v[min], se necessário
    if(min != i){
      struct racional *tmp = v[i];
      v[i] = v[min];
      v[min] = tmp;
    }
  }
}


struct racional *soma_vetor(struct racional **v, int n)
{
  struct racional *soma = cria_r(0,1); //cria um racional "soma" com valor 0/1 (significa zero mas em racional)
  if (soma == NULL) return NULL;
  // se não conseguiu alocar memória, aborta
  if (!soma) return NULL;

  //percorre o vetor
  for(int i=0; i<n; i++){

    struct racional tmp; //variável temporária para guardar o resultado da soma
    if(soma_r(soma, v[i], &tmp)){
      *soma = tmp; //atualiza 'soma' com o resultado armazenado em tmp
    }
  }
  simplifica_r(soma);

  return soma;
}


/* programa principal */
int main ()
{
  int n;

  //ler n
  scanf("%d", &n);
  
  //se n fora dos parâmetros
  if(n<=0 || n>=MAX) return 0;


  /* Inicialmente, você vai alocar dinamicamente um vetor de ponteiros para N números racionais.*/
  //Aqui você está alocando espaço para n ponteiros (não para os racionais ainda). Cada posição vetor[i] será um ponteiro para um struct racional.
  //aloca vetor de ponteiros
  struct racional **vetor = malloc(n * sizeof(struct racional *)); //usa **vetor pq quero um ponteiro para ponteiros, no caso um vetor de ponteiros. 
  //struct racional * seria um ponteiro para uma estrutura racional (um vetor contínuo de racionais).
  if(!vetor) return 0; 


  /*Em seguida, você vai inicializar o vetor com ponteiros para N números racionais lidos a partir do teclado e vai inserir estes ponteiros, na mesma ordem da leitura, no vetor.*/
  for(int i=0; i<n; i++){
      long num, den;
      scanf("%ld %ld", &num, &den);
      vetor[i] = criar_r(num, den);
  }

  //imprime vetor
  printf("VETOR = ");
  for(int i=0; i<n; i++){
        imprime_r(vetor[i]);
        printf(" ");
  }

  //imprime o vetor sem os inválidos
  n = remove_invalidos(vetor, n);
  printf("\nVETOR = ");
  for(int i=0; i<n; i++){
        imprime_r(vetor[i]);
        printf(" ");
  }

//imprime o vetor ordenado em ordem crescente
  ordena_vetor(vetor, n);
  printf("\nVETOR = ");
  for(int i=0; i<n; i++){
    imprime_r(vetor[i]);
    printf(" ");
  }

  //imprime a soma de todos os elementos do vetor
  struct racional resultado = soma_vetor(vetor, n);
  printf("\nSOMA = ");
  imprime_r(resultado);

  //liberar os racionais apontados pelo vetor
   printf("\nVETOR = ");
   for(int i=0; i<n; i++){
    imprime_r(vetor[i]);
    printf(" ");
  }

  //liberar o vetor de ponteiros
  free(vetor);
  vetor = NULL;

//liberar o espaço utilizado para fazer o cálculo da soma




  return 0;
}

