#include <stdio.h>
#include <stdlib.h>
#include "screen.h"

// Define o tamanho do labirinto
#define coluna 20
#define linha 20

// Define o labirinto como uma matriz de caracteres
char labirinto_inicial[linha][coluna + 1] = {
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

//aloca dinamicamente o labirinto
void aloca_labirinto(char ***labirinto) {

    *labirinto = (char **)calloc(linha, sizeof(char *));

    for (int i = 0; i < linha; i++)
    {
        (*labirinto)[i] = (int *)calloc((coluna + 1), sizeof(int));
    }
}

void preenche_labirinto(char **labirinto) {

    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna + 1; j++)
        {
            labirinto[i][j] = labirinto_inicial[i][j];
        }
    }   
}
// Função para desenhar o labirinto na tela
void desenhaLabirinto(char **labirinto)
{
    int offsetX = (MAXX - coluna) / 2;
    int offsetY = (MAXY - linha) / 2;

    for (int y = 0; y < linha; y++)
    {
        screenGotoxy(offsetX + 1, offsetY + y + 1); // Define a posição do cursor com o deslocamento calculado
        for (int x = 0; x < coluna; x++)
        {
            char ch = labirinto[y][x];
            if (ch == '1')
            {
                screenSetColor(WHITE, BLACK); // Paredes em branco
            }
            else if (ch == 'E')
            {
                screenSetColor(GREEN, BLACK); // Jogador em verde
            }
            else if (ch == 'S')
            {
                screenSetColor(RED, BLACK);   // Saída em vermelho
            }
            else
            {
                screenSetColor(WHITE, BLACK); // Caminhos em branco
            }
            printf("%c", ch); // Imprime o caractere
        }
    }
    screenUpdate(); // Atualiza a tela para refletir as mudanças
}

int main()
{
    char **labirinto;
    // Inicializa a tela e desenha as bordas
    screenInit(1);
    aloca_labirinto(&labirinto);
    preenche_labirinto(labirinto);

    // Desenha o labirinto na tela
    desenhaLabirinto(labirinto);

    // Aguarda o usuário pressionar Enter para finalizar
    getchar();

    // Finaliza a tela
    screenDestroy();

    return 0;
}