/** funções para colocar o terminal em raw mode e modo normal, são necessárias para fazer a navegaçãop com as setas*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include "teclado.h"
#include "tabuleiro.h"

//variaveis para controlar a posição do cursor na matriz
int p = 0; //controla a posição de linha na matriz
int pc = 0; //controla a posição de coluna na matriz
int bombas_ao_redor = 0; //variavel que vai contar quantas bombas tem ao redor da célula selecionada

void disable_raw_mode(struct termios *orig){
    if(orig != NULL){
        tcsetattr(STDIN_FILENO, TCSANOW, orig);
    }
}

//coloca o terminal em modo raw
void enable_raw_mode(struct termios *orig){
    struct termios raw;
    if(orig == NULL){
        return;
    }

    tcgetattr(STDIN_FILENO, orig);
    raw = *orig;

    //desativa o modo canônico, eco e interrupção por sinais
    raw.c_lflag &= ~(ICANON | ECHO | ISIG);
    raw.c_cc[VMIN] = 1; //espera pelo menos 1 byte
    raw.c_cc[VTIME] = 0; //não usa tempo limite

    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void navegacao(tabuleiro* t){
    struct termios orig_termios;
    char c;

    if(t == NULL){
        return;
    }

    p = 0;
    pc = 0;
    enable_raw_mode(&orig_termios);
    printf("Use as setas para mover e Enter para selecionar. Q para sair.\n");

    while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){
        if(c == '\x1b'){
            char seq[2];
            if(read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1 && seq[0] == '['){
                switch(seq[1]){
                    case 'A':
                        if(p > 0){
                            p--;
                        }
                        break;
                    case 'B':
                        if(p < t->linhas - 1){
                            p++;
                        }
                        break;
                    case 'C':
                        if(pc < t->colunas - 1){
                            pc++;
                        }
                        break;
                    case 'D':
                        if(pc > 0){
                            pc--;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        else if(c == '\n' || c == '\r'){
            revelar_celula(t, p, pc);
            if(t->status == 2){
                break;
            }
        }

        printf("\033[2J\033[H");
        imprimir(t);
        printf("\nCursor: linha %d, coluna %d\n", p, pc);
    }

    disable_raw_mode(&orig_termios);
}