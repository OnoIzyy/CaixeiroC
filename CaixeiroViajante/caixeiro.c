#include <stdio.h>
#include <limits.h>

//definição de cidades para as matrizes
#define CIDADES 7

// Nomes das cidades
const char* nomes[CIDADES] = {
    "Toquio", "Paris", "Nova Iorque", "RJ",
    "Londres", "Cairo", "Berlim"
};

int dist[CIDADES][CIDADES]= {
    {0, 12, 53, 20, 35, 30, 25},
    {12, 0, 25, 30, 53, 20, 35},
    {53, 25, 0, 12, 30, 35, 20},
    {20, 30, 12, 0, 25, 53, 35},
    {35, 53, 30, 25, 0, 12, 20},
    {30, 20, 35, 53, 12, 0, 25},
    {25, 35, 20, 35, 20, 25, 0}
    
};

int menorDistancia= INT_MAX;
int melhorRota[CIDADES  +1];// isso volta a cidade inicial

void troca(int *a,int*b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

//calcula a distancia total da rota
void calcularDistancia(int rota[])
{
    int soma=0;
    for(int i=0;i<CIDADES-1;i++){
        soma+=dist[rota[i]][rota[i+1]];
    }
    soma+=dist[rota[CIDADES-1]][rota[0]];

    if(soma<menorDistancia)
    {
        menorDistancia =soma;
        for(int i=0;i<CIDADES;i++){
            melhorRota[i]=rota[i];
        }
        melhorRota[CIDADES]=rota[0];
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
    int rota[CIDADES] = {0, 1, 2, 3,4,5,6}; // Cidades Toquio,Paris, Nova Iorque, RJ, Londres,Cairo, Berlim

    gerarRotas(rota, 1, CIDADES - 1); // fixa cidade A como início

    printf("Melhor rota: ");
    for (int i = 0; i <= CIDADES; i++) {
        printf("%s\n", nomes[melhorRota[i]]);
    }
    printf("\nDistância total: %d\n", menorDistancia);

    return 0;
}
