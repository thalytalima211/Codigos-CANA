#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
Implemente uma função em C que dado um array de tamanho N dessa estrutura 
(necessita de alocação dinâmica de memória), ordene o arraypelo campo escolhido pelo usuário. 
Cada campo deve ser ordenado por um método distinto. 
*/

struct pessoa {
    int Matricula;
    char Nome[30];
    float Nota;
};

void quickSort(struct pessoa *vetor, int baixo, int alto, int campo);
int particionar(struct pessoa *vetor, int baixo, int alto, int campo);
int comparar(struct pessoa a, struct pessoa b, int campo);
void trocar(struct pessoa *a, struct pessoa *b);
void imprimir(struct pessoa *vetor, int n);

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
        printf("1 - Ordenar por Matrícula\n");
        printf("2 - Ordenar por Nome\n");
        printf("3 - Ordenar por Nota\n");
        printf("Escolha: ");
        scanf("%d", &campo);
    
        if (campo >= 1 && campo <= 3) {
            quickSort(vetor, 0, n - 1, campo);
            printf("\n--- Resultado ordenado ---\n");
            imprimir(vetor, n);
        } else if (campo != 0) {
            printf("Opção inválida. Tente novamente.\n");
        }
    
    } while (campo != 0);

    free(vetor);
    return 0;
}

void quickSort(struct pessoa *vetor, int baixo, int alto, int campo) {
    if (baixo < alto) {
        int pi = particionar(vetor, baixo, alto, campo);
        quickSort(vetor, baixo, pi - 1, campo);
        quickSort(vetor, pi + 1, alto, campo);
    }
}

int particionar(struct pessoa *vetor, int baixo, int alto, int campo) {
    struct pessoa pivo = vetor[alto];
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        if (comparar(vetor[j], pivo, campo) < 0) {
            i++;
            trocar(&vetor[i], &vetor[j]);
        }
    }

    trocar(&vetor[i + 1], &vetor[alto]);
    return i + 1;
}

int comparar(struct pessoa a, struct pessoa b, int campo) {
    switch (campo) {
        case 1:
            return a.Matricula - b.Matricula;
        case 2:
            return strcmp(a.Nome, b.Nome);
        case 3:
            return (a.Nota > b.Nota) - (a.Nota < b.Nota);
        default:
            return 0;
    }
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
