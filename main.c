#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "carta.h"
#include "funcoesDeLista.h"
#include "funcoesDeFila.h"
#include "funcoesDePilha.h"
#include "funcoesAdicionais.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Lista *mao;
    mao = NULL;
    mao = criarLista();

    Lista **colecaoDoJogador;
    colecaoDoJogador = (Lista**)malloc(sizeof(Lista*)*COLECOES);
    for (int i = 0; i < COLECOES; i++){
        colecaoDoJogador[i] = criarLista();
    }

    Fila **mesa;
    mesa = (Fila**)malloc(sizeof(Lista*)*FILAS_DE_CARTAS);
    for (int i = 0; i < FILAS_DE_CARTAS; i++){
        mesa[i] = criarFila();
    }

    Pilha *baralho;
    baralho = NULL;
    baralho = criarPilha();

    Carta c;
    Carta cartaAuxiliar;

    for (int i = 1; i <= CARTAS_TOTAL; i++){
        c.numero = i;
        c.bois = 1;
        if(c.numero % 10 == 0 && c.numero % 2 == 0){
            c.bois = 3;
        }
        if(c.numero % 11 == 0){
            c.bois = 5;
        }
        if(c.numero % 5 == 0 && c.numero % 2 == 1){
            c.bois = 2;
        }
        if(c.numero == 55){
            c.bois = 7;
        }
        inserirPilha(baralho,c);
    }

    for (int i = 0; i < CARTAS_TOTAL; i++){
        embaralhar(baralho);
    }

    for (int i = 0; i < CARTAS_DO_JOGADOR; i++){
        removerPilha(baralho,&c);
        c.jogador = 1;
        inserirOrenado(mao,c);
    }

    printf("Mesa: \n");
    for (int i = 0; i < FILAS_DE_CARTAS; i++){
        removerPilha(baralho,&c);
        inserirFila(mesa[i],c);
        exibirFila(mesa[i]);
    }

    printf("\nSua coleção: ");
    exibirLista(colecaoDoJogador[0]);
    printf("Sua mão: ");
    exibirLista(mao);
    printf("        ");
    for (int i = 1; i <= CARTAS_DO_JOGADOR; i++){
        printf(" (%d) ", i);
    }

    printf("\n");
    int opcaoCarta;
    do
    {
        printf("\nDigite o indice (de 1 a 10) da carta que quer jogar: ");
        scanf("%d", &opcaoCarta);
    } while (opcaoCarta < 1 || opcaoCarta > 10);


    int diferenca;
    acessarIndice(mao,opcaoCarta,&c);
    removerIndice(mao,opcaoCarta);


    return 0;
}
