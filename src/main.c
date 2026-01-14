
#include "trie.h"
#include <stddef.h>
#include <stdio.h>

#include "trie.h"

int main() {
    printf("Hello World\n");

    no_trie* raiz = trie_criar();

    trie_inserir(raiz, "abacaxi");
    trie_inserir(raiz, "antes");
    trie_inserir(raiz, "romulo");
    trie_inserir(raiz, "arte");

    size_t quantidade = 0;

    char** palavras = trie_listar_palavras(raiz, &quantidade);
    printf("--- Antes da remocao ---\n");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }

    trie_liberar_lista(palavras, quantidade);
    printf("\nRemovendo 'romulo'...\n");
    trie_remover(raiz, "romulo");
    palavras = trie_listar_palavras(raiz, &quantidade);
    printf("--- Depois da remocao ---\n");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }

    trie_liberar_lista(palavras, quantidade);
    printf("\nRemovendo 'antes'...\n");
    trie_remover(raiz, "antes");
    palavras = trie_listar_palavras(raiz, &quantidade);
    printf("--- Depois da remocao ---\n");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }

    trie_liberar_lista(palavras, quantidade);
    printf("\nRemovendo 'abacaxi'...\n");
    trie_remover(raiz, "abacaxi");
    palavras = trie_listar_palavras(raiz, &quantidade);
    printf("--- Depois da remocao ---\n");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }

    trie_liberar_lista(palavras, quantidade);
    printf("\nRemovendo 'arte'...\n");
    trie_remover(raiz, "arte");
    palavras = trie_listar_palavras(raiz, &quantidade);
    printf("--- Depois da remocao ---\n");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }
    trie_liberar_lista(palavras, quantidade);
    printf("\nRemovendo 'abacaxi'...\n");
    trie_remover(raiz, "abacaxi");
    palavras = trie_listar_palavras(raiz, &quantidade);
    printf("--- Depois da remocao ---\n");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }

    trie_liberar_lista(palavras, quantidade);
    trie_destruir(raiz);

    return 0;
}
