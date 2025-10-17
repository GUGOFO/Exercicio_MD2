//==========================================================
//                      AUTORES
//      Gustavo Gomes Fornaciari - 241032519
//      Ana Beatriz Souza Araujo - 241025891
//==========================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void limpar_buffer(void);
unsigned long long pow_ull(unsigned long long base, int exp);

//==========================================================
//              PROGRAMA PRINCIPAL
//==========================================================

int main(void) {
    printf("====================================================\n");
    printf("     QUESTAO 03: A RAZAO DE EFICIENCIA DE UM NUMERO\n");
    printf("====================================================\n\n");

    int N;
    // Garante que a entrada do usuario seja um numero valido dentro do intervalo.
    do {
        printf("Digite um numero N (entre 1 e 100000): ");
        if (scanf("%d", &N) != 1) {
            limpar_buffer();
            N = 0;
        }
        if (N < 1 || N > 100000) {
            printf("[AVISO] O numero deve estar entre 1 e 100000. Tente novamente.\n\n");
        }
    } while (N < 1 || N > 100000);

    printf("\n================== PASSO 1: FATORACAO PRIMA ==================\n\n");
    printf("Decompondo N = %d em seus fatores primos (Metodo: Trial Division)\n\n", N);

    int n = N;
    // Armazena fatores e expoentes em arrays.
    // Para N <= 100000, o numero de fatores primos distintos e pequeno.
    int primes[32];
    int exps[32];
    int pf_count = 0;

    // Caso especial: N = 1 nao tem fatores primos e suas funcoes tau e sigma sao 1.
    if (n == 1) {
        printf("   Observacao: N = 1. O numero 1 nao possui fatores primos.\n");
        printf("\n============ PASSO 2: CALCULO DE TAU E SIGMA ============\n\n");
        printf("   tau(1) = 1\n");
        printf("   sigma(1) = 1\n");
        printf("\n===================== RESULTADO FINAL =====================\n\n");
        printf("A Razao de Eficiencia (sigma(1) / tau(1)) de 1 eh:\n\n");
        printf("   ***********************\n");
        printf("   * Razao: %-12.2f *\n", 1.00);
        printf("   ***********************\n");
        printf("\n===========================================================\n");
        return 0;
    }

    // Otimizacao: remove todos os fatores 2 de n.
    int count = 0;
    while (n % 2 == 0) {
        count++;
        n /= 2;
    }
    if (count > 0) {
        primes[pf_count] = 2;
        exps[pf_count] = count;
        pf_count++;
        printf("   Fator: 2, Expoente: %d\n", count);
    }

    // Procura por fatores impares a partir de 3, ate a raiz quadrada de n.
    for (int p = 3; (long long)p * p <= n; p += 2) {
        count = 0;
        while (n % p == 0) {
            count++;
            n /= p;
        }
        if (count > 0) {
            primes[pf_count] = p;
            exps[pf_count] = count;
            pf_count++;
            printf("   Fator: %d, Expoente: %d\n", p, count);
        }
    }

    // Se 'n' ainda for maior que 1, o valor restante e um fator primo.
    if (n > 1) {
        primes[pf_count] = n;
        exps[pf_count] = 1;
        pf_count++;
        printf("   Fator: %d, Expoente: 1\n", n, 1);
    }

    printf("\nResumo da fatoracao de %d:\n", N);
    for (int i = 0; i < pf_count; i++) {
        printf("   p_%d = %d, a_%d = %d\n", i + 1, primes[i], i + 1, exps[i]);
    }

    printf("\n\n============ PASSO 2: CALCULO DE TAU E SIGMA ============\n\n");
    
    // tau(N) e o produto de (expoente + 1) para cada fator primo.
    unsigned long long tau = 1ULL;
    for (int i = 0; i < pf_count; i++) {
        tau *= (unsigned long long)(exps[i] + 1);
    }
    printf("1) tau(N): Numero de divisores de N.\n");
    printf("   Aplicando tau(N) = (a1 + 1) * (a2 + 1) * ...\n");
    printf("   tau(%d) = ", N);
    for (int i = 0; i < pf_count; i++) {
        if (i > 0) printf(" * ");
        printf("(%d+1)", exps[i]);
    }
    printf(" = %llu\n\n", tau);

    // sigma(N) e o produto dos termos calculados pela formula para cada fator primo.
    unsigned long long sigma = 1ULL;
    printf("2) sigma(N): Soma dos divisores de N.\n");
    printf("   Aplicando sigma(N) = PROD [ (p^(a+1) - 1) / (p - 1) ]\n");
    for (int i = 0; i < pf_count; i++) {
        unsigned long long p = (unsigned long long)primes[i];
        int a = exps[i];
        unsigned long long p_pow = pow_ull(p, a + 1);
        unsigned long long numer = p_pow - 1ULL;
        unsigned long long denom = p - 1ULL;
        unsigned long long termo = numer / denom;
        printf("   Para p=%llu, a=%d: termo = ((%llu^%d)-1)/(%llu-1) = %llu\n", p, a, p, a + 1, p, termo);
        sigma *= termo;
    }
    printf("\n   sigma(%d) = %llu\n", N, sigma);

    double razao = (double)sigma / (double)tau;

    printf("\n\n===================== RESULTADO FINAL =====================\n\n");
    printf("A Razao de Eficiencia (sigma(N) / tau(N)) de %d eh:\n\n", N);
    printf("   ***********************\n");
    printf("   * Razao: %-12.2f *\n", razao);
    printf("   ***********************\n");
    printf("\n===========================================================\n");

    return 0;
}

//==========================================================
//              DEFINICAO DAS FUNCOES
//==========================================================

// Calcula base^exp de forma eficiente usando exponenciacao por quadratura.
unsigned long long pow_ull(unsigned long long base, int exp) {
    unsigned long long res = 1ULL;
    while (exp > 0) {
        if (exp % 2 == 1) res *= base;
        base *= base;
        exp /= 2;
    }
    return res;
}

// Limpa o buffer de entrada (stdin) para evitar erros de leitura.
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}