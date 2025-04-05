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


int podePosicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;

        switch (direcao) {
            case 'H': c += i; break;           // Horizontal
            case 'V': l += i; break;           // Vertical
            case 'D': l += i; c += i; break;   // Diagonal ↘
            case 'E': l += i; c -= i; break;   // Diagonal ↙
        }


        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
            return 0;

        // Verifica se já existe outro navio
        if (tabuleiro[l][c] == NAVIO)
            return 0;
    }
    return 1;
}


void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;

        switch (direcao) {
            case 'H': c += i; break;
            case 'V': l += i; break;
            case 'D': l += i; c += i; break;
            case 'E': l += i; c -= i; break;
        }

        tabuleiro[l][c] = NAVIO;
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);


    int linhas[4] = {1, 5, 0, 2};
    int colunas[4] = {1, 8, 2, 7};
    char direcoes[4] = {'H', 'V', 'D', 'E'}; // H = horizontal, V = vertical, D = diagonal ↘, E = diagonal ↙


    for (int i = 0; i < 4; i++) {
        if (podePosicionarNavio(tabuleiro, linhas[i], colunas[i], direcoes[i])) {
            posicionarNavio(tabuleiro, linhas[i], colunas[i], direcoes[i]);
        } else {
            printf("Erro: Não foi possível posicionar o navio %d (linha %d, coluna %d, direção %c)\n",
                   i + 1, linhas[i], colunas[i], direcoes[i]);
        }
    }


    exibirTabuleiro(tabuleiro);

    return 0;
}
