#ifndef TABULEIRO_H
    #define TABULEIRO_H
    #include <stdbool.h>
    #include <time.h>

    typedef struct{
        int valor;
        bool revelada;
        bool marcada;
        bool ebomba;
    }celula;

    typedef struct{
        int linhas;
        int colunas;
        int nrbombas;
        celula** matriz;
        int status; //0 = em andamento, 1 = ganhou, 2 = perdeu
        time_t tempo_inicio;
        int tempo_segundos;
    } tabuleiro;

    //cabeçalhos das funções
    tabuleiro* alocar(int linhas, int colunas);
    void preencher(tabuleiro* t);
    void imprimir (tabuleiro *t);
    void liberar(tabuleiro* t);
    void coloca_bombas(tabuleiro* t, int nrbombas);
    int contar_bombas_ao_redor(tabuleiro* t, int p, int pc);
    void revelar_celula(tabuleiro* t, int p, int pc);
    void atualizar_tempo_tabuleiro(tabuleiro* t);
    void resolver_tabuleiro_automatico(tabuleiro* t);
    #endif
    