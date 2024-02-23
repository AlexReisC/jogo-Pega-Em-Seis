#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

    printf("Mao de %s: \n", nomeDeUsuario);
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

void adicionarCartaNaFila(Fila **filas, Lista **colecoes, Lista *cartas){
    Carta cartaJogada;
    Carta cartaAuxiliar;

    int diferenca, indiceDaMenor, qtdFilasMaiores, menorDiferenca;

    while (quantidade(cartas) > 0){
        acessarIndice(cartas, 1, &cartaJogada);
        removerIndice(cartas, 1);

        menorDiferenca = 104;
        qtdFilasMaiores = 0;

        for (int i = 0; i < FILAS_DE_CARTAS; i++){
            acessarFila(filas[i], &cartaAuxiliar);
            if(cartaAuxiliar.numero < cartaJogada.numero){
                diferenca = cartaJogada.numero - cartaAuxiliar.numero;
                if(diferenca < menorDiferenca){
                    menorDiferenca = diferenca;
                    indiceDaMenor = i;
                }
            } else {
                qtdFilasMaiores++;
            }
        }

        if(qtdFilasMaiores == 4){
            if(cartaJogada.jogador == 1){
                int filaEscolhida;
                do
                {
                    printf("Escolha (de 1 a 4) uma fila para pegar todas as cartas: ");
                    scanf("%d", &filaEscolhida);
                } while (filaEscolhida < 1 || filaEscolhida > 4);

                int indiceDaColecao = cartaJogada.jogador - 1;
                while (tamanhoFila(filas[filaEscolhida-1]) > 0){
                    removerFila(filas[filaEscolhida-1], &cartaAuxiliar);
                    inserirOrenado(colecoes[indiceDaColecao], cartaAuxiliar);
                }
                inserirFila(filas[filaEscolhida-1], cartaJogada);
            } else {
                srand(time(NULL));
                int filaAleatoria = rand() % 4;

                int indiceDaColecao = cartaJogada.jogador - 1;
                while (tamanhoFila(filas[filaAleatoria]) > 0){
                    removerFila(filas[filaAleatoria], &cartaAuxiliar);
                    inserirOrenado(colecoes[indiceDaColecao], cartaAuxiliar);
                }
                inserirFila(filas[filaAleatoria], cartaJogada);
            }
        } else {
            if(tamanhoFila(filas[indiceDaMenor]) == 5){
                int indiceDaColecao = cartaJogada.jogador - 1;
                for (int i = 0; i < FILAS_DE_CARTAS+1; i++){
                    removerFila(filas[indiceDaMenor], &cartaAuxiliar);
                    inserirOrenado(colecoes[indiceDaColecao], cartaAuxiliar);
                }
            }
            inserirFila(filas[indiceDaMenor], cartaJogada);
        }
    }
}
