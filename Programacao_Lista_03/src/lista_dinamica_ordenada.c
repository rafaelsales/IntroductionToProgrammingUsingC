/*
 ============================================================================
 Arquivo     : Programação - Lista 03 - Questao 01 (LISTA DINAMICA ORDENADA)
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// declaracao dos tipos usados na implementacao
struct lista_ordenada {
	int info;
	struct lista_ordenada* prox;
};

typedef struct lista_ordenada No;

struct no_cabeca {
	struct lista_ordenada* prox;
};

typedef struct no_cabeca No_cabeca;

//cria lista
No_cabeca* criaLista(void) {
	No_cabeca* inicio = (No_cabeca*) malloc(sizeof(No_cabeca));
	inicio->prox = NULL;
	return inicio;
}

// insere preservando a ordenacao
void insereLista(No_cabeca* inicio, int valor) {
	No* novo = (No*) malloc(sizeof(No));
	No* percorre = inicio->prox;
	if (novo != NULL) {
		if ((inicio->prox == NULL) || (valor < inicio->prox->info)) {
			novo->prox = inicio->prox;
			inicio->prox = novo;
		} else {
			while ((percorre->prox != NULL) && (percorre->prox->info < valor)) {
				percorre = percorre->prox;
			}
			novo->prox = percorre->prox;
			percorre->prox = novo;
		}
		novo->info = valor;
		printf(" -> Insercao realizada com sucesso!\n");
	} else
		printf(" ** Erro na insercao\n");
}

// busca no cujo campo info tem o valor procurado
No* busca(No_cabeca* inicio, int valor) {
	No* percorre = inicio->prox;
	while (percorre != NULL) {
		if (percorre->info == valor)
			return percorre; // caso encontre, ja retorna o no
		percorre = percorre->prox;
	}
	return NULL; // caso nao encontre
}

// algoritmo de busca que facilita a remocao de um dado no (pois retorna o no anterior ao que sera removido)
No* busca_anterior(No_cabeca* inicio, int valor) {
	No* ant_buscada;
	No* buscada;
	if (inicio->prox != NULL) {
		ant_buscada = inicio->prox;
		buscada = inicio->prox;
		// se o buscado for o primeiro no, ele eh retornado
		if (inicio->prox->info == valor)
			return inicio->prox;
		while ((buscada->prox != NULL) && (buscada->info != valor)) {
			ant_buscada = buscada;
			buscada = buscada->prox;
		}
		if (buscada->info == valor)
			return ant_buscada;
		return NULL;
	}
	printf(" ** Lista Vazia!!\n");
	return NULL;
}

//remove elemento (caso exista) da lista
void removeLista(No_cabeca* inicio, int valor) {
	No* ant_buscada;
	No* buscada;
	if (inicio->prox != NULL) {
		ant_buscada = busca_anterior(inicio, valor);
		if (ant_buscada != NULL) {
			if (ant_buscada->info == valor) { // teste para ver se o buscado ja eh o primeiro no
				buscada = ant_buscada;
				inicio->prox = buscada->prox;
			} else {
				buscada = ant_buscada->prox;
				ant_buscada->prox = buscada->prox;
			}
			free(buscada);
			printf(" -> Remocao realizada com sucesso!\n");
		} else
			printf(" ** Valor nao encontrado na lista\n");
	} else
		printf(" ** Lista vazia\n");
}

// imprime do inicio para o fim
void imprimeLista(No_cabeca* inicio) {
	No* percorre = inicio->prox;
	if (inicio->prox != NULL) {
		while (percorre != NULL) {
			printf("%d\n", percorre->info);
			percorre = percorre->prox;
		}
	} else
		printf(" ** Lista vazia!!\n");
}

// main usado para fazer testes
int main(void) {
	No_cabeca* inicio = criaLista();
	No* buscado;
	int controle = 1, opcao, valor;
	printf("-- Lista Dinamica Ordenada --\n");
	while (controle == 1) {
		printf("\n -> Para inserir elemento, digite 1\n");
		printf(" -> Para remover elemento, digite 2\n");
		printf(" -> Para buscar elemento, digite 3\n");
		printf(" -> Para imprimir a lista, digite 4\n");
		printf(" * Opcao: ");
		scanf("%d", &opcao);
		switch (opcao) {
		case 1: {
			printf("\nQual o valor a ser incluso? ");
			scanf("%d", &valor);
			insereLista(inicio, valor);
			break;
		}
		case 2: {
			printf("\nQual o valor a ser removido? ");
			scanf("%d", &valor);
			removeLista(inicio, valor);
			break;
		}
		case 3: {
			printf("\nQual o valor a ser buscado? ");
			scanf("%d", &valor);
			buscado = busca(inicio, valor);
			if (buscado == NULL)
				printf("\n *** Valor inexistente na lista\n");
			else
				printf("\n *** Valor existente na lista\n");
			break;
		}
		case 4:
			imprimeLista(inicio);
			break;
		default:
			printf("\n *** Operacao invalida!\n");
		}
		printf(" ** Deseja continuar? (Sim-1/Nao-0) ");
		scanf("%d", &controle);
	}
	return 0;
}
