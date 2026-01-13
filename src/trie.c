/**
 * @file trie.c
 * @brief Implementação das funções da Trie ternária.
 */

#include "trie.h"

#include "util.h"

#include <stdbool.h>
#include <stdlib.h>

/**
 * @struct lista_palavras
 * @brief Array dinâmico de strings.
 *
 * Armazena o array de strings de forma dinâmica,
 * sempre atualizando a capacidade e tamanho.
 */
typedef struct {
    char** palavras;
    size_t tamanho;
    size_t capacidade;
} lista_palavras;

/*
 * Implementação:
 * - Assume capacidade inicial como 8.
 * - Quando tamanho for igual a capacidade, capacidade é dobrada.
 */
static bool lista_push(lista_palavras* l, const char* palavra) {
    if (l->tamanho == l->capacidade) {
        size_t nova_cap = l->capacidade ? l->capacidade * 2 : 8;
        char** tmp =
            (char**) realloc((void*) l->palavras, nova_cap * sizeof *tmp);
        if (!tmp) {
            return false;
        }
        l->palavras = tmp;
        l->capacidade = nova_cap;
    }

    char* dup = string_dup(palavra);
    if (!dup) {
        return false;
    }

    l->palavras[l->tamanho++] = dup;
    return true;
}

/*
 * Implementação:
 * - Função utilitária para garantir crescimento seguro de buffer.
 * - Assume capacidade inicial de 32.
 * - Quando necessário, dobra a capacidade.
 */
static bool
garantir_tamanho_buffer(char** buf, size_t* cap, size_t necessario) {
    if (necessario <= *cap) {
        return true;
    }

    size_t nova_cap = *cap ? *cap * 2 : 32;
    while (nova_cap < necessario) {
        nova_cap *= 2;
    }

    char* tmp = realloc(*buf, nova_cap);
    if (!tmp) {
        return false;
    }

    *buf = tmp;
    *cap = nova_cap;
    return true;
}

/*
 * Implementação:
 * - Função interna utilizada para obter as palavras contidas na Trie.
 * - Obtém palavras em ordem lexicográfica.
 */
static bool tst_coletar(no_trie* no,
                        char** buffer,
                        size_t* capacidade,
                        size_t profundidade,
                        lista_palavras* lista) {
    if (!no) {
        return true;
    }

    if (!tst_coletar(
            no->no_esquerdo, buffer, capacidade, profundidade, lista)) {
        return false;
    }

    if (no->caractere != '\0') {
        if (!garantir_tamanho_buffer(buffer, capacidade, profundidade + 2)) {
            return false;
        }

        (*buffer)[profundidade] = no->caractere;

        if (no->terminal) {
            (*buffer)[profundidade + 1] = '\0';
            if (!lista_push(lista, *buffer)) {
                return false;
            }
        }

        if (!tst_coletar(
                no->no_meio, buffer, capacidade, profundidade + 1, lista)) {
            return false;
        }
    }

    return tst_coletar(no->no_direito, buffer, capacidade, profundidade, lista);
}

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

/*
 * Implementação:
 * - Utiliza a estrutura lista_palavras para obter as palavras
 *   sem definir limite máximo.
 * - Utiliza a função interna tst_coletar para obter as palavras.
 * - Retorna array de strings e indica quantidade de palavras
 *   encontradas.
 */
char** trie_listar_palavras(no_trie* raiz, size_t* quantidade) {
    if (!raiz || !quantidade) {
        return NULL;
    }

    lista_palavras lista = {0};
    char* buffer = NULL;
    size_t cap = 0;

    if (!tst_coletar(raiz->no_meio, &buffer, &cap, 0, &lista)) {
        free(buffer);
        trie_liberar_lista(lista.palavras, lista.tamanho);
        return NULL;
    }

    free(buffer);

    *quantidade = lista.tamanho;
    return lista.palavras;
}

/*
 * Implementação:
 * - Percorre o array de strings e libera cada palavra.
 */
void trie_liberar_lista(char** palavras, size_t n) {
    if (!palavras) {
        return;
    }

    for (size_t i = 0; i < n; i++) {
        free(palavras[i]);
    }

    free((void*) palavras);
}
