//==========================================================
//                      AUTORES
//      Gustavo Gomes Fornaciari - 241032519
//      Ana Beatriz Souza Araujo - 241025891
//==========================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//==========================================================
//              DECLARAÇÃO DAS FUNÇÕES
//==========================================================

int g(int x, int n);
long long int MDC(long long int a, long long int b, int mostrar);
int eh_primo(long long int p);
long long int potencia_modular(long long int base, long long int exp, long long int mod, int mostrar);
long long int Algoritmo_Estendido_De_Euclides(long long int a, long long int b, long long int *x, long long int *y);
int Fatoracao_Interativa(int n);
long long int inverso_modular(long long int e, long long int z);
long long int divisao_euclidiana(long long int a, long long int b, long long int *q, long long int *r);

//==========================================================
//              PROGRAMA PRINCIPAL
//==========================================================

int main() {
    int n1, n2;
    int p, q;

    printf("====================================================\n");
    printf("    IMPLEMENTACAO DO SISTEMA DE CRIPTOGRAFIA RSA    \n");
    printf("====================================================\n\n");

    // ETAPA 1: FATORAÇÃO
    printf("================ ETAPA 1: Fatoracao (Metodo p de Pollard) =================\n\n");

    // Validação da entrada para N1
    do {
        printf("Digite o primeiro numero composto N1 (entre 100 e 9999): ");
        scanf("%d", &n1);
        if (n1 < 100 || n1 > 9999) {
            printf("[AVISO] O numero deve ter 3 ou 4 digitos. Tente novamente.\n");
        }
    } while (n1 < 100 || n1 > 9999);
    p = Fatoracao_Interativa(n1);

    // Validação da entrada para N2
    do {
        printf("\nDigite o segundo numero composto N2 (entre 100 e 9999): ");
        scanf("%d", &n2);
        if (n2 < 100 || n2 > 9999) {
            printf("[AVISO] O numero deve ter 3 ou 4 digitos. Tente novamente.\n");
        }
    } while (n2 < 100 || n2 > 9999);
    q = Fatoracao_Interativa(n2);

    printf("\n\n....................................................\n");
    printf("Os fatores primos para o RSA foram definidos como:\n");
    printf("p = %d (fator de N1)\n", p);
    printf("q = %d (fator de N2)\n", q);
    printf("....................................................\n\n");

    // ETAPA 2: GERAÇÃO DE CHAVES
    printf("================== ETAPA 2: Geracao das Chaves RSA ===================\n\n");

    long long int n = (long long int)p * q;
    printf("1. Calculo do modulo (n):\n   n = p * q = %d * %d = %lld\n", p, q, n);

    // Validação do módulo 'n' para o sistema de pré-codificação
    if (n <= 36) {
        printf("\n[ERRO FATAL] O modulo n (%lld) eh menor ou igual a 36.\n", n);
        printf("A criptografia nao funcionara pois o alfabeto vai ate Z=36.\n");
        printf("Escolha numeros N1 e N2 que resultem em fatores p e q maiores.\n");
        return 1;
    }

    long long int z = (long long int)(p - 1) * (q - 1);
    printf("\n2. Calculo da Funcao Totiente de Euler (z):\n   z = (p-1)*(q-1) = %d * %d = %lld\n", p - 1, q - 1, z);

    long long int e = 0, d = 0;

    printf("\n3. Escolha do expoente publico (e):\n");
    printf("   Procurando o menor inteiro e > 1 tal que MDC(e, z) = 1\n");
    for(long long int i = 2; i < z; i++){
        if (MDC(i, z, 0) == 1) {
            e = i;
            printf("   O expoente publico 'e' escolhido eh: %lld\n", e);
            break;
        }
    }

    printf("\n4. Calculo do expoente privado (d):");
    d = inverso_modular(e, z);

    printf("\n....................................................\n");
    printf("Chave Publica: (n, e) = (%lld, %lld)\n", n, e);
    printf("Chave Privada: (n, d) = (%lld, %lld)\n", n, d);
    printf("....................................................\n\n");

    int buffer;
    while ((buffer = getchar()) != '\n' && buffer != EOF); // Limpa o buffer de entrada

    // ETAPA 3: CRIPTOGRAFIA E DESCRIPTOGRAFIA
    printf("============== ETAPA 3: Codificacao e Decodificacao ===============\n\n");
    char frase[101];
    printf("Digite a mensagem a ser criptografada: ");
    fgets(frase, sizeof(frase), stdin);
    frase[strcspn(frase, "\n")] = 0; // Remove a nova linha

    int tamanho_msg = strlen(frase);
    long long int *M = malloc(tamanho_msg * sizeof(long long int));
    long long int *C = malloc(tamanho_msg * sizeof(long long int));

    // Pré-codificação
    printf("\n1. Pre-codificacao da mensagem (A=11, ..., Z=36, Espaco=00):\n   ");
    for(int i = 0; i < tamanho_msg; i++){
        char original_char = frase[i];
        if(original_char >= 'a' && original_char <= 'z') original_char -= 32;

        if(original_char == ' ')
            M[i] = 0;
        else if (original_char >= 'A' && original_char <= 'Z')
            M[i] = original_char - 'A' + 11;
        else
            M[i] = 0; // Caracteres não suportados viram espaço
    }

    for (int i = 0; i < tamanho_msg; i++)
        printf("%02lld ", M[i]);
    printf("\n");

    // Processo de Criptografia
    printf("\n\n==================== INICIO DA CRIPTOGRAFIA ====================\n");
    printf("2. Processo de Criptografia (C = M^e mod n)\n");
    for(int i = 0; i < tamanho_msg; i++){
        long long int M_bloco = M[i];
        printf("\n   Criptografando bloco M = %lld:\n", M_bloco);

        // Justificativa da escolha do método de redução de expoente
        if (eh_primo(n)) { // Caso improvável, mas exigido
            printf("     Condicao: n (%lld) eh primo.\n", n);
            printf("     Metodo: Pequeno Teorema de Fermat para reduzir o expoente.\n");
            long long int expoente_reduzido = e % (n - 1);
            printf("     Calculo do expoente reduzido: %lld mod (%lld - 1) = %lld\n", e, n, expoente_reduzido);
            C[i] = potencia_modular(M_bloco, expoente_reduzido, n, 1);
        }
        else if (MDC(M_bloco, n, 0) == 1) { // Caso mais comum
            printf("     Condicao: MDC(M, n) = MDC(%lld, %lld) = 1.\n", M_bloco, n);
            printf("     Metodo: Teorema de Euler para reduzir o expoente.\n");
            long long int expoente_reduzido = e % z; // z = phi(n)
            printf("     Calculo do expoente reduzido: %lld mod %lld (z) = %lld\n", e, z, expoente_reduzido);
            C[i] = potencia_modular(M_bloco, expoente_reduzido, n, 1);
        }
        else { // Caso onde M e n não são coprimos
            printf("     Condicao: MDC(M, n) = MDC(%lld, %lld) != 1.\n", M_bloco, n);
            printf("     Metodo: Teorema da Divisao Euclidiana para reduzir o expoente.\n");
            long long int q_, r_;
            divisao_euclidiana(e, z, &q_, &r_);
            printf("     Calculo: %lld = %lld * %lld + %lld. Novo expoente eh o resto: %lld\n", e, z, q_, r_, r_);
            C[i] = potencia_modular(M_bloco, r_, n, 1);
        }
        printf("\n   Bloco criptografado C = %lld\n", C[i]);
    }

    printf("\n   Mensagem Criptografada Final:\n   ");
    int tamanho_bloco_n = floor(log10(n)) + 1;
    for (int i = 0; i < tamanho_msg; i++)
        printf("%0*lld ", tamanho_bloco_n, C[i]);
    printf("\n");
    printf("===================== FIM DA CRIPTOGRAFIA =====================\n");

    // >>>>>>>>>> PAUSA INTERATIVA <<<<<<<<<<
    printf("\n\nPressione ENTER para iniciar a decodificacao...");
    getchar(); // Pausa e espera o usuário pressionar Enter

    // Processo de Descriptografia
    long long int *M_decifrado = malloc(tamanho_msg * sizeof(long long int));
    char *frase_decifrada = malloc(tamanho_msg + 1);

    printf("\n\n=================== INICIO DA DESCRIPTOGRAFIA ==================\n");
    printf("3. Processo de Descriptografia (M = C^d mod n)\n");
    for (int i = 0; i < tamanho_msg; i++){
        long long int C_bloco = C[i];
        printf("\n   Descriptografando bloco C = %lld:\n", C_bloco);

        // Justificativa da escolha do método de redução de expoente (espelhado da criptografia)
        if (eh_primo(n)) {
            printf("     Condicao: n (%lld) eh primo.\n", n);
            printf("     Metodo: Pequeno Teorema de Fermat para reduzir o expoente.\n");
            long long int expoente_reduzido = d % (n - 1);
            printf("     Calculo do expoente reduzido: %lld mod (%lld - 1) = %lld\n", d, n, expoente_reduzido);
            M_decifrado[i] = potencia_modular(C_bloco, expoente_reduzido, n, 1);
        }
        else if (MDC(C_bloco, n, 0) == 1) {
            printf("     Condicao: MDC(C, n) = MDC(%lld, %lld) = 1.\n", C_bloco, n);
            printf("     Metodo: Teorema de Euler para reduzir o expoente.\n");
            long long int expoente_reduzido = d % z;
            printf("     Calculo do expoente reduzido: %lld mod %lld (z) = %lld\n", d, z, expoente_reduzido);
            M_decifrado[i] = potencia_modular(C_bloco, expoente_reduzido, n, 1);
        }
        else {
            printf("     Condicao: MDC(C, n) = MDC(%lld, %lld) != 1.\n", C_bloco, n);
            printf("     Metodo: Teorema da Divisao Euclidiana para reduzir o expoente.\n");
            long long int q_, r_;
            divisao_euclidiana(d, z, &q_, &r_);
            printf("     Calculo: %lld = %lld * %lld + %lld. Novo expoente eh o resto: %lld\n", d, z, q_, r_, r_);
            M_decifrado[i] = potencia_modular(C_bloco, r_, n, 1);
        }
        printf("\n   Bloco descriptografado M = %lld\n", M_decifrado[i]);
    }
    printf("==================== FIM DA DESCRIPTOGRAFIA ==================\n");

    // Pós-decodificação
    for(int i = 0; i < tamanho_msg; i++){
        if(M_decifrado[i] == 0)
            frase_decifrada[i] = ' ';
        else
            frase_decifrada[i] = M_decifrado[i] - 11 + 'A';
    }
    frase_decifrada[tamanho_msg] = '\0';

    printf("\n\n====================== RESULTADO FINAL =======================\n\n");
    printf("Mensagem Original:    %s\n", frase);
    printf("Mensagem Decifrada:   %s\n\n", frase_decifrada);

    if(strcmp(frase, frase_decifrada) == 0)
        printf("[SUCESSO] A mensagem decifrada e identica a original!\n");
    else
        printf("[ERRO] A mensagem decifrada e diferente da original!\n");
    printf("============================================================\n");

    free(M);
    free(C);
    free(M_decifrado);
    free(frase_decifrada);
    return 0;
}

