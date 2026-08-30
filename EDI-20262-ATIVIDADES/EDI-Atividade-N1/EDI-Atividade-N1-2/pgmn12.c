#include <stdio.h>

#define TAMANHO_ESTOQUE 5
#define ESTOQUE_MINIMO 10

int estoque[TAMANHO_ESTOQUE];

void exibirCabecalho(void) {
    printf("SISTEMA DE ESTOQUE LOJA CONSTRUMAIS\n");
}

void preencherEstoque(void) {
    int *p = estoque;
    int i;
    for (i = 0; i < TAMANHO_ESTOQUE; i++) {
        printf("Quantidade do produto %d: ", i + 1);
        scanf("%d", p + i); /* (p + i) é o endereço de memória do elemento */
    }
}

void exibirEstoque(int momento) {
    int *p = estoque;
    int i;
    
    if (momento == 0) {
        printf("\n-- Estoque atual (antes da reposicao) --\n");
    } else {
        printf("\n-- Estoque final (apos reposicao) --\n");
    }

    for (i = 0; i < TAMANHO_ESTOQUE; i++) {
        printf("Produto %d: %d unidades\n", i + 1, *(p + i));
    }
}

float calcularMediaEstoque(void) {
    int *p = estoque;
    int soma = 0;
    int i;

    for (i = 0; i < TAMANHO_ESTOQUE; i++) {
        /*'p + i' representa o ENDEREÇO DE MEMÓRIA da posição 'i'.
         '*(p + i)' representa o VALOR ARMAZENADO no endereço da posição 'i'. */
        
        soma = soma + *(p + i);
    }

    return (float)soma / TAMANHO_ESTOQUE;
}

void simularReposicao(int quantidadeAtual, int reposicao) {
    int resultado = quantidadeAtual + reposicao;
    printf("Simulacao para o produto 1: %d + %d = %d (nao aplicado ainda)\n", 
            quantidadeAtual, reposicao, resultado);
}

void aplicarReposicaoGeral(int reposicao) {
    int *p = estoque;
    int i;
    
    for (i = 0; i < TAMANHO_ESTOQUE; i++) {
            *(p + i) = *(p + i) + reposicao;
    }
}

void identificarEstoqueCritico(int minimo) {
    int *p = estoque;
    int criticos = 0;
    int i;

    printf("\n-- Analise de estoque critico (minimo = %d unidades) --\n", minimo);

    for (i = 0; i < TAMANHO_ESTOQUE; i++) {
        if (*(p + i) < minimo) {
            printf("Produto %d esta em nivel critico: %d unidades (abaixo do minimo)\n", 
                    i + 1, *(p + i));
            criticos = criticos + 1; 
        }
    }

    if (criticos == 0) {
        printf("Estoque regularizado.\n");
    }
}

int main(void) {
    int reposicao;

    exibirCabecalho();

    preencherEstoque();

    printf("Quantidade de reposicao a aplicar: ");
    scanf("%d", &reposicao);

    exibirEstoque(0);

    printf("\n-- Simulacao de reposicao (passagem por valor) --\n");
    simularReposicao(estoque[0], reposicao);
    printf("Quantidade do produto 1 apos a simulacao (inalterada): %d\n", estoque[0]);

    printf("\n-- Aplicacao real da reposicao (ponteiro interno ao vetor global) --\n");
    aplicarReposicaoGeral(reposicao);
    printf("Reposicao de %d unidades aplicada a todos os produtos do estoque.\n", reposicao);

    exibirEstoque(1);

    printf("\n-- Media geral do estoque --\n");
    printf("Media final: %.2f unidades\n", calcularMediaEstoque());

    identificarEstoqueCritico(ESTOQUE_MINIMO);

    return 0;
}
