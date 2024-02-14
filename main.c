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
    Carta cartaAuxiliar;

    for (int i = 1; i <= CARTAS_TOTAL; i++){
        cartaDeUsoGeral.numero = i;
        cartaDeUsoGeral.bois = 1;
        if(cartaDeUsoGeral.numero % 10 == 0 && cartaDeUsoGeral.numero % 2 == 0){
            cartaDeUsoGeral.bois = 3;
        }
        if(cartaDeUsoGeral.numero % 11 == 0){
            cartaDeUsoGeral.bois = 5;
        }
        if(cartaDeUsoGeral.numero % 5 == 0 && cartaDeUsoGeral.numero % 2 == 1){
            cartaDeUsoGeral.bois = 2;
        }
        if(cartaDeUsoGeral.numero == 55){
            cartaDeUsoGeral.bois = 7;
        }
        inserirPilha(baralho,cartaDeUsoGeral);
    }

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

    printf("Bem vindo! Digite seu nome... ");
    scanf("%29s", nomeDoUsuario);
    printf("Digite a quantidade de jogadores, além de você, no jogo... ");
    scanf("%d", &numeroDePcs);

    int rodadasJogadas = 1;
    while (rodadasJogadas <= RODADAS_TOTAIS){
        exibirTela(mao, colecaoDoJogador[0], mesa, &nomeDoUsuario);

        int cartaEscolhida;
        do
        {
            printf("\nDigite o indice (de 1 a 10) da carta que quer jogar: ");
            scanf("%d", &cartaEscolhida);
        } while (cartaEscolhida < 1 || cartaEscolhida > 10);

        acessarIndice(mao, cartaEscolhida, &cartaDeUsoGeral);
        removerIndice(mao, cartaEscolhida);
        inserirOrenado(cartasDaRodada, cartaDeUsoGeral);

        for (int i = 1; i <= numeroDePcs; i++){
            removerPilha(baralho,&cartaAuxiliar);
            cartaAuxiliar.jogador = i+1;
            inserirOrenado(cartasDaRodada,cartaAuxiliar);
        }

        int diferenca, indiceDaMenor, qtdFilasMaiores;
        int menorDiferenca = 104;
        while (quantidade(cartasDaRodada) > 0){
            acessarIndice(cartasDaRodada, 1, &cartaDeUsoGeral);
            removerIndice(cartasDaRodada, 1);
            qtdFilasMaiores = 0;

            for (int i = 0; i < FILAS_DE_CARTAS; i++){
                acessarFila(mesa[i], &cartaAuxiliar);
                printf("Carta da rodada: %d ", cartaDeUsoGeral.numero);
                printf("Carta da mesa: %d ", cartaAuxiliar.numero);
                if(cartaAuxiliar.numero < cartaDeUsoGeral.numero){
                    printf("É menor!! ");
                    diferenca = cartaAuxiliar.numero - cartaDeUsoGeral.numero;
                    if(diferenca < menorDiferenca){
                        menorDiferenca = diferenca;
                        indiceDaMenor = i;
                    }
                } else {
                    qtdFilasMaiores++;
                }
            }

            if(qtdFilasMaiores == 4){
                if(cartaDeUsoGeral.jogador == 1){
                    int filaEscolhida;
                    do
                    {
                        printf("Escolha (de 1 a 4) uma fila para pegar todas as cartas: ");
                        scanf("%d", &filaEscolhida);
                    } while (filaEscolhida < 1 || filaEscolhida > 4);

                    int indiceDaColecao = cartaDeUsoGeral.jogador - 1;
                    while (tamanhoFila(mesa[filaEscolhida-1]) > 0){
                        removerFila(mesa[filaEscolhida-1], &cartaAuxiliar);
                        inserirOrenado(colecaoDoJogador[indiceDaColecao], cartaAuxiliar);
                    }
                    inserirFila(mesa[filaEscolhida-1], cartaDeUsoGeral);
                } else {
                    srand(time(NULL));
                    int filaAleatoria = rand() % 4;

                    int indiceDaColecao = cartaDeUsoGeral.jogador - 1;
                    while (tamanhoFila(mesa[filaAleatoria]) > 0){
                        removerFila(mesa[filaAleatoria], &cartaAuxiliar);
                        inserirOrenado(colecaoDoJogador[indiceDaColecao], cartaAuxiliar);
                    }
                    inserirFila(mesa[filaAleatoria], cartaDeUsoGeral);
                }
            } else {
                if(tamanhoFila(mesa[indiceDaMenor]) == 5){
                    int indiceDaColecao = cartaDeUsoGeral.jogador - 1;
                    for (int i = 0; i < 5; i++){
                        removerFila(mesa[indiceDaMenor], &cartaAuxiliar);
                        inserirOrenado(colecaoDoJogador[indiceDaColecao], cartaAuxiliar);
                    }
                }
                inserirFila(mesa[indiceDaMenor], cartaDeUsoGeral);
            }
        }

        rodadasJogadas++;
    }


    return 0;
}
