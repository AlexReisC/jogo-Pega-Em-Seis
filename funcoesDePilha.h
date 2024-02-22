typedef struct no* Pilha;

Pilha* criarPilha();
int inserirPilha(Pilha *, struct carta);
int removerPilha(Pilha *, struct carta *); // Já remove e acessa
void embaralhar(Pilha *);
int tamanhoPilha(Pilha *);

