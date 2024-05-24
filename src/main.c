#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"

#define COLUNA 20 // Definir o tamanho do labirinto
#define LINHA 19 // Definir o tamanho do labirinto

int personagem_x = 1; // Posição inicial do personagem
int personagem_y = 0; // Posição inicial do personagem
int chaves_cont = 0; // Número de chaves coletadas

typedef struct {
    char nome[100];  // Nome do jogador
    int chaves;      // Número de chaves coletadas
    double score;    // Score do jogador, medido em segundos
} Jogador;

void InicializaJogador(Jogador *jogador) {
    printf("Digite seu nome: ");
    fgets(jogador->nome, sizeof(jogador->nome), stdin);
    jogador->nome[strcspn(jogador->nome, "\n")] = 0;  // Remove o \n
    jogador->chaves = 0;  // Inicia com zero chaves
    jogador->score = 0;   // Inicia o score com zero
}

void ColetaChave(Jogador *jogador) {
    jogador->chaves++;  // Incrementa o contador de chaves
    printf("Você coletou %d chave(s).\n", jogador->chaves);
}

void SalvaScore(Jogador jogador) {
    FILE *file = fopen("scores.txt", "a");  // Abre o arquivo em modo de append
    if (file == NULL) {
        perror("Falha ao abrir o arquivo");
        return;
    }
    fprintf(file, "Nome: %s, Chaves: %d, Tempo: %.2f segundos\n", jogador.nome, jogador.chaves, jogador.score);
    fclose(file);
}

void TelaInicio()
{
    screenClear();  // Limpando a tela para garantir que não há texto residual

    int offsetX = (MAXX - 30) / 2; // Tentando centralizar a mensagem na tela
    int offsetY = (MAXY - 10) / 2; // Tentando centralizar a mensagem na tela

    char ch = '\0';

    screenGotoxy(offsetX, offsetY ); // Move o caracter para a posição calculada
    printf("* Bem-vindo ao MazeRun *");

    screenGotoxy(offsetX, offsetY + 1); // Move o caracter para a posição calculada
    printf("* Pressione 'c' para começar *");

    screenGotoxy(offsetX, offsetY + 2); // Move o caracter para a posição calculada
    printf("* Para jogar, use as teclas 'a', 'w', 's' e 'd' *");

    screenUpdate();  // Atualizando a tela para refletir as mudanças

    while (ch != 'c')
    {
        ch = readch();  // Esperando o jogador digitar 'c' para começar o game
    }
}

