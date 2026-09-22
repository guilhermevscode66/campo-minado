/** funções para colocar o terminal em raw mode e modo normal, são necessárias para fazer a navegaçãop com as setas*/
#ifndef TECLADO_H
#define TECLADO_H
#include <unistd.h>
#include <termios.h>
#include "tabuleiro.h"

void disable_raw_mode(struct termios *orig);
void enable_raw_mode(struct termios *orig);
void navegacao(tabuleiro *t);
#endif