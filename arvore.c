#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"

//variável global para contar o número de nós criados no programa
int nos_gerados = 1;

Folha* criar_no(int *pos, int **matriz_in) {
	Folha *folha = (Folha*) malloc(sizeof(Folha));

	//posição do zero
	folha -> pos_zero[0] = pos[0];
	folha -> pos_zero[1] = pos[1];

	//colocando ponteiros filhos como nulo inicialmente
	folha->esq = NULL;	
	folha->dir = NULL;
	folha->cima = NULL;
	folha->baixo = NULL;
	folha -> pai = NULL;
	//colocando a matriz no nó
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			(folha)->matriz[i][j] = matriz_in[i][j];
		}
	}


   return folha;
}

int* achar_zero(int **matriz, int *pos_zero){
	for(int i = 0; i<3; i++){
		for(int j = 0; j<3; j++){
			if(matriz[i][j] == 0){
				pos_zero[0] = i;
				pos_zero[1] = j;
				return pos_zero;
			}
		}
	}

	return pos_zero;
}

void imprime_no(Folha *p){
	if(p==NULL)return;

	//imprime o tabuleiro
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			printf("%d ", (p -> matriz[i][j]));
		}
		printf("\n");
	}

	//imprime o vetor da posição do zero
	printf("%d %d\n", (p->pos_zero[0])+1, (p->pos_zero[1])+1);
}

Folha* criar_arvore(){
	return NULL;
}

int verifica_folha(Folha *p){
	//estado objetivo está armazenado nesta função
	//para alterar o objetivo basta alterar esta matriz:
	int matriz_final[3][3] = 
	{{1,2,3},
	 {4,5,6},
	 {7,8,0}
	};

	//verificando igualdade
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(matriz_final[i][j] != p->matriz[i][j]){
				return 0;
			}
		}
	}

	return 1;
}

void destruir_arvore(Folha **raiz){//função recursiva
	if (*raiz == NULL) return;
	destruir_arvore(&((*raiz)->esq));
	destruir_arvore(&((*raiz)->dir));
	destruir_arvore(&((*raiz)->cima));
	destruir_arvore(&((*raiz)->baixo));
	free(*raiz);
	*raiz = NULL;
}

int gerar_filhos(Folha *p, Folha *raiz,int vector[]){
	//a geração de filhos pode expandir a arvore em até 4 nós
	//movendo o 0 para a direita, esquerda, cima e baixo

	//primeiro verifica-se se é possível mover o 0 para a direção desejada
	//e verifica se o nó gerado já não existe na arvore
	
	//para verificar a existencia fazemos essa verificação no vetor
	//via chave do nó. A chave nada mais é que um inteiro com os números
	//dentro do tabuleiro ex: 876243150. Se vector[876243150] == 1
	//esse tabuleiro ja existe na arvore e portanto não entra novamente

	int key;
	//criar chave é algoritmo simples para pegar numeros da matriz e transformá-los em um int
	key = criar_chave(p);
	vector[key] = 1;
	
	for(int x = 0; x <= 3; x++){
		//o loop de 0 a 3 representa a geração de cada filho
		//sendo x=0 o filho movendo o 0 para a esquerda e assim por diante

		if(x == 0){
			//x=0 gera novo estado movendo 0 para a esquerda
			//gerar filho movendo 0 para a esquerda
			int **matriz_nova = malloc(3*sizeof(int*));
			for(int i=0;i<3;i++){
				matriz_nova[i] = malloc(3*sizeof(int));
			}
			int *pos_zero_new = malloc(2*sizeof(int));

			for(int i=0; i<3; i++){
				for(int j=0; j<3; j++){
					matriz_nova[i][j] =  (p)->matriz[i][j];
				}
			}

			pos_zero_new[0] = (p)->pos_zero[0];
			pos_zero_new[1] = (p)->pos_zero[1];

			if(pos_zero_new[1] > 0){
				//trocando elemento da celula da esquerda com o zero que
				//está a direita
				int aux;
				aux = matriz_nova[pos_zero_new[0]][pos_zero_new[1]];
				matriz_nova[pos_zero_new[0]][pos_zero_new[1]] = matriz_nova[pos_zero_new[0]][pos_zero_new[1]-1];
				matriz_nova[pos_zero_new[0]][pos_zero_new[1]-1] = aux;

				pos_zero_new[1] = pos_zero_new[1] - 1;
				//criando nó com nova matriz
				Folha *aux_no = criar_no(pos_zero_new,matriz_nova);
				key = criar_chave(aux_no);

				if(vector[key]){
					//verificando se o nó já contém na arvore
					for(int i=0;i<3;i++){
						free(matriz_nova[i]);
					}
					free(matriz_nova);
					free(pos_zero_new);
					free(aux_no);
				}
				else{
					//se estiver tudo ok, coloca na arvore
					nos_gerados++;
					p->esq = aux_no;
					(p->esq)->pai = p;
					for(int i=0;i<3;i++){
						free(matriz_nova[i]);
					}
					free(matriz_nova);
					free(pos_zero_new);

				}
				
			}
			else{
				for(int i=0;i<3;i++){
					free(matriz_nova[i]);
				}
				free(matriz_nova);
				free(pos_zero_new);
				
			}
		}
		else if(x == 1){
			//x=0 gera novo estado movendo 0 para baixo
			//gerar filho movendo 0 para baixo
			int **matriz_nova = malloc(3*sizeof(int*));
			for(int i=0;i<3;i++){
				matriz_nova[i] = malloc(3*sizeof(int));
			}
			int *pos_zero_new = malloc(2*sizeof(int));

			for(int i=0; i<3; i++){
				for(int j=0; j<3; j++){
					matriz_nova[i][j] =  (p)->matriz[i][j];
				}
			}

			pos_zero_new[0] = (p)->pos_zero[0];
			pos_zero_new[1] = (p)->pos_zero[1];

			if(pos_zero_new[0] < 2){
				//trocando elemento da celula de baixo com o zero que
				//está acima
				int aux;
				aux = matriz_nova[pos_zero_new[0]][pos_zero_new[1]];
				matriz_nova[pos_zero_new[0]][pos_zero_new[1]] = matriz_nova[pos_zero_new[0]+1][pos_zero_new[1]];
				matriz_nova[pos_zero_new[0]+1][pos_zero_new[1]] = aux;

				pos_zero_new[0] = pos_zero_new[0] + 1;
				//criando nó com nova matriz
				Folha *aux_no = criar_no(pos_zero_new,matriz_nova);
				key = criar_chave(aux_no);

				if(vector[key]){
					//verificando se o nó já contém na arvore
					for(int i=0;i<3;i++){
						free(matriz_nova[i]);
					}
					free(matriz_nova);
					free(pos_zero_new);
					free(aux_no);
					
				}
				else{
					nos_gerados++;
					p->baixo = aux_no;
					(p->baixo)->pai = p;
					for(int i=0;i<3;i++){
						free(matriz_nova[i]);
					}
					free(matriz_nova);
					free(pos_zero_new);
				}
				
			}
			else{
				for(int i=0;i<3;i++){
					free(matriz_nova[i]);
				}
				free(matriz_nova);
				free(pos_zero_new);
				
			}
		}
		else if(x == 2){
			//x=0 gera novo estado movendo 0 para a direita
			//gerar filho movendo 0 para a direita
			int **matriz_nova = malloc(3*sizeof(int*));
			for(int i=0;i<3;i++){
				matriz_nova[i] = malloc(3*sizeof(int));
			}
			int *pos_zero_new = malloc(2*sizeof(int));

			for(int i=0; i<3; i++){
				for(int j=0; j<3; j++){
					matriz_nova[i][j] =  (p)->matriz[i][j];
				}
			}

			pos_zero_new[0] = (p)->pos_zero[0];
			pos_zero_new[1] = (p)->pos_zero[1];

			if(pos_zero_new[1] < 2){
				//trocando elemento da celula da direita com o zero que
				//está a esquerda
				int aux;
				aux = matriz_nova[pos_zero_new[0]][pos_zero_new[1]];
				matriz_nova[pos_zero_new[0]][pos_zero_new[1]] = matriz_nova[pos_zero_new[0]][pos_zero_new[1]+1];
				matriz_nova[pos_zero_new[0]][pos_zero_new[1]+1] = aux;

				pos_zero_new[1] = pos_zero_new[1] + 1;
				//criando nó com nova matriz
				Folha *aux_no = criar_no(pos_zero_new,matriz_nova);
				key = criar_chave(aux_no);

				if(vector[key]){
					//verificando se o nó já contém na arvore
						for(int i=0;i<3;i++){
						free(matriz_nova[i]);
					}
					free(matriz_nova);
					free(pos_zero_new);
					free(aux_no);
					
				}
				else{
					nos_gerados++;
					p->dir = aux_no;
					(p->dir)->pai = p;
					for(int i=0;i<3;i++){
						free(matriz_nova[i]);
					}
					free(matriz_nova);
					free(pos_zero_new);
				}
				
			}
			else{
				for(int i=0;i<3;i++){
					free(matriz_nova[i]);
				}
				free(matriz_nova);
				free(pos_zero_new);
				
			}
		}
		else if(x == 3){
			//x=0 gera novo estado movendo 0 para cima
			//gerar filho movendo 0 para cima
			int **matriz_nova = malloc(3*sizeof(int*));
			for(int i=0;i<3;i++){
				matriz_nova[i] = malloc(3*sizeof(int));
			}
			int *pos_zero_new = malloc(2*sizeof(int));

			for(int i=0; i<3; i++){
				for(int j=0; j<3; j++){
					matriz_nova[i][j] =  (p)->matriz[i][j];
				}
			}

			pos_zero_new[0] = (p)->pos_zero[0];
			pos_zero_new[1] = (p)->pos_zero[1];

			if(pos_zero_new[0] > 0){
				//trocando elemento da celula de cima com o zero que
				//está abaixo
				int aux;
				aux = matriz_nova[pos_zero_new[0]][pos_zero_new[1]];
				matriz_nova[pos_zero_new[0]][pos_zero_new[1]] = matriz_nova[pos_zero_new[0]-1][pos_zero_new[1]];
				matriz_nova[pos_zero_new[0]-1][pos_zero_new[1]] = aux;

				pos_zero_new[0] = pos_zero_new[0] - 1;
				//criando nó com nova matriz
				Folha *aux_no = criar_no(pos_zero_new,matriz_nova);
				key = criar_chave(aux_no);

				if(vector[key]){
					//verificando se o nó já contém na arvore
						for(int i=0;i<3;i++){
						free(matriz_nova[i]);
					}
					free(matriz_nova);
					free(pos_zero_new);
					free(aux_no);
					
				}
				else{
					nos_gerados++;
					p->cima = aux_no;
					(p->cima)->pai = p;
					for(int i=0;i<3;i++){
						free(matriz_nova[i]);
					}
					free(matriz_nova);
					free(pos_zero_new);
				}

			}
			else{
				for(int i=0;i<3;i++){
					free(matriz_nova[i]);
				}
				free(matriz_nova);
				free(pos_zero_new);
				
			}
		}

	}


	return 0;
}

int criar_chave(Folha* raiz){
	int nums[9];
	int k = 0;

	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			nums[k] = raiz->matriz[i][j];
			k++;
		}
	}

	int numero = 0;
	int potencia = 1;
	for(int i = 0; i < 9; i++){

			numero = numero + (nums[8-i] * potencia);
			potencia *= 10;
	}

	return numero;
}

int percurso_largura(Folha *p,int vetor[]){
	//criando fila para realizar busca em largura
	Fila *f = fila_criar();
	printf("Processando...\n");

	//as variáveis do tipo (No) são uma estrutura de dados que contém:
	//um ponteiro para um endereço de um nó da arvore
	//e um ponteiro para o próximo, uma vez que esse tipo de struct será usado
	//nas filas e listas do programa

	//já o tipo de dado Folha contem vetor com posição do zero, a matriz do estado
	//que armazena e ponteiros para os seus possíveis filhos(dir, esq, cima e baixo)
	//essas estruturas estão criadas no arquivo lista_circular.h

	//assim as filas/listas serão como vagões de trem, em que cada vagão(nó da lista) armazenará
	//uma referência para um nó(chamado de Folha) da arvore

	//criando variavel para armazenar a folha raiz
	No *leaf = (No*) malloc(sizeof(No));
	(leaf)->end = p;
	leaf->prox = NULL;


	//armazenando o primeiro a ser processado na variavel 'raiz'
	Folha *raiz = p; 

	//enfileirando a raíz
	fila_adicionar(&f, leaf->end);
	
	//até aqui, apenas o nó raíz está na fila
	//agora tomamos o nó raíz e enfileiraremos seus filhos 
	//e assim por diante

	//algoritmo BFS INICIADO	
	while(fila_vazia(f) != 1){
		
		
		//desinfileirando o primeiro(raiz)	
		p = acessar_inicio(f);
		//expandindo os filhos
		gerar_filhos(p,raiz,vetor);
		//verificando se p é o estado objetivo
		if(verifica_folha(p)){
			printf("SOLVED\n");
			imprime_caminho(raiz,p);
			printf("Estados Enfileirados: %d\n", fila_tam(f));
			break;
		}
		//desenfileira de fato
		fila_remover(&f);

		//enfileira os filhos de p
		if(p!=NULL){
			(leaf)->end = p->esq;
			fila_adicionar(&f, leaf->end);


			(leaf)->end = p->dir;
			fila_adicionar(&f, leaf->end);


			(leaf)->end = p->cima;
			fila_adicionar(&f, leaf->end);


			(leaf)->end = p->baixo;
			fila_adicionar(&f, leaf->end);

		}
		
	}
	
	free(leaf);
	fila_destruir(&f);	
	return 0;
}

void imprime_caminho(Folha *raiz, Folha *no){
	Folha *auxFolha = no;
	int num = 0;
	No *press = criar_lista();

	//imprime caminho basicamente vai colocando
	//os nós no inicio de uma lista. O nó aux vai andando para o pai
	//dos nós até chegar na raiz 
	//Depois basta printar a lista

	while(auxFolha != raiz){
		adicionar_inicio(&press,auxFolha);
		//imprime_no(aux);
		num++;
		auxFolha = auxFolha->pai;
	}

	No* q, *aux=press; 
	if(press!=NULL){
		for (q = (press)->prox; q != aux; q = q->prox){
			imprime_no(q->end);
			printf("\n");
		}
		imprime_no(q->end);
		printf("\n");
	}

	destruir_lista(&press);
	printf("SOLVED!\nDETALHES:\n");
	printf("Passos: %d\n", num);
	printf("Nós Gerados: %d\n", nos_gerados);
	
	 
}
