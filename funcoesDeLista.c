#include <stdio.h>
#include <stdlib.h>
#include "carta.h"
#include "funcoesDeLista.h"

struct no{
    struct carta dados;
    struct no *prox;
};

typedef struct no No;

Lista* criarLista(){
    Lista *li = (Lista*)malloc(sizeof(Lista));

    if(li != NULL){
        *li = NULL;
    }

    return li;
}

int inserirOrenado(Lista *li, struct carta dados){
    if(li == NULL){
        return 0;
    }

    No *novo = (No*)malloc(sizeof(No));
    novo->dados = dados;
    if(*li == NULL){
        *li = novo;
        novo->prox = NULL;
        return 1;
    }

    No *aux = *li;
    No *ant = *li;
    int indice = 1;
    while(aux != NULL){
        if(novo->dados.numero < aux->dados.numero && indice == 1){
            novo->prox = aux;
            *li = novo;
            break;
        }
        else if(novo->dados.numero < aux->dados.numero && indice > 1){
            novo->prox = aux;
            ant->prox = novo;
            break;
        }
        else if(novo->dados.numero > aux->dados.numero){
            ant = aux;
            aux = aux->prox;
            indice++;
        }
    }

    if(aux == NULL){
        ant->prox = novo;
        novo->prox = NULL;
    }

    return 1;
}

int acessarIndice(Lista *li, int indice, struct carta *dados){
    if(*li == NULL || li == NULL){
        return 0;
    }

    if(indice > 0){
        No *aux = *li;
        No *ant;
        if(indice == 1){
            *dados = (*li)->dados;
            return 1;
        }

        int i = 1;
        while (i != indice){
            if(aux == NULL){
                return 0;
            }
            ant = aux;
            aux = aux->prox;
            i++;
        }
        *dados = aux->dados;
        return 1;
    }
    else {
        return 0;
    }
}

int removerIndice(Lista *li, int indice){
    if(*li == NULL){
        return -1;
    }

    No *aux = *li;
    No *ant = *li;

    if(indice == 1){
        *li = aux->prox;
        return 1;
    }

    int i = 1;
    while (i != indice && aux != NULL){
        ant = aux;
        aux = aux->prox;
        i++;
    }
    if(aux == NULL){
        return -1;
    }
    ant->prox = aux->prox;
    free(aux);

    return 1;
}

int exibirLista(Lista *li){
    if(*li == NULL){
        printf("\n");
        return 0;
    }

    No *aux = *li;
    while(aux != NULL){
        printf("[%d] ", aux->dados.numero);
        aux = aux->prox;
    }
    printf("\n");

    return 1;
}

int quantidade(Lista *li){
    if(*li == NULL){
        return 0;
    }

    int qtd = 0;
    No *aux = *li;
    while(aux != NULL){
        qtd++;
        aux = aux->prox;
    }

    return qtd;
}
