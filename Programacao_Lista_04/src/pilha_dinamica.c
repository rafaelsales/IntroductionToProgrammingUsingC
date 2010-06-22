/*
 ============================================================================
 Arquivo     : Programação - Lista 04 - PILHA DINÂMICA
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct no {
	int info;
	struct no* prox;
};
typedef struct no No;

struct no_final {
	No* prox;
};
typedef struct no_final Fim;

Fim* criaPilha() {
	Fim* topo = (Fim*) malloc(sizeof(Fim));
	topo->prox = NULL;
	return topo;
}

void empilha(Fim* topo, int valor) {
	No* novo = (No*) malloc(sizeof(No));
	if (novo != NULL) {
		novo->info = valor;
		novo->prox = topo->prox;
		topo->prox = novo;
	} else
		printf("Erro na insercao\n");
}

//retorna -1, caso a lista esteja vazia
int* desempilha(Fim* topo) {
	No* no_desempilhado;
	int* desempilhado=(int*)malloc(sizeof(int));
	if (topo->prox != NULL) {
		no_desempilhado = topo->prox;
		*desempilhado = no_desempilhado->info;
		topo->prox = no_desempilhado->prox;
		free(no_desempilhado);
		return desempilhado;
	}
	printf("Pilha vazia!\n");
	return NULL;
}

// imprime do topo para a base
void imprimePilha(Fim* topo) {
	No* percorre = topo->prox;
	if (percorre != NULL) {
		while (percorre != NULL) {
			printf("%d\n", percorre->info);
			percorre = percorre->prox;
		}
	} else
		printf("Pilha vazia!\n");
}

No* buscaPilha(Fim* topo, int valor) {
	No* percorre = topo->prox;
	while (percorre != NULL) {
		if (percorre->info == valor)
			return percorre;
		percorre = percorre->prox;
	}
	return NULL;
}

// main usado para fazer testes
int main(void) {
    int* desempilhado;
	Fim* topo = criaPilha();
	No* buscado;
	int controle = 1, opcao, valor;
	printf("    ==== Pilha ====");
	while (controle == 1) {
		printf("\n -> Para inserir elemento, digite 1\n");
		printf(" -> Para remover elemento, digite 2\n");
		printf(" -> Para buscar elemento, digite 3\n");
		printf(" -> Para imprimir a lista, digite 4\n");
		printf(" => ");
		scanf("%d", &opcao);
		switch (opcao) {
		case 1: {
			printf("\nQual o valor a ser incluso? ");
			scanf("%d", &valor);
			empilha(topo, valor);
			break;
		}
		case 2: {
			desempilhado=desempilha(topo);
	        if(desempilhado!=NULL) printf("\n - Valor desempilhado: %d\n", *desempilhado);
			break;
		}
		case 3: {
			printf("\nQual o valor a ser buscado? ");
			scanf("%d", &valor);
			buscado = buscaPilha(topo, valor);
			if (buscado == NULL)
				printf("\n *** Valor inexistente na pilha\n");
			else
				printf("\n *** Valor existente na pilha\n");
			break;
		}
		case 4:
			imprimePilha(topo);
			break;
		default:
			printf("\n *** Operacao invalida!\n");
		}
		printf(" ** Deseja continuar? (Sim-1/Nao-0) ");
		scanf("%d", &controle);
	}
	return 0;
}

