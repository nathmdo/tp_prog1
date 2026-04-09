/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"

#define MAX 100
//o racional.c não precisa declarar...


/* coloque aqui as funções auxiliares que precisar neste arquivo */

//Remove os elementos inválidas do vetor e retorna o novo tamanho.
int remove_invalidos(struct racional v[], int n){
  int novo_n = 0;
  for(int i=0; i<n; i++){
    if(valido_r(v[i])){
      v[novo_n] = v[i];
      novo_n++;
    }
  }
  return novo_n;
}

//Ordena o vetor de racionais usando o Selection Sort
void ordena_vetor(struct racional v[], int n) 
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
      struct racional tmp = v[i];
      v[i] = v[min];
      v[min] = tmp;
    }
  }
}

//Soma todos os elementos do vetor de racionais
struct racional soma_vetor(struct racional v[], int n)
{
  struct racional soma = cria_r(0,1); //cria um racional "soma" com valor 0/1 (significa zero mas em racional)
  for(int i=0; i<n; i++){ 
    struct racional tmp; //variável temporária para guardar o resultado da soma
    if(soma_r(soma, v[i], &tmp)){
      soma = tmp; //atualiza 'soma' com o resultado armazenado em tmp
    }
  }

  return soma;
}


/* programa principal */
int main ()
{
  //vetor de racionais
  struct racional vetor[MAX];

  int n;

  //ler n
  scanf("%d", &n);
  
  //se n fora dos parâmetros
  if(n<=0 || n>=MAX) return 0;

  //ler n racionais e por no vetor
  for(int i=0; i<n; i++)
  {
    long num, den;
    scanf("%ld %ld", &num, &den);
    vetor[i] = cria_r(num, den);
  }

  //Imprime o vetor inicial
  printf("VETOR = ");
  for(int i=0; i<n; i++)
  {
    imprime_r(vetor[i]);
    printf(" ");
  }

  //Imprime o vetor sem elementos inválidos
  n = remove_invalidos(vetor, n);
  printf("\nVETOR = ");
  for(int i=0; i<n; i++){
    imprime_r(vetor[i]);
    printf(" ");
  }


  //imprime o vetor ordenado
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

  printf("\n");  

  return (0) ;
}
