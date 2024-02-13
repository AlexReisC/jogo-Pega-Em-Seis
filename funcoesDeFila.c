#include <stdio.h>
#include <stdlib.h>
#include "carta.h"
#include "funcoesDeFila.h"

struct no{
    struct carta dados;
    struct no *prox;
};

typedef struct no No;

struct fila{
    struct no *inicio;
    struct no *fim;
};

Fila *criarFila(){
    Fila *fi = (Fila*)malloc(sizeof(Fila));
    if(fi != NULL){
        fi->inicio = NULL;
        fi->fim = NULL;
    }
    return fi;
}

int inserirFila(Fila *fi, struct carta novosDados){
    if(fi == NULL){
        return 0;
    }

    No *nova = (No*)malloc(sizeof(No));
    if(nova == NULL){
        return 0;
    }
    nova->dados = novosDados;
    nova->prox = NULL;

    if(fi->fim == NULL){
        fi->inicio = nova;
    }
    else{
        fi->fim->prox = nova;
    }
    fi->fim = nova;

    return 1;
}

int removerFila(Fila *fi, struct carta *dados){
    if(fi == NULL || fi->inicio == NULL){
        return 0;
    }

    No *aux = fi->inicio;
    fi->inicio = fi->inicio->prox;
    if(fi->inicio == NULL){
        fi->fim = NULL;
    }

    dados->numero = aux->dados.numero;
    dados->bois = aux->dados.bois;
    dados->jogador = aux->dados.jogador;
    free(aux);
    return 1;
}

int acessarFila(Fila *fi, struct carta *dados){
    if(fi == NULL || fi->inicio == NULL){
        return 0;
    }

    *dados = fi->fim->dados;
    return 1;
}

int exibirFila(Fila *fi){
    if(fi == NULL || fi->inicio == NULL){
        printf("\n");
        return 0;
    }

    No *aux = fi->inicio;

    while(aux != NULL){
        printf("[%d] ", aux->dados.numero);
        aux = aux->prox;
    }
    printf("\n");

    return 1;
}

int tamanhoFila(Fila *fi){
    if(fi == NULL || fi->inicio == NULL){
        return 0;
    }

    int tamanhoFila = 0;
    No *aux = fi->inicio;

    while(aux != NULL){
        tamanhoFila++;
        aux = aux->prox;
    }

    return tamanhoFila;
}
