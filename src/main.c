#include "dicionario.h"
#include "menu.h"

int main() {
    // cppcheck-suppress constVariablePointer
    dicionario* dicionario = menu_inicial();
    if (!dicionario) {
        return -1;
    }

    menu_principal(dicionario);

    dicionario_destruir(dicionario);

    return 0;
}
