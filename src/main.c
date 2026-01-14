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

    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }

    trie_liberar_lista(palavras, quantidade);

    printf("Busca pelo prefixo 'a':\n");
    palavras = trie_buscar_por_prefixo(raiz, "a", &quantidade);

    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }

    trie_liberar_lista(palavras, quantidade);
    trie_destruir(raiz);

    return 0;
}
