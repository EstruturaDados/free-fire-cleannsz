#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20

// ===============================================================
//                         STRUCT PRINCIPAL
// ===============================================================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;   // 1 = prioridade baixa | 10 = altíssima prioridade
} Componente;

// ===============================================================
//                       VARIÁVEIS GLOBAIS
// ===============================================================
long comparacoes = 0;  // usado para medir desempenho

// ===============================================================
//                FUNÇÕES DE ORDENAÇÃO
// ===============================================================

// ---------------------------------------------------------------
// Bubble Sort — Ordena por nome (string)
// ---------------------------------------------------------------
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// ---------------------------------------------------------------
// Insertion Sort — Ordena por tipo (string)
// ---------------------------------------------------------------
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
        }
        comparacoes++;  // última comparação que quebra o while
        v[j + 1] = chave;
    }
}

// ---------------------------------------------------------------
// Selection Sort — Ordena por prioridade (int)
// ---------------------------------------------------------------
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
}

// ===============================================================
//                      BUSCA BINÁRIA POR NOME
// ===============================================================
int buscaBinariaPorNome(Componente v[], int n, char nome[]) {
    int ini = 0, fim = n - 1;
    long comp = 0;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comp++;

        int cmp = strcmp(v[meio].nome, nome);

        if (cmp == 0) {
            comparacoes = comp;
            return meio;
        }
        if (cmp > 0) fim = meio - 1;
        else ini = meio + 1;
    }

    comparacoes = comp;
    return -1;
}

// ===============================================================
//                        MOSTRAR COMPONENTES
// ===============================================================
void mostrarComponentes(Componente v[], int n) {
    printf("\n===== COMPONENTES =====\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// ===============================================================
//          FUNÇÃO PRA MEDIR TEMPO E EXECUTAR O ALGORITMO
// ===============================================================
double medirTempo(void (*algoritmo)(Componente[], int),
                  Componente v[], int n) {

    clock_t inicio = clock();
    algoritmo(v, n);
    clock_t fim = clock();

    return (double)(fim - inicio) / CLOCKS_PER_SEC;  // segundos
}

// ===============================================================
//                          MAIN
// ===============================================================
int main() {
    Componente lista[MAX_COMP];
    int total = 0;
    int op;

    // --------------------------
    //     Entrada dos dados
    // --------------------------
    printf("===== NIVEL MESTRE =====\n");
    printf("Quantos componentes deseja cadastrar (max 20)? ");
    scanf("%d", &total);
    getchar();  

    if (total > MAX_COMP) total = MAX_COMP;

    for (int i = 0; i < total; i++) {
        printf("\nComponente %d\n", i + 1);

        printf("Nome: ");
        fgets(lista[i].nome, 30, stdin);
        lista[i].nome[strcspn(lista[i].nome, "\n")] = 0;

        printf("Tipo: ");
        fgets(lista[i].tipo, 20, stdin);
        lista[i].tipo[strcspn(lista[i].tipo, "\n")] = 0;

        printf("Prioridade (1 a 10): ");
        scanf("%d", &lista[i].prioridade);
        getchar();
    }

    // --------------------------
    //       MENU PRINCIPAL
    // --------------------------
    do {
        printf("\n===== MENU =====\n");
        printf("1 - Ordenar por nome (Bubble Sort)\n");
        printf("2 - Ordenar por tipo (Insertion Sort)\n");
        printf("3 - Ordenar por prioridade (Selection Sort)\n");
        printf("4 - Buscar componente-chave (apenas apos ordenacao por nome)\n");
        printf("5 - Exibir componentes\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar();

        // Copia auxiliar para testes
        Componente copia[MAX_COMP];
        memcpy(copia, lista, sizeof(lista));

        if (op == 1) {
            double tempo = medirTempo(bubbleSortNome, copia, total);
            printf("\nOrdenado por NOME (Bubble Sort)\n");
            mostrarComponentes(copia, total);
            printf("\nComparacoes: %ld\nTempo: %.6fs\n", comparacoes, tempo);
            memcpy(lista, copia, sizeof(lista));  

        } else if (op == 2) {
            double tempo = medirTempo(insertionSortTipo, copia, total);
            printf("\nOrdenado por TIPO (Insertion Sort)\n");
            mostrarComponentes(copia, total);
            printf("\nComparacoes: %ld\nTempo: %.6fs\n", comparacoes, tempo);
            memcpy(lista, copia, sizeof(lista));

        } else if (op == 3) {
            double tempo = medirTempo(selectionSortPrioridade, copia, total);
            printf("\nOrdenado por PRIORIDADE (Selection Sort)\n");
            mostrarComponentes(copia, total);
            printf("\nComparacoes: %ld\nTempo: %.6fs\n", comparacoes, tempo);
            memcpy(lista, copia, sizeof(lista));

        } else if (op == 4) {
            char chave[30];
            printf("Digite o nome do componente-chave: ");
            fgets(chave, 30, stdin);
            chave[strcspn(chave, "\n")] = 0;

            int pos = buscaBinariaPorNome(lista, total, chave);

            if (pos != -1) {
                printf("\nComponente-chave encontrado!\n");
                printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                    lista[pos].nome, lista[pos].tipo, lista[pos].prioridade);
            } else {
                printf("\nComponente NAO encontrado!\n");
            }

            printf("Comparacoes na busca binaria: %ld\n", comparacoes);

        } else if (op == 5) {
            mostrarComponentes(lista, total);
        }

    } while (op != 0);

    printf("Encerrando o sistema...\n");
    return 0;
}
