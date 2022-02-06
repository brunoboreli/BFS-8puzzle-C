#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int main(){

	//alocação da matriz do estado inicial
	int **matriz_in = malloc(3*sizeof(int*));
	for(int i=0;i<3;i++){
		matriz_in[i] = malloc(3*sizeof(int));
	}
	//criando arvore 
	Folha *raiz = criar_arvore();


	printf("8PUZZLE SOLVER\nAutor: Bruno Boreli\n");
	printf("Digite o tabuleiro inicial:\n");

	//escaneando a matriz do estado inicial
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			scanf("%d", &matriz_in[i][j]);
		}
	}
	//criando vetor que acha a posição do zero na matriz inicial
	//isso é importante para mover os zeros e, portanto, gerar
	//cada filho do nó. A posição do zero é sempre passada
	//para facilitar esse processo
	int *pos_zero = malloc(2*sizeof(int));



	if(raiz == NULL){
		//func para achar a posição do zero
		achar_zero(matriz_in, pos_zero);

		//função cria nó e armazena na arvore
		raiz = criar_no(pos_zero,matriz_in);

	}

	printf("\n");

	//vetor para verificar se um nó já foi inserido na arvore
	int num_chaves = 876543211;
	//Vetor dotado de chaves para os possíveis estados. Se um estado já foi colocado na arvore
	//sua posição neste vetor constará como 1, caso contrário constará como 0.
	int *vector = (int*) (malloc(num_chaves*sizeof(int)));

	//chama a BFS passando o vetor de chaves e o estado inicial (nó raiz da arvore)
	percurso_largura(raiz,vector);

	printf("Autor: Bruno Boreli\n");
	
	
	//desalocando arvore
	destruir_arvore(&raiz);
	//desalocando memoria da matriz e posiçaõ do zero
	for(int i=0;i<3;i++){
		free(matriz_in[i]);
	}
	free(matriz_in);
	free(pos_zero);

	return 0;
}
