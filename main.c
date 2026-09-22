#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "teclado.h"
#include "tabuleiro.h"

int main(void)
{
    while(1){
        srand(time(NULL));

        int linhas;
        int colunas;
        int nrbombas;
        int modo;
        tabuleiro* t;

        printf("Digite o número de linhas:\n");
        scanf("%d", &linhas);
        printf("Digite o número de colunas:\n");
        scanf("%d", &colunas);

        printf("Digitte o número de bombas:\n");
        scanf("%d", &nrbombas);

        while(nrbombas > linhas * colunas){
            printf("O numero de bombas não pode ser maior que o numero de celulas. Atualmente voce possui %d celulas\n", linhas * colunas);
            fflush(stdin);
            printf("Digitte o número de bombas:\n");
            scanf("%d", &nrbombas);
        }

        printf("Escolha o modo:\n1 - Jogar manualmente\n2 - Resolver automaticamente\n");
        scanf("%d", &modo);

        t = alocar(linhas, colunas);
        preencher(t);
        coloca_bombas(t, nrbombas);
        atualizar_tempo_tabuleiro(t);

        if(modo == 2){
            resolver_tabuleiro_automatico(t);
            printf("\nTempo total: %d segundos\n", t->tempo_segundos);
            imprimir(t);
            liberar(t);
            return 0;
        }

        imprimir(t);
        printf("****Campo minado:\n");
        printf("Use as setas para mover entre as celulas e enter para escolher, q para desistir.\r\n");

        navegacao(t);
        atualizar_tempo_tabuleiro(t);
        printf("\nTempo total: %d segundos\n", t->tempo_segundos);
        liberar(t);
        return 0;
    }
}
