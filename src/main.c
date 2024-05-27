#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // para a função sleep()
#include "timer.h"
#include "screen.h"
#include "keyboard.h"

#define COLUNA 20 // Definir o tamanho do labirinto
#define LINHA 19 // Definir o tamanho do labirinto

int personagem_x = 1; // Posição inicial do personagem
int personagem_y = 0; // Posição inicial do personagem
int chaves_cont = 0; // Número de chaves coletadas

typedef struct{
    char nome[100];  // Nome do jogador
    int chaves;      // Número de chaves coletadas
    double score;    // Score do jogador, medido em segundos
    char saida[50]; // Conseguiu sair
} jogador;

void TelaInicio();
void TelaPedirNome(jogador *jgdr);
void DesenhaLabirinto(char **labirinto, jogador jgdr);
void chaves(char **labirinto);
void MostrarMensagemMorte(jogador *jgdr);
void MostrarMensagemVitoria(jogador *jgdr);
void MoverPersonagem(int x, int y, char **labirinto, int *correr, jogador *jgdr);
void SalvaScore(jogador jgdr);
void ColetaChave(jogador *jgdr);
void ResetarJogo(jogador *jgdr, char **labirinto);
void TelaReniciar( int *correr);
void DesenhaTempo();

char labirintoInicial[LINHA][COLUNA + 1] = { // Preenchendo o labirinto com o conteúdo desejado
    "-O------------------",
    "|                  |",
    "|   |   |- |  | -- |",
    "||    -          _ |",
    "||-    -   -  -  | |",
    "|       |   |-|    |",
    "| |   -      |  |- |",
    "|     | | - |-|    |",
    "| |-|         |  | |",
    "|  | | |  -| |-|   |",
    "| | -     |-|    |-|",
    "|  | |   -     -|  |",
    "|       |-|  -| |- |",
    "|-    | |    |-  | |",
    "|   |     -        |",
    "|   |-|       -  | |",
    "| |        |-| |-| |",
    "|   | | |T|  |     |",
    "---------S----------"
};

int main() {
    int i;
    int correr = 1;
    char **labirinto;

    jogador jgdr;

    labirinto = (char **)calloc(LINHA, sizeof(char*)); // Alocando dinamicamente a matriz do labirinto
    for (i = 0; i < LINHA; i++) {
        labirinto[i] = (char *)calloc(COLUNA + 1, sizeof(char));
    }

    keyboardInit(); // Inicializa o teclado
    screenInit(1); // Inicializa a tela e desenha as bordas

    TelaInicio(); // Mostra a tela de início
    TelaPedirNome(&jgdr); // Pede o nome do jogador

    while (1) {
        ResetarJogo(&jgdr, labirinto); // Reinicia o jogo

        // Inicializa o temporizador para medir o tempo do jogo
        timerInit(1);

        while (correr) { // Criei um while true que pode virar false
            if (keyhit()) {
                // Verifica se alguma tecla foi pressionada
                char ch = readch(); // Lê a tecla que foi pressionada

                if (ch == 'w') {
                    MoverPersonagem(personagem_x, personagem_y - 1, labirinto, &correr, &jgdr); // Modifica as coordenadas do personagem
                } else if (ch == 's') {
                    MoverPersonagem(personagem_x, personagem_y + 1, labirinto, &correr, &jgdr); // Modifica as coordenadas do personagem
                } else if (ch == 'a') {
                    MoverPersonagem(personagem_x - 1, personagem_y, labirinto, &correr, &jgdr); // Modifica as coordenadas do personagem
                } else if (ch == 'd') {
                    MoverPersonagem(personagem_x + 1, personagem_y, labirinto, &correr, &jgdr); // Modifica as coordenadas do personagem
                } else if (ch == 'l') {
                    correr = 0;
                }

                DesenhaLabirinto(labirinto, jgdr);
                DesenhaTempo();  // Desenha novamente o labirinto na tela com a posição atualizada do personagem
            }
        }

        // Calcula o tempo decorrido e salva no jogador
        jgdr.score = getTimeDiff() / 1000.0; // Converte de milissegundos para segundos

        SalvaScore(jgdr);

        TelaReniciar(&correr);  // Passando a referência de correr para a função

        if (correr == 0) {
            break;  // Sai do loop principal se o jogador escolher não reiniciar
        }
    }

    for (i = 0; i < LINHA; i++) { // Liberando memória alocada
        free(labirinto[i]);
    }
    free(labirinto);

    screenDestroy(); // Finaliza a tela
    keyboardDestroy(); // Finaliza o teclado

    return 0;
} // Fim da main

// Inicio das funções declaradas acima

