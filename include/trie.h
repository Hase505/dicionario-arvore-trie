#ifndef TRIE_H
#define TRIE_H

/**
 * @file trie.h
 * @brief Definição da estrutura e API de uma Trie ternária (TST).
 */

#include <stdbool.h>
#include <stdlib.h>

/**
 * @struct no_trie
 * @brief Nó de uma Trie ternária (Ternary Search Trie).
 *
 * Cada nó armazena um caractere e três ponteiros:
 * - no_esquerdo: caracteres menores
 * - no_meio: próximo caractere da chave
 * - no_direito: caracteres maiores
 *
 * O campo terminal indica se o caminho até este nó
 * representa o fim de uma palavra válida.
 */
typedef struct no_trie {
    struct no_trie* no_esquerdo;
    struct no_trie* no_meio;
    struct no_trie* no_direito;
    bool terminal;
    char caractere;
} no_trie;

/**
 * @brief Cria um novo nó de Trie inicializado.
 *
 * Todos os ponteiros são inicializados como NULL
 * e os campos escalares como zero.
 *
 * @return Ponteiro para o nó criado ou NULL em caso de falha.
 */
no_trie* trie_criar();

/**
 * @brief Libera recursivamente toda a Trie.
 *
 * Percorre todas as subárvores e libera a memória associada.
 *
 * @param raiz Ponteiro para a raiz da Trie.
 */
void trie_destruir(no_trie* raiz);

/*
 * @brief Insere palavra na Trie.
 *
 * Assume raiz como nó sentinela e começa a inserir a partir
 * do no_meio da raiz.
 *
 * @param raiz Ponteiro para a raiz da Trie.
 * @param palavra String a ser inserida na Trie.
 */
void trie_inserir(no_trie* raiz, const char* palavra);

/*
 * @brief Lista todas as palavras contidas na Trie informada.
 *
 * Obtém um array de todas as palavras da Trie, em ordem
 * lexicográfica. Indica a quantidade de palavras encontradas.
 * O array de strings retornado deve ser liberado com trie_liberar_lista.
 *
 * @param raiz Ponteiro para a raiz da Trie.
 * @param quantidade Ponteiro para indicar quantidade de palavras encontradas.
 *
 * @return Array de palavras encontradas.
 */
char** trie_listar_palavras(no_trie* raiz, size_t* quantidade);

/*
 * @brief Realiza busca por prefixo na Trie.
 *
 * Retorna todas as palavras que contém o prefixo informado.
 *
 * @param raiz Ponteiro para a raiz da Trie.
 * @param prefixo String do prefixo.
 * @param quantidade Ponteiro para indicar quantidade de palavras encontradas.
 *
 * @return Array de palavras encontradas.
 */
char**
trie_buscar_por_prefixo(no_trie* raiz, const char* prefixo, size_t* quantidade);

/*
 * @brief Libera o array de palavras informado.
 *
 * @param palavras Array de palavras a ser liberado.
 * @param n Quantidade de palavras existentes no array.
 */
void trie_liberar_lista(char** palavras, size_t n);

#endif
