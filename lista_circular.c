#include <stdlib.h>
#include <stdio.h>
#include "lista_circular.h"

No* criar_lista() {
    return NULL;
}

void destruir_lista(No **p) {//versão iterativa
    if(*p == NULL) return;// lista vazia
    No *q = (*p)->prox, *aux;
    while(q != *p){
        aux = q;
        q = q->prox;
        free(aux);
    }
    free(*p);
    *p = NULL;
}



void adicionar_inicio(No** p, Folha* x){//p recebe &L
    No *q = (No*) malloc(sizeof(No));
    q->end = (x);
    if(*p == NULL){ //lista vazia
        *p = q;
        q->prox = q;
    }
    else{
        q->prox = (*p)->prox;
        (*p)->prox = q;
    }
}

void adicionar_final(No **p, Folha* x) {// p recebe L
    No *q = (No*) malloc(sizeof(No));
    q->end = (x);
    if(*p == NULL){ //lista vazia
        *p = q;
        q->prox = q;
    }
    else{
        q->prox = (*p)->prox;
        (*p)->prox = q;
        *p = q;
    }
}

void remover_inicio(No **p) {// p recebe L
    if(*p==NULL) return; //lista vazia
    No* q = *p;
    if(q->prox==q){//1 único nó
        
        free(q); 
        *p = NULL;
        return;
    }
    q = q->prox;
    (*p)->prox = q->prox;
    free(q);
}

void remover_final(No **p) {// p recebe L
    if(*p==NULL) return; //lista vazia
    No* q = *p;
    if(q->prox==q){//1 único nó
        free(q); *p = NULL;
        return;
    }
    No *aux = q;
    while(q->prox != aux) q = q->prox;
    q->prox = aux->prox;
    *p = q;
    free(aux);
}


