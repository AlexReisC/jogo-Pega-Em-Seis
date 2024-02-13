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

    int rodadasJogadas = 1;
    while (rodadasJogadas <= RODADAS_TOTAIS){
        exibirTela(mao, mesa);

        int opcaoCarta;
        do
        {
            printf("\nDigite o indice (de 1 a 10) da carta que quer jogar: ");
            scanf("%d", &opcaoCarta);
        } while (opcaoCarta < 1 || opcaoCarta > 10);

        acessarIndice(mao,opcaoCarta,&cartaDeUsoGeral);
        removerIndice(mao,opcaoCarta);

        Lista *cartasJogadas;
        cartasJogadas = criarLista();
        for (int i = 1; i < COLECOES; i++){
            removerPilha(baralho,&cartaAuxiliar);
            inserirOrenado(cartasJogadas,cartaAuxiliar);
        }

        int diferencaDeCartas[4];
        int filaMenor[4];
        int contaFilaMaior = 0, menorDiferenca;
        for (int i = 0; i < FILAS_DE_CARTAS; i++){
            acessarFila(mesa[i],&cartaAuxiliar);
            if(cartaAuxiliar.numero < cartaDeUsoGeral.numero){
                diferencaDeCartas[i] = cartaDeUsoGeral.numero - cartaAuxiliar.numero;
            }
            else {
                contaFilaMaior++;
            }
        }

        if(contaFilaMaior == 4){
            int filaEscolhida;
            do
            {
              printf("\nEscolha uma fila para pegar todas as cartas (de 1 a 4)");
              scanf("%d", &filaEscolhida);
            } while (filaEscolhida < 1 || filaEscolhida > 4);


            for (int i = 0; FILAS_DE_CARTAS+1; i++){
                removerFila(mesa[filaEscolhida-1],&cartaAuxiliar);
                inserirOrenado(colecaoDoJogador[0],cartaAuxiliar);
            }
            inserirFila(mesa[filaEscolhida-1],cartaDeUsoGeral);
        }
        else{
            int qtdVetorDiferencas = sizeof(diferencaDeCartas) / sizeof(diferencaDeCartas[0]);
            menorDiferenca = diferencaDeCartas[0];
            filaMenor[0] = 0;
            for(int i = 1; i < qtdVetorDiferencas; i++){
                if(diferencaDeCartas[i] < menorDiferenca){
                    menorDiferenca = diferencaDeCartas[i];
                    filaMenor[i] = i;
                }
            }
            for (int i = 0; i < FILAS_DE_CARTAS; i++){
                if(i == filaMenor[i] && diferencaDeCartas[i] == menorDiferenca){
                    if(tamanhoFila(mesa[i]) == 5){
                        int j = 0;
                        while(j < FILAS_DE_CARTAS+1){
                            removerFila(mesa[i],&cartaAuxiliar);
                            inserirOrenado(colecaoDoJogador[0],cartaAuxiliar);
                            j++;
                        }
                        inserirFila(mesa[i],cartaDeUsoGeral);
                    }
                    else{
                        inserirFila(mesa[i],cartaDeUsoGeral);
                    }
                }
            }
        }
        rodadasJogadas++;
    }


    return 0;
}
