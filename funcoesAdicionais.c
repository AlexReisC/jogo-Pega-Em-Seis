#include <stdio.h>
#include <stdlib.h>
#include "carta.h"
#include "funcoesAdicionais.h"

void trocar(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

int particionar(int lista[], int inicio, int fim){
    int pivo = lista[fim];
    int i = inicio - 1;
    for (int j = inicio; j <= fim - 1; i++){
        if(lista[j] < pivo){
            i++;
            trocar(&lista[i], &lista[j]);
        }
    }

    trocar(&lista[i+1], &lista[fim]);
    return i+1;
}

void quickSort(int lista[], int inicio, int fim){
    if(inicio < fim){
        int indicePivo = particionar(lista, inicio, fim);
        quickSort(lista, inicio, indicePivo - 1);
        quickSort(lista, indicePivo + 1, fim);
    }
}
