#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include"tabuleiro.h"

//criando a função que vai alocar tudo
   tabuleiro* alocar(int linhas, int colunas)
{
 tabuleiro* t = malloc(sizeof(tabuleiro));
 t->linhas = linhas;
 t->colunas = colunas;
 t->status = 0;
 t->tempo_inicio = time(NULL);
 t->tempo_segundos = 0;
 t->matriz = malloc(linhas * sizeof(celula*));
for(int i =0; i<t->linhas; i++){
t->matriz[i] = malloc(colunas * sizeof(celula));

}
return t;
}
//criando a função pra preencher o tabuleiro
void preencher(tabuleiro* t)
{
    for(int i=0; i<t->linhas; i++){
        for(int j=0; j<t->colunas; j++){
            t->matriz[i][j].valor = 0;
            t->matriz[i][j].revelada = false;
            t->matriz[i][j].marcada = false;
            t->matriz[i][j].ebomba = false;
        }
    }
}
//criando uma função pra imprimir as células
void imprimir(tabuleiro* t)
{
    printf("    ");
    for(int j = 0; j < t->colunas; j++){
        printf("%2d ", j);
    }
    printf("\n");

    for(int i = 0; i < t->linhas; i++){
        printf("%2d  ", i);
        for(int j = 0; j < t->colunas; j++){
            if(!t->matriz[i][j].revelada){
                printf("#  ");
            } else if(t->matriz[i][j].ebomba){
                printf("*  ");
            } else if(t->matriz[i][j].marcada){
                printf("F  ");
            } else {
                printf("%d  ", t->matriz[i][j].valor);
            }
        }
        printf("\n");
    }
}
//criando uma função pra liberar a memória
void liberar(tabuleiro* t){
    for(int i=0; i<t->linhas; i++){
    free(t->matriz[i]);
    
    }
    free(t->matriz);
free(t);
    
}
//criando a função que coloca as bombas no lugar
void coloca_bombas(tabuleiro* t, int nrbombas)
{
    int b = 0;

    while(b < nrbombas)
    {
        int l = rand() % t->linhas;
        int c = rand() % t->colunas;

        if(!t->matriz[l][c].ebomba)
        {
            t->matriz[l][c].ebomba = true;
            t->matriz[l][c].valor = -1;
            b++;
        }
    }

    for(int i = 0; i < t->linhas; i++){
        for(int j = 0; j < t->colunas; j++){
            if(!t->matriz[i][j].ebomba){
                t->matriz[i][j].valor = contar_bombas_ao_redor(t, i, j);
            }
        }
    }
}

void atualizar_tempo_tabuleiro(tabuleiro* t){
    if(t == NULL || t->status == 2){
        return;
    }

    time_t agora = time(NULL);
    t->tempo_segundos = (int)difftime(agora, t->tempo_inicio);
}

int contar_bombas_ao_redor(tabuleiro* t, int p, int pc){
    int bombas_ao_redor = 0;
    for(int i = p-1; i <= p+1; i++){
        for(int j = pc-1; j <= pc+1; j++){
            if(i >= 0 && i < t->linhas && j >= 0 && j < t->colunas){
                if(t->matriz[i][j].ebomba){
                    bombas_ao_redor++;
                }
            }
        }
    }
    return bombas_ao_redor;
}
void revelar_celula(tabuleiro* t, int p, int pc){
    if(p < 0 || p >= t->linhas || pc < 0 || pc >= t->colunas){
        return;
    }

    if(t->matriz[p][pc].ebomba){
        t->status = 2; //perdeu
        return;
    }

    if(t->matriz[p][pc].revelada){
        return;
    }

    t->matriz[p][pc].revelada = true;
    int bombas_ao_redor = contar_bombas_ao_redor(t, p, pc);
    if(bombas_ao_redor == 0){
        for(int i = p-1; i <= p+1; i++){
            for(int j = pc-1; j <= pc+1; j++){
                if(i != p || j != pc){
                    revelar_celula(t, i, j);
                }
            }
        }
    }
}

static void marcar_bombas_por_logica(tabuleiro* t)
{
    bool mudou = true;

    while(mudou){
        mudou = false;

        for(int i = 0; i < t->linhas; i++){
            for(int j = 0; j < t->colunas; j++){
                if(!t->matriz[i][j].revelada || t->matriz[i][j].ebomba){
                    continue;
                }

                int numero = t->matriz[i][j].valor;
                if(numero < 0){
                    continue;
                }

                int bombas_flagadas = 0;
                int ocultas = 0;

                for(int x = i - 1; x <= i + 1; x++){
                    for(int y = j - 1; y <= j + 1; y++){
                        if(x < 0 || x >= t->linhas || y < 0 || y >= t->colunas){
                            continue;
                        }

                        if(x == i && y == j){
                            continue;
                        }

                        if(t->matriz[x][y].marcada){
                            bombas_flagadas++;
                        }

                        if(!t->matriz[x][y].revelada && !t->matriz[x][y].marcada){
                            ocultas++;
                        }
                    }
                }

                if(numero == bombas_flagadas){
                    for(int x = i - 1; x <= i + 1; x++){
                        for(int y = j - 1; y <= j + 1; y++){
                            if(x < 0 || x >= t->linhas || y < 0 || y >= t->colunas){
                                continue;
                            }
                            if(x == i && y == j){
                                continue;
                            }
                            if(!t->matriz[x][y].revelada && !t->matriz[x][y].marcada){
                                revelar_celula(t, x, y);
                                mudou = true;
                            }
                        }
                    }
                }

                if(numero == bombas_flagadas + ocultas){
                    for(int x = i - 1; x <= i + 1; x++){
                        for(int y = j - 1; y <= j + 1; y++){
                            if(x < 0 || x >= t->linhas || y < 0 || y >= t->colunas){
                                continue;
                            }
                            if(x == i && y == j){
                                continue;
                            }
                            if(!t->matriz[x][y].revelada && !t->matriz[x][y].marcada){
                                t->matriz[x][y].marcada = true;
                                mudou = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

void resolver_tabuleiro_automatico(tabuleiro* t)
{
    if(t == NULL){
        return;
    }

    bool encontrou = true;

    while(encontrou && t->status != 2){
        encontrou = false;
        marcar_bombas_por_logica(t);

        for(int i = 0; i < t->linhas; i++){
            for(int j = 0; j < t->colunas; j++){
                if(!t->matriz[i][j].revelada && !t->matriz[i][j].marcada && !t->matriz[i][j].ebomba){
                    revelar_celula(t, i, j);
                    encontrou = true;
                    break;
                }
            }
            if(encontrou){
                break;
            }
        }
    }

    t->status = 1;
    atualizar_tempo_tabuleiro(t);
}
