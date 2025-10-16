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
        if (MDC(i, z, 1) == 1) {
            E = i;
            printf("\nO 'E' escolhido eh %d\n", E);
            break;
        }
        printf("\nComo d != 1 continuaremos a nossa busca");
    }

    printf("\nAgora iremos procurar o EXPOENTE PRIVADO\n");
    D = inverso_modular(E, z);
    printf("\nO 'D' escolhido eh %d", D);

    printf("\n\nChave Publica: ( %d , %d )", N, E);
    printf("\nChave Privada: ( %d , %d )\n\n", N, D);

    //remoção de buffer
    int buffer;
    while ((buffer = getchar()) != '\n' && buffer != EOF);

    char frase[101]; 
    int *M; //Frase pré-codificação
    M = malloc(sizeof(frase) * sizeof(int));

    printf("Mande sua mensagem para que possamos criptografar: ");
    fgets(frase, sizeof(frase), stdin);

    int teste = 0;

    for(int i = 0; frase[i] != '\n'; i++){
        if(frase[i] == ' ')
            M[i] = 0;
        else
            M[i] = frase[i] - 54;
        teste++;
    }

    printf("Sua mensagem pre codificada esta assim:\n   ");
    for (int i = 0; i < teste; i++){
        printf("%02d", M[i]);
    }
    printf("\n");

    int *C; //Frase Codificado
    C = malloc(sizeof(frase) * sizeof(int));

    for(int i = 0; i < teste; i++){
        if (eh_primo(E) && M[i] % E != 0){
            i++; //Place Hoder
        }
        else if (MDC(M[i], N, 0) == 1){
            i++; //Place Hoder
        }
        else {
            i++; //Place Hoder
        }
    }
    

    free(M);
    return 0;
} 
