#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3


void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}


void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}


int podePosicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int horizontal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (horizontal ? 0 : i);
        int c = coluna + (horizontal ? i : 0);
        if (l >= TAMANHO_TABULEIRO || c >= TAMANHO_TABULEIRO || tabuleiro[l][c] == NAVIO) {
            return 0; // Não pode posicionar
        }
    }
    return 1; // Pode posicionar
}


void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int horizontal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (horizontal ? 0 : i);
        int c = coluna + (horizontal ? i : 0);
        tabuleiro[l][c] = NAVIO;
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

   
    inicializarTabuleiro(tabuleiro);

   
    int linhaHorizontal = 2, colunaHorizontal = 4;
    int linhaVertical = 5, colunaVertical = 7;

    
    if (podePosicionarNavio(tabuleiro, linhaHorizontal, colunaHorizontal, 1)) {
        posicionarNavio(tabuleiro, linhaHorizontal, colunaHorizontal, 1);
    } else {
        printf("Erro: Não foi possível posicionar o navio horizontal.\n");
    }

    if (podePosicionarNavio(tabuleiro, linhaVertical, colunaVertical, 0)) {
        posicionarNavio(tabuleiro, linhaVertical, colunaVertical, 0);
    } else {
        printf("Erro: Não foi possível posicionar o navio vertical.\n");
    }

    exibirTabuleiro(tabuleiro);

    return 0;
}
