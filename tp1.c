/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>  // para rand() e srand()
#include "racional.h"


/* programa principal */
int main ()
{
    srand (0); /* use assim, com zero */

    int n, max;

    scanf ("%d", &n); //leitura do valor n sendo  1 < n < 100
    scanf ("%d", &max); //leitura de max sendo 0 < max < 30

    //verifica e imprime
    if((n>=1 && n<100) && (max>0 && max<30) ){
        printf("%d %d\n", n, max);
    } else {
        return(0); //saiiii
    }

    for(int i=1; i<n; i++){
    
        printf("%d: ", i);

        // sorteia racionais com numerador e denominador entre -max e max 
        struct racional r1 = sorteia_r(-max, max);
        struct racional r2 = sorteia_r(-max, max);

       /* printf("DEBUG r1.num=%ld r1.den=%ld | r2.num=%ld r2.den=%ld\n", r1.num, r1.den, r2.num, r2.den);

        printf("DEBUG valido_r(r1)=%d valido_r(r2)=%d\n", valido_r(r1), valido_r(r2));
*/


        /*Se algum for inválido imprime e retorna 1 */
        if(!valido_r(r1) || !valido_r(r2)){
            printf("NUMERO INVALIDO");
            return 1;
        }

        imprime_r(r1);
        printf(" ");
        imprime_r(r2);
        
        

        //calcula
        struct racional soma = soma_r(r1, r2);
        struct racional sub = subtrai_r(r1, r2);
        struct racional multi = multiplica_r(r1, r2);
        struct racional divi = divide_r(r1, r2);

       /* if(valido_r(divisao)){
            printf("DIVISAO INVALIDA");
            return 1;
        }*/

        //imprime
        printf(" ");
        imprime_r(soma);
        printf(" ");
        imprime_r(sub);
        printf(" ");
        imprime_r(multi);
        printf(" ");
        imprime_r(divi);

        //muda linha
        printf("\n");

    }


    return (0) ;
}
