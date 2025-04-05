#include <stdio.h>

#define TAM 10
#define TAM_NAVIO 3
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5
#define TAM_HABILIDADE 5


void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;
}


void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf(". ");
            else if (tabuleiro[i][j] == NAVIO)
                printf("N ");
            else if (tabuleiro[i][j] == HABILIDADE)
                printf("* ");
            else
                printf("? ");
        }
        printf("\n");
    }
}


int podePosicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;
        switch (direcao) {
            case 'H': c += i; break;
            case 'V': l += i; break;
            case 'D': l += i; c += i; break;
            case 'E': l += i; c -= i; break;
        }
        if (l < 0 || l >= TAM || c < 0 || c >= TAM || tabuleiro[l][c] == NAVIO)
            return 0;
    }
    return 1;
}

void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
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


void gerarCone(int cone[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int centro = TAM_HABILIDADE / 2;
            cone[i][j] = (j >= centro - i && j <= centro + i) ? 1 : 0;
        }
    }
}


void gerarCruz(int cruz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            cruz[i][j] = (i == centro || j == centro) ? 1 : 0;
        }
    }
}


void gerarOctaedro(int octaedro[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int dist = abs(i - centro) + abs(j - centro);
            octaedro[i][j] = (dist <= centro) ? 1 : 0;
        }
    }
}


void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    int offset = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int l = origemLinha - offset + i;
                int c = origemColuna - offset + j;
                if (l >= 0 && l < TAM && c >= 0 && c < TAM && tabuleiro[l][c] == AGUA)
                    tabuleiro[l][c] = HABILIDADE;
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

   
    int linhas[4] = {1, 5, 0, 2};
    int colunas[4] = {1, 8, 2, 7};
    char direcoes[4] = {'H', 'V', 'D', 'E'};
    for (int i = 0; i < 4; i++) {
        if (podePosicionarNavio(tabuleiro, linhas[i], colunas[i], direcoes[i])) {
            posicionarNavio(tabuleiro, linhas[i], colunas[i], direcoes[i]);
        }
    }

    
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

   
    aplicarHabilidade(tabuleiro, cone, 6, 2);      // Cone apontando para baixo
    aplicarHabilidade(tabuleiro, cruz, 4, 4);      // Cruz no centro
    aplicarHabilidade(tabuleiro, octaedro, 2, 7);  // Octaedro no canto

   
    exibirTabuleiro(tabuleiro);

    return 0;
}
