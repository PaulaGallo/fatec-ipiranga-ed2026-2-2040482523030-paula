/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*
* Disciplina : Estrutura de Dados *
* Prof . Verissimo *
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*
* Objetivo do Programa : Alocação Dinâmica de Memória e Recursividade em Linguagem C *
* (vetor alocado dinamicamente com malloc, percorrido e processado por meio de funções recursivas) *
* Data - 29 / 08 / 2026 *
* Autor : Paula Fernanda Gallo Silva *
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define VALOR_PREMIUM 100.0

void exibirCabecalho(void) {
	printf ("=================================\n");
    printf ("LAVA-RAPIDO BRILHO TOTAL - FILA DE ATENDIMENTO\n");
    printf ("=================================\n");
}

typedef struct {
    char placa[8];
    float valor;
} Veiculo;

void preencherFrota(Veiculo *frota, int quantidade){
    for (int i = 0; i<quantidade; i++){
        printf ("Placa do veiculo %d: ", i+1);
        scanf ("%s", (frota + i)->placa);
        
        printf("Valor do servico (R$): ");
        scanf ("%f", &(frota +i)->valor);
    }
}

void exibirFrotaRecursivo(Veiculo *frota, int indice, int quantidade) {
        if (indice >= quantidade) {
        return;
    }

    printf("%d) Placa: %s | Valor: R$ %.2f\n", 
           indice + 1, 
           frota[indice].placa, 
           frota[indice].valor);

    exibirFrotaRecursivo(frota, indice + 1, quantidade);
}

float calcularValorTotalRecursivo(Veiculo *frota, int indice, int quantidade) {
    // Caso Base: se o índice atingiu o fim do vetor, a soma restante é 0
    if (indice >= quantidade) {
        return 0.0f;
    }

    // Passo Recursivo: valor do elemento atual + soma dos elementos restantes
    return frota[indice].valor + calcularValorTotalRecursivo(frota, indice + 1, quantidade);
}


int buscarVeiculoRecursivo(Veiculo *frota, int indice, int quantidade, char placa[8]) {
    // Caso Base 1: percorreu todo o vetor e não encontrou a placa
    if (indice >= quantidade) {
        return -1;
    }

    // Caso Base 2: encontrou a placa no índice atual
    if (strcmp(frota[indice].placa, placa) == 0) {
        return indice;
    }

    // Passo Recursivo: avança para a próxima posição do índice
    return buscarVeiculoRecursivo(frota, indice + 1, quantidade, placa);
}

int contarPremiumRecursivo(Veiculo *frota, int indice, int quantidade) {
    if (indice >= quantidade) {
        return 0;
    }

    // Passo recursivo: se for premium, soma 1; senão, soma 0
    if (frota[indice].valor >= VALOR_PREMIUM) {
        return 1 + contarPremiumRecursivo(frota, indice + 1, quantidade);
    } else {
        return 0 + contarPremiumRecursivo(frota, indice + 1, quantidade);
    }
}

int main()
{
    int quantidade;
    
	exibirCabecalho();
	
	printf("Quantos veiculos serao atendidos hoje? ");
    scanf("%d", &quantidade);
    
    Veiculo *frota = (Veiculo *) malloc(quantidade * sizeof(Veiculo));

    if (frota == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }
    
    preencherFrota(frota, quantidade);
    
    printf("\n--- Veiculos atendidos hoje ---\n");
    exibirFrotaRecursivo(frota, 0, quantidade);
    
    char placaBusca[8];
    printf("\n--- Busca recursiva por placa ---\n");
    printf("Placa a ser pesquisada: ");
    scanf("%s", placaBusca);

    int pos = buscarVeiculoRecursivo(frota, 0, quantidade, placaBusca);

    if (pos != -1) {
        printf("Veiculo encontrado na posicao %d! Placa: %s | Valor: R$ %.2f\n", 
               pos + 1, frota[pos].placa, frota[pos].valor);
    } else {
        printf("Veiculo nao encontrado na frota.\n");
    }

    int qtdPremium = contarPremiumRecursivo(frota, 0, quantidade);
    float total = calcularValorTotalRecursivo(frota, 0, quantidade);
        printf("\n--- Resumo do dia ---\n");
        printf("Total de veiculos atendidos: %d\n", quantidade);
        printf("Servicos premium (>= R$ 100.00): %d\n", qtdPremium);
        printf("Valor total arrecadado: R$ %.2f\n", total);

    free(frota);
    frota = NULL;
    
    printf("\nMemoria da frota liberada com sucesso. Sistema encerrado.\n");
    
	return 0;
}

