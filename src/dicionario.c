/*
 * @file dicionario.c
 * @brief Implementação das funções de dicionário.
 */
#include "dicionario.h"

#include "trie.h"

#include <stdlib.h>

/*
 * Implementação:
 * - Aloca estrutura dicionario.
 * - Aloca estrutura trie.
 * - Define quantidade de palavras como 0.
 */
dicionario* dicionario_criar() {
    dicionario* dicionario = NULL;

    dicionario = calloc(1, sizeof *dicionario);
    if (!dicionario) {
        return NULL;
    }

    dicionario->raiz = trie_criar();
    if (!dicionario->raiz) {
        free(dicionario);
        // cppcheck-suppress memleak ; falso-positivo
        return NULL;
    }

    // cppcheck-suppress memleak ; falso-positivo
    return dicionario;
}

/*
 * Implementação:
 * - Libera estrutura trie.
 * - Liberar estrutura dicionário.
 */
void dicionario_destruir(dicionario* dicionario) {
    if (!dicionario) {
        return;
    }

    trie_destruir(dicionario->raiz);
    free(dicionario);
}