//==========================================================
//              DEFINIÇÃO DAS FUNÇÕES
//==========================================================

// Função de iteração para o método p de Pollard
int g(int x, int n){
    long long int val = (long long int)x * x + 1;
    int resultado = val % n;
    printf("      g(%d) = (%d^2 + 1) mod %d = %d\n", x, x, n, resultado);
    return resultado;
}

// Algoritmo de Euclides para calcular o Máximo Divisor Comum (MDC)
long long int MDC(long long int a, long long int b, int mostrar){
    if(mostrar == 1)
        printf("    Calculando MDC(%lld, %lld) via Algoritmo de Euclides:\n", a , b);

    long long int original_a = a;
    long long int original_b = b;

    while(b != 0){
        long long int quociente = a / b;
        long long int resto = a % b;
        if(mostrar == 1)
            printf("        %lld = %lld * %lld + %lld\n", a, b, quociente, resto);
        a = b;
        b = resto;
    }
    if(mostrar == 1)
        printf("    MDC(%lld, %lld) = %lld\n", original_a, original_b, a);
    return a;
}

// Função para verificar se um número é primo
int eh_primo(long long int p){
    if(p <= 1) return 0;
    if(p <= 3) return 1;
    if(p % 2 == 0 || p % 3 == 0) return 0;
    for(long long int i = 5; i * i <= p; i = i + 6){
        if(p % i == 0 || p % (i + 2) == 0) return 0;
    }
    return 1;
}

