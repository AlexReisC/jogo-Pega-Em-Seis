typedef struct fila Fila;

Fila* criarFila();
int inserirFila(Fila *, struct carta);
int removerFila(Fila *, struct carta *); // J� remove e acessa
int acessarFila(Fila *, struct carta *);
int exibirFila(Fila *);
int tamanhoFila(Fila *);
