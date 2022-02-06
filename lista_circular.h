
//struct da folha da arvore
typedef struct folha{
	int pos_zero[2];
	int matriz[3][3];
	struct folha *esq, *dir, *cima, *baixo, *pai;
} Folha;

typedef struct no {
    Folha *end;//guarda o endereço para uma folha da arvore
    struct no *prox;
} No;

No* criar_lista();
void destruir_lista(No **L);

//Adicionar
void adicionar_inicio(No** p, Folha* x);
void adicionar_final(No **L, Folha *x);


//Remover
void remover_inicio(No **L);
void remover_final(No **L);
