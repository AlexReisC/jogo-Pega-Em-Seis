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
