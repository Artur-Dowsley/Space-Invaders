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

typedef struct {
    char nome[20];
    int tempo;
} Recorde;

// Variáveis globais
#define INIMIGOS_POR_LINHA 6
#define NUM_LINHAS 4
#define NUM_INIMIGOS (INIMIGOS_POR_LINHA * NUM_LINHAS)
#define MAX_PROJETEIS 4
#define LARGURA 80
#define ALTURA 24

int tempo = 0;
int contadorProjetilInimigo = 0;
Recorde *recordes = NULL;
int numRecordes=0;
int especial = 0;

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

void pedirNome(char *nome) {
    int inicio_x = (LARGURA - 20) / 2;
    int inicio_y = ALTURA / 2 + 2;
    screenGotoxy(inicio_x, inicio_y);
    printf("Digite seu nome: ");
    screenGotoxy(inicio_x + strlen("Digite seu nome: "), inicio_y);
    fgets(nome, 20, stdin);
    nome[strcspn(nome, "\n")] = '\0';
}

// Função para adicionar o recorde no arquivo
void adicionarRecorde(Recorde **recordes, int *numRecordes, int tempo)
{
    char nome[20];
    pedirNome(nome);  // Pede o nome do jogador

    // Adiciona o recorde na memória
    *recordes = realloc(*recordes, (*numRecordes + 1) * sizeof(Recorde));
    snprintf((*recordes)[*numRecordes].nome, 20, "%s", nome);
    (*recordes)[*numRecordes].tempo = tempo;
    (*numRecordes)++;

    FILE *arquivo = fopen("recordes.txt", "a");
    if (arquivo)
    {
        fprintf(arquivo, "%s %d\n", nome, tempo);
        fclose(arquivo);
    }
}

// Função para carregar os recordes do arquivo
void carregarRecordes(Recorde **recordes, int *numRecordes)
{
    FILE *arquivo = fopen("recordes.txt", "r");

    if (arquivo)
    {
        char nome[20];
        int tempo;

        while (fscanf(arquivo, "%s %d", nome, &tempo) == 2)
        {
            *recordes = realloc(*recordes, (*numRecordes + 1) * sizeof(Recorde));
            snprintf((*recordes)[*numRecordes].nome, 20, "%s", nome);
            (*recordes)[*numRecordes].tempo = tempo;
            (*numRecordes)++;
        }
        fclose(arquivo);
    }
}

// Função para mostrar os recordes
void mostrarRecordes(Recorde *recordes, int numRecordes)
{
    screenClear();
    printf("Recordes:\n");
    for (int i = 0; i < numRecordes; i++)
    {
        printf("%d. %s - %d segundos\n", i + 1, recordes[i].nome, recordes[i].tempo);
    }
}

// Função de GAME OVER caso jogador seja derrotado
void desenha_game_over(){

  screenInit(1);
  const char *mensagem = "GAME-OVER";
  int tamanho_mensagem = strlen(mensagem);
  int inicio_x = (LARGURA - tamanho_mensagem) / 2;
  int inicio_y = ALTURA / 2;
  screenSetColor(RED, BLACK);
  for (int i = 0; i < tamanho_mensagem; ++i){
    desenha_caractere(inicio_x + i, inicio_y, mensagem[i]);
  }
}

// Função para mensagem de Vitória após jogador eliminar todos inimigos
void tela_vitoria()
{
    screenInit(1);
    const char *mensagem = "VOCE VENCEU!";
    int tamanho_mensagem = strlen(mensagem);
    int inicio_x = (LARGURA - tamanho_mensagem) / 2;
    int inicio_y = ALTURA / 2;
    screenSetColor(GREEN, BLACK);

    for (int i = 0; i < tamanho_mensagem; ++i)
    {
        desenha_caractere(inicio_x + i, inicio_y, mensagem[i]);
    }

    adicionarRecorde(&recordes, &numRecordes, tempo/16);
    mostrarRecordes(recordes, numRecordes);
    timerInit(3000);
    while (!timerTimeOver());
    exit(0);

}

// Função para desenhar o tempo e o especial no topo da tela
void desenha_tempo()
{
    char str_tempo[100];
    snprintf(str_tempo, sizeof(str_tempo), "Tempo: %d segundos | Especial: %d", tempo / 16, especial);
    int tamanho_mensagem = strlen(str_tempo);
    int inicio_x = (LARGURA - tamanho_mensagem) / 2;
    screenSetColor(DARKGRAY, BLACK);
    for (int i = 0; i < tamanho_mensagem; ++i)
    {
        desenha_caractere(inicio_x + i, 0, str_tempo[i]);
    }
}


// Função para definição do formato dos elementos
void desenho(Jogador jogador, Inimigo inimigos[], Projetil projeteisJogador[], Projetil projeteisInimigo[]) {

  screenClear();
  screenInit(1);
  screenSetColor(LIGHTGREEN, BLACK);
  desenha_caractere(jogador.pos.x, jogador.pos.y, 'W');

  for (int i = 0; i < NUM_INIMIGOS; ++i){
    if (inimigos[i].vivo){
            screenGotoxy(inimigos[i].pos.x - 1, inimigos[i].pos.y);
            printf("👾");
    }
  }

  for (int i = 0; i < MAX_PROJETEIS; ++i){
    if (projeteisJogador[i].ativo){
      screenSetColor(WHITE, BLACK);
      desenha_caractere(projeteisJogador[i].pos.x, projeteisJogador[i].pos.y, '|');
    }
    if (projeteisInimigo[i].ativo){
      screenSetColor(WHITE, BLACK);
      desenha_caractere(projeteisInimigo[i].pos.x, projeteisInimigo[i].pos.y, '|');
    }
  }

  desenha_tempo();
  screenUpdate();
}

