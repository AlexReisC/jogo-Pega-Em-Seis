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

    srand(time(NULL));

    for (int i = CARTAS_TOTAL - 1; i > 0; i--) {
        int indiceAleatorio = rand() % (i + 1);

        No *cartaAuxiliar = *pi;
        No *cartaSorteada = *pi;
        for (int j = 0; j < i; j++) {
            cartaAuxiliar = cartaAuxiliar->prox;
        }
        for (int j = 0; j < indiceAleatorio; j++) {
            cartaSorteada = cartaSorteada->prox;
        }
        Carta aux = cartaAuxiliar->dados;
        cartaAuxiliar->dados = cartaSorteada->dados;
        cartaSorteada->dados = aux;
    }
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
