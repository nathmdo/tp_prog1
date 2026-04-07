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


/* programa principal */
int main ()
{
  //vetor de racionais
  struct racional vetor[MAX];

  int n;

  //ler n
  scanf("%d", &n);
  
  //se n fora dos parâmetros
  if(n<=0 || n>=MAX)
  {
    return 0;
  }
  // if(n <= 0 || n >= MAX) return 0;

  for(int i=0; i<n; i++)
  {
    scanf("%ld", num);
    scanf("%ld", den);
    vetor[i] = cria_r(num, den);
  }

  return (0) ;
}
