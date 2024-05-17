#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

void free_maze(int linhas, char **maze) {

    for (int i = 0; i < linhas; i++)
    {
        free(maze[i]);
    }

    free(maze);   
}

void read_maze(int *linhas, int *colunas, char ***maze) {

    char tmp[13];
    FILE *f = fopen("txt/map.txt", "r");
    if (f == NULL)
    {
        printf("Erro ao ler o labirinto.");
        exit(1);
    }

    fscanf(f, "%d %d ", linhas, colunas);
    *maze = (char **)calloc(*linhas, sizeof(char *));  
    for (int i = 0; i < *linhas; i++)
    {
        (*maze)[i] = (char *)calloc(*colunas + 1, sizeof(char));
    
        fgets(tmp, 13, f);
        if (tmp[strlen(tmp) - 1] == '\n')
        {
            tmp[strlen(tmp) - 1] = 0;
        }

        strcpy((*maze)[i], tmp);
    }
    
    fclose(f);   
}

void draw_maze(int linhas, int colunas, char **maze) {
    int scale_x = 7;  
    int scale_y = 3;

    int startX = MINX + 1;
    int startY = MINY + 1;

    for (int y = 0; y < linhas; y++) {
        for (int sy = 0; sy < scale_y; sy++) { 
            for (int x = 0; x < colunas; x++) {
                for (int sx = 0; sx < scale_x; sx++) {  
                    screenGotoxy(startX + x * scale_x + sx, startY + y * scale_y + sy);
                    if ((maze)[y][x] == '1')
                    {
                        printf("%c", '|');
                    }
                    else {

                        printf(" ");
                    }
                    
                }
            }
        }
    }
}

int main() 
{
    int linhas;
    int colunas;
    char **maze;
    screenHideCursor();
    read_maze(&linhas, &colunas, &maze);
    draw_maze(linhas, colunas, maze);
}
