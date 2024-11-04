#include "keyboard.h"
#include "screen.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estruturas para as definições dos elementos
typedef struct {
  int x, y;
} Posicao;

typedef struct {
  Posicao pos;
} Jogador;

typedef struct {
  Posicao pos;
  int ativo;
} Projetil;

typedef struct {
  Posicao pos;
  int vivo;
} Inimigo;

// Variáveis globais
#define INIMIGOS_POR_LINHA 6
#define NUM_LINHAS 4
#define NUM_INIMIGOS (INIMIGOS_POR_LINHA * NUM_LINHAS)
#define MAX_PROJETEIS 4
#define LARGURA 80
#define ALTURA 24

int tempo = 0;
int contadorProjetilInimigo = 0;

// Funções do Código:

// Função de inicialização dos elementos e do jogo em si
void inicializa(Jogador **jogador, Inimigo **inimigos, Projetil **projeteisJogador, Projetil **projeteisInimigo){

  *jogador = (Jogador *)malloc(sizeof(Jogador));
  (*jogador)->pos.x = LARGURA / 2;
  (*jogador)->pos.y = ALTURA - 3;

  *inimigos = (Inimigo *)malloc(NUM_INIMIGOS * sizeof(Inimigo));
  for (int i = 0; i < NUM_INIMIGOS; ++i){
    (*inimigos)[i].pos.x = (i % INIMIGOS_POR_LINHA + 1) * (LARGURA / (INIMIGOS_POR_LINHA + 1));
    (*inimigos)[i].pos.y = 3 + (i / INIMIGOS_POR_LINHA) * 2;
    (*inimigos)[i].vivo = 1;
  }

  *projeteisJogador = (Projetil *)malloc(MAX_PROJETEIS * sizeof(Projetil));
  *projeteisInimigo = (Projetil *)malloc(MAX_PROJETEIS * sizeof(Projetil));

  for (int i = 0; i < MAX_PROJETEIS; ++i){
    (*projeteisJogador)[i].ativo = 0;
    (*projeteisInimigo)[i].ativo = 0;
  }
  
}

void desenha_caractere(int x, int y, char caractere){

  screenGotoxy(x, y); // Move o cursor para a posição (x, y)
  putchar(caractere); // Desenha o caractere
}

// Função para finalizar jogo
void finaliza(){

  keyboardDestroy();
  timerDestroy();
  screenDestroy();
}

int main() {
    screenInit(1);
    keyboardInit(0);

    Jogador *jogador;
    Inimigo *inimigos;
    Projetil *projeteisJogador;
    Projetil *projeteisInimigo;

    inicializa(&jogador, &inimigos, &projeteisJogador, &projeteisInimigo);

    free(jogador);
    free(inimigos);
    free(projeteisJogador);
    free(projeteisInimigo);

    finaliza();
    return 0;
}