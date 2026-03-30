/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 */

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* programa principal */
int main()
{
    srand(0);

    int n, max;

    scanf("%d", &n);   // leitura do valor n sendo  0 < n < 100
    scanf("%d", &max); // leitura de max sendo 0 < max < 30

    // verifica e imprime n e max
    if ((n > 0 && n < 100) && (max > 0 && max < 30))
    {
        printf("%d %d\n", n, max);
    }
    else
    {
        return (0);
    }


    for (int i = 1; i <= n; i++)
    {
        printf("%d: ", i);

        struct racional soma, sub, multi, divi;

        // sorteia racionais com numerador e denominador entre -max e max
        struct racional r1 = sorteia_r(-max, max);
        struct racional r2 = sorteia_r(-max, max);

        imprime_r(r1);
        printf(" ");
        imprime_r(r2);
        printf(" ");

        if (!valido_r(r1) || !valido_r(r2))
        {
            printf("NUMERO INVALIDO");
            printf("\n");
            return 1;
        }

        // calcula
        soma = soma_r(r1, r2);
        sub = subtrai_r(r1, r2);
        multi = multiplica_r(r1, r2);
        divi = divide_r(r1, r2);

        if (!valido_r(divi))
        {
            printf("DIVISAO INVALIDA");
            printf("\n");
            return 1;
        }

        // imprime
        imprime_r(soma);
        printf(" ");
        imprime_r(sub);
        printf(" ");
        imprime_r(multi);
        printf(" ");
        imprime_r(divi);

        printf("\n");

    }

    return (0);
}
