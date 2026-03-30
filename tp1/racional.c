/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
 */

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* retorna um número aleatório entre min e max, inclusive. */
long aleat(long min, long max)
{

  if (min > max)
  { // Garante que min <= max
    long temp = min;
    min = max;
    max = temp;
  }

  return min + rand() % (max - min + 1);
}

/* Máximo Divisor Comum entre a e b      */
long mdc(long a, long b)
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

/* Mínimo Múltiplo Comum entre a e b */
long mmc(long a, long b)
{
  return (a * b) / mdc(a, b);
}

// Recebe um número racional e o simplifica.
struct racional simplifica_r(struct racional r)
{
  if (r.den == 0)
  {
    return r;
  }

  // Calcula o MDC do numerador e denominador
  long divisor = mdc(labs(r.num), labs(r.den));

  r.num = r.num / divisor;
  r.den = r.den / divisor;

  // jogo de sinais
  if (r.den < 0)
  {
    r.num = -r.num;
    r.den = -r.den;
  }
  return r;
}

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r(long numerador, long denominador)
{
  struct racional r;
  r.num = numerador;
  r.den = denominador;
  return r;
}

// Retorna 1 se o racional r for válido ou 0 se for inválido.
int valido_r(struct racional r)
{

  if (r.den == 0)
  {
    return 0; // inválido
  }
  return 1; // válido
}

// Retorna um número racional aleatório na forma simplificada.
struct racional sorteia_r(long min, long max)
{

  long num = aleat(min, max); // sorteia numerador
  long den = aleat(min, max); // sorteia denominador

  // cria racional com os valores sorteados
  struct racional r = cria_r(num, den);

  // simplifica e retorna
  return simplifica_r(r);
}

// Imprime um racional r
void imprime_r(struct racional r)
{
  // Racional invalido
  if (!valido_r(r))
  {
    printf("INVALIDO");
    return;
  }

  r = simplifica_r(r);

  // Se numerador = 0
  if (r.num == 0)
  {
    printf("0");
    return;
  }

  // Se denominador = 1
  if (r.den == 1)
  {
    printf("%ld", r.num);
    return;
  }

  if (r.num == r.den)
  {
    printf("1");
    return;
  }

  printf("%ld/%ld", r.num, r.den);
}

/* Retorna a soma dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional soma_r(struct racional r1, struct racional r2)
{

  struct racional resultado;

  if (valido_r(r1) && valido_r(r2))
  {
    resultado.num = ((r1.num * r2.den) + (r2.num * r1.den));
    resultado.den = r1.den * r2.den;
    resultado = simplifica_r(resultado);
  }
  else
  {
    resultado.num = 0;
    resultado.den = 0;
  }

  return resultado;
}

/* Retorna a subtração dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional subtrai_r(struct racional r1, struct racional r2)
{

  struct racional resultado;

  if (valido_r(r1) && valido_r(r2))
  {
    resultado.num = ((r1.num * r2.den) - (r2.num * r1.den));
    resultado.den = r1.den * r2.den;
    resultado = simplifica_r(resultado);
  }
  else
  {
    resultado.num = 0;
    resultado.den = 0;
  }

  return resultado;
}

/* Retorna a multiplicação dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional multiplica_r(struct racional r1, struct racional r2)
{

  struct racional resultado;

  if (valido_r(r1) && valido_r(r2))
  {
    resultado.num = r1.num * r2.num;
    resultado.den = r1.den * r2.den;
    resultado = simplifica_r(resultado);
  }
  else
  {
    resultado.num = 0;
    resultado.den = 0;
  }

  return resultado;
}

/* Retorna a divisão dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido.
 * observe que a divisão com r1 e r2 válidos pode gerar um racional inválido */
struct racional divide_r(struct racional r1, struct racional r2)
{

  struct racional resultado;

  if (valido_r(r1) && valido_r(r2))
  {

    resultado.num = r1.num * r2.den;
    resultado.den = r1.den * r2.num;

    // se o denominador virou zero, marca como inválido
    if (resultado.den == 0)
    {
      resultado.num = 0;
      resultado.den = 0;
    }
    else
    {
      resultado = simplifica_r(resultado);
    }
  }
  else
  {
    resultado.num = 0;
    resultado.den = 0;
  }

  return resultado;
}
