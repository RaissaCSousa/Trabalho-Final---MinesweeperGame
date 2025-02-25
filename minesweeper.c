#include  <time.h>
#include  <ctype.h>
#include  "minesweeper.h"

//códigos de cores
#define CYAN_BG  "\033[46m   \033[0m"   
#define GREEN_FG  "\033[32m"             
#define BLUE_FG  "\033[34m"              
#define MAGENTA_FG  "\033[35m"           
#define RED_FG  "\033[31m"               
#define RESET  "\033[0m"                 

//cria o tabuleiro alocando memória para as células
Celula **criarTabuleiro(int linhas, int colunas) {
    Celula **tabuleiro =  (Celula **)malloc(linhas * sizeof(Celula *));
    for (int i =  0; i < linhas; i++) {
        tabuleiro[i] =  (Celula *)calloc(colunas, sizeof(Celula));
    }
    return tabuleiro;
}

//posiciona as minas de forma aleatória
void posicionarMinas(Celula **tabuleiro, int linhas, int colunas, int num_minas) {
    int colocadas = 0;
    while (colocadas < num_minas) {
        int r_linha = rand() % linhas;
        int r_coluna = rand() % colunas;
        if (!tabuleiro[r_linha][r_coluna].mina) {
            tabuleiro[r_linha][r_coluna].mina = 1;
            colocadas++;
        }
    }
}

//calcula o número de minas vizinhas para cada célula
void calcularVizinhos( Celula **tabuleiro, int linhas, int colunas) {
    for (int i = 0;  i < linhas; i++) {
        for (int j = 0; j  < colunas; j++) {
            if (!tabuleiro[i][j].mina) {
                int count  = 0;
                for (int di = -1; di <= 1; di++)  {
                    for (int dj = -1; dj <= 1; dj++)  {
                        int ni = i + di;
                        int nj = j + dj;
                        if  (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas &&
                            tabuleiro[ni][nj].mina) {
                            count++;
                        }
                    }
                }
                tabuleiro[i][j].vizinhos = count;
            }
        }
    }
}

//retornar a cor baseada no número de vizinhos
//azul para uma mina, rosa para duas e vermelho para três ou quatro
const char* getCorVizinhos(int vizinhos) {
    if (vizinhos == 1) {
        return BLUE_FG;   
    } else if (vizinhos == 2)  {
        return MAGENTA_FG;
    } else if (vizinhos >= 3 && vizinhos <= 4)  {
        return RED_FG; 
    } else {
        return RESET; 
    }
}

//exibe o tabuleiro com as coordenadas
void exibirTabuleiro(Celula **tabuleiro, int linhas, int colunas)  {
    // Exibe a numeração das colunas (dezenas)
    printf("    ");
    for (int j = 0; j < colunas; j++){
        int num = j + 1;
        if (num >= 10) {
            int tens = num / 10;
            printf("  %s%d%s ", GREEN_FG, tens, RESET);
        } else {
            printf("    ");
        }
    }
    printf("\n");

    //exibe a numeração das colunas do tabuleiro
    printf("    ");
    for (int j = 0; j < colunas; j++)  {
        int num = j + 1;
        int ones = num % 10;
        printf("  %s%d%s ", GREEN_FG, ones, RESET);
    }
    printf("\n");

    for (int i = 0; i < linhas; i++)  {
        printf("   ");
        for (int j = 0; j < colunas; j++)  {
            printf("+---");
        }
        printf("+\n");

        printf (" %s%c%s ", GREEN_FG, 'A' + i, RESET);
        for (int j =  0; j < colunas; j++) {
            if (tabuleiro[i][j].revelado)  {
                if (tabuleiro[i][j].mina) {
                    printf("| %s*%s ", RED_FG, RESET);
                } else {
                    const char* cor = getCorVizinhos(tabuleiro[i][j].vizinhos);
                    printf("| %s%2d%s", cor, tabuleiro[i][j].vizinhos, RESET);
                }
            } else if (tabuleiro[i][j].marcado)  {
                printf("| %s#%s ", RED_FG, RESET);
            } else {
                printf("|%s", CYAN_BG);
            }
        }
        printf("|\n");
    }
    printf("   ");
    for (int j = 0; j < colunas; j++)  {
        printf("+---");
    }
    printf("+\n");
}

