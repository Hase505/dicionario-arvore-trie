#include "menu.h"
#include "dicionario.h"
#include "trie.h"
#include "util.h"
#include <ctype.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define PATH_MAX 256

void limpar_tela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static size_t min(size_t a, size_t b) {
    return (a < b) ? a : b;
}
static void aguardar_tela() {
    printf("Pressione qualquer tecla para continuar...\n");
    getchar();
}

static void inicio_menu() {
    printf("--------------------DICIONARIO--------------------\n");
}

static void menu_exibir_opcoes() {
    printf("1 - Consultar palavra\n");
    printf("2 - Imprimir dicionário\n");
    printf("3 - Carregar arquivo de remoção\n");
    printf("0 - Sair\n");
    printf("\n");
}

static int menu_ler_opcao(size_t* saida) {
    char buffer[64];
    char* endptr;
    unsigned long long valor;

    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return 0; // erro de leitura
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if (buffer[0] == '-') {
        return 0; // rejeita número negativo
    }

    errno = 0;
    valor = strtoull(buffer, &endptr, 10);

    if (endptr == buffer || errno == ERANGE) {
        return 0; // erro na conversão
    }

    while (isspace((unsigned char) *endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return 0; // caracteres inválidos após número
    }

    if (valor > SIZE_MAX) {
        return 0; // valor maior que size_t máximo
    }

    *saida = (size_t) valor;
    return 1; // sucesso
}

static void menu_consultar_prefixo(dicionario* dicionario) {
    char prefixo[PATH_MAX];

    limpar_tela();
    inicio_menu();

    printf("Informe o prefixo:\n");
    fgets(prefixo, sizeof prefixo, stdin);

    size_t quantidade = 0;
    char** palavras =
        dicionario_buscar_por_prefixo(dicionario, prefixo, &quantidade);
    if (!palavras) {
        printf("\nNenhuma palavra encontrada.\n");
        aguardar_tela();
        return;
    }

    printf("\n");
    for (size_t i = 0; i < min(quantidade - 1, 9); i++) {
        printf("%s, ", palavras[i]);
    }
    printf("%s\n\n", palavras[min(quantidade - 1, 9)]);

    trie_liberar_lista(palavras, quantidade);

    aguardar_tela();
}

static void menu_imprimir_dicionario(dicionario* dicionario) {
    size_t quantidade = 0;
    char** palavras = dicionario_listar_palavras(dicionario, &quantidade);
    if (!palavras) {
        limpar_tela();
        inicio_menu();
        printf("Nenhuma palavra encontrada.\n");
        aguardar_tela();
        return;
    }

    limpar_tela();
    inicio_menu();

    for (size_t i = 0; i < quantidade - 1; i++) {
        printf("%s, ", palavras[i]);
    }
    printf("%s\n\n", palavras[quantidade - 1]);

    trie_liberar_lista(palavras, quantidade);

    aguardar_tela();
}

void menu_carregar_arquivo_remocao(dicionario* dicionario) {
    char caminho[PATH_MAX];

    while (1) {
        limpar_tela();
        inicio_menu();

        printf("Informe o caminho do arquivo (ou 'sair'):\n");
        if (!fgets(caminho, sizeof caminho, stdin)) {
            return;
        }

        trim(caminho);

        if (strcmp(caminho, "sair") == 0) {
            return;
        }

        if (dicionario_remover_de_arquivo(dicionario, caminho)) {
            return;
        }

        printf("\nErro ao carregar arquivo.\n");
        aguardar_tela();
    }
}
dicionario* menu_inicial(void) {

    char caminho[PATH_MAX];

    while (1) {
        limpar_tela();
        inicio_menu();

        printf("Informe o caminho do arquivo (ou 'sair'):\n");
        if (!fgets(caminho, sizeof caminho, stdin)) {
            return NULL;
        }

        trim(caminho);

        if (strcmp(caminho, "sair") == 0) {
            return NULL;
        }

        dicionario* d = dicionario_criar();
        if (!d) {
            printf("Erro interno.\n");
            return NULL;
        }

        if (dicionario_adicionar_de_arquivo(d, caminho)) {
            return d;
        }

        dicionario_destruir(d);
        printf("\nErro ao carregar arquivo.\n");
        aguardar_tela();
    }
}

void menu_principal(dicionario* d) {
    size_t opcao;

    do {
        limpar_tela();

        inicio_menu();
        menu_exibir_opcoes();
        menu_ler_opcao(&opcao);

        switch (opcao) {
        case 1:
            menu_consultar_prefixo(d);
            break;
        case 2:
            menu_imprimir_dicionario(d);
            break;
        case 3:
            menu_carregar_arquivo_remocao(d);
            break;
        case 0:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}
