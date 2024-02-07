typedef struct no* Lista;

Lista* criarLista();
int inserirOrenado(Lista *, struct carta);
int acessarIndice(Lista *, int, struct carta*);
int removerIndice(Lista *, int);
int exibirLista(Lista *);
int quantidade(Lista *);
