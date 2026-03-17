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

        sorteia_r(n, max);

        printf("%d :", i);


    }


    return (0) ;
}
