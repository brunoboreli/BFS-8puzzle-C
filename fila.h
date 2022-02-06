#include "lista_circular.h"

//Dados
typedef struct{
    int tam;
    No* L;
}Fila;

//Funções
Fila* fila_criar();
void fila_destruir(Fila **F);

//Adicionar
void fila_adicionar(Fila **F, Folha* x);
 
int fila_vazia(Fila *p);
int fila_tam(Fila *p);
Folha* acessar_inicio(Fila* p);

//Remover
void fila_remover(Fila **F);

