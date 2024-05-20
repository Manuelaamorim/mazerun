/**
 * keyboard.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <termios.h>
#include <unistd.h>

#include "keyboard.h"

static struct termios initialSettings, newSettings;
static int peekCharacter;


void keyboardInit()
{
    tcgetattr(0,&initialSettings); // Obtém as configurações atuais do terminal
    newSettings = initialSettings; // Faz uma cópia das configurações
    newSettings.c_lflag &= ~ICANON; // Desativa o modo canônico (buffering de entrada)
    newSettings.c_lflag &= ~ECHO; // Desativa o eco (eco das teclas digitadas)
    newSettings.c_lflag &= ~ISIG; // Desativa sinais (como Ctrl+C)
    newSettings.c_cc[VMIN] = 1; // Define o número mínimo de caracteres para leitura
    newSettings.c_cc[VTIME] = 0; // Define o tempo de espera (timeout) para a leitura
    tcsetattr(0, TCSANOW, &newSettings); // Aplica as novas configurações imediatamente
}

void keyboardDestroy()
{
    tcsetattr(0, TCSANOW, &initialSettings); // Restaura as configurações originais do terminal
}

int keyhit()
{
    unsigned char ch;
    int nread;

    if (peekCharacter != -1) return 1; // Verifica se já há uma tecla armazenada
    
    newSettings.c_cc[VMIN]=0; // Configura o terminal para leitura não bloqueante
    tcsetattr(0, TCSANOW, &newSettings); // Configura o terminal para leitura não bloqueante
    nread = read(0,&ch,1); // Tenta ler um caractere do terminal
    newSettings.c_cc[VMIN]=1; // Restaura a configuração original
    tcsetattr(0, TCSANOW, &newSettings); // Restaura a configuração original
    
    if(nread == 1) 
    {
        peekCharacter = ch; //Se uma tecla foi lida, armazena-a e retorna 1
        return 1;
    }
    
    return 0; // Caso contrário, retorna 0
}

int readch()
{
    char ch;

    if(peekCharacter != -1)
    {
        ch = peekCharacter;
        peekCharacter = -1; // Se há uma tecla armazenada, retorna-a
        return ch;
    }
    read(0,&ch,1); // Caso contrário, lê uma tecla do terminal
    return ch; // Retorna a tecla lida
}
