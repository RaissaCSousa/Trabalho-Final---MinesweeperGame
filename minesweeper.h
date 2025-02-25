#ifndef MINESWEEPER_H
#define MINESWEEPER_H

//constantes de configuração
#define MIN_LINHAS 5
#define MAX_LINHAS 26
#define MIN_COLUNAS 5
#define MAX_COLUNAS 40
#define MIN_MINAS 7

//célula do tabuleiro
typedef struct Celula {
    int mina;
    int vizinhos;
    int revelado;
    int marcado;
    struct Celula *cima, *baixo, *esquerda, *direita;
} Celula;

//funções
Celula **criarTabuleiro(int linhas, int colunas);
void posicionarMinas (Celula **tabuleiro, int linhas, int colunas, int num_minas);
void calcularVizinhos(Celula **tabuleiro, int linhas, int colunas);
void exibirTabuleiro(Celula **tabuleiro, int linhas, int colunas);
void abrirCelula (Celula **tabuleiro, int linhas, int colunas, int i, int j);
void jogar(Celula **tabuleiro, int linhas, int colunas, int num_minas);
void liberarTabuleiro(Celula **tabuleiro, int linhas);

#endif
