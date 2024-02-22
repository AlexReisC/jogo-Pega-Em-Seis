#include <stdio.h>
#include <stdlib.h>
#include "carta.h"
#include "funcoesAdicionais.h"
#include "funcoesDeLista.h"
#include "funcoesDeFila.h"

int exibirTela(Lista *li, Lista *ld, Fila **fi, char *nomeDeUsuario){
    int filasVazias = fi[0] == NULL && fi[1] == NULL && fi[2] == NULL && fi[3] == NULL ? 1 : 0;

    if(filasVazias){
        return 0;
    }

    printf("Mesa: \n");
    for (int i = 0; i < FILAS_DE_CARTAS; i++){
        exibirFila(fi[i]);
    }

    printf("\nColecao de %s: ", nomeDeUsuario);
    exibirLista(ld);

    printf("\nMao de %s: \n", nomeDeUsuario);
    exibirLista(li);

    for (int i = 1; i <= CARTAS_DO_JOGADOR; i++){
        printf(" (%d) ", i);
    }

    printf("\n");

    return 1;
}

int contarPontuacao(Lista *li){
    if(*li == NULL){
        return 0;
    }

    int pontos = 0;
    Carta cartaContaPontos;

    for (int i = 1; i <= quantidade(li); i++){
        acessarIndice(li, i, &cartaContaPontos);
        pontos += cartaContaPontos.bois;
    }

    return pontos;
}

void atribuirBois(struct carta *elemento, Pilha *pilha){
    for (int i = 1; i <= CARTAS_TOTAL; i++){
        elemento->numero = i;
        elemento->bois = 1;
        if(elemento->numero % 10 == 0 && elemento->numero % 2 == 0){
            elemento->bois = 3;
        }
        if(elemento->numero % 11 == 0){
            elemento->bois = 5;
        }
        if(elemento->numero % 5 == 0 && elemento->numero % 2 == 1){
            elemento->bois = 2;
        }
        if(elemento->numero == 55){
            elemento->bois = 7;
        }
        inserirPilha(pilha,*elemento);
    }
}