void DesenhaLabirinto(char **labirinto) { // Função para desenhar o labirinto na tela

    screenClear();  // Limpando a tela para garantir que não há texto residual

    int offsetX = (MAXX - COLUNA) / 2;
    int offsetY = (MAXY - LINHA) / 2;

    for (int y = 0; y < LINHA; y++) {
        screenGotoxy(offsetX + 1, offsetY + y + 1); // Move o caracter para a posição calculada
        for (int x = 0; x < COLUNA; x++) {
            char ch = labirinto[y][x];
            if (ch == '1') {
                screenSetColor(WHITE, BLACK); // Paredes em branco
            } else if (ch == 'O') {
                screenSetColor(GREEN, BLACK); // Jogador em verde
            } else if (ch == 'S') {
                screenSetColor(BLUE, BLACK);   // Saída em vermelho
            } 
            else if (ch == 'K') {
                screenSetColor(YELLOW, BLACK); // Chaves em amarelo
            }else {
                screenSetColor(WHITE, BLACK); // Caminhos em branco
            }
            printf("%c", ch); // Imprime o caractere
        }
    }
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

int MostrarMensagemMorte() {

    screenClear(); // Limpa a tela antes de exibir a mensagem

    //char ch='\0';

    int offsetX = (MAXX - 30) / 2; // Calcula a posição horizontal para centralizar a mensagem
    int offsetY = (MAXY - 1) / 2; // Calcula a posição vertical para centralizar a mensagem

    screenGotoxy(offsetX, offsetY); // Move o cursor para a posição calculada
    screenSetColor(RED, BLACK); // Define a cor do texto para vermelho
    printf("Você morreu :( Tente novamente! Quem sabe você tem mais sorte da próxima vez!");; // Exibe a mensagem
    screenGotoxy(offsetX, offsetY + 1); // Move o cursor para a posição calculada
    printf("Aperte 'r' para recomeçar ou 'q' para sair!");; // Exibe a mensagem
    screenUpdate(); // Atualiza a tela para refletir as mudanças

    // while (ch != 'l')
    // {
    //     ch = readch();  // Esperando o jogador digitar 'c' para sair do game

    // } 
    char ch;
    
    while (1) {
        ch = readch();  // Aguarda a entrada do usuário
        if (ch == 'r') {
            return 1;  // Reiniciar o jogo
        } else if (ch == 'q') {
            return 0;  // Sair do jogo
        }
    }
}

void MostrarMensagemVitoria() {
    screenClear();
    int offsetX = (MAXX - 30) / 2; // Calcula a posição horizontal para centralizar a mensagem
    int offsetY = (MAXY - 1) / 2; // Calcula a posição vertical para centralizar a mensagem

    screenGotoxy(offsetX, offsetY); // Move o cursor para a posição calculada
    screenSetColor(GREEN, BLACK); // Define a cor do texto para verde
    printf("Parabéns! Você venceu!"); // Exibe a mensagem
    screenGotoxy(offsetX, offsetY + 1); // Move o cursor para a posição calculada (funciona como um \n)
    printf("Aperte 'r' para recomeçar!"); // Exibe a mensagem
    screenUpdate(); // Atualiza a tela para refletir as mudanças

    getchar(); // Espera o usuário pressionar uma tecla para encerrar
}

void MoverPersonagem(int x, int y, char **labirinto, int *correr) {
    if (labirinto[y][x] == ' ' || labirinto[y][x] == 'K') { // se a posição desejada for ' ' ou 'K', ele avança
    if (labirinto[y][x] == 'K') {
        chaves_cont++; // Incrementa o número de chaves coletadas
    }
    labirinto[personagem_y][personagem_x] = ' '; // Remove o personagem da posição antiga
    personagem_x = x; // Atualiza as coordenadas do personagem
    personagem_y = y; // Atualiza as coordenadas do personagem
    labirinto[personagem_y][personagem_x] = 'O'; // Coloca o personagem na nova posição
    }
    else if (labirinto[y][x] == '1') { // se a posição desejada for '1', o jogo acaba, aparecendo uma tela de você morreu
        labirinto[personagem_y][personagem_x] = 'O'; // Coloca o personagem na posição da parede
        DesenhaLabirinto(labirinto); // Atualiza o labirinto para mostrar o personagem na parede
        *correr = 0; // Altera o valor principal, pois foi chamada em um ponteiro
        MostrarMensagemMorte(); // Mostra a mensagem de morte
    }

    else if (labirinto[y][x] == 'S') {
        if (chaves_cont == 3) { // se a posição desejada for 'S', o jogo acaba, aparecendo uma tela de você ganhou
        *correr = 0; // Altera o valor principal, pois foi chamada em um ponteiro
        MostrarMensagemVitoria(); // Mostra a mensagem de vitória
    }
}    
}
int main() {
    int i; 
    int correr = 1;
    char **labirinto;
    Jogador jogador;
    InicializaJogador(&jogador);

    labirinto = (char **)calloc(LINHA, sizeof(char*)); // Alocando dinamicamente a matriz do labirinto
    for (i = 0; i < LINHA; i++) {
        labirinto[i] = (char *)calloc(COLUNA + 1, sizeof(char));
    }

    char labirintoInicial[LINHA][COLUNA + 1] = { // Preenchendo o labirinto com o conteúdo desejado
    "1O111111111111111111",
    "1  111111          1",
    "11 11   11 1111 11 1",
    "11    1    1     1 1",
    "1111111111 1 11  1 1",
    "1   1   11 1111    1",
    "11  1 1 11  1   11 1",
    "1     1 11111 1 1 11",
    "1 11 11       1  1 1",
    "1  1 11111111111   1",
    "11 1 11   11    11 1",
    "1  1 11 1    11  1 1",
    "1  1    1111 111 111",
    "11   1111    111 111",
    "11 1     1111      1",
    "1   111  1    1  1 1",
    "1 1   1 1  11 111  1",
    "1   1 1 1 1  1     1",
    "111111111S1111111111"
    };

    for (i = 0; i < LINHA; i++) { // Copia a matriz estática para a matriz dinâmica
        strcpy(labirinto[i], labirintoInicial[i]);
    }

    srand(time(NULL)); // Inicializa o gerador de números aleatórios com a hora atual
    chaves(labirinto); // Coloca as chaves em posições aleatórias
    keyboardInit(); // Inicializa o teclado
    screenInit(1); // Inicializa a tela e desenha as bordas

    TelaInicio(); // Mostra a tela de início

    screenClear(); // Limpa a tela antes de desenhar o labirinto

    DesenhaLabirinto(labirinto); // Desenha o labirinto na tela
    clock_t inicio_tempo = clock(); //Inicializa o relógio

    do{
        while (correr) { // Criei um while true que pode virar false
            if (keyhit())
            {
                // Verifica se alguma tecla foi pressionada
                char ch = readch(); // Lê a tecla que foi pressionada

                while (1)
                {

                    if (ch == 'w')
                    {
                        MoverPersonagem(personagem_x, personagem_y - 1, labirinto, &correr); // Modifica as coordenadas do personagem
                        break;

                    }

                    else if (ch == 's')
                    {

                        MoverPersonagem(personagem_x, personagem_y + 1, labirinto, &correr); // Modifica as coordenadas do personagem
                        break;

                    }

                    else if (ch == 'a')
                    {

                        MoverPersonagem(personagem_x - 1, personagem_y, labirinto, &correr); // Modifica as coordenadas do personagem
                        break;

                    }

                    else if (ch == 'd')
                    {

                        MoverPersonagem(personagem_x + 1, personagem_y, labirinto, &correr); // Modifica as coordenadas do personagem
                        break;

                    }

                    else if (ch == 'l')
                    {
                        correr = 0;
                        break;
                    }

                    else
                        break;
                }

                DesenhaLabirinto(labirinto); // Desenha novamente o labirinto na tela com a posição atualizada do personagem
            }
        }
    } while(MostrarMensagemMorte());

    clock_t final_tempo = clock();
    double tempo_gasto = (double)(final_tempo - inicio_tempo) / CLOCKS_PER_SEC;  // Tempo em segundos
    jogador.score = tempo_gasto;

    SalvaScore(jogador);

    for (i = 0; i < LINHA; i++) { // Liberando memória alocada
        free(labirinto[i]);
    }
    free(labirinto);


    screenDestroy(); // Finaliza a tela
    keyboardDestroy(); // Finaliza o teclado

    return 0;
}
