#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
Implemente uma função em C que dado um array de tamanho N dessa estrutura 
(necessita de alocação dinâmica de memória), ordene o array pelo campo escolhido pelo usuário. 
Cada campo deve ser ordenado por um método distinto. 
*/

struct pessoa {
    int Matricula;
    char Nome[30];
    float Nota;
};

void trocar(struct pessoa *a, struct pessoa *b);
void imprimir(struct pessoa *vetor, int n);
int comparar(struct pessoa a, struct pessoa b, int campo);

// QuickSort para Matricula
void quickSort(struct pessoa *vetor, int baixo, int alto);
int particionar(struct pessoa *vetor, int baixo, int alto);

// MergeSort para Nome
void mergeSort(struct pessoa *vetor, int esq, int dir);
void merge(struct pessoa *vetor, int esq, int meio, int dir);

// InsertionSort para Nota
void insertionSort(struct pessoa *vetor, int n);

int main() {
    int n, campo;

    printf("Digite o número de pessoas: ");
    scanf("%d", &n);
    struct pessoa *vetor = malloc(n * sizeof(struct pessoa));

    for (int i = 0; i < n; i++) {
        printf("Pessoa %d:\n", i+1);
        printf("Matrícula: "); scanf("%d", &vetor[i].Matricula);
        printf("Nome: "); scanf(" %[^\n]", vetor[i].Nome);
        printf("Nota: "); scanf("%f", &vetor[i].Nota);
    }

    do {
        printf("\nComo deseja ordenar o vetor?\n");
        printf("0 - Encerrar\n");
        printf("1 - Ordenar por Matrícula (QuickSort)\n");
        printf("2 - Ordenar por Nome (MergeSort)\n");
        printf("3 - Ordenar por Nota (InsertionSort)\n");
        printf("Escolha: ");
        scanf("%d", &campo);
    
        switch (campo) {
            case 1:
                quickSort(vetor, 0, n - 1);
                break;
            case 2:
                mergeSort(vetor, 0, n - 1);
                break;
            case 3:
                insertionSort(vetor, n);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

        if (campo >= 1 && campo <= 3) {
            printf("\n--- Resultado ordenado ---\n");
            imprimir(vetor, n);
        }
    
    } while (campo != 0);

    free(vetor);
    return 0;
}

void trocar(struct pessoa *a, struct pessoa *b) {
    struct pessoa temp = *a;
    *a = *b;
    *b = temp;
}

void imprimir(struct pessoa *vetor, int n) {
    for (int i = 0; i < n; i++) {
        printf("Matrícula: %d | Nome: %s | Nota: %.2f\n",
               vetor[i].Matricula, vetor[i].Nome, vetor[i].Nota);
    }
}

// ---------- Funções QuickSort (Matrícula) ----------
void quickSort(struct pessoa *vetor, int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(vetor, baixo, alto);
        quickSort(vetor, baixo, pi - 1);
        quickSort(vetor, pi + 1, alto);
    }
}

int particionar(struct pessoa *vetor, int baixo, int alto) {
    struct pessoa pivo = vetor[alto];
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        if (vetor[j].Matricula < pivo.Matricula) {
            i++;
            trocar(&vetor[i], &vetor[j]);
        }
    }

    trocar(&vetor[i + 1], &vetor[alto]);
    return i + 1;
}

// ---------- Funções MergeSort (Nome) ----------
void mergeSort(struct pessoa *vetor, int esq, int dir) {
    if (esq < dir) {
        int meio = (esq + dir) / 2;
        mergeSort(vetor, esq, meio);
        mergeSort(vetor, meio + 1, dir);
        merge(vetor, esq, meio, dir);
    }
}

void merge(struct pessoa *vetor, int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    struct pessoa *L = malloc(n1 * sizeof(struct pessoa));
    struct pessoa *R = malloc(n2 * sizeof(struct pessoa));

    for (int i = 0; i < n1; i++) L[i] = vetor[esq + i];
    for (int j = 0; j < n2; j++) R[j] = vetor[meio + 1 + j];

    int i = 0, j = 0, k = esq;
    while (i < n1 && j < n2) {
        if (strcmp(L[i].Nome, R[j].Nome) <= 0)
            vetor[k++] = L[i++];
        else
            vetor[k++] = R[j++];
    }

    while (i < n1) vetor[k++] = L[i++];
    while (j < n2) vetor[k++] = R[j++];

    free(L);
    free(R);
}

// ---------- Funções InsertionSort (Nota) ----------
void insertionSort(struct pessoa *vetor, int n) {
    for (int i = 1; i < n; i++) {
        struct pessoa key = vetor[i];
        int j = i - 1;

        while (j >= 0 && vetor[j].Nota > key.Nota) {
            vetor[j + 1] = vetor[j];
            j--;
        }

        vetor[j + 1] = key;
    }
}