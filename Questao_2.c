//==========================================================
//                      AUTORES
//      Gustavo Gomes Fornaciari - 241032519
//      Ana Beatriz Souza Araujo - 241025891
//==========================================================

#include <stdio.h>
#include <stdlib.h>

//==========================================================
//              DECLARACAO DAS FUNCOES
//==========================================================

long long int MDC(long long int a, long long int b, int mostrar);
long long int MMC(long long int a, long long int b);
void limpar_buffer();

//==========================================================
//              PROGRAMA PRINCIPAL
//==========================================================

int main() {
    // Titulo do Programa
    printf("====================================================\n");
    printf("          QUESTAO 02: CHAVES PERIODICAS\n");
    printf("====================================================\n\n");

    // Entrada do numero de chaves (N) com validacao
    int N;
    do {
        printf("Digite o numero de chaves (N, entre 1 e 10): ");
        if (scanf("%d", &N) != 1) {
            limpar_buffer();
            N = 0; // Forca a repeticao do loop
        }
        if (N < 1 || N > 10) {
            printf("[AVISO] O numero de chaves deve estar entre 1 e 10. Tente novamente.\n\n");
        }
    } while (N < 1 || N > 10);

    // Entrada dos ciclos de ativacao com validacao
    long long int ciclos[10];
    printf("\nDigite os %d ciclos de ativacao (C_i, entre 2 e 20), separados por espaco:\n> ", N);
    int entrada_valida = 1;
    for (int i = 0; i < N; i++) {
        if (scanf("%lld", &ciclos[i]) != 1) {
            limpar_buffer();
            entrada_valida = 0;
            break; // Sai do loop se a entrada for invalida
        }
        if (ciclos[i] < 2 || ciclos[i] > 20) {
            printf("[AVISO] O ciclo %lld esta fora do intervalo permitido (2 a 20).\n", ciclos[i]);
            entrada_valida = 0;
        }
    }

    if (!entrada_valida) {
        printf("\nPor favor, reinicie o programa com valores validos.\n");
        return 1; // Encerra se a entrada for invalida
    }

    printf("\n================== INICIO DO CALCULO ==================\n\n");
    printf("Objetivo: Encontrar o Menor Multiplo Comum (MMC) de todos os ciclos.\n");
    printf("O MMC representa o primeiro ano em que todas as chaves estao ativas simultaneamente.\n\n");

    // Calculo iterativo do MMC
    long long int mmc_atual = ciclos[0];
    printf("Passo 1: O calculo comeca com o ciclo da primeira chave.\n   MMC inicial = %lld\n", mmc_atual);

    for (int i = 1; i < N; i++) {
        long long int proximo_ciclo = ciclos[i];
        printf("\nPasso %d: Calculando o MMC entre o resultado anterior (%lld) e o proximo ciclo (%lld).\n", i + 1, mmc_atual, proximo_ciclo);
        mmc_atual = MMC(mmc_atual, proximo_ciclo);
        printf("   MMC atualizado para: %lld\n", mmc_atual);

        // Interpretacao didatica
        printf("      Isso significa que o conjunto de chaves analisado ate agora se alinha a cada %lld anos.\n", mmc_atual);
    }

    long long int mmc_final = mmc_atual;

    // Exibicao do resultado final
    printf("\n===================== RESULTADO FINAL =====================\n\n");
    printf("O Menor Multiplo Comum (MMC) de todos os ciclos eh: %lld.\n\n", mmc_final);

    if (mmc_final > 50) {
        printf("Este valor eh maior que o limite de 50 anos estipulado no problema.\n");
        printf("[IMPOSSIBILIDADE] Nao ha um ano valido para o uso simultaneo de todas as chaves.\n");
    } else {
        printf("O primeiro ano futuro (maior que 0 e dentro do limite de 50) em que todas\n");
        printf("as chaves podem ser utilizadas simultaneamente eh:\n\n");
        printf("   ****************\n");
        printf("   * ANO: %-4lld  *\n", mmc_final);
        printf("   ****************\n\n");
        printf("Interpretacao: apos %lld anos, todas as chaves atingirao novamente o mesmo\n", mmc_final);
        printf("ponto de ativacao, funcionando simultaneamente no mesmo ano.\n");
    }
    printf("\n===========================================================\n");

    return 0;
}


//==========================================================
//              DEFINICAO DAS FUNCOES
//==========================================================

// Calcula o Maximo Divisor Comum (MDC) usando o Algoritmo de Euclides.
long long int MDC(long long int a, long long int b, int mostrar){
    if(mostrar == 1)
        printf("   Calculando MDC(%lld, %lld) via Algoritmo de Euclides:\n", a , b);

    long long int original_a = a;
    long long int original_b = b;

    while(b != 0){
        long long int quociente = a / b;
        long long int resto = a % b;
        if(mostrar == 1)
            printf("      %lld = %lld * %lld + %lld\n", a, b, quociente, resto);
        a = b;
        b = resto;
    }
    if(mostrar == 1)
        printf("   MDC(%lld, %lld) = %lld\n", original_a, original_b, a);
    return a;
}

// Calcula o Minimo Multiplo Comum (MMC) usando a formula baseada no MDC.
long long int MMC(long long int a, long long int b) {
    if (a == 0 || b == 0) return 0;
    
    long long int mdc_val = MDC(a, b, 1);

    long long int mmc_val = (a / mdc_val) * b;
    printf("   Calculando MMC(%lld, %lld) pela formula: (%lld * %lld) / %lld = %lld\n", a, b, a, b, mdc_val, mmc_val);
    
    return mmc_val;
}

// Limpa o buffer de entrada (stdin) para evitar erros de leitura.
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


