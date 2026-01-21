#ifndef MENU_H
#define MENU_H

/*
 * @file menu.h
 * @brief Definição de menus interativos com usuário.
 */

#include "dicionario.h"

/*
 * @brief Menu inicial do programa.
 *
 * Solicita ao usuário o caminho para o arquivo contendo
 * as palavras que serão inseridas no dicionário.
 *
 * O dicionário retornado deve ser liberado pelo chamador.
 *
 * @return Ponteiro para o dicionário criado.
 */
dicionario* menu_inicial();

/*
 * @brief Menu principal do programa.
 *
 * Exibe as funcionalidades principais do programa ao usuário,
 * obtendo seu input.
 *
 * @param dicionario Ponteiro para o dicionário que será utilizado pelo usuário.
 */
void menu_principal(dicionario* dicionario);

#endif
