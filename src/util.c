/**
 * @file util.c
 * @brief Implementação das funções auxiliares.
 */

#include "util.h"

#include <ctype.h>
#include <string.h>

/*
 * Implementação:
 * - Valida palavra comparando com caracteres a-z e A-Z.
 */
int palavra_valida(const char* str) {
    for (; *str; str++) {
        if (!((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z'))) {
            return 0;
        }
    }
    return 1;
}

/*
 * Implementação:
 * - Remove espaços no começo da string.
 * - Remove espaços no final da string.
 * - O conteúdo da string será deslocado se for necessário.
 */
void trim(char* str) {
    if (!str) {
        return;
    }

    // Remover espaços do início
    char* inicio = str;
    while (isspace((unsigned char) *inicio)) {
        inicio++;
    }

    // Se a string for só espaços
    if (*inicio == '\0') {
        str[0] = '\0';
        return;
    }

    // Remover espaços do final
    char* fim = inicio + strlen(inicio) - 1;
    while (fim > inicio && isspace((unsigned char) *fim)) {
        fim--;
    }

    // Novo final de string
    *(fim + 1) = '\0';

    // Copiar resultado para o início da string
    if (str != inicio) {
        // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
        memmove(str, inicio, fim - inicio + 2); // +2 pra incluir '\0'
    }
}

/*
 * Implementação:
 * - Utiliza a função 'tolower' em todos os caracteres.
 */
void string_para_minusculo(char* s) {
    if (!s) {
        return;
    }

    for (; *s; s++) {
        *s = (char) tolower((unsigned char) *s);
    }
}
