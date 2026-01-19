#include <stddef.h>
#include <stdio.h>

#include "dicionario.h"
#include "trie.h"

int main() {
    dicionario* dicionario = dicionario_criar();

    // Teste: ler arquivo
    dicionario_adicionar_de_arquivo(dicionario, "teste.txt");

    dicionario_adicionar_palavra(dicionario, "abacaxi");
    dicionario_adicionar_palavra(dicionario, "abertura");
    dicionario_adicionar_palavra(dicionario, "romulo");
    dicionario_adicionar_palavra(dicionario, "antedeguemon");

    size_t quantidade = 0;
    char** palavras = trie_listar_palavras(dicionario->raiz, &quantidade);

    printf("Todas as palavras:\n");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }
    printf("\n");

    trie_liberar_lista(palavras, quantidade);
    quantidade = 0;

    printf("Quantidade de palavras: %zu\n\n", dicionario->total_palavras);

    palavras = dicionario_buscar_por_prefixo(dicionario, " A", &quantidade);

    printf("Todas as palavras após buscar por prefixo 'a':\n");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }
    printf("\n");

    trie_liberar_lista(palavras, quantidade);
    quantidade = 0;

    dicionario_remover_palavra(dicionario, "abacaxi");
    palavras = trie_listar_palavras(dicionario->raiz, &quantidade);

    printf("Todas as palavras após remover 'abacaxi':\n");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }
    printf("\n");
    printf("Quantidade de palavras: %zu\n\n", dicionario->total_palavras);

    trie_liberar_lista(palavras, quantidade);
    quantidade = 0;

    dicionario_remover_de_arquivo(dicionario, "teste.txt");
    palavras = trie_listar_palavras(dicionario->raiz, &quantidade);
    printf("Todas as palavras após remover do arquivo:\n");
    for (size_t i = 0; i < quantidade; i++) {
        printf("%s\n", palavras[i]);
    }

    trie_liberar_lista(palavras, quantidade);

    dicionario_destruir(dicionario);

    return 0;
}
