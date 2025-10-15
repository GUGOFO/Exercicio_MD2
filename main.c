#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcoes.h"

int main(){

    int n1, n2;
    int p, q;
    
    printf("\nColoque o numero que voce quer fatorar (PRODUTO DE PRIMOS DISTINTOS):");
    scanf("%d", &n1);
    p = Fatoracao_Interativa(n1);

    printf("\nColoque o numero que voce quer fatorar (PRODUTO DE PRIMOS DISTINTOS):");
    scanf("%d", &n2);
    q = Fatoracao_Interativa(n2);

    printf("\nCom isso, achamos nossos 'p' e 'q', sendo eles:\n");
    printf("    p = %d\n    q = %d\n", p, q);

    //Chaves_RSA

    int N = p * q;
    int z = (p - 1)*(q - 1);
    int E = 0, D = 0;

    printf("\nAgora iremos procurar o EXPOENTE PUBLICO, comecando em 1");
    for(int i = 2; i < z; i++){
        printf("\n");
        if (MDC(i, z) == 1) {
            E = i;
            printf("\nO 'E' escolhido eh %d\n", E);
            break;
        }
        printf("\nComo d != 1 continuaremos a nossa busca");
    }

    printf("\nAgora iremos procurar o EXPOENTE PRIVADO\n");
    D = inverso_modular(E, z);
    printf("\nO 'D' escolhido eh %d", D);


    return 0;
} 