// Exponenciação modular rápida
long long int potencia_modular(long long int base, long long int exp, long long int mod, int mostrar) {
    long long int resultado = 1;
    long long int original_exp = exp;
    base %= mod;

    if (mostrar) {
        printf("\n     Exponenciacao modular para (%lld ^ %lld) mod %lld:\n", base, original_exp, mod);
        printf("     Estado Inicial: res = 1, base = %lld, exp = %lld\n", base, exp);
    }

    int passo = 1;
    while (exp > 0) {
        if (exp % 2 == 1) { // Expoente Ímpar
            if(mostrar) {
                printf("\n     Passo %d (exp = %lld, impar):\n", passo, exp);
                printf("       Resultado eh multiplicado pela base: res = (%lld * %lld) %% %lld = ", resultado, base, mod);
            }
            resultado = (resultado * base) % mod;
            if(mostrar) printf("%lld\n", resultado);

        } else if(mostrar) { // Expoente Par
            printf("\n     Passo %d (exp = %lld, par):\n", passo, exp);
            printf("       Resultado nao muda.\n");
        }

        exp >>= 1; // exp = exp / 2

        // Apenas mostra a atualização da base se houver uma próxima iteração
        if (exp > 0) {
            if(mostrar) printf("       Base eh elevada ao quadrado: base = (%lld^2) %% %lld = ", base, mod);
            base = (base * base) % mod;
            if(mostrar) printf("%lld\n", base);
            if(mostrar) printf("       Expoente atualizado para a proxima iteracao: %lld\n", exp);
        }
        passo++;
    }
    return resultado;
}

