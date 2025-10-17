# Trabalho de Matemática Discreta II - Implementações em C

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