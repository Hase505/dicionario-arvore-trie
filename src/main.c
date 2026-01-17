#include <stddef.h>
#include <stdio.h>

#include "dicionario.h"
#include "trie.h"

int main() {
    no_trie* raiz = trie_criar();

    // Teste: ler arquivo
    size_t lidas = 0;
    char** linhas = dicionario_ler_arquivo("teste.txt", &lidas);

    if (linhas) {
        printf("Arquivo lido: %zu linhas\n", lidas);
        printf("Primeiras 5 linhas:\n");
        for (size_t i = 0; i < lidas && i < 5; i++) {
            printf("  %zu: %s\n", i + 1, linhas[i]);
        }
        printf("\n");
        trie_liberar_lista(linhas, lidas);
    } else {
        printf("Erro ao ler arquivo\n\n");
    }

    trie_inserir(raiz, "abacaxi");
    trie_inserir(raiz, "abertura");
    trie_inserir(raiz, "romulo");
    trie_inserir(raiz, "antedeguemon");

    size_t quantidade = 0;
    char** palavras = trie_listar_palavras(raiz, &quantidade);

    printf("Todas as palavras:\n");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }
    printf("\n");

    trie_liberar_lista(palavras, quantidade);
    quantidade = 0;

    trie_remover(raiz, "abertura");
    palavras = trie_listar_palavras(raiz, &quantidade);

    printf("Todas as palavras após remover 'abertura':\n");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }
    printf("\n");

    trie_liberar_lista(palavras, quantidade);
    quantidade = 0;

    palavras = trie_buscar_por_prefixo(raiz, "a", &quantidade);

    printf("Todas as palavras após buscar por prefixo 'a':\n");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }
    printf("\n");

    trie_liberar_lista(palavras, quantidade);
    trie_destruir(raiz);

    return 0;
}