void TelaInicio() {
    screenClear();  // Limpando a tela para garantir que não há texto residual

    int offsetX = (MAXX - 30) / 2; // Tentando centralizar a mensagem na tela
    int offsetY = (MAXY - 10) / 2; // Tentando centralizar a mensagem na tela

    char ch;

    screenGotoxy(offsetX, offsetY); // Move o caracter para a posição calculada
    printf("* Bem-vindo ao MazeRun *");

    screenGotoxy(offsetX, offsetY + 1); // Move o caracter para a posição calculada
    printf("* Pressione 'c' para começar ou 'l' para sair! *");

    screenGotoxy(offsetX, offsetY + 2); // Move o caracter para a posição calculada
    printf("* Para jogar, use as teclas 'a', 'w', 's' e 'd' *");

    screenUpdate();  // Atualizando a tela para refletir as mudanças

    while (ch != 'c') {
        ch = readch();  // Esperando o jogador digitar 'c' para começar o game
    }
}

void TelaPedirNome(jogador *jgdr) {
    screenClear();  // Limpando a tela para garantir que não há texto residual

    int offsetX = (MAXX - 30) / 2; // Tentando centralizar a mensagem na tela
    int offsetY = (MAXY - 10) / 2; // Tentando centralizar a mensagem na tela

    screenGotoxy(offsetX, offsetY); // Move o caracter para a posição calculada
    printf("Digite o Nome do Jogador:");

    screenUpdate();  // Atualizando a tela para refletir as mudanças

    keyboardDestroy(); // Desativar captura de teclas temporariamente

    screenGotoxy(offsetX, offsetY + 1); // Move o caracter para a posição calculada
    fgets(jgdr->nome, sizeof(jgdr->nome), stdin);

    jgdr->nome[strcspn(jgdr->nome, "\n")] = 0;  // Remove o \n
    jgdr->chaves = 0;  // Inicia com zero chaves
    jgdr->score = 0;   // Inicia o score com zero
    strcpy(jgdr->saida, "");

    keyboardInit(); // Reinicializa captura de teclas após a entrada do nome

    screenUpdate();  // Atualizando a tela para refletir as mudanças
}

void DesenhaLabirinto(char **labirinto, jogador jgdr) { // Função para desenhar o labirinto na tela
    screenClear();  // Limpando a tela para garantir que não há texto residual

    int offsetX = (MAXX - COLUNA) / 2;
    int offsetY = (MAXY - LINHA) / 2;

    for (int y = 0; y < LINHA; y++) {
        screenGotoxy(offsetX + 1, offsetY + y + 1); // Move o caracter para a posição calculada
        for (int x = 0; x < COLUNA; x++) {
            char ch = labirinto[y][x];
            if (ch == '-' || ch == '|') {
                screenSetColor(WHITE, BLACK); // Paredes em branco
            } else if (ch == 'O') {
                screenSetColor(GREEN, BLACK); // Jogador em verde
            } else if (ch == 'S') {
                screenSetColor(BLUE, BLACK);   // Saída em vermelho
            } else if (ch == 'K') {
                screenSetColor(YELLOW, BLACK); // Chaves em amarelo
            }else if (ch == 'T') {
                screenSetColor(RED, BLACK); // Cadeado em vermelho
            }
            else {
                screenSetColor(WHITE, BLACK); // Caminhos em branco
            }
            printf("%c", ch); // Imprime o caractere
        }
    }
    screenGotoxy(offsetX + 25, offsetY + 1); // Move o caracter para a posição calculada
    printf("Quantidade de chaves coletadas: %d/3", jgdr.chaves);
    screenUpdate(); // Atualiza a tela para refletir as mudanças
}

void chaves(char **labirinto) {
    int chaves = 0;
    while (chaves < 3) {
        int x = rand() % COLUNA;
        int y = rand() % LINHA;
        if (labirinto[y][x] == ' ' && (x != personagem_x || y != personagem_y)) {
            labirinto[y][x] = 'K';
            chaves++;
        }
    }
}

void MostrarMensagemMorte(jogador *jgdr) {
    screenClear(); // Limpa a tela antes de exibir a mensagem

    char ch = '\0';

    int offsetX = (MAXX - 30) / 2; // Calcula a posição horizontal para centralizar a mensagem
    int offsetY = (MAXY - 1) / 2; // Calcula a posição vertical para centralizar a mensagem

    screenGotoxy(offsetX, offsetY); // Move o cursor para a posição calculada
    screenSetColor(RED, BLACK); // Define a cor do texto para vermelho
    printf("Você morreu :( Tente novamente! Quem sabe você tem mais sorte da próxima vez!"); // Exibe a mensagem
    screenGotoxy(offsetX, offsetY + 1); // Move o cursor para a posição calculada
    printf("* Aperte 'l' para sair *"); // Exibe a mensagem
    strcpy(jgdr->saida, "Não conseguiu sair");
    screenUpdate(); // Atualiza a tela para refletir as mudanças

    while (ch != 'l') {
        ch = readch();  // Esperando o jogador digitar 'l' para sair do game
    }
}

