#include <stdio.h>
#include <stdlib.h>
#include "carta.h"
#include "funcoesDePilha.h"
#include <time.h>

struct no{
    struct carta dados;
    struct no *prox;
};

typedef struct no No;

Pilha *criarPilha(){
    Pilha *pi = (Pilha*)malloc(sizeof(Pilha));
    if(pi != NULL){
        *pi = NULL;
    }

    return pi;
}

int inserirPilha(Pilha *pi, struct carta novosDados){
    if(pi == NULL){
        return 0;
    }

    No *novo = (No*)malloc(sizeof(No));
    if (novo == NULL){
        return 0;
    }

    novo->dados = novosDados;
    novo->prox = *pi;
    *pi = novo;
    return 1;
}

int removerPilha(Pilha *pi, struct carta *dados){
    if(*pi == NULL || pi == NULL){
        return 0;
    }

    No *aux = *pi;
    *pi = aux->prox;
    dados->numero = aux->dados.numero;
    dados->bois = aux->dados.bois;
    dados->jogador = aux->dados.jogador;
    free(aux);
    return 1;
}

void embaralhar(Pilha *pi){
    if(pi == NULL && *pi == NULL){
        printf("\nBaralho vazio\n");
        exit(1);
    }

    int contador = 1;
    int indiceCarta;
    indiceCarta = 1 + rand() % CARTAS_TOTAL;

    No *posInicio = *pi;
    No *posFim = *pi;

    while(posFim != NULL && contador != indiceCarta){
        posFim = posFim->prox;
        contador++;
    }

    *pi = posInicio->prox;
    posInicio->prox = posFim->prox;
    posFim->prox = posInicio;

}

int tamanhoPilha(Pilha *pi){
    if(*pi == NULL){
        return 0;
    }

    int tamanhoPilha = 0;
    No *aux = *pi;
    while(aux != NULL){
        tamanhoPilha++;
        aux = aux->prox;
    }

    return tamanhoPilha;
}
