/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max)
{
  if (min > max)
  { // Garante que min <= max
    long temp = min;
    min = max;
    max = temp;
  }

  return min + rand() % (max - min + 1);
}

/* Máximo Divisor Comum entre a e b */
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

/* Mínimo Múltiplo Comum entre a e b */
long mmc (long a, long b)
{
  return (a * b) / mdc(a, b);
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r)
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

/* implemente as demais funções de racional.h aqui */


/* Retorna o numerador do racional r */
long numerador_r (struct racional r)
{
  return r.num;
}

/* Retorna o denominador do racional r */
long denominador_r (struct racional r)
{
  return r.den;
}

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador)
{
  struct racional r;
  r.num = numerador;
  r.den = denominador;
  return r;
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido.
 * Um racional é inválido se seu denominador for zero */
int valido_r (struct racional r)
{
  if (r.den == 0)
  {
    return 0; // inválido
  }
  return 1; // válido
}

/* Retorna um número racional aleatório na forma simplificada.
 * Deve ser sorteado o numerador e depois o denominador.
 * o racional gerado pode ser válido ou inválido.
 * O numerador e o denominador devem ser inteiros entre min e max. */
struct racional sorteia_r (long min, long max)
{
  long num = aleat(min, max); // sorteia numerador
  long den = aleat(min, max); // sorteia denominador

  // cria racional com os valores sorteados
  struct racional r = cria_r(num, den);

  // simplifica e retorna
  return simplifica_r(r);
}



/* Imprime um racional r, respeitando estas regras:
   - o racional deve ser impresso na forma simplificada;
   - não imprima espaços em branco e não mude de linha;
   - a saída deve ter o formato "num/den", a menos dos casos abaixo:
     - se o racional for inválido, imprime a mensagem "NaN" (Not a Number);
     - se o numerador for 0, imprime somente "0";
     - se o denominador for 1, imprime somente o numerador;
     - se o numerador e denominador forem iguais, imprime somente "1";
     - se o racional for negativo, o sinal "-" vem antes do numerador;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r (struct racional r)
{

  // Racional invalido
  if (!valido_r(r))
  {
    printf("NaN");
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


  /*
  if(!valido_r(r)){
    printf("NaN");
  } 
  
  r = simplifica_r(r);

  if (r.num == 0){ //se num = 0
    printf("0");
  } else if (r.den == 1) //se den = 1
  {
    printf("%ld", r.num);
  } else if (r.num == r.den)// se iguais
  {
    printf("1");
  } else {
    printf("%ld/%ld", r.num, r.den);
  }*/
  
  
}

/********************************************************************** */
/* Compara dois racionais r1 e r2. Retorno: -2 se r1 ou r2 for inválido,
 * -1 se r1 < r2, 0 se r1 = r2 ou 1 se r1 > r2 */
int compara_r (struct racional r1, struct racional r2)
{
  if(!valido_r(r1) || !valido_r(r2)) return -2;
  
  r1 = simplifica_r(r1);
  r2 = simplifica_r(r2);
  
  /* Compara usando produto cruzado
  Se os numeradores e denominadores forem grandes, a multiplicação pode ultrapassar o limite de int. Usando long long, você reduz o risco de overflow.
  𝑛𝑢𝑚1⋅𝑑𝑒𝑛2 e 𝑛𝑢𝑚2⋅𝑑𝑒𝑛1  
  Se 𝑛𝑢𝑚1⋅𝑑𝑒𝑛2<𝑛𝑢𝑚2⋅𝑑𝑒𝑛1,então 𝑟1<𝑟2.
  Se 𝑛𝑢𝑚1𝑑𝑒𝑛2>𝑛𝑢𝑚2⋅𝑑𝑒𝑛1, então 𝑟1>𝑟2.
  Se forem iguais, 𝑟1=𝑟2.*/
  long long a = (long long) r1.num * r2.den;
  long long b = (long long) r2.num * r1.den;
  if (a < b) return -1;
  if (a > b) return 1;
  return 0;
  
}

/* Retorna a soma dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int soma_r (struct racional r1, struct racional r2, struct racional *r3)
{
  if(!r3 || !valido_r(r1) || !valido_r(r2)) return 0;

  // Calcula soma
  r3->num = r1.num * r2.den + r2.num * r1.den;
  r3->den = r1.den * r2.den;
  *r3 = simplifica_r(*r3);
  return valido_r(*r3);


}

/* Retorna a subtracao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int subtrai_r (struct racional r1, struct racional r2, struct racional *r3)
{
  //se o ponteiro r3 for nulo ou se r1/r2 forem inválidos, não dá pra somar
  if (!r3 || !valido_r(r1) || !valido_r(r2)) return 0;
    r3->num = r1.num * r2.den - r2.num * r1.den;
    r3->den = r1.den * r2.den;
    *r3 = simplifica_r(*r3); // Simplifica o resultado (por exemplo, 2/4 vira 1/2)
    return valido_r(*r3); // Retorna 1 se o resultado for válido, 0 se não for
}

/* Retorna a multiplicacao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int multiplica_r (struct racional r1, struct racional r2, struct racional *r3)
{
  if (!r3 || !valido_r(r1) || !valido_r(r2)) return 0;
    r3->num = r1.num * r2.num;
    r3->den = r1.den * r2.den;
    *r3 = simplifica_r(*r3);
    return valido_r(*r3);
}
/* Retorna a divisao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int divide_r (struct racional r1, struct racional r2, struct racional *r3)
{
   if (!r3 || !valido_r(r1) || !valido_r(r2)) return 0;
    if (r2.num == 0) return 0; // divisão inválida
    r3->num = r1.num * r2.den;
    r3->den = r1.den * r2.num;
    *r3 = simplifica_r(*r3);
    return valido_r(*r3);
}