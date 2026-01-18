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

/**
 * @brief Lê linhas de um arquivo (função pública).
 *
 * Carrega todas as linhas do arquivo em um array dinâmico.
 * Remove caractere newline das linhas.
 * Ignora linhas vazias.
 *
 * @param caminho Caminho do arquivo a ser lido.
 * @param quantidade Ponteiro para receber quantidade de linhas lidas.
 *
 * @return Array de strings com as linhas do arquivo, ou NULL em caso de
 * falha. Deve ser liberado com trie_liberar_lista.
 */
char** dicionario_ler_arquivo(const char* caminho, size_t* quantidade);

/*
 * @brief Adiciona palavra ao dicionário.
 *
 * Se palavra for adicionada com sucesso
 * quantidade de palavras é incrementada.
 *
 * @param dicionario Ponteiro para dicionário utilizado.
 * @param palavra Palavra a ser adicionada no dicionário.
 *
 * @return true se foi possível adicionar, false se não.
 */
bool dicionario_adicionar_palavra(dicionario* dicionario, const char* palavra);

/*
 * @brief Remove uma palavra no dicionário.
 *
 * Se palavra for removida com sucesso
 * quantidade de palavras é decrementada.
 *
 * @param dicionario Ponteiro para dicionário utilizado.
 * @param palavra Palavra que será removida no dicionário.
 *
 * @return true se foi possível remover, false se não.
 */
bool dicionario_remover_palavra(dicionario* dicionario, const char* palavra);

/*
 * @brief Busca palavras por prefixo no dicionário.
 *
 * O retorno deve ser liberado pelo chamador.
 *
 * @param dicionario Ponteiro para dicionário utilizado.
 * @param prefixo Prefixo das palavras que serão retornadas.
 * @param quantidade Ponteiro informando a quantidade de palavras retornadas.
 *
 * @return Array de strings armazenando as palavras encontradas.
 */
char** dicionario_buscar_por_prefixo(dicionario* dicionario,
                                     const char* prefixo,
                                     size_t* quantidade);

/*
 * @brief Obtém todas as palavras contidas no dicionário.
 *
 * O retorno deve ser liberado pelo chamador.
 *
 * @param dicionario Ponteiro para dicionário utilizado.
 * @param quantidade Ponteiro informando a quantidade de palavras retornadas.
 *
 * @return Array de strings armazenando as palavras encontradas.
 */
char** dicionario_listar_palavras(dicionario* dicionario, size_t* quantidade);

#endif