void MostrarMensagemVitoria(jogador *jgdr) {
    screenClear();
    char ch = '\0';

    int offsetX = (MAXX - 30) / 2; // Calcula a posição horizontal para centralizar a mensagem
    int offsetY = (MAXY - 1) / 2; // Calcula a posição vertical para centralizar a mensagem

    screenGotoxy(offsetX, offsetY); // Move o cursor para a posição calculada
    screenSetColor(GREEN, BLACK); // Define a cor do texto para verde
    printf("Parabéns! Você venceu!"); // Exibe a mensagem
    screenGotoxy(offsetX, offsetY + 1); // Move o cursor para a posição calculada (funciona como um \n)
    printf("* Aperte 'l' para sair *"); // Exibe a mensagem
    strcpy(jgdr->saida, "Conseguiu sair");
    screenUpdate(); // Atualiza a tela para refletir as mudanças

    while (ch != 'l') {
        ch = readch();  // Esperando o jogador digitar 'l' para sair do game
    }
}

void MoverPersonagem(int x, int y, char **labirinto, int *correr, jogador *jgdr) {
    if (labirinto[y][x] == ' ' || labirinto[y][x] == 'K') { // se a posição desejada for ' ' ou 'K', ele avança
        if (labirinto[y][x] == 'K') {
            chaves_cont++; // Incrementa o número de chaves coletadas
            ColetaChave(jgdr);
        } if (chaves_cont==3)
        {
            labirinto[17][9]=' ';
        }
        labirinto[personagem_y][personagem_x] = ' '; // Remove o personagem da posição antiga
        personagem_x = x; // Atualiza as coordenadas do personagem
        personagem_y = y; // Atualiza as coordenadas do personagem
        labirinto[personagem_y][personagem_x] = 'O'; // Coloca o personagem na nova posição
    } else if (labirinto[y][x] == '|' || labirinto[y][x] == '-') { // se a posição desejada for '1', o jogo acaba, aparecendo uma tela de você morreu
        labirinto[personagem_y][personagem_x] = 'O'; // Coloca o personagem na posição da parede
        DesenhaLabirinto(labirinto, *jgdr); // Atualiza o labirinto para mostrar o personagem na parede
        *correr = 0; // Altera o valor principal, pois foi chamada em um ponteiro
        MostrarMensagemMorte(jgdr); // Mostra a mensagem de morte
    } else if (labirinto[y][x] == 'S') {
        if (chaves_cont == 3) { // se a posição desejada for 'S', o jogo acaba, aparecendo uma tela de você ganhou
            *correr = 0; // Altera o valor principal, pois foi chamada em um ponteiro
            MostrarMensagemVitoria(jgdr); // Mostra a mensagem de vitória
        }
    }
}

void SalvaScore(jogador jgdr) {
    FILE *file = fopen("scores.txt", "a");  // Abre o arquivo em modo de append
    if (file == NULL) {
        perror("Falha ao abrir o arquivo");
        return;
    }
    fprintf(file, "Nome: %s, Chaves: %d, Tempo: %.2f segundos, %s\n", jgdr.nome, jgdr.chaves, jgdr.score, jgdr.saida);
    fclose(file);
}

void ColetaChave(jogador *jgdr) {
    jgdr->chaves++;  // Incrementa o contador de chaves
}

void ResetarJogo(jogador *jgdr, char **labirinto) {
    personagem_x = 1; // Resetar a posição inicial do personagem
    personagem_y = 0; // Resetar a posição inicial do personagem
    chaves_cont = 0; // Resetar o número de chaves coletadas

    // Resetar o labirinto
    for (int i = 0; i < LINHA; i++) {
        strcpy(labirinto[i], labirintoInicial[i]);
    }

    // Reposicionar as chaves
    chaves(labirinto);

    // Resetar o jogador
    jgdr->chaves = 0;

    // Redesenhar o labirinto
    DesenhaLabirinto(labirinto, *jgdr);
}


void TelaReniciar(int *correr) {
    screenClear();  // Limpando a tela para garantir que não há texto residual

    int offsetX = (MAXX - 30) / 2; // Tentando centralizar a mensagem na tela
    int offsetY = (MAXY - 10) / 2; // Tentando centralizar a mensagem na tela

    char ch;
    screenGotoxy(offsetX, offsetY); // Move o caracter para a posição calculada
    printf("Deseja reiniciar o jogo?");
    screenGotoxy(offsetX+1, offsetY+1); // Move o caracter para a posição calculada
    printf("* Pressione 's' para sim e 'n' para não *");
    screenUpdate();  // Atualizando a tela para refletir as mudanças

    while (1) {
        ch = readch();
        if (ch == 's') {
            *correr = 1;
            break;
        } else if (ch == 'n') {
            *correr = 0;
            break;
        }
    }
}

void DesenhaTempo() {
    int offsetX = 2; // Posição X para desenhar o tempo
    int offsetY = 2; // Posição Y para desenhar o tempo
    screenGotoxy(offsetX, offsetY); // Move o cursor para a posição calculada
    printf("Tempo: %.2f s", getTimeDiff() / 10000.0); // Imprime o tempo decorrido em segundos
    screenUpdate(); // Atualiza a tela para refletir as mudanças
}   