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
   tabuleiro* alocar(int linhas, int colunas)
{
 tabuleiro* t = malloc(sizeof(tabuleiro));
 t->linhas = linhas;
 t->colunas = colunas;
 t->celulas = malloc(linhas * sizeof(int*));
for(int i =0; i<t->linhas; i++){
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
    for(int i=0; i<t->linhas; i++){
    free(t->celulas[i]);
    
    }
    free(t->celulas);
free(t);
    
}
//criando a função que coloca as bombas no lugar
void coloca_bombas(tabuleiro* t )
{
   
int b=0; //contador de bombas pra ser incrementado

    while(b < t->linhas*t->colunas)
    {
    int l = rand() % t->linhas;
    int c = rand() % t->colunas;
    if(t->celulas[l][c] !=-1){
        t->celulas[l][c] = -1;
        b++;
        }
    else{
        l = rand() %t->linhas;
        c = rand() % t->colunas;
        }
if(b == t->linhas*t->colunas){
    break;
}

}

}


int main()
{

    //inicializa o seed do gerador aleatório
srand(time(NULL));

    int linhas ;
    int colunas ;
    int nrbombas ;
    tabuleiro* t;
    printf("Digite o número de linhas:\n");
    scanf("%d",&linhas);
printf("Digite o número de colunas:\n");
scanf("%d",&colunas);
//verifica se o número de bombas é maior que o número de células


printf("Digitte o número de bombas:\n");
scanf("%d",&nrbombas);


while(nrbombas > t->linhas*t->colunas){
break;
if(nrbombas > t->linhas*t->colunas)
printf("O numero de bombas não pode ser maior que o numero de celulas. Atualmente voce possui %d celulas\n", t->linhas*t->colunas);
fflush(stdin);
printf("Digitte o número de bombas:\n");
}

     t =alocar(linhas, colunas);
preencher(t);
imprimir(t);
liberar(t);
    return 0;
}