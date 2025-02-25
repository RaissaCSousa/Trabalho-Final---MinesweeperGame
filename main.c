/*
 * Trabalho Final - Minesweeper
 * Alunos: Ravena Marques Carvalho e Raissa Costa Sousa
 * Disciplina: Programação (CK0226)
 * Professor: Miguel Franklin
 */

 #include  <stdio.h>
 #include  <stdlib.h>
 #include  <time.h>
 #include  "minesweeper.h"
 
 int main()  {
     int linhas, colunas, num_minas;
     srand(time(NULL));  // Inicializa a semente
 
     //dimensões do tabuleiro
     printf("Digite o numero de linhas (5-26): ");
     scanf("%d", &linhas);
     printf("Digite o numero de colunas (5-40): ");
     scanf("%d", &colunas);
     
     //valida dimensoes
     if (linhas < MIN_LINHAS || linhas > MAX_LINHAS || colunas < MIN_COLUNAS || colunas > MAX_COLUNAS)  {
         printf("Dimensao invalida!\n") ;
         return 1;
     }
     
     int max_minas = (linhas * colunas) / 5;
     // Lê número de minas
     printf("Digite o numero de minas (7-%d): ", max_minas);
     scanf("%d", &num_minas);
     
     //valida número de minas
     if (num_minas < MIN_MINAS || num_minas > max_minas)  {
         printf("Numero de minas inválido!\n");
         return 1;
     }
     
     //cria e inicializa o tabuleiro
     Celula **tabuleiro = criarTabuleiro(linhas, colunas);
     posicionarMinas(tabuleiro, linhas, colunas, num_minas);
     calcularVizinhos(tabuleiro, linhas, colunas);
     
     return 0;
 }