#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"

#define COLUNA 20 // Definir o tamanho do labirinto
#define LINHA 19 // Definir o tamanho do labirinto

int personagem_x = 1; // Posição inicial do personagem
int personagem_y = 0; // Posição inicial do personagem


void DesenhaLabirinto(char **labirinto) { // Função para desenhar o labirinto na tela
    int offsetX = (MAXX - COLUNA) / 2;
    int offsetY = (MAXY - LINHA) / 2;

    for (int y = 0; y < LINHA; y++) {
        screenGotoxy(offsetX + 1, offsetY + y + 1); // Define a posição do cursor com o deslocamento calculado
        for (int x = 0; x < COLUNA; x++) {
            char ch = labirinto[y][x];
            if (ch == '1') {
                screenSetColor(WHITE, BLACK); // Paredes em branco
            } else if (ch == 'E') {
                screenSetColor(GREEN, BLACK); // Jogador em verde
            } else if (ch == 'S') {
                screenSetColor(RED, BLACK);   // Saída em vermelho
            } else {
                screenSetColor(WHITE, BLACK); // Caminhos em branco
            }
            printf("%c", ch); // Imprime o caractere
        }
    }
    screenUpdate(); // Atualiza a tela para refletir as mudanças
}

void MoverPersonagem(int x, int y, char **labirinto, int *correr) {
    if (labirinto[y][x] == ' ') { // se a posição desejada for ' ', ele avança
        labirinto[personagem_y][personagem_x] = ' '; // Remove o personagem da posição antiga
        personagem_x = x; // Atualiza as coordenadas do personagem
        personagem_y = y; // Atualiza as coordenadas do personagem
        labirinto[personagem_y][personagem_x] = 'E'; // Coloca o personagem na nova posição
    }

    else if (labirinto[y][x] == 'S') { // se a posição desejada for 'S', o jogo acaba
        *correr=0; // Altera o valor principal, pois foi chamada em um ponteiro
    }

    else if (labirinto[y][x] == '1') { // se a posição desejada for '1', o jogo acaba
        *correr=0; // Altera o valor principal, pois foi chamada em um ponteiro
    }
}

int main() {
    int i;
    int correr = 1;
    char **labirinto;


    labirinto = (char **)calloc(LINHA, sizeof(char*)); // Alocando dinâmicamente a matriz do labirinto
    for (i = 0; i < LINHA; i++) {
        labirinto[i] = (char *)calloc(COLUNA + 1, sizeof(char));
    }

    char labirintoInicial[LINHA][COLUNA + 1] = { // Preenchendo o labirinto com o conteúdo desejado
        "1E111111111111111111",
        "1  111111          1",
        "11 11   11 1111 11 1",
        "11    1    1     1 1",
        "1111111111 1 11  1 1",
        "1   1   11 1 11    1",
        "11  1 1 11      11 1",
        "1     1 11111 1 1 11",
        "1 11 11       1  1 1",
        "1  1 11111111111   1",
        "11 1 11   11    11 1",
        "1  1 11 1    11  1 1",
        "1  1    1111 111 111",
        "11   1111    111 111",
        "11 1     1111    111",
        "1   111  1    111111",
        "1 1   1 1  11 111111",
        "1   1 1 1 1        1",
        "111111111S1111111111"
    };

    for (i = 0; i < LINHA; i++) { // Copia a matriz estática para a matriz dinâmica
        strcpy(labirinto[i], labirintoInicial[i]);
    }

    keyboardInit(); // Inicializa o teclado
    screenInit(1); // Inicializa a tela e desenha as bordas
    DesenhaLabirinto(labirinto); // Desenha o labirinto na tela

    while (correr) {
        if (keyhit()) { // Verifica se alguma tecla foi pressionada
            char ch = readch(); // Lê a tecla que foi pressionada

            while (1)
            {

                if (ch=='w')
                {

                    MoverPersonagem(personagem_x, personagem_y - 1, labirinto, &correr);
                    break;

                }

                else if (ch=='s')
                {

                    MoverPersonagem(personagem_x, personagem_y + 1, labirinto, &correr);
                    break;

                }

                else if (ch=='a')
                {

                    MoverPersonagem(personagem_x - 1, personagem_y, labirinto, &correr);
                    break;

                }

                else if (ch=='d')
                {

                    MoverPersonagem(personagem_x + 1, personagem_y, labirinto, &correr);
                    break;

                }

                else if (ch=='l')
                {

                    correr=0;
                    break;

                }

                else
                    break;

            }

            DesenhaLabirinto(labirinto); // Desenha novamente o labirinto na tela com a posição atualizada do personagem
        }


    }

    for (i = 0; i < LINHA; i++) { // Liberando memória alocada
        free(labirinto[i]);
    }
    free(labirinto);

    screenDestroy(); // Finaliza a tela
    keyboardDestroy(); // Finaliza o teclado

    return 0;
}
