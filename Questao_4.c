//==========================================================
//                      AUTORES
//      Gustavo Gomes Fornaciari - 241032519
//      Ana Beatriz Souza Araujo - 241025891
//==========================================================

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Função para calcular o máximo divisor comum (MDC) com exibição dos passos
int mdcComPassos(int a, int b) {
    int resto;
    // [1] O laço 'while' do Algoritmo de Euclides continua até o divisor (b) ser 0.
    while (b != 0) {
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        // [2] O próximo divisor 'b' se torna o 'resto' da divisão anterior.
        b = resto;
    }
    return a;
}
int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    // [3] Chamada da função MDC, conforme template
    mdcComPassos(a, m);

    while (m != 0) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    // [4] Se o inverso 'x1' for negativo, ajusta para o representante positivo.
    if (x1 < 0)
        x1 += m0; 
        
    printf("\nSubstituindo, temos que o inverso de %d em %d é %d.\n\n", A, B, x1);
    return x1;
}

int powMod(int base, int exp, int mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        // [5] Se o expoente 'exp' for ímpar, multiplica o resultado pela base.
        if (exp % 2 == 1) 
            res = (res * b) % mod;
        b = (b * b) % mod;
        exp >>= 1;
    }
    return (int)res;
}
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int H, G, Zn, x, n1;

    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x);
    printf("Insira n1: ");
    scanf("%d", &n1);
    printf("\n");

    // [6] Chama a função para encontrar o inverso modular
    int inverso = inversoModular(G, Zn); 
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicação modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    printf(" Sendo %d o inverso de %d.\n", inverso, G);

    // [7] Chama a função de exponenciação modular
    int resultado = powMod(a, x, n1); 
    printf("Valor final da congruência: %d\n", resultado);

    return 0;
}

/*
    ==========================================================
                    SOLUCAO COMPLETA - QUESTAO 4
    ==========================================================

    PARTE 1: SAIDA DO PROGRAMA (COM VALORES H=7, G=3, Zn=11, x=10, n1=13)
    ---------------------------------------------------------------------
    Insira H: 7 
    Insira G: 3
    Insira Zn: 11
    Insira x: 10
    Insira n1: 13

    Algoritmo de Euclides: 3 mod 11 = 3
    Algoritmo de Euclides: 11 mod 3 = 2
    Algoritmo de Euclides: 3 mod 2 = 1
    Algoritmo de Euclides: 2 mod 1 = 0

    Substituindo, temos que o inverso de 3 em 11 é 4.

    Fazendo a multiplicação modular: 7 * 4 mod 11 = 6
    Sendo 4 o inverso de 3.
    Valor final da congruência: 4

    ----------------------------------------------------------

    PARTE 2: RESPOSTAS (VERDADEIRO OU FALSO)
    -------------------------------------------
    1. O algoritmo de Euclides estendido e utilizado para calcular o inverso modular de um numero.
       * V

    2. Se mdc(G,Zn) != 1, o programa ainda consegue encontrar o inverso de G em Zn.
       * F

    3. A operacao (H * inverso) % Zn representa a divisao modular de H por G.
       * V

    4. Se n1 for primo, o codigo aplica o Pequeno Teorema de Fermat para simplificar o calculo de a^x mod n1.
       * V

    5. A funcao powMod implementa o calculo de potencia modular utilizando multiplicacoes diretas sem otimizacao.
       * F 

    6. Quando o resultado do inverso e negativo, o codigo ajusta o valor somando o modulo m0.
       * V 

    7. O calculo de fi(n1) (funcao totiente de Euler) e utilizado apenas quando n1 nao e primo.
       * F 
    */