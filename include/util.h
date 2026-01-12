#ifndef UTIL_H
#define UTIL_H

/**
 * @file util.h
 * @brief Definição das funções auxiliares.
 */

/**
 * @brief Verifica se a palavra informada é válida.
 *
 * Verifica se todos os caracteres são letras (maiúsculas e minúsculas).
 *
 * @param str String a ser validada.
 *
 * @return 1 se a palavra for válida ou 0 se for inválida.
 */
int palavra_valida(const char* str);

/**
 * @brief Remove espaços à esquerda e à direita da string.
 *
 * @param str String a ser alterada.
 */
void trim(char* str);

#endif
