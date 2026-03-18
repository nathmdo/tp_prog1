/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"


/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max)
{
  //long num = rand() % 31; //sorteia um numero de 1 a 30
  //long num = min + rand() % (max - min + 1);//fórmula generalizada acho que está mais certa hihi
  //de min até max   de -max até max

  //Garante que min <= max
  if(min > max){
    long temp = min;
    min = max;
    max = temp;
  }

  //Fórmula
  return min + rand() % (max - min + 1);
}


/************testar********** z*/
/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b)
{
  long resto;

  while(b!=0){
    resto = a % b;
    a = b;
    b = resto;
  }

  return a;
}
//usa scanf("%ld", &y)



/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  return (a*b) / mdc(a,b);
}




/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r(struct racional r)
{
  if( r.den == 0 ){
    return r;
  }

  // Calcula o MDC do numerador e denominador
    long divisor = mdc(r.num, r.den);

    r.num = r.num/divisor;
    r.den = r.den/divisor;

    /*****************melhorar*************** */
    //jogo de sinais
    if( r.num < 0 && r.den < 0){
      r.num = -r.num;
      r.den = -r.den;
    }

    if( r.num > 0 && r.den < 0){
      r.num = -r.num;
      r.den = -r.den;
    }

    return r;
}
/***********revisar*********** */




/* implemente as demais funções aqui */


/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador){

  struct racional r;
  r.num = numerador;
  r.den = denominador;
  return r;
  
}


/* Retorna 1 se o racional r for válido ou 0 se for inválido.
 * Um racional é inválido se seu denominador for zero */
int valido_r (struct racional r){

  if(r.den = 0){
        return 0;//inválido
  }

 return 1;//válido

}


/* Retorna um número racional aleatório na forma simplificada.
 * Deve ser sorteado o numerador e depois o denominador.
 * o racional gerado pode ser válido ou inválido.
 * O numerador e o denominador devem ser inteiros entre min e max. */
struct racional sorteia_r (long min, long max){
  
  long num = aleat(min,max);
  long den = aleat(min,max);

  // cria racional com os valores sorteados
  struct racional r = cria_r(num, den);
  
  // simplifica antes de retornar
    r = simplifica_r(r); 
    return r;

}

/* Imprime um racional r, respeitando estas regras:
   - o racional deve ser impresso na forma simplificada;
   - não imprima espaços em branco e não mude de linha;
   - a saída deve ter o formato "num/den", a menos dos casos abaixo:
     - se o racional for inválido, deve imprimir a mensagem "INVALIDO";
     - se o numerador for 0, deve imprimir somente "0";
     - se o denominador for 1, deve imprimir somente o numerador;
     - se o numerador e denominador forem iguais, deve imprimir somente "1";
     - se o racional for negativo, o sinal "-" deve vir antes do numerador;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r (struct racional r){ //NÃO RETORNA NADAAAAA

  //Simplifica primeiro
  r = simplifica_r(r);

  //Racional invalido
  if(valido_r(r)){
    printf("INVALIDO");
    return;
  }

  //Se numerador = 0
  if(r.num = 0){
    printf("0");
    return;
  }
  
  //Se denominador = 1
  if(r.den = 1){
    printf("num");
    return;
  }

  if(r.num == r.den){
    printf("1");
    return;
  }

  //Não sei se ajusta o sinal aqui ou em simplifica********
  /*// Ajusta sinal: se ambos negativos, fica positivo
    if (r.num < 0 && r.den < 0) {
        r.num = -r.num;
        r.den = -r.den;
    }
    // Se só um é negativo, imprime com sinal antes do numerador
    else if (r.den < 0) {
        r.num = -r.num;
        r.den = -r.den;
    }*/

  printf("%ld/%ld ", r.num, r.den);//ld pq usa long int

}



/* Retorna a soma dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional soma_r (struct racional r1, struct racional r2){
  /* implemente aqui */
}



/* Retorna a subtração dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional subtrai_r (struct racional r1, struct racional r2){
  /* implemente aqui */
}



/* Retorna a multiplicação dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional multiplica_r (struct racional r1, struct racional r2){
  /* implemente aqui */
}



/* Retorna a divisão dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido.
 * observe que a divisão com r1 e r2 válidos pode gerar um racional inválido */
struct racional divide_r (struct racional r1, struct racional r2){
  /* implemente aqui */
}