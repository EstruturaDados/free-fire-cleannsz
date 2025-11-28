#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================================================================
//                         STRUCTS
// ================================================================

// Item padrão da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ================================================================
//              VARIÁVEIS GLOBAIS DE CONTAGEM
// ================================================================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

#define MAX_ITENS 50

// ================================================================
//                  FUNÇÕES DO VETOR
// ================================================================
void inserirItemVetor(Item vetor[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    printf("Nome: ");
    scanf(" %[^\n]", vetor[*total].nome);

    printf("Tipo: ");
    scanf(" %[^\n]", vetor[*total].tipo);

    printf("Quantidade: ");
    scanf("%d", &vetor[*total].quantidade);

    (*total)++;
    printf("Item inserido!\n");
}

void removerItemVetor(Item vetor[], int *total) {
    if (*total == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome a remover: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < *total; i++) {
        if (strcmp(vetor[i].nome, nomeBusca) == 0) {
            for (int j = i; j < *total - 1; j++) {
                vetor[j] = vetor[j + 1];
            }
            (*total)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item nao encontrado!\n");
}

void listarVetor(Item vetor[], int total) {
    if (total == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    printf("\n--- Itens no Vetor ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
    }
}

int buscarSequencialVetor(Item vetor[], int total, char nome[]) {
    comparacoesSequencial = 0;

    for (int i = 0; i < total; i++) {
        comparacoesSequencial++;
        if (strcmp(vetor[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

void ordenarVetor(Item vetor[], int total) {
    // Bubble Sort
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Item tmp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = tmp;
            }
        }
    }
    printf("Vetor ordenado!\n");
}

int buscarBinariaVetor(Item vetor[], int total, char nome[]) {
    comparacoesBinaria = 0;
    int inicio = 0, fim = total - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(vetor[meio].nome, nome);

        if (cmp == 0) return meio;
        else if (cmp > 0) fim = meio - 1;
        else inicio = meio + 1;
    }
    return -1;
}

// ================================================================
//                FUNÇÕES DA LISTA ENCADEADA
// ================================================================
void inserirItemLista(No** lista) {
    No* novo = (No*) malloc(sizeof(No));

    printf("Nome: ");
    scanf(" %[^\n]", novo->dados.nome);

    printf("Tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = *lista;
    *lista = novo;

    printf("Item inserido!\n");
}

void removerItemLista(No** lista) {
    if (*lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome a remover: ");
    scanf(" %[^\n]", nomeBusca);

    No* atual = *lista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            if (anterior == NULL)
                *lista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Item removido!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item nao encontrado!\n");
}

void listarLista(No* lista) {
    if (lista == NULL) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    printf("\n--- Itens na Lista Encadeada ---\n");
    No* atual = lista;

    while (atual != NULL) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

int buscarSequencialLista(No* lista, char nome[]) {
    comparacoesSequencial = 0;
    No* atual = lista;

    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) return 1;
        atual = atual->proximo;
    }
    return 0;
}

// ================================================================
//                         MENU PRINCIPAL
// ================================================================
int main() {
    Item mochilaVetor[MAX_ITENS];
    int totalVetor = 0;

    No* mochilaLista = NULL;

    int opcaoEstrutura;
    int opcaoOperacao;

    do {
        printf("\n===== NIVEL AVENTUREIRO =====\n");
        printf("Escolha a estrutura:\n");
        printf("1 - Vetor\n");
        printf("2 - Lista Encadeada\n");
        printf("0 - Sair\n-> ");
        scanf("%d", &opcaoEstrutura);

        if (opcaoEstrutura == 0) break;

        do {
            printf("\n----- Operacoes -----\n");
            printf("1 - Inserir\n");
            printf("2 - Remover\n");
            printf("3 - Listar\n");
            printf("4 - Busca Sequencial\n");
            if (opcaoEstrutura == 1) {
                printf("5 - Ordenar Vetor\n");
                printf("6 - Busca Binaria\n");
            }
            printf("0 - Voltar\n-> ");
            scanf("%d", &opcaoOperacao);

            if (opcaoEstrutura == 1) {  
                // -------------------------------------
                //              VETOR
                // -------------------------------------
                char nomeBusca[30];

                switch (opcaoOperacao) {
                    case 1: inserirItemVetor(mochilaVetor, &totalVetor); break;
                    case 2: removerItemVetor(mochilaVetor, &totalVetor); break;
                    case 3: listarVetor(mochilaVetor, totalVetor); break;
                    case 4:
                        printf("Nome para buscar: ");
                        scanf(" %[^\n]", nomeBusca);
                        int idx;
                        idx = buscarSequencialVetor(mochilaVetor, totalVetor, nomeBusca);
                        if (idx != -1) printf("Item encontrado: %s\n", mochilaVetor[idx].nome);
                        else printf("Item nao encontrado.\n");
                        printf("Comparacoes: %d\n", comparacoesSequencial);
                        break;
                    case 5:
                        ordenarVetor(mochilaVetor, totalVetor);
                        break;
                    case 6:
                        printf("Nome para buscar: ");
                        scanf(" %[^\n]", nomeBusca);
                        int pos;
                        pos = buscarBinariaVetor(mochilaVetor, totalVetor, nomeBusca);
                        if (pos != -1) printf("Item encontrado: %s\n", mochilaVetor[pos].nome);
                        else printf("Item nao encontrado.\n");
                        printf("Comparacoes (binaria): %d\n", comparacoesBinaria);
                        break;
                }

            } else {
                // -------------------------------------
                //            LISTA ENCADEADA
                // -------------------------------------
                char nomeBusca[30];

                switch (opcaoOperacao) {
                    case 1: inserirItemLista(&mochilaLista); break;
                    case 2: removerItemLista(&mochilaLista); break;
                    case 3: listarLista(mochilaLista); break;
                    case 4:
                        printf("Nome para buscar: ");
                        scanf(" %[^\n]", nomeBusca);
                        if (buscarSequencialLista(mochilaLista, nomeBusca))
                            printf("Item encontrado!\n");
                        else
                            printf("Item nao encontrado.\n");
                        printf("Comparacoes: %d\n", comparacoesSequencial);
                        break;
                }
            }

        } while (opcaoOperacao != 0);

    } while (opcaoEstrutura != 0);

    printf("Saindo...\n");
    return 0;
}
