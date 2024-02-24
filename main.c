#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
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

    Carta cartaDeUsoGeral;

    atribuirBois(&cartaDeUsoGeral, baralho);

    srand(time(NULL));
    for (int i = 0; i < CARTAS_TOTAL; i++){
        embaralhar(baralho);
    }

    for (int i = 0; i < CARTAS_DO_JOGADOR; i++){
        removerPilha(baralho,&cartaDeUsoGeral);
        cartaDeUsoGeral.jogador = 1;
        inserirOrenado(mao,cartaDeUsoGeral);
    }

    for (int i = 0; i < FILAS_DE_CARTAS; i++){
        removerPilha(baralho,&cartaDeUsoGeral);
        inserirFila(mesa[i],cartaDeUsoGeral);
    }

    Lista *cartasDaRodada;
    cartasDaRodada = NULL;
    cartasDaRodada = criarLista();

    char nomeDoUsuario[30];
    int numeroDePcs;

    printf("Bem vindo! Digite seu nome: ");
    scanf("%29s", nomeDoUsuario);
    while( getchar() != '\n' );

    do
    {
        printf("Digite a quantidade de jogadores, alem de voce, no jogo (1 a 9): ");
        scanf("%d", &numeroDePcs);
        while( getchar() != '\n' );
    } while (numeroDePcs < 1 || numeroDePcs > 9);

    int rodadasJogadas = 1;
    while (rodadasJogadas <= RODADAS_TOTAIS){
        exibirTela(mao, colecaoDoJogador[0], mesa, &nomeDoUsuario);

        int cartaEscolhida;
        do
        {
            printf("Digite o indice (de 1 a 10) da carta que quer jogar: ");
            scanf("%d", &cartaEscolhida);
            while( getchar() != '\n' );
        } while (cartaEscolhida < 1 || cartaEscolhida > 10 || cartaEscolhida > quantidade(mao));

        acessarIndice(mao, cartaEscolhida, &cartaDeUsoGeral);
        removerIndice(mao, cartaEscolhida);
        inserirOrenado(cartasDaRodada, cartaDeUsoGeral);

        for (int i = 1; i <= numeroDePcs; i++){
            removerPilha(baralho,&cartaDeUsoGeral);
            cartaDeUsoGeral.jogador = i+1;
            inserirOrenado(cartasDaRodada, cartaDeUsoGeral);
        }

        adicionarCartaNaFila(mesa, colecaoDoJogador, cartasDaRodada);

        rodadasJogadas++;
    }

    printf("\n-------------------------");
    printf("\n----- O JOGO ACABOU -----\n");

    exibirPontuacao(colecaoDoJogador, numeroDePcs+1);

    return 0;
}
