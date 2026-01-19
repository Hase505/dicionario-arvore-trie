/*
 * @file dicionario.c
 * @brief Implementação das funções de dicionário.
 */
#include "dicionario.h"

#include "trie.h"
#include "util.h"

#include <stddef.h>
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
 * - Realiza cópia da string informada.
 * - Realiza trim da cópia.
 * - Converte a cópia para minúsculo.
 * - Verifica se a string final é uma palavra válida.
 * - Se for válida, retorna string final; do contrário, retorna NULL.
 */
static char* normalizar_palavra(const char* palavra) {
    char* palavra_normalizada = string_dup(palavra);

    trim(palavra_normalizada);
    string_para_minusculo(palavra_normalizada);
    if (!palavra_valida(palavra_normalizada)) {
        free(palavra_normalizada);
        return NULL;
    }

    return palavra_normalizada;
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

/*
 * Implementação:
 * - Normaliza e valida palavra antes de inserir.
 * - Insere na árvore trie.
 * - Se inserção for válida, incrementa quantidade de palavras.
 */
bool dicionario_adicionar_palavra(dicionario* dicionario, const char* palavra) {
    if (!dicionario || !palavra) {
        return false;
    }
    bool inseriu = false;

    char* palavra_normalizada = normalizar_palavra(palavra);
    if (!palavra_normalizada) {
        return inseriu;
    }

    if (trie_inserir(dicionario->raiz, palavra_normalizada)) {
        dicionario->total_palavras++;
        inseriu = true;
    }

    free(palavra_normalizada);
    return inseriu;
}

/*
 * Implementação:
 * - Normaliza e valida palavra antes de remover.
 * - Remove na árvore trie.
 * - Se remoção for válida, decrementa quantidade de palavras.
 */
bool dicionario_remover_palavra(dicionario* dicionario, const char* palavra) {
    if (!dicionario || !palavra) {
        return false;
    }

    bool removeu = false;

    char* palavra_normalizada = normalizar_palavra(palavra);
    if (!palavra_normalizada) {
        return removeu;
    }

    trim(palavra_normalizada);
    string_para_minusculo(palavra_normalizada);
    if (!palavra_valida(palavra_normalizada)) {
        free(palavra_normalizada);
        return removeu;
    }

    if (trie_remover(dicionario->raiz, palavra_normalizada)) {
        dicionario->total_palavras--;
        removeu = true;
    }

    free(palavra_normalizada);
    return removeu;
}

/*
 * Implementação:
 * - Normaliza e valida palavra antes de buscar por prefixo.
 * - Busca por prefixo na trie.
 */
char** dicionario_buscar_por_prefixo(dicionario* dicionario,
                                     const char* prefixo,
                                     size_t* quantidade) {
    if (!dicionario) {
        return NULL;
    }

    char* palavra_normalizada = normalizar_palavra(prefixo);
    if (!palavra_normalizada) {
        return NULL;
    }

    char** lista = trie_buscar_por_prefixo(
        dicionario->raiz, palavra_normalizada, quantidade);

    free(palavra_normalizada);
    return lista;
}

/*
 * Implementação:
 * - Realiza listagem das palavras na trie.
 */
char** dicionario_listar_palavras(dicionario* dicionario, size_t* quantidade) {
    if (!dicionario) {
        return NULL;
    }
    return trie_listar_palavras(dicionario->raiz, quantidade);
}

/*
 * Implementação:
 * - Lê todas as palavras que estão contidas no arquivo (1 por linha).
 * - Adiciona as palavras que são válidas.
 */
// cppcheck-suppress constParameterPointer
bool dicionario_adicionar_de_arquivo(dicionario* dicionario,
                                     const char* caminho) {
    if (!dicionario || !caminho) {
        return false;
    }

    size_t quantidade = 0;
    char** palavras = ler_arquivo(caminho, &quantidade);
    if (!palavras) {
        return false;
    }

    for (size_t i = 0; i < quantidade; i++) {
        dicionario_adicionar_palavra(dicionario, palavras[i]);
    }

    trie_liberar_lista(palavras, quantidade);
    return true;
}

/*
 * Implementação:
 * - Lê todas as palavras que estão contidas no arquivo (1 por linha).
 * - Remove as palavras que são válidas.
 */
// cppcheck-suppress constParameterPointer
bool dicionario_remover_de_arquivo(dicionario* dicionario,
                                   const char* caminho) {
    if (!dicionario || !caminho) {
        return false;
    }

    size_t quantidade = 0;
    char** palavras = ler_arquivo(caminho, &quantidade);
    if (!palavras) {
        return false;
    }

    for (size_t i = 0; i < quantidade; i++) {
        dicionario_remover_palavra(dicionario, palavras[i]);
    }

    trie_liberar_lista(palavras, quantidade);
    return true;
}
