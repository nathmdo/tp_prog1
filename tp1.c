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
    if((n>1 & n<100) && (max>0 & max<30) ){
        printf("%d %d\n", n, max);
    } else {
        return(0); //saiiii
    }

    for(int i=0; i<n; i++){
    
        // sorteia racionais com numerador e denominador entre -max e max 
        struct racional r1 = sorteia_r(-max, max);
        struct racional r2 = sorteia_r(-max, max);

        printf("%d: ", i);

        imprime_r(r1);
        printf(" ");
        imprime_r(r2);
        
        if(!valido_r(r1) || !valido_r(r2)){
            printf("NUMERO INVALIDO");
            return 1;
        }

        //calcula
        soma_r(r1, r2);
        subtrai_r(r1, r2);
        multiplica_r(r1, r2);
        divide_r(r1, r2);

       /* if(valido_r(divisao)){
            printf("DIVISAO INVALIDA");
            return 1;
        }*/

        //imprime
        soma_r(r1, r2);
        subtrai_r(r1, r2);
        multiplica_r(r1, r2);
        divide_r(r1, r2);

        //muda linha
        printf("\n");

    }


    return (0) ;
}
