#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ---------------------------------------------------------------
// Struct que representa um item do inventário
// ---------------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Funções obrigatórias
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);

// ---------------------------------------------------------------
// Função principal
// ---------------------------------------------------------------
int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n===== SISTEMA DE INVENTÁRIO - NIVEL NOVATO =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch (opcao) {
            case 1:
                inserirItem(mochila, &total);
                break;
            case 2:
                removerItem(mochila, &total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// ---------------------------------------------------------------
// Função para inserir um item no inventário
// ---------------------------------------------------------------
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("A mochila esta cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("Nome do item: ");
    fgets(mochila[*total].nome, 30, stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = '\0'; // remove \n

    printf("Tipo do item (arma, municao, cura...): ");
    fgets(mochila[*total].tipo, 20, stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    getchar();

    (*total)++;

    printf("Item adicionado com sucesso!\n");
    listarItens(mochila, *total);
}

// ---------------------------------------------------------------
// Função para remover um item da mochila pelo nome
// ---------------------------------------------------------------
void removerItem(Item mochila[], int *total) {
    char nomeBusca[30];
    int found = -1;

    if (*total == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // Busca sequencial para encontrar o item
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Item nao encontrado!\n");
        return;
    }

    // Remoção: desloca todos os itens para a esquerda
    for (int i = found; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*total)--;

    printf("Item removido com sucesso!\n");
    listarItens(mochila, *total);
}

// ---------------------------------------------------------------
// Exibir todos os itens do inventário
// ---------------------------------------------------------------
void listarItens(Item mochila[], int total) {
    printf("\n===== ITENS NA MOCHILA =====\n");

    if (total == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// ---------------------------------------------------------------
// Busca sequencial: procura item pelo nome
// ---------------------------------------------------------------
void buscarItem(Item mochila[], int total) {
    char nomeBusca[30];
    int found = -1;

    printf("Digite o nome do item para buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Item nao encontrado!\n");
    } else {
        printf("\nItem encontrado:\n");
        printf("Nome: %s\n", mochila[found].nome);
        printf("Tipo: %s\n", mochila[found].tipo);
        printf("Quantidade: %d\n", mochila[found].quantidade);
    }
}
