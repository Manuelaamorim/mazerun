#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"

// Define o tamanho do labirinto
#define COLUNA 20
#define LINHA 19

// Função para desenhar o labirinto na tela
void desenhaLabirinto(char **labirinto)
{
    int offsetX = (MAXX - COLUNA) / 2;
    int offsetY = (MAXY - LINHA) / 2;

    for (int y = 0; y < LINHA; y++)
    {
        screenGotoxy(offsetX + 1, offsetY + y + 1); // Define a posição do cursor com o deslocamento calculado
        for (int x = 0; x < COLUNA; x++)
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
    int i;
    char **labirinto;

    // Alocação dinâmica da matriz labirinto
    labirinto = (char **)calloc(LINHA, sizeof(char*));
    for (i = 0; i < LINHA; i++)
    {
        labirinto[i] = (char *)calloc(COLUNA + 1, sizeof(char));
    }

    // Preenchendo o labirinto com o conteúdo desejado
    char labirintoInicial[LINHA][COLUNA + 1] = {
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

    for (i = 0; i < LINHA; i++) // Copia a matriz estática para a matriz dinámica
    {
        strcpy(labirinto[i], labirintoInicial[i]);
    }

    // Inicializa a tela e desenha as bordas
    screenInit(1);

    // Desenha o labirinto na tela
    desenhaLabirinto(labirinto);

    // Aguarda o usuário pressionar Enter para finalizar
    getchar();

    // Libera a memória alocada
    for (i = 0; i < LINHA; i++)
    {
        free(labirinto[i]);
    }
    free(labirinto);

    // Finaliza a tela
    screenDestroy();

    return 0;
}
