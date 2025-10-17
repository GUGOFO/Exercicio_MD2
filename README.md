# MD2

Este repositório contém as implementações em C para a atividade prática da disciplina de Matemática Discreta II.

**Autores:**
* Gustavo Gomes Fornaciari - 241032519
* Ana Beatriz Souza Araujo - 241025891

## Como Compilar e Executar

Você pode compilar e executar os arquivos de duas maneiras principais.

### 1. Via Terminal (CMD / PowerShell com GCC)

Este método requer que você tenha um compilador C como o GCC (MinGW no Windows) instalado e configurado no PATH do seu sistema.

1.  Abra o terminal na pasta onde os arquivos `.c` estão localizados.
2.  Compile o programa desejado usando o comando `gcc`.
3.  Execute o arquivo gerado.

**Comandos:**

```bash
# Para compilar a Questao 1 (o -lm é necessário por causa da biblioteca math.h)
gcc -o Questao_1 Questao_1.c -lm

# Para executar
./Questao_1

# Para compilar a Questao 2
gcc -o Questao_2 Questao_2.c

# Para executar
./Questao_2

# Para compilar a Questao 3 (o -lm é necessário)
gcc -o Questao_3 Questao_3.c -lm

# Para executar
./Questao_3

# Para compilar a Questao 4
gcc -o Questao_4 Questao_4.c

# Para executar
./Questao_4
2. Via Visual Studio Code
Este método é mais simples se você tiver o ambiente configurado.

Pré-requisitos:

Tenha o VS Code instalado.

Tenha um compilador C (como o MinGW) instalado.

Instale a extensão "C/C++" da Microsoft no VS Code.

Passos para Executar:

Abra a pasta do projeto no VS Code.

Abra o arquivo .c que deseja executar (ex: Questao_1.c).

Abra o terminal integrado do VS Code (atalho: Ctrl + ').

Use os mesmos comandos de compilação e execução da seção anterior.

Descrição das Questões e Exemplos de Entrada
Aqui está um resumo do que cada programa faz, com exemplos de entradas que você pode usar para testar.

Questão 1: Sistema de Criptografia RSA
O que faz: Implementa o sistema criptográfico RSA completo, desde a fatoração de números para gerar as chaves até a codificação e decodificação de uma mensagem.

Exemplo de Entrada:

Digite o primeiro numero composto N1: 143
Digite o segundo numero composto N2: 221
Digite a mensagem a ser criptografada: OLA MUNDO
Questão 2: Chaves Periódicas
O que faz: Calcula o primeiro ano (o Mínimo Múltiplo Comum) em que um conjunto de chaves com ciclos de ativação diferentes estarão ativas simultaneamente.

Exemplo de Entrada:

Digite o numero de chaves: 3
Digite os 3 ciclos de ativacao: 2 3 5 (Resultado esperado: 30)
Questão 3: A Razão de Eficiência de um Número
O que faz: Calcula a "Razão de Eficiência" de um número N, que é a soma de seus divisores dividida pela quantidade de seus divisores.

Exemplo de Entrada:

Digite um numero N: 100
Questão 4: Divisão Modular e Congruência
O que faz: Resolve uma série de operações de aritmética modular, incluindo o cálculo do inverso modular e a exponenciação modular.

Exemplo de Entrada (valores fixos do enunciado):

Insira H: 7
Insira G: 3
Insira Zn: 11
Insira x: 10
Insira n1: 13