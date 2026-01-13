/**
 * @file trie.c
 * @brief Implementação das funções da Trie ternária.
 */

#include "trie.h"

#include "util.h"

#include <stdbool.h>
#include <stdlib.h>

/*
 * Implementação:
 * - Função interna utilizada para inserção de forma recursiva.
 * - Insere caractere a caractere na Trie, utilizando nós esquerdos,
 *   direitos e do meio.
 */
static no_trie* trie_inserir_rec(no_trie* no, const char* palavra) {
    if (!no) {
        no = calloc(1, sizeof *no);
        if (!no) {
            return NULL;
        }
        no->caractere = *palavra;
    }

    if (*palavra < no->caractere) {
        no_trie* tmp = trie_inserir_rec(no->no_esquerdo, palavra);
        if (!tmp) {
            return no;
        }
        no->no_esquerdo = tmp;
    } else if (*palavra > no->caractere) {
        no_trie* tmp = trie_inserir_rec(no->no_direito, palavra);
        if (!tmp) {
            return no;
        }
        no->no_direito = tmp;
    } else {
        if (*(palavra + 1) == '\0') {
            no->terminal = true;
        } else {
            no_trie* tmp = trie_inserir_rec(no->no_meio, palavra + 1);
            if (!tmp) {
                return no;
            }
            no->no_meio = tmp;
        }
    }

    return no;
}

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

/*
 * Implementação:
 * - Assume raiz como sentinela
 * - Chama função interna trie_inserir_rec a partir do
 *   no_meio da raiz.
 */
void trie_inserir(no_trie* raiz, const char* palavra) {
    if (!raiz || !palavra || !*palavra) {
        return;
    }

    // Inserção sempre começa no filho do meio da raiz sentinela
    raiz->no_meio = trie_inserir_rec(raiz->no_meio, palavra);
}
