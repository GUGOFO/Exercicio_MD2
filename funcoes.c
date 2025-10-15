#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcoes.h"

//==============================================
//              FUNÇÕES BASICAS
//==============================================

int g(int x, int n){
    int resultado = (x*x + 1) % n;
    printf("    g(%d) = (%d^2 + 1) mod %d = %d\n", x, x, n, resultado);
    return resultado;
}

int MDC(int a, int b){
    printf("\n    MDC( %d , %d )\n", a , b);
    while(b != 0){
        int quociente = a / b;
        int resto = a % b;
        printf("    %d = %d x %d + %d\n", a, b, quociente, resto);
        a = b;
        b = resto;
    }
    printf("    d = %d\n", a);
    return a;
}

int Algoritmo_Estendido_De_Euclides(int a, int b, int *x, int *y){
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    int x1, y1;
    int mdc = Algoritmo_Estendido_De_Euclides(b, a % b, &x1, &y1);

    printf("\n     Calculando coeficientes para Algoritmo Estendido De Euclides( %d , %d ):", a, b);
    *x = y1;
    *y = x1 - (a / b) * y1;
    printf("\n       %d - (%d/%d)*%d = %d", x1, a, b, y1, *y);

    return mdc;
}

//==============================================
//              FUNÇÕES AVANÇADAS
// =============================================

int Fatoracao_Interativa(int n){

    int tartaruga = 2, lebre = 2; int d = 1;

    printf("\nConsiderando: x0 = 2 e c = 1\n");

    while(d == 1){
        printf("\nAchando a 'tartaruga':\n");
        tartaruga = g(tartaruga, n);
        printf("Achando a 'lebre':\n");
        lebre =  g(g(lebre, n), n);
        printf("Achando o MDC(|tartaruga - lebre|, N):\n");
        d = MDC(abs(tartaruga - lebre),n);

        if( d > 1 && d < n){
            printf("\nUm fator de %d eh %d\n", n, d);
        } else {
            printf("\nFator comum nao encontrado\n");
        }
    }

    return d;
}

int inverso_modular(int e, int z){
    int x, y;
    printf("\n   Utlilizando o Algoritmo Estendido de Euclides para encontrar o inverso:");
    int mdc = Algoritmo_Estendido_De_Euclides(e, z, &x, &y);
    printf("\n\n   Resultado final do AEE: mdc = %d, x = %d, y = %d", mdc, x, y);
    int d = (x % z + z) % z;

    printf("\n   Ajustando para D ser positivo: D = (%d %% %d + %d) %% %d = %d\n", x, z, z, z, d);

    return d;
}