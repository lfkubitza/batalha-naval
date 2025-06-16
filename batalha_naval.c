#include <stdio.h>

#define TAB_SIZE 10
#define HAB_SIZE 5

// Função para inicializar o tabuleiro com água (0)
void inicializaTabuleiro(int tab[TAB_SIZE][TAB_SIZE]) {
    for (int i = 0; i < TAB_SIZE; i++)
        for (int j = 0; j < TAB_SIZE; j++)
            tab[i][j] = 0;
}

// Função para posicionar navios manualmente (representado por 3)
void posicionaNavios(int tab[TAB_SIZE][TAB_SIZE]) {
    // Exemplo simples: três navios em posições fixas
    tab[2][3] = 3;
    tab[2][4] = 3;
    tab[2][5] = 3;
    
    tab[5][5] = 3;
    tab[6][5] = 3;
    tab[7][5] = 3;
    
    tab[8][1] = 3;
    tab[8][2] = 3;
    tab[8][3] = 3;
}

// Função para criar matriz da habilidade CONE (5x5)
void criaHabilidadeCone(int cone[HAB_SIZE][HAB_SIZE]) {
    // A ideia: um "cone" que começa com 1 elemento no topo, depois 3 na linha do meio, 5 na base
    for (int i = 0; i < HAB_SIZE; i++) {
        for (int j = 0; j < HAB_SIZE; j++) {
            // Limites para formar o cone apontando para baixo
            // Linha 0: coluna central só (2)
            // Linha 1: colunas 1 a 3
            // Linha 2: colunas 0 a 4 (toda linha)
            if (i == 0 && j == 2) cone[i][j] = 1;
            else if (i == 1 && j >= 1 && j <= 3) cone[i][j] = 1;
            else if (i == 2 && j >= 0 && j <= 4) cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Função para criar matriz da habilidade CRUZ (5x5)
void criaHabilidadeCruz(int cruz[HAB_SIZE][HAB_SIZE]) {
    int meio = HAB_SIZE / 2;
    for (int i = 0; i < HAB_SIZE; i++) {
        for (int j = 0; j < HAB_SIZE; j++) {
            // Cruz: linha do meio e coluna do meio são 1
            if (i == meio || j == meio)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Função para criar matriz da habilidade OCTAEDRO (5x5)
void criaHabilidadeOctaedro(int octaedro[HAB_SIZE][HAB_SIZE]) {
    int meio = HAB_SIZE / 2;
    for (int i = 0; i < HAB_SIZE; i++) {
        for (int j = 0; j < HAB_SIZE; j++) {
            // Losango: posições cuja soma das distâncias ao centro <= meio
            int distLinha = (i > meio) ? i - meio : meio - i;
            int distColuna = (j > meio) ? j - meio : meio - j;
            if (distLinha + distColuna <= meio)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// Função que sobrepõe a habilidade no tabuleiro
void aplicaHabilidade(int tab[TAB_SIZE][TAB_SIZE], int hab[HAB_SIZE][HAB_SIZE], int origemLinha, int origemColuna) {
    int meio = HAB_SIZE / 2;

    for (int i = 0; i < HAB_SIZE; i++) {
        for (int j = 0; j < HAB_SIZE; j++) {
            if (hab[i][j] == 1) {
                int tabLinha = origemLinha - meio + i;
                int tabColuna = origemColuna - meio + j;

                // Verifica se está dentro dos limites do tabuleiro
                if (tabLinha >= 0 && tabLinha < TAB_SIZE && tabColuna >= 0 && tabColuna < TAB_SIZE) {
                    // Só marca se não for navio (3), para não sobrescrever navio
                    if (tab[tabLinha][tabColuna] == 0) {
                        tab[tabLinha][tabColuna] = 5;
                    }
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibeTabuleiro(int tab[TAB_SIZE][TAB_SIZE]) {
    printf("Legenda: 0=Agua, 3=Navio, 5=Area habilidade\n\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            if (tab[i][j] == 0)
                printf(". ");    // Água representada por ponto
            else if (tab[i][j] == 3)
                printf("N ");    // Navio
            else if (tab[i][j] == 5)
                printf("* ");    // Área de efeito da habilidade
            else
                printf("? ");    // Caso inesperado
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE];
    int cone[HAB_SIZE][HAB_SIZE];
    int cruz[HAB_SIZE][HAB_SIZE];
    int octaedro[HAB_SIZE][HAB_SIZE];

    // Inicializa o tabuleiro e os navios
    inicializaTabuleiro(tabuleiro);
    posicionaNavios(tabuleiro);

    // Cria as matrizes das habilidades usando condicionais
    criaHabilidadeCone(cone);
    criaHabilidadeCruz(cruz);
    criaHabilidadeOctaedro(octaedro);

    // Define pontos de origem fixos para as habilidades
    int origemConeLinha = 3, origemConeColuna = 3;
    int origemCruzLinha = 6, origemCruzColuna = 6;
    int origemOctaedroLinha = 8, origemOctaedroColuna = 2;

    // Aplica as habilidades no tabuleiro
    aplicaHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    aplicaHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    aplicaHabilidade(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    // Exibe o tabuleiro final
    exibeTabuleiro(tabuleiro);

    return 0;
}
