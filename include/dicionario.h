#ifndef DICIONARIO_H
#define DICIONARIO_H

/*
 * @file dicionario.h
 * @brief Definição de estrutura e API de um dicionário.
 */

#include "trie.h"

#include <stddef.h>

/**
 * @struct dicionario
 * @brief Representa um dicionário (conjunto de palavras únicas).
 *
 * É armazenado a raiz da árvore TRIE e a quantidade total de palavras.
 */
typedef struct dicionario {
    no_trie* raiz;
    size_t total_palavras;
} dicionario;

/*
 * @brief Inicializa uma estrutura de dicionário
 *
 * @return Ponteiro para o dicionário criado ou NULL em caso de falha.
 */
dicionario* dicionario_criar();

/*
 * @brief Libera a estrutura de dicionário.
 *
 * @param dicionario Dicionário a ser liberado.
 */
void dicionario_destruir(dicionario* dicionario);

#endif
