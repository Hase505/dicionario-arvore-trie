/*
 * @file dicionario.c
 * @brief Implementação das funções de dicionário.
 */
#include "dicionario.h"

#include "trie.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_LINHA 256

/*
 * Implementação:
 * - Abre arquivo em modo leitura.
 * - Lê cada linha e armazena em array dinâmico.
 * - Remove caractere newline das linhas.
 * - Ignora linhas vazias.
 * - Retorna array de strings com quantidade total.
 */
static char** ler_arquivo(const char* caminho, size_t* quantidade) {
    FILE* arquivo = fopen(caminho, "r");
    if (!arquivo) {
        if (quantidade) {
            *quantidade = 0;
        }
        return NULL;
    }

    char buffer[TAM_LINHA];
    char** palavras = NULL;
    size_t contador = 0;
    size_t capacidade = 10;

    palavras = (char**) malloc(capacidade * sizeof(char*));
    if (!palavras) {
        fclose(arquivo);
        if (quantidade) {
            *quantidade = 0;
        }
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), arquivo)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[0] == '\0') {
            continue;
        }

        if (contador >= capacidade) {
            capacidade *= 2;
            char** temp =
                (char**) realloc((char*) palavras, capacidade * sizeof(char*));
            if (!temp) {
                trie_liberar_lista(palavras, contador);
                fclose(arquivo);
                if (quantidade) {
                    *quantidade = 0;
                }
                return NULL;
            }
            palavras = temp;
        }

        palavras[contador] = string_dup(buffer);
        if (!palavras[contador]) {
            trie_liberar_lista(palavras, contador);
            fclose(arquivo);
            if (quantidade) {
                *quantidade = 0;
            }
            return NULL;
        }

        contador++;
    }

    fclose(arquivo);

    if (quantidade) {
        *quantidade = contador;
    }

    return palavras;
}

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
char** dicionario_ler_arquivo(const char* caminho, size_t* quantidade) {
    return ler_arquivo(caminho, quantidade);
}
