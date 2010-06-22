/*
 ============================================================================
 Arquivo     : Programação - Lista 05 - Questao 01 (Arvore Binaria de Busca)
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>

struct arv_busca {
	int info;
	int vazia;
	struct arv_busca* esq;
	struct arv_busca* dir;
};
typedef struct arv_busca no;

no* criaArv(void) {
	no* raiz = (no*) malloc(sizeof(no));
	raiz->vazia = 1;
	printf("Arvore criada!\n");
	return raiz;
}

no* buscaArv(no* raiz, int valor) {
	no* percorre = raiz, *ant_percorre = raiz;
	if (raiz->vazia != 1) {
		while ((percorre != NULL) && (valor != percorre->info)) {
			ant_percorre = percorre;
			if (valor > percorre->info)
				percorre = percorre->dir;
			else
				percorre = percorre->esq;
		}
		return percorre;
	}
	return NULL;
}

no* buscaAntArv(no* raiz, int valor) { // retorno o noh pai do buscado (NULL, caso noh pai inexistente)
	no* percorre = raiz, *ant_percorre = NULL;
	if (raiz->vazia != 1) {
		while ((percorre != NULL) && (valor != percorre->info)) {
			ant_percorre = percorre;
			if (valor > percorre->info)
				percorre = percorre->dir;
			else
				percorre = percorre->esq;
		}
		return ant_percorre;
	}
	return NULL;
}

no* insereArv(no* raiz, int valor) {
	no* retorno = NULL;
	if (raiz != NULL) {
		if (buscaArv(raiz, valor) == NULL) {
			if (raiz->vazia == 1) {
				raiz->info = valor;
				raiz->vazia = 0;
				raiz->esq = NULL;
				raiz->dir = NULL;
				retorno = raiz;
			} else {
				no* percorre, *ant_percorre;
				no* novo = (no*) malloc(sizeof(no));
				novo->info = valor;
				novo->vazia = 0;
				novo->esq = NULL;
				novo->dir = NULL;
				if (valor > raiz->info)
					percorre = raiz->dir;
				else
					percorre = raiz->esq;
				ant_percorre = raiz;
				while (percorre != NULL) {
					ant_percorre = percorre;
					if (valor > percorre->info)
						percorre = percorre->dir;
					else
						percorre = percorre->esq;
				}
				if (valor > ant_percorre->info)
					ant_percorre->dir = novo;
				else
					ant_percorre->esq = novo;
				retorno = novo;
			}
			printf("Valor incluso com sucesso!\n");
		} else
			printf("Valor ja existente!\n");
	}
	return retorno;
}

void balancoMaior(no* raiz_buscado) { // raiz_buscado->esq é diferente de NULL
	no* percorre, *ant_percorre;
	if ((raiz_buscado != NULL) && (raiz_buscado->esq != NULL)) {
		percorre = raiz_buscado->esq;
		ant_percorre = raiz_buscado;
		while (percorre->dir != NULL) {
			ant_percorre = percorre;
			percorre = percorre->dir;
		}
		raiz_buscado->info = percorre->info;
		if (percorre != raiz_buscado->esq)
			ant_percorre->dir = percorre->esq;
		else
			raiz_buscado->esq = percorre->esq;
		free(percorre);
	}
}

void balancoMenor(no* raiz_buscado) { // raiz_buscado->dir é diferente de NULL
	no* percorre, *ant_percorre;
	if ((raiz_buscado != NULL) && (raiz_buscado->dir != NULL)) {
		percorre = raiz_buscado->dir;
		ant_percorre = raiz_buscado;
		while (percorre->esq != NULL) {
			ant_percorre = percorre;
			percorre = percorre->esq;
		}
		raiz_buscado->info = percorre->info;
		if (percorre != raiz_buscado->dir)
			ant_percorre->esq = percorre->dir;
		else
			raiz_buscado->dir = percorre->dir;
		free(percorre);
	}
}

no* removeArv(no* raiz, int valor) {
	no* buscado = buscaArv(raiz, valor), *ant_buscado =
			buscaAntArv(raiz, valor);
	if (buscado != NULL) {
		if (buscado->esq != NULL) {
			balancoMaior(buscado);
		} else {
			if (buscado->dir != NULL) {
				balancoMenor(buscado);
			} else {
				if (ant_buscado == NULL) {
					printf("Remocao do valor %d realizada com sucesso!\n",
							valor);
					printf("Arvore destruida!!!\n");
					free(buscado);
					return NULL;
				}//else
				if (ant_buscado->dir == buscado)
					ant_buscado->dir = NULL;
				else
					ant_buscado->esq = NULL;
				free(buscado);
			}
		}
		printf("Remocao do valor %d realizada com sucesso!\n", valor);
	} else
		printf("Elemento inexistente na arvore!\n");
	return raiz;
}

void imprimePreOrdem(no* raiz) {
	no* percorre = raiz;
	if (percorre != NULL) {
		printf("<%d>", percorre->info);
		imprimePreOrdem(percorre->esq);
		imprimePreOrdem(percorre->dir);
	}
}

void imprimePosOrdem(no* raiz) {
	no* percorre = raiz;
	if (percorre != NULL) {
		imprimePosOrdem(percorre->esq);
		imprimePosOrdem(percorre->dir);
		printf("<%d>", percorre->info);
	}
}

void imprimeSimetrica(no* raiz) {
	no* percorre = raiz;
	if (percorre != NULL) {
		imprimeSimetrica(percorre->esq);
		printf("<%d>", percorre->info);
		imprimeSimetrica(percorre->dir);
	}
}

int main() {
	int opcao = 0, valor;
	no* raiz = NULL, *no;
	do {
		system("cls");
		printf("|||||||||| MENU |||||||||| \n");
		printf("(1) Criar Arvore\n");
		printf("(2) Inserir em Arvore\n");
		printf("(3) Remover de Arvore\n");
		printf("(4) Buscar elemento em Arvore\n");
		printf("(5) Imprimir (Pre-Ordem)\n");
		printf("(6) Imprimir (Pos-Ordem)\n");
		printf("(7) Imprimir (Ordem Simetrica)\n");
		printf("(8) Encerrar\n");
		printf("Opcao: ");
		scanf("%d", &opcao);
		getchar();
		switch (opcao) {
		case 1: {
			raiz = criaArv();
			printf("Tecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 2: {
			if (raiz != NULL) {
				printf("Valor a ser incluso: ");
				scanf("%d", &valor);
				getchar();
				no = insereArv(raiz, valor);
			} else
				printf("Crie a arvore antes!\n");
			printf("Tecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 3: {
			if (raiz != NULL) {
				printf("Valor a ser removido: ");
				scanf("%d", &valor);
				getchar();
				raiz = removeArv(raiz, valor);
			} else
				printf("Crie a arvore antes!\n");
			printf("Tecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 4: {
			if (raiz != NULL) {
				printf("Valor a ser buscado: ");
				scanf("%d", &valor);
				getchar();
				if (buscaArv(raiz, valor) != NULL)
					printf(" *** Valor presente na arvore!\n");
				else
					printf(" *** Valor ausente na arvore!\n");
			} else
				printf("Crie a arvore antes!\n");
			printf("Tecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 5: {
			if ((raiz != NULL) && (raiz->vazia != 1)) {
				printf("\n -> Impressao em Pre-Ordem\n");
				imprimePreOrdem(raiz);
			} else
				printf("Arvore Vazia\n");
			printf("\n\nTecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 6: {
			if ((raiz != NULL) && (raiz->vazia != 1)) {
				printf("\n -> Impressao em Pos-Ordem\n");
				imprimePosOrdem(raiz);
			} else
				printf("Arvore Vazia\n");
			printf("\n\nTecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 7: {
			if ((raiz != NULL) && (raiz->vazia != 1)) {
				printf("\n -> Impressao em Ordem Simetrica\n");
				imprimeSimetrica(raiz);
			} else
				printf("Arvore Vazia\n");
			printf("\n\nTecle ENTER para continuar\n");
			getchar();
			break;
		}
		}
	} while (opcao != 8);
	return 0;
}
