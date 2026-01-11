/**
 * @file trie.c
 * @brief Implementação das funções da Trie ternária.
 */

#include "trie.h"

#include <stdlib.h>

/*
 * Implementação:
 * - Usa calloc para garantir inicialização zero de todos os campos,
 *   evitando lixo em ponteiros e no flag terminal.
 * - Retorna apenas o nó raiz; a estrutura cresce sob demanda.
 */
no_trie* trie_criar() {
    return calloc(1, sizeof(no_trie));
}

/*
 * Implementação:
 * - Destruição em pós-ordem para garantir que filhos sejam liberados
 *   antes do nó atual.
 * - Função é NULL-safe: permite chamadas com raiz == NULL.
 * - Assume estrutura acíclica (invariante da trie).
 */
void trie_destruir(no_trie* raiz) {
    if (!raiz) {
        return;
    }

    trie_destruir(raiz->no_esquerdo);
    trie_destruir(raiz->no_meio);
    trie_destruir(raiz->no_direito);

    free(raiz);
}
