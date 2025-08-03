#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* 
Implemente uma função em C que dado um array de tamanho N dessa estrutura 
(necessita de alocação dinâmica de memória), ordene o array pelo campo escolhido pelo usuário. 
Cada campo deve ser ordenado por um método distinto. 
*/

// Estrutura principal
struct pessoa {
    int matricula;
    char nome[30];
    float nota;
};

// ---------- Protótipos das funções ----------
// Para Matricula
void ordenarPorRadix(struct pessoa *pessoas, int n);
int obterDigito(int valor, int w, int base);

// Para Nome
void ordenarPorMerge(struct pessoa *pessoas, int esquerda, int direita);
void mesclarPorNome(struct pessoa *pessoas, int esquerda, int meio, int direita);

// Para Nota
void ordenarPorShell(struct pessoa *pessoas, int n);

// ====================== MAIN ======================

int main() {
    int n, opcao;

    printf("Digite o número de pessoas: ");
    scanf("%d", &n);

    struct pessoa *pessoas = malloc(n * sizeof(struct pessoa));

    // Leitura dos dados
    for (int i = 0; i < n; i++) {
        printf("\nPessoa %d:\n", i + 1);
        printf("Matrícula: ");
        scanf("%d", &pessoas[i].matricula);
        printf("Nome: ");
        scanf("%s", pessoas[i].nome);
        printf("Nota: ");
        scanf("%f", &pessoas[i].nota);
    }

    // Menu de opções
    do {
        printf("\nComo deseja ordenar?\n");
        printf("1 - Matrícula (Radix Sort)\n");
        printf("2 - Nome (Merge Sort)\n");
        printf("3 - Nota (Shell Sort - decrescente)\n");
        printf("0 - Encerrar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                ordenarPorRadix(pessoas, n);
                break;
            case 2:
                ordenarPorMerge(pessoas, 0, n - 1);
                break;
            case 3:
                ordenarPorShell(pessoas, n);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

        // Exibe o resultado apenas se o usuário não escolheu sair
        if (opcao != 0) {
            printf("\n--- Lista Ordenada ---\n");
            for (int i = 0; i < n; i++)
                printf("%d | %s | %.2f\n", pessoas[i].matricula, pessoas[i].nome, pessoas[i].nota);
        }

    } while (opcao != 0);

    free(pessoas);
    return 0;
}

// ====================== RADIX SORT ======================

// Função auxiliar para obter o dígito em determinada posição (coluna w)
// Exemplo: se valor=123 e w=0 (unidade) → retorna 3
//          se w=1 (dezena) → retorna 2
int obterDigito(int valor, int w, int base) {
    int i = -1, digito;
    do {
        i++;
        digito = valor % base;  // Obtém o dígito menos significativo
        valor /= base;          // Remove o último dígito
    } while (i != w);           // Repete até chegar na posição desejada
    return digito;
}

// Implementação do Radix Sort para ordenar por matrícula
// O algoritmo ordena os números por cada dígito, da menor ordem (unidade) para a maior.
void ordenarPorRadix(struct pessoa *pessoas, int n) {
    int base = 10;   // Sistema decimal
    int num_digitos = 0;

    // Descobre o maior número de matrícula para saber quantos dígitos ele tem
    int maior = pessoas[0].matricula;
    for (int i = 1; i < n; i++)
        if (pessoas[i].matricula > maior)
            maior = pessoas[i].matricula;

    while (maior > 0) {
        maior /= 10;
        num_digitos++;
    }

    // Vetores auxiliares
    struct pessoa *aux = malloc(n * sizeof(struct pessoa));
    int *count = malloc(base * sizeof(int));
    int *posicao = malloc(base * sizeof(int));

    // Para cada dígito (unidade, dezena, centena...)
    for (int w = 0; w < num_digitos; w++) {

        // Inicializa os vetores de contagem e posição
        for (int j = 0; j < base; j++) {
            count[j] = 0;
            posicao[j] = 0;
        }

        // Conta quantos elementos possuem cada dígito na posição w
        for (int i = 0; i < n; i++) {
            int d = obterDigito(pessoas[i].matricula, w, base);
            count[d]++;
        }

        // Calcula as posições finais de cada dígito no vetor ordenado
        for (int j = 1; j < base; j++)
            posicao[j] = posicao[j-1] + count[j-1];

        // Coloca os elementos na ordem correta em aux
        for (int i = 0; i < n; i++) {
            int d = obterDigito(pessoas[i].matricula, w, base);
            aux[posicao[d]++] = pessoas[i];
        }

        // Copia o vetor auxiliar de volta para pessoas
        for (int i = 0; i < n; i++)
            pessoas[i] = aux[i];
    }

    free(aux);
    free(count);
    free(posicao);
}

// ====================== MERGE SORT ======================

// Função que mescla dois subvetores já ordenados (usando nomes como critério)
void mesclarPorNome(struct pessoa *pessoas, int esquerda, int meio, int direita) {
    int tamanho = direita - esquerda + 1;
    struct pessoa *temp = malloc(tamanho * sizeof(struct pessoa));

    int p1 = esquerda;    // Ponteiro da metade esquerda
    int p2 = meio + 1;    // Ponteiro da metade direita
    int i = 0;

    // Compara os elementos das duas metades e coloca em ordem
    while (p1 <= meio && p2 <= direita) {
        if (strcmp(pessoas[p1].nome, pessoas[p2].nome) < 0)
            temp[i++] = pessoas[p1++];
        else
            temp[i++] = pessoas[p2++];
    }

    // Copia os elementos restantes (se houver)
    while (p1 <= meio) temp[i++] = pessoas[p1++];
    while (p2 <= direita) temp[i++] = pessoas[p2++];

    // Copia de volta para o vetor original
    for (i = 0; i < tamanho; i++)
        pessoas[esquerda + i] = temp[i];

    free(temp);
}

// Função recursiva do Merge Sort
void ordenarPorMerge(struct pessoa *pessoas, int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = floor((esquerda + direita) / 2);

        // Ordena a primeira metade
        ordenarPorMerge(pessoas, esquerda, meio);

        // Ordena a segunda metade
        ordenarPorMerge(pessoas, meio + 1, direita);

        // Mescla as duas metades já ordenadas
        mesclarPorNome(pessoas, esquerda, meio, direita);
    }
}

// ====================== SHELL SORT ======================

// Implementação do Shell Sort para ordenar por nota (ordem decrescente)
void ordenarPorShell(struct pessoa *pessoas, int n) {
    int gap = 1;

    // Calcula o maior intervalo inicial (gap)
    do {
        gap = 3 * gap + 1;
    } while (gap < n);

    // Enquanto houver intervalos para comparar
    do {
        gap /= 3;

        // Faz inserção com gap
        for (int i = gap; i < n; i++) {
            struct pessoa temp = pessoas[i];
            int j = i - gap;

            // Para ordem decrescente, usamos temp.nota > pessoas[j].nota
            while (j >= 0 && temp.nota > pessoas[j].nota) {
                pessoas[j + gap] = pessoas[j];
                j -= gap;
            }
            pessoas[j + gap] = temp;
        }
    } while (gap > 1);
}
