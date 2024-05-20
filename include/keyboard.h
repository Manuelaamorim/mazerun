/**
 * keyboard.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

void keyboardInit(); // Inicializa as configurações do teclado

void keyboardDestroy(); // Restaura as configurações iniciais do teclado
    
int keyhit(); // Verifica se alguma tecla foi pressionada

int readch(); // Lê a tecla pressionada

#endif /* __KEYBOARD_H__ */
