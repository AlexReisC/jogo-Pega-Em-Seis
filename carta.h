#define CARTAS_TOTAL 104
#define FILAS_DE_CARTAS 4
#define COLECOES 10
#define CARTAS_DO_JOGADOR 10
#define RODADAS_TOTAIS 10

struct carta{
    int numero;
    int bois;
    int jogador;
};

typedef struct carta Carta;
