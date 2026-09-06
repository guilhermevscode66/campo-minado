#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include <unistd.h>
#include <termios.h>
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
//for pra preencher as células que não são bombas
for(int i=0; i<t->linhas; i++){
    for(int j=0; j<t->colunas; j++){
        t->celulas[i][j] = 0;
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
void coloca_bombas(tabuleiro* t, int nrbombas)
{
   //recebe a quantidade de bombas do usuário, compara essa quantidade com um contador e coloca as bombas nas células
int b=0; //contador de bombas pra ser incrementado

        
        while(b < nrbombas)
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

}

}

/** funções para colocar o terminal em raw mode e modo normal, são necessárias para fazer a navegaçãop com as setas*/

void disable_raw_mode(struct termios *orig){
    tcsetattr(STDIN_FILENO, TCSANOW, orig);
}

//coloca o terminal em modo raw
void enable_raw_mode(struct termios *orig){
    struct termios raw;
    tcgetattr(STDIN_FILENO, orig);
    raw = *orig;
//desativa o modo canônico, eco e interrupção por sinais
raw.c_lflag &= ~(ICANON | ECHO | ISIG);

raw.c_cc[VMIN] = 1; //espera pelo menos 1 byte
raw.c_cc[VTIME] = 0; //não usa tempo limite

tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}




int main()
{

    //inicializa o seed do gerador aleatório
srand(time(NULL));

    int linhas ;
    int colunas ;
    int nrbombas ;
    int p=0; //posição de linha na matriz pra percorrer com as setas
    int pc = 0; //posição de colunas da matriz
    int bombas_ao_redor=0; //o número de bombas que foram achadas ao redor de uma célula
    tabuleiro* t;
struct termios orig_termios;

    printf("Digite o número de linhas:\n");
    scanf("%d",&linhas);
printf("Digite o número de colunas:\n");
scanf("%d",&colunas);

printf("Digitte o número de bombas:\n");
scanf("%d",&nrbombas);

//verifica se o número de bombas é maior que o número de células
while(nrbombas > linhas*colunas){
printf("O numero de bombas não pode ser maior que o numero de celulas. Atualmente voce possui %d celulas\n", linhas*colunas);
fflush(stdin);
printf("Digitte o número de bombas:\n");
scanf("%d", &nrbombas);
}

     t =alocar(linhas, colunas);
preencher(t);
coloca_bombas(t, nrbombas);
imprimir(t);


enable_raw_mode(&orig_termios);
printf("****Campo minado:\n");
printf("Use as setas para mover entre as celuas e enter para escolher, q para desistir.\r\n");
char c;
while(read(STDIN_FILENO, &c, 1)==1 && c !='q'){
    //verifica se o caractere sendo enviado é o esc (\x1b)
    if(c == '\x1b'){
        char seq[2];
        //tenta ler os outros 2 caracteres da entrra ver qual seta esta sendo precionadaada pa
        if(read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO,&seq[1],1 ) == 1){
        if(seq[0] == '['){
            //verifica se é seta cima, baixo, esquerda ou direita
            switch(seq[1]){
//então almenta ou diminui uma celula
case 'A':

    if(p >0){
p = p-1;
printf("linha %d, coluna %d\r\n", p, pc);
    }
break;
case 'B':
if(p < t->linhas-1){
p = p+1;
printf("linha %d, coluna %d \r\n",p, pc);
}
break;
case 'C':
if(pc < t->colunas-1){
    pc = pc+1;
    printf("coluna %d",pc);
}
break;
case 'D':
if(pc > 0){
    pc = pc-1;
    printf("coluna %d",pc);
}
break;
default:
printf("sequencia de escape não tratada: ESC[%c\r\n", seq[1]); break;
            }
        }
    }else{
        printf("tecla ESC (precionada sozinha)");
    }
    
    }
//se o caractere digitado for enter, revela a célula celecionada
 if(c == '\n'){
    //se tiver bomba encerra o jogo
if(t->celulas[p][pc] == -1){
    printf("Fim de jogo!"); exit(1);
}else{
//se tiver bomba ao redor conta quantas tem
if(t->celulas[p+1][pc] ==-1){ bombas_ao_redor++;}
if(t->celulas[p-1][pc] ==-1){bombas_ao_redor++;}
if(t->celulas[p][pc+1] ==-1){bombas_ao_redor++;}
if(t->celulas[p][pc-1] ==-1){bombas_ao_redor++;}
printf("%d",bombas_ao_redor);
}
}

}

disable_raw_mode(&orig_termios);
liberar(t);
    return 0;
}
