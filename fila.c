#include <stdlib.h>
#include <stdio.h>
#include "fila.h"


Fila* fila_criar() {
    Fila *p = (Fila*) malloc(sizeof(Fila));
    (p->L) = criar_lista();
    p->tam = 0;
    return p;
}

int fila_vazia(Fila *p){
    if(p==NULL){
        return 1;
    }
    else if(p->tam == 0){
        return 1;
    }
    else{
        return 0;
    }

}

int fila_tam(Fila *p){
    return p->tam;

}

Folha* acessar_inicio(Fila* p){
    //função retorna a folha que está no inicio da fila
    return (((p)->L)->prox)->end;
}

void fila_destruir(Fila **p) {// p recebe &F
    destruir_lista(&(((*p)->L)));
    free(*p);
    *p = NULL;
}

void fila_adicionar(Fila **p, Folha* x) {// p recebe &F
    if(x==NULL){

    }else {
        adicionar_final(&((*p)->L), x);
        (*p)->tam++;
    }
    
}

void fila_remover(Fila **p) {// p recebe &L
    remover_inicio(&((*p)->L));
    (*p)->tam--;
}
