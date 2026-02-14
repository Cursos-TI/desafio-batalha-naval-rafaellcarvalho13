#include <stdio.h>

#define TAM 10
#define HABILIDADE_TAM 5

int main() {

    // =====================================================
    // 1️⃣ TABULEIRO BASE
    // =====================================================
    int tabuleiro[TAM][TAM];

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0; // Água
        }
    }

    // =====================================================
    // 2️⃣ NAVIOS (apenas para visualização)
    // =====================================================
    tabuleiro[2][2] = 3;
    tabuleiro[2][3] = 3;
    tabuleiro[2][4] = 3;

    tabuleiro[6][7] = 3;
    tabuleiro[7][7] = 3;
    tabuleiro[8][7] = 3;

    // =====================================================
    // 3️⃣ MATRIZES DE HABILIDADE (0 = fora, 1 = afetado)
    // =====================================================
    int cone[HABILIDADE_TAM][HABILIDADE_TAM];
    int cruz[HABILIDADE_TAM][HABILIDADE_TAM];
    int octaedro[HABILIDADE_TAM][HABILIDADE_TAM];

    int centro = HABILIDADE_TAM / 2;

    // ---------- CONE (apontando para baixo) ----------
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {

            // Forma de cone: expande a cada linha
            if (j >= centro - i && j <= centro + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }

    // ---------- CRUZ ----------
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {

            if (i == centro || j == centro)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }

    // ---------- OCTAEDRO (LOSANGO) ----------
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {

            // Distância Manhattan gera losango
            if ( (i - centro <= 0 ? centro - i : i - centro) +
                 (j - centro <= 0 ? centro - j : j - centro) <= centro)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }

    // =====================================================
    // 4️⃣ PONTOS DE ORIGEM NO TABULEIRO
    // =====================================================
    int origem_cone_linha = 0, origem_cone_coluna = 0;
    int origem_cruz_linha = 5, origem_cruz_coluna = 5;
    int origem_octa_linha = 9, origem_octa_coluna = 9;

    // =====================================================
    // 5️⃣ SOBREPOSIÇÃO DAS HABILIDADES
    // =====================================================

    // ---------- CONE ----------
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {

            int linha_tab = origem_cone_linha + i;
            int coluna_tab = origem_cone_coluna + j;

            if (linha_tab < TAM && coluna_tab < TAM) {
                if (cone[i][j] == 1 && tabuleiro[linha_tab][coluna_tab] == 0)
                    tabuleiro[linha_tab][coluna_tab] = 5;
            }
        }
    }

    // ---------- CRUZ ----------
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {

            int linha_tab = origem_cruz_linha - centro + i;
            int coluna_tab = origem_cruz_coluna - centro + j;

            if (linha_tab >= 0 && linha_tab < TAM &&
                coluna_tab >= 0 && coluna_tab < TAM) {

                if (cruz[i][j] == 1 && tabuleiro[linha_tab][coluna_tab] == 0)
                    tabuleiro[linha_tab][coluna_tab] = 5;
            }
        }
    }

    // ---------- OCTAEDRO ----------
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {

            int linha_tab = origem_octa_linha - centro + i;
            int coluna_tab = origem_octa_coluna - centro + j;

            if (linha_tab >= 0 && linha_tab < TAM &&
                coluna_tab >= 0 && coluna_tab < TAM) {

                if (octaedro[i][j] == 1 && tabuleiro[linha_tab][coluna_tab] == 0)
                    tabuleiro[linha_tab][coluna_tab] = 5;
            }
        }
    }

    // =====================================================
    // 6️⃣ EXIBIÇÃO FINAL
    // =====================================================
    printf("\nTABULEIRO COM HABILIDADES\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}