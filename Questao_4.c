//==========================================================
//                      AUTORES
//      Gustavo Gomes Fornaciari - 241032519
//      Ana Beatriz Souza Araujo - 241025891
//==========================================================

#include <stdio.h>

// Funcao para calcular o maximo divisor comum (MDC) com exibicao dos passos
int mdcComPassos(int a, int b) {
    int resto;
    int original_a = a;
    int original_b = b;

    printf("Calculando MDC(%d, %d) via Algoritmo de Euclides:\n", a, b);
    // [1] A condicao de parada do Algoritmo de Euclides e quando b se torna 0.
    while (b != 0) {
        resto = a % b;
        printf("  %d mod %d = %d\n", a, b, resto);
        a = b;
        // [2] O antigo b se torna o resto da divisao.
        b = resto;
    }
    printf("MDC(%d, %d) = %d\n", original_a, original_b, a);
    return a;
}

// Funcao para encontrar o inverso modular usando o Algoritmo Estendido de Euclides.
int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a;

    if (m == 1) return 0;

    // Loop principal do Algoritmo Estendido de Euclides
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // [4] Se o inverso x1 for negativo, ajusta para o intervalo [0, m-1].
    if (x1 < 0)
        x1 += m0;

    printf("\nSubstituindo, temos que o inverso de %d em %d eh %d.\n\n", A, m0, x1);
    return x1;
}

// Funcao para calcular a potencia modular (base^exp mod mod) de forma eficiente.
int powMod(int base, int exp, int mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        // [5] Se o expoente e impar, multiplica a base no resultado.
        if (exp % 2 == 1)
            res = (res * b) % mod;
        b = (b * b) % mod;
        exp >>= 1; // Equivale a exp = exp / 2
    }
    return (int)res;
}

int main() {
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

    Verificando se o inverso modular existe...
    Calculando MDC(3, 11) via Algoritmo de Euclides:
      3 mod 11 = 3
      11 mod 3 = 2
      3 mod 2 = 1
      2 mod 1 = 0
    MDC(3, 11) = 1

    O inverso modular existe. Prosseguindo...

    Substituindo, temos que o inverso de 3 em 11 eh 4.

    Fazendo a multiplicacao modular: 7 * 4 mod 11 = 6
    Sendo 4 o inverso de 3
    Valor final da congruencia: 4

    ----------------------------------------------------------

    PARTE 2: RESPOSTAS (VERDADEIRO OU FALSO)
    -------------------------------------------
    1. O algoritmo de Euclides estendido e utilizado para calcular o inverso modular de um numero.
       * V (Verdadeiro). A funcao `inversoModular` implementa este algoritmo para encontrar o inverso.

    2. Se mdc(G,Zn) != 1, o programa ainda consegue encontrar o inverso de G em Zn.
       * F (Falso). Matematicamente, o inverso modular so existe se mdc(G, Zn) = 1, o que o programa agora verifica.

    3. A operacao (H * inverso) % Zn representa a divisao modular de H por G.
       * V (Verdadeiro). Esta e a definicao da divisao no contexto da aritmetica modular.

    4. Se n1 for primo, o codigo aplica o Pequeno Teorema de Fermat para simplificar o calculo de a^x mod n1.
       * F (Falso). A funcao `powMod` usa exponenciacao por quadratura, um metodo geral que funciona para qualquer `n1`.

    5. A funcao powMod implementa o calculo de potencia modular utilizando multiplicacoes diretas sem otimizacao.
       * F (Falso). A funcao implementa a "exponenciacao por quadratura", um metodo altamente otimizado.

    6. Quando o resultado do inverso e negativo, o codigo ajusta o valor somando o modulo m0.
       * V (Verdadeiro). A linha `if (x1 < 0) x1 += m0;` garante que o resultado seja positivo.

    7. O calculo de fi(n1) (funcao totiente de Euler) e utilizado apenas quando n1 nao e primo.
       * F (Falso). A funcao totiente de Euler nao e calculada ou utilizada em nenhuma parte do codigo.
    */

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

    // Adiciona uma checagem de robustez: o inverso so existe se MDC(G, Zn) == 1.
    printf("Verificando se o inverso modular existe...\n");
    int mdc_val = mdcComPassos(G, Zn);
    if (mdc_val != 1) {
        printf("\n[ERRO] O inverso modular de %d mod %d nao existe, pois mdc(%d, %d) = %d != 1.\n", G, Zn, G, Zn, mdc_val);
        return 1; // Encerra o programa com um codigo de erro.
    }
    printf("\nO inverso modular existe. Prosseguindo...\n");

    // [6] Chamada da funcao para encontrar o inverso modular de G.
    int inverso = inversoModular(G, Zn);
    int a = (long long)(H * inverso) % Zn; // Cast para long long para evitar overflow intermediario

    printf("Fazendo a multiplicacao modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    printf("Sendo %d o inverso de %d\n", inverso, G);

    // [7] Chamada da funcao para calcular a potencia modular a^x mod n1.
    int resultado = powMod(a, x, n1);

    printf("Valor final da congruencia: %d\n", resultado);
    return 0;
}