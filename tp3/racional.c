/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 * Atualizado em 09/09/2025 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

struct racional {
  long num;          /* numerador   */
  long den;          /* denominador */
};

/* Maximo Divisor Comum entre a e b */
long mdc (long a, long b)
{
  long resto;

  while (b != 0)
  {
    resto = a % b;
    a = b;
    b = resto;
  }
  return a;
}

/* Minimo Multiplo Comum entre a e b */
long mmc (long a, long b)
{
  return (a * b) / mdc(a, b);
}

long l_abs(long x) {
    return x < 0 ? -x : x;
}

/* Simplifica o número racional indicado no parâmetro. */
int simplifica_r (struct racional *r)
{
  if(r==NULL || r->den==0) return 0;

  // Calcula o MDC do numerador e denominador
  long divisor = mdc(l_abs(r->num), l_abs(r->den));

  //simplifica
  r->num = r->num / divisor;
  r->den = r->den / divisor;

  // jogo de sinais
  if (r->den < 0)
  {
    r->num = -r->num;
    r->den = -r->den;
  }
  return 1;
}

/* Retorna o numerador do racional r */
long numerador_r (struct racional *r)
{
  if(r == NULL) return 0;
  return r->num;
}

/* Retorna o denominador do racional r */
long denominador_r (struct racional *r)
{
  if(r == NULL) return 0;
  return r->den;
}

/* Cria um número racional com o numerador e denominador indicados
 * e retorna um ponteiro que aponta para ele.
 * A memória para o número racional deve ser alocada dinamicamente
 * por esta função. Retorna NULL se não conseguiu alocar a memória. */
struct racional *cria_r (long numerador, long denominador){
  struct racional *r = malloc(sizeof(struct racional));

  r->den = denominador;
  r->num = numerador;

  return r;
}

/* Libera a memória alocada para o racional apontado por r */
void destroi_r (struct racional **r)
{
  if(r != NULL && *r != NULL){
    free(*r);
    *r = NULL;
  }
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido. */
int valido_r (struct racional *r)
{
  if(r == NULL) return 0;
  if(r->den == 0) return 0;
  return 1;
}

/* Imprime um racional r */
void imprime_r (struct racional *r)
{
  if(r == NULL){ 
    printf("NULL");
    return;
  }
  if(!valido_r(r)){ 
    printf("NaN");
    return;
  }

  struct racional copia = *r;
  simplifica_r(&copia);

  if(copia.num == 0){
    printf("0");
    return;
  }
  if(copia.num == copia.den){
    printf("1");
    return;
  }
  if(copia.den == 1){ 
    printf("%ld", copia.num);
    return;
  }
  
  printf("%ld/%ld", copia.num, copia.den);
}

/* Compara dois números racionais r1 e r2.
 * Retorna -2 se r1 ou r2 for inválido ou se o respectivo ponteiro for nulo.
 * Retorna -1 se r1 < r2; 0 se r1 = r2; 1 se r1 > r2. */
int compara_r (struct racional *r1, struct racional *r2)
{
  if(r1 == NULL || r2 == NULL) return -2;
  if(!valido_r(r1) || !valido_r(r2)) return -2;

  /*long m = mmc(r1->den, r2->den);

  long a = r1->num * (m / r1->den);
  long b = r2->num * (m / r2->den);

  long long a = (long long) r1->num * r2->den;
  long long b = (long long) r2->num * r1->den;*/

  // normaliza sinais localmente
  long n1 = numerador_r(r1);
  long d1 = denominador_r(r1);
  long n2 = numerador_r(r2);
  long d2 = denominador_r(r2);

  if (d1 < 0) {
    n1 = -n1;
    d1 = -d1;
  }
  if (d2 < 0) {
    n2 = -n2;
    d2 = -d2;
  }

  long long a = (long long) n1 * d2;
  long long b = (long long) n2 * d1;

  if (a < b) return -1;
  if (a > b) return 1;
  return 0;
}


/* Coloca em *r3 a soma simplificada dos racionais *r1 e *r2. */
int soma_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
  if(r1 == NULL || r2 == NULL || r3 == NULL) return 0;
  if (!valido_r(r1) || !valido_r(r2)) return 0;

  r3->num = r1->num * r2->den + r2->num * r1->den;
  r3->den = r1->den * r2->den;
  
  return simplifica_r(r3);
}

/* Coloca em *r3 a diferença simplificada dos racionais *r1 e *r2.*/
int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3)
{  
  if(r1 == NULL || r2 == NULL || r3 == NULL) return 0;
  if (!valido_r(r1) || !valido_r(r2)) return 0;
    
  r3->num = r1->num * r2->den - r2->num * r1->den;
  r3->den = r1->den * r2->den;
  
  return simplifica_r(r3);
}

/* Coloca em *r3 o produto simplificado dos racionais *r1 e *r2. */
int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
  if(r1 == NULL || r2 == NULL || r3 == NULL) return 0;
  if (!valido_r(r1) || !valido_r(r2)) return 0;

  r3->num = r1->num * r2->num;
  r3->den = r1->den * r2->den;

  return simplifica_r(r3);
}

/* Coloca em *r3 a divisão simplificada do racional *r1 por *r2.*/
int divide_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
  if(r1 == NULL || r2 == NULL || r3 == NULL) return 0;
  if (!valido_r(r1) || !valido_r(r2)) return 0;
  if (r2->num == 0) return 0;

  r3->num = r1->num * r2->den;
  r3->den = r1->den * r2->num;
  
  return simplifica_r(r3);
}