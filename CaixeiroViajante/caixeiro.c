#include <stdio.h>
#include <limits.h>
#include <windows.h>  // para QueryPerformanceCounter

#define CIDADES 7

const char* nomes[CIDADES] = {
    "Toquio", "Paris", "Nova Iorque", "RJ",
    "Londres", "Cairo", "Berlim"
};

int dist[CIDADES][CIDADES] = {
    {0, 12, 53, 20, 35, 30, 25},
    {12, 0, 25, 30, 53, 20, 35},
    {53, 25, 0, 12, 30, 35, 20},
    {20, 30, 12, 0, 25, 53, 35},
    {35, 53, 30, 25, 0, 12, 20},
    {30, 20, 35, 53, 12, 0, 25},
    {25, 35, 20, 35, 20, 25, 0}
};

int menorDistancia = INT_MAX;
int melhorRota[CIDADES + 1];

void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void calcularDistancia(int rota[]) {
    int soma = 0;
    for (int i = 0; i < CIDADES - 1; i++) {
        soma += dist[rota[i]][rota[i + 1]];
    }
    soma += dist[rota[CIDADES - 1]][rota[0]];

    if (soma < menorDistancia) {
        menorDistancia = soma;
        for (int i = 0; i < CIDADES; i++) {
            melhorRota[i] = rota[i];
        }
        melhorRota[CIDADES] = rota[0];
    }
}

void gerarRotas(int rota[], int inicio, int fim) {
    if (inicio == fim) {
        calcularDistancia(rota);
        return;
    }
    for (int i = inicio; i <= fim; i++) {
        troca(&rota[inicio], &rota[i]);
        gerarRotas(rota, inicio + 1, fim);
        troca(&rota[inicio], &rota[i]);
    }
}

int main() {
    LARGE_INTEGER freq, start, end;
    double tempo_execucao;

    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    int rota[CIDADES] = {0, 1, 2, 3, 4, 5, 6};
    gerarRotas(rota, 1, CIDADES - 1);

    QueryPerformanceCounter(&end);

    tempo_execucao = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;

    printf("Melhor rota: ");
    for (int i = 0; i <= CIDADES; i++) {
        printf("%s", nomes[melhorRota[i]]);
        if (i < CIDADES) printf(" -> ");
    }
    printf("\n");

    printf("Distancia total: %d\n", menorDistancia);
    printf("Tempo de execucao: %.6f segundos\n", tempo_execucao);

    return 0;
}