// Implementação recursiva do Algoritmo Estendido de Euclides
long long int Algoritmo_Estendido_De_Euclides(long long int a, long long int b, long long int *x, long long int *y){
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    long long int x1, y1;
    long long int mdc = Algoritmo_Estendido_De_Euclides(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return mdc;
}

// Método p de Pollard para encontrar um fator não trivial de n
int Fatoracao_Interativa(int n){
    if (n % 2 == 0) return 2;
    int tartaruga = 2, lebre = 2; int d = 1;
    printf("\nFatorando N = %d (semente x0 = 2):\n", n);
    int iteracao = 1;
    while(d == 1){
        printf("\n   Iteracao %d:\n", iteracao++);
        printf("     Tartaruga:\n");
        tartaruga = g(tartaruga, n);
        printf("     Lebre:\n");
        lebre =  g(g(lebre, n), n);
        printf("     MDC(|%d - %d|, %d):\n", tartaruga, lebre, n);
        d = MDC(abs(tartaruga - lebre), n, 1);

        if(d > 1 && d < n){
            printf("\n   Fator nao trivial de %d encontrado: %d\n", n, d);
        } else if (d == n) {
             printf("\n[ERRO] Falha na fatoracao com a semente atual. O metodo encontrou N.\n");
             exit(1);
        }
    }
    return d;
}

// Função para encontrar o inverso modular
long long int inverso_modular(long long int e, long long int z){
    long long int x, y;
    printf("\n   Usando o Algoritmo Estendido de Euclides para encontrar o inverso de %lld mod %lld.\n", e, z);
    long long int mdc = Algoritmo_Estendido_De_Euclides(e, z, &x, &y);

    if(mdc != 1){
        printf("\n   [ERRO] Inverso modular nao existe pois E e z nao sao coprimos (MDC != 1).\n");
        exit(1);
    }

    // Garante que o resultado seja positivo
    long long int d = (x % z + z) % z;
    printf("   O inverso modular (d) eh: %lld\n", d);
    return d;
}

// Implementa a divisão euclidiana
long long int divisao_euclidiana(long long int a, long long int b, long long int *q, long long int *r) {
    if (b == 0) return 0; // Evita divisão por zero
    *q = a / b;
    *r = a % b;
    // Ajuste para resto negativo
    if (*r < 0) {
        *r += b;
        (*q)--;
    }
    return 1;
}