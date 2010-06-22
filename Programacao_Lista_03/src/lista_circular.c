/*
 ============================================================================
 Arquivo     : Programação - Lista 03 - Questao 02 (LISTA CIRCULAR)
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// declaracao de tipos usados na implementacao
struct lista_circular {
	int info;
	struct lista_circular* prox;
};

typedef struct lista_circular No;

// declaracao das funcoes da lista
No* criaLista(void);
No* insereLista(No* fim, int valor);
No* busca_anterior(No* fim, int valor);
No* busca(No* fim, int valor);
No* removeLista(No* fim, int valor);
void imprimeLista(No* fim);

// cria lista
No* criaLista(void) {
	return NULL;
}

// insere no fim da lista e retorna o novo no fim
No* insereLista(No* fim, int valor) {
	No* novo = (No*) malloc(sizeof(No));
	if (novo != NULL) {
		novo->info = valor;
		if (fim == NULL) {
			novo->prox = novo;
		} else {
			novo->prox = fim->prox;
			fim->prox = novo;
		}
		printf("Inclusao realizada\n");
		return novo;
	}
	printf("Erro na insercao\n");
	return fim;
}

// retorna o no anterior ao no com o valor buscada (para facilitar a reordenacao da lista
// o no buscado eh, portanto, ant_buscado->prox
No* busca_anterior(No* fim, int valor) {
	No* ant_buscada = fim;
	if (fim != NULL) {
		while ((ant_buscada->prox->info != valor) && (ant_buscada->prox != fim)) {
			ant_buscada = ant_buscada->prox;
		}
		if (ant_buscada->prox->info == valor)
			return ant_buscada;
	}
	return NULL;
}

// retorna o no com o valor buscado (NULL, caso nao encontrado)
No* busca(No* fim, int valor) {
	No* buscada, *anterior_buscado = busca_anterior(fim, valor);
	if (anterior_buscado == NULL) {
		buscada = NULL;
	} else
		buscada = anterior_buscado->prox;
	return buscada;
}

// remove elemento (caso pertenca a lista) e retorna o novo fim
No* removeLista(No* fim, int valor) {
	No* ant_buscada = busca_anterior(fim, valor);
	No* buscada;
	if (fim != NULL) {
		if (ant_buscada != NULL) {
			buscada = ant_buscada->prox;
			if (buscada->prox == buscada) {
				free(buscada);
				printf("Valor removido\n");
				return NULL;
			} else {
				ant_buscada->prox = buscada->prox;
				if (buscada == fim)
					fim = ant_buscada;
				free(buscada);
				printf("Valor removido\n");
			}
		} else
			printf("Valor nao encontrado na lista\n");
	} else
		printf("Lista vazia\n");
	return fim;
}

// imprime do inicio para o fim
void imprimeLista(No* fim) {
	No* percorre;
	if (fim != NULL) {
		percorre = fim->prox;
		while (percorre != fim) {
			printf("%d\n", percorre->info);
			percorre = percorre->prox;
		}
		printf("%d\n", fim->info);
	} else
		printf("Lista Vazia!\n");
}

// funcao main (para testar lista)
int main(void) {
	No* fim = criaLista(), *buscado;
	int controle = 1, opcao, valor;
	printf(" -- Lista Circular --\n");
	while (controle == 1) {
		printf("\n -> Para inserir elemento, digite 1\n");
		printf(" -> Para remover elemento, digite 2\n");
		printf(" -> Para buscar elemento, digite 3\n");
		printf(" -> Para imprimir a lista, digite 4\n");
		printf(" Opcao: ");
		scanf("%d", &opcao);
		switch (opcao) {
		case 1: {
			printf("\nQual o valor a ser incluso? ");
			scanf("%d", &valor);
			fim = insereLista(fim, valor);
			break;
		}
		case 2: {
			printf("\nQual o valor a ser removido? ");
			scanf("%d", &valor);
			fim = removeLista(fim, valor);
			break;
		}
		case 3: {
			printf("\nQual o valor a ser buscado? ");
			scanf("%d", &valor);
			buscado = busca(fim, valor);
			if (buscado == NULL)
				printf("\n *** Valor inexistente na lista\n");
			else
				printf("\n *** Valor existente na lista\n");
			break;
		}
		case 4:
			imprimeLista(fim);
			break;
		default:
			printf("\n *** Operacao invalida!\n");
		}
		printf(" ** Deseja continuar? (Sim-1/Nao-0) ");
		scanf("%d", &controle);
	}

	return 0;
}
