#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
typedef struct{
    int linhas;
    int colunas;
    int nrbombas;
    int** celulas;
    
    int com_bomba;
} tabuleiro;
//criando a função que vai alocar tudo
   tabuleiro* alocar(int linhas, int colunas, int num_bombas)
{
 tabuleiro* t = malloc(sizeof(tabuleiro));
 t->linhas = linhas;
 t->colunas = colunas;
 t->celulas = malloc(linhas * sizeof(int*));
for(int i =0; i<t<-linhas; i++){
t->celulas[i] = malloc(colunas * sizeof(int));

}
return t;
}
//criando a função pra preencher o tabuleiro
void preencher(tabuleiro* t)
{
    //for pra preencher as células com bombas
for(int i = 0; i<t->linhas; i++){
    for(int j=0; j<t->colunas; j++){
        t->celulas[i][j] = -1;
    }
}

//for pra preencher as células que não são bombas
for(int i=0; i<t->linhas; i++){
    for(int j=0; j<t->colunas; j++){
        t->celulas[i][j] =0;
    }
}

}
//criando uma função pra imprimir as células
void imprimir(tabuleiro* t)
{
        for(int i=0; i<t->linhas; i++){
        for(int j=0; j<t->colunas; j++){
            printf("[%d][%d] = %d\n", i, j, t->celulas[i][j]);
        }
    }

}
//criando uma função pra liberar a memória
void liberar(tabuleiro* t){
    for(int i=0; i<t->celulas; i++){
    free(t->celulas[i]);
    free(t->celulas);
free(t);
    }
}
//criando a função que coloca as bombas no lugar
void coloca_bombas(tabuleiro** matriz)
{
   tabuleiro** p = &matriz;
   
int b=0; //contador de bombas pra ser incrementado
//contadores de linha e coluna

int i =0;
int j= 0;
//inicializa o seed do gerador aleatório
srand(time(NULL));
while(b < p->num_bombas )
{
int r = rand()%matriz.linhas;
int c = rand()%matriz.colunas;
if(matriz[i][j].com_bomba ==false){

}
}

}


int main()
{
    int linhas = 3;
    int colunas = 3;
    int nrbombas = 2;
    printf("Digite o número de linhas:\n");
    scanf("%d",&linhas);
printf("Digite o número de colunas:\n");
scanf("%d",&colunas);
printf("Digitte o número de bombas:\n");
scanf("%d",&nrbombas);

    tabuleiro* t =alocar(linhas, colunas, nrbombas);
preencher(t);
imprimir(t);
liberar(t);
    return 0;
}