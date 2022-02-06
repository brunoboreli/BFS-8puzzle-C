
#include "fila.h"
// Criando interface para arvore n-ária

// Funções
Folha* criar_arvore();
Folha* criar_no(int *pos, int **matriz_in);

int* achar_zero(int **matriz, int *pos_zero);
void destruir_arvore(Folha **raiz);

void imprime_no(Folha *p);

int percurso_largura(Folha *p, int vetor[]);

int gerar_filhos(Folha *p, Folha *raiz,int vector[]);

int criar_chave(Folha* raiz);

void imprime_caminho(Folha *raiz, Folha *no);