// Função para atualização de informações na tela
void atualiza(Jogador *jogador, Inimigo inimigos[], Projetil projeteisJogador[], Projetil projeteisInimigo[]) {

    if (especial < 100)
    {
        especial++;
    }

    int todosInimigosMortos = 1; // Variável para verificar se todos os inimigos estão mortos
    tempo++;

    for (int i = 0; i < MAX_PROJETEIS; ++i) {
        if (projeteisJogador[i].ativo) {
            projeteisJogador[i].pos.y--;
            if (projeteisJogador[i].pos.y < 1) {
                projeteisJogador[i].ativo = 0;
            }

            for (int j = 0; j < NUM_INIMIGOS; ++j) {
                if (inimigos[j].vivo && projeteisJogador[i].pos.x == inimigos[j].pos.x && projeteisJogador[i].pos.y == inimigos[j].pos.y
                || inimigos[j].vivo && projeteisJogador[i].pos.x == inimigos[j].pos.x-1 && projeteisJogador[i].pos.y == inimigos[j].pos.y) {

                    inimigos[j].vivo = 0;
                    projeteisJogador[i].ativo = 0;
                }
            }
        }

        if (projeteisInimigo[i].ativo) {
            if (contadorProjetilInimigo % 2== 0) {
                projeteisInimigo[i].pos.y++;
                if (projeteisInimigo[i].pos.y >= ALTURA - 1) {
                    projeteisInimigo[i].ativo = 0;
                }

                if (projeteisInimigo[i].pos.x == jogador->pos.x && projeteisInimigo[i].pos.y == jogador->pos.y) {
                    screenClear();
                    screenUpdate();
                    desenha_game_over(); // Game Over
                    timerInit(3000); // Inicializa o temporizador com 3000 ms
                    while (!timerTimeOver()); // Aguarda até que o tempo tenha passado
                    
                    exit(0);
                }
            }
        }
    }

    contadorProjetilInimigo++;

    for (int i = 0; i < NUM_INIMIGOS; ++i) {
        if (inimigos[i].vivo) {
            todosInimigosMortos = 0; // Se encontrar um inimigo vivo, define como 0
            if (rand() % 100 < 10) {
                for (int j = 0; j < 3; ++j) {
                    for (int k = 0; k < MAX_PROJETEIS; ++k) {
                        if (!projeteisInimigo[k].ativo) {
                            projeteisInimigo[k].pos.x = inimigos[i].pos.x;
                            projeteisInimigo[k].pos.y = inimigos[i].pos.y + 1;
                            projeteisInimigo[k].ativo = 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    if (todosInimigosMortos) {
        screenClear();
        screenUpdate();
        tela_vitoria();  // Ganhou
        timerInit(3000); // Inicializa o temporizador com 3000 ms
        while (!timerTimeOver()); // Aguarda até que o tempo tenha passado
        
        exit(0);
    }

    if (keyhit()) {
        int ch = readch();

        if (ch == 's' && especial == 100)
        {
            for (int i = 0; i < MAX_PROJETEIS; ++i)
            {
                if (!projeteisJogador[i].ativo)
                {
                    projeteisJogador[i].pos.x = jogador->pos.x - 1 + i; 
                    projeteisJogador[i].pos.y = jogador->pos.y - 1;
                    projeteisJogador[i].ativo = 1;
                }
            }
            especial = 0; 
        }
        if (ch == 'a' && jogador->pos.x > 2) {
            jogador->pos.x--;
        }
        if (ch == 'd' && jogador->pos.x < LARGURA - 3) {
            jogador->pos.x++;
        }
        if (ch == ' ') {
            int podeAtirar = 1;
            for (int i = 0; i < MAX_PROJETEIS; ++i) {
                if (projeteisJogador[i].ativo) {
                    podeAtirar = 0;
                    break;
                }
            }
            if (podeAtirar) {
                for (int i = 0; i < MAX_PROJETEIS; ++i) {
                    if (!projeteisJogador[i].ativo) {
                        projeteisJogador[i].pos.x = jogador->pos.x;
                        projeteisJogador[i].pos.y = jogador->pos.y - 1;
                        projeteisJogador[i].ativo = 1;
                        break;
                    }
                }
            }
        }
    }
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

    carregarRecordes(&recordes, &numRecordes);

    inicializa(&jogador, &inimigos, &projeteisJogador, &projeteisInimigo);

    while (1) {
        desenho(*jogador, inimigos, projeteisJogador, projeteisInimigo);
        atualiza(jogador, inimigos, projeteisJogador, projeteisInimigo);

        if (timerTimeOver()) {
            timerInit(60);
        }

        while (!timerTimeOver());
    }

    free(jogador);
    free(inimigos);
    free(projeteisJogador);
    free(projeteisInimigo);

    finaliza();
    return 0;
}