//abre uma célula e, se ela não possuir minas vizinhas, expande recursivamente
void abrirCelula(Celula **tabuleiro, int linhas, int colunas, int i, int j)  {
    if  (i < 0 || i >= linhas || j < 0 || j >= colunas || tabuleiro[i][j].revelado)
        return;
    
    tabuleiro[i][j].revelado =  1;
    
    if (tabuleiro[i][j].vizinhos == 0) {
        for (int di = -1; di <= 1; di++)  {
            for (int dj = -1; dj <= 1; dj++)  {
                int ni = i + di;
                int nj = j + dj;
                if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas)  {
                    abrirCelula(tabuleiro, linhas, colunas, ni, nj);
                }
            }
        }
    }
}

//revela todas as minas no tabuleiro (usada quando o jogador acerta uma mina)
void revelarMinas(Celula **tabuleiro, int linhas, int colunas)  {
    for (int i = 0; i < linhas; i++)  {
        for (int j = 0; j < colunas; j++)  {
            tabuleiro[i][j].revelado =  1;
        }
    }
}

//função principal do jogo
void jogar(Celula **tabuleiro, int linhas, int colunas, int num_minas) {
    char comando[10];
    int i, j;
    char tipo_comando; 

    while (1) {
        exibirTabuleiro(tabuleiro, linhas, colunas);

        int entrada_valida = 0;
        while (!entrada_valida) {
            printf("Digite sua jogada: ");
            scanf("%s", comando);

            tipo_comando = comando[0]; 
            int offset =  (tipo_comando == '#' || tipo_comando == '!') ? 1 : 0; 

            if (isalpha(comando[offset])) {
                i = toupper(comando[offset]) - 'A';

                if (isdigit(comando[offset + 1])) {
                    j = atoi(&comando[offset + 1]) - 1;
                } else {
                    printf("Entrada invalida! Use o formato correto (ex: A5, #B7, !C3).\n");
                    continue;
                }
            } else {
                printf("Entrada invalida! Use o formato correto (ex: A5, #B7, !C3).\n");
                continue;
            }

            if (i >= 0 && i < linhas && j >= 0 && j < colunas)  {
                entrada_valida = 1;
            } else {
                printf("Coordenada fora dos limites! Tente novamente.\n");
            }
        }

        if (tipo_comando == '#') { 
            if (!tabuleiro[i][j].revelado) {
                tabuleiro[i][j].marcado = 1;
            }
        } else if (tipo_comando == '!') {  
            if (tabuleiro[i][j].marcado) {
                tabuleiro[i][j].marcado = 0;
            }
        } else { 
            if (tabuleiro[i][j].mina) {
                printf("Voce acertou uma mina!\n");
                revelarMinas(tabuleiro, linhas, colunas);
                exibirTabuleiro(tabuleiro, linhas, colunas);
                printf("Voce acertou uma mina! Fim de jogo.\n");
                return;
            }
            abrirCelula(tabuleiro, linhas, colunas, i, j);
        }

        int celulas_reveladas =  0, total_celulas = linhas * colunas - num_minas;
        for (int x = 0; x < linhas; x++)  {
            for (int y = 0; y < colunas; y++)  {
                if (tabuleiro[x][y].revelado)  {
                    celulas_reveladas++;
                }
            }
        }
        if (celulas_reveladas == total_celulas) {
            exibirTabuleiro(tabuleiro, linhas, colunas);
            printf("Parabens! Voce venceu!\n");
            return;
        }
    }
}

//libera a memória alocada para o tabuleiro
void liberarTabuleiro(Celula **tabuleiro, int linhas)  {
    for (int i = 0; i < linhas; i++)  {
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}
