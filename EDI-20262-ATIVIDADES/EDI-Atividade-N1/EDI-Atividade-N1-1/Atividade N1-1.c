#include <stdio.h>

/* Define a quantidade fixa de alunos da turma */
#define TAMANHO_TURMA 5

void exibirCabecalho(void);
float calcularMedia(float vetor[], int tamanho);
void simularAjuste(float notaOriginal, float bonus);
void aplicarBonus(float *nota, float bonus);

void exibirCabecalho(void) {
    printf("=================================\n");
    printf("SISTEMA DE NOTAS - TURMA ADS\n");
    printf("=================================\n");
}

float calcularMedia(float vetor[], int tamanho) {
    float soma = 0;
    int i;
    
    /* O vetor é passado para a função pelo seu endereço,
       permitindo acessar os elementos originais */

    for(i = 0; i < tamanho; i++){
        soma = soma + vetor[i];
    }
    return soma / tamanho;
}

void simularAjuste(float notaOriginal, float bonus) {
    float novaNota;

    novaNota = notaOriginal + bonus;

    printf("\n--- Simulacao do ajuste (passagem por valor) ---\n");
    printf("Simulacao para o aluno 1: %.2f + %.2f = %.2f (nao aplicado ainda)\n",
           notaOriginal, bonus, novaNota);
}

/* Recebe o endereco da nota para alterar o valor
   original armazenado no vetor */
void aplicarBonus(float *nota, float bonus) {
    *nota = *nota + bonus;
}

int main()
{
    float notas[TAMANHO_TURMA];
    float bonus;
    float mediaInicial;
    float mediaFinal;
    int i;

    exibirCabecalho();

    for(i = 0; i < TAMANHO_TURMA; i++) {
        printf("Nota do aluno %d: ", i + 1 );
        scanf("%f", &notas[i]);
    }

    printf("\nInforme o valor do bonus a aplicar: ");
    scanf("%f", &bonus);

    mediaInicial = calcularMedia(notas, TAMANHO_TURMA);

    printf("\n--- Media da turma antes do ajuste ---\n");
    printf("Media inicial: %.2f\n", mediaInicial);

    simularAjuste(notas[0], bonus);

    printf("Nota do aluno 1 apos a simulacao (inalterada): %.2f\n",
           notas[0]);

    printf("\n--- Aplicacao real do bonus (passagem por referencia) ---\n");

    for(i = 0; i < TAMANHO_TURMA; i++) {
        aplicarBonus(&notas[i], bonus);
    }

    printf("Bonus de %.2f aplicado a todas as notas da turma.\n",
           bonus);

    printf("\n--- Notas finais da turma ---\n");

    for(i = 0; i < TAMANHO_TURMA; i++) {
        printf("Aluno %d: %.2f\n", i + 1, notas[i]);
    }

    mediaFinal = calcularMedia(notas, TAMANHO_TURMA);

    printf("\n--- Media da turma apos o ajuste ---\n");
    printf("Media final: %.2f\n", mediaFinal);

    return 0;
}