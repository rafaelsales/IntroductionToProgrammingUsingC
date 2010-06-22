/*
 ============================================================================
 Arquivo     : Programação - Prova 02 - Questao 01
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMANDO_LIMPAR_CONSOLE "cls" //Para Windows: "cls" ; Para Linux: "clear"
struct arv_busca {
	char info;
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

no* buscaArv(no* raiz, char valor) {
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

no* buscaAntArv(no* raiz, char valor) { // retorno o noh pai do buscado (NULL, caso noh pai inexistente)
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

int abs(int x) {
	if (x < 0)
		return -x;
	return x;
}

no* insereArv1(no* raiz, char valor) {
	no* retorno = NULL;
	if (raiz != NULL) { //insere sem repeticao
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
			printf(" *** Elemento ja existente!! (Apenas arvore 2 aceita repeticao)\n ");
	}
	return retorno;
}

no* insereArv2(no* raiz, char valor) {
	no* retorno = NULL;
	if (raiz != NULL) { //insere mesmo repetindo
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

no* removeArv(no* raiz, char valor) {
	no* buscado = buscaArv(raiz, valor), *ant_buscado = buscaAntArv(raiz, valor);
	if (buscado != NULL) {
		if (buscado->esq != NULL) {
			balancoMaior(buscado);
		} else {
			if (buscado->dir != NULL) {
				balancoMenor(buscado);
			} else {
				if (ant_buscado == NULL) {
					printf("Remocao do valor %c realizada com sucesso!\n", valor);
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
		printf("Remocao do valor %c realizada com sucesso!\n", valor);
	} else
		printf("Elemento inexistente na arvore!\n");
	return raiz;
}

void imprimePreOrdem(no* raiz) {
	no* percorre = raiz;
	if (percorre != NULL) {
		printf("<%c>", percorre->info);
		imprimePreOrdem(percorre->esq);
		imprimePreOrdem(percorre->dir);
	}
}

void imprimePosOrdem(no* raiz) {
	no* percorre = raiz;
	if (percorre != NULL) {
		imprimePosOrdem(percorre->esq);
		imprimePosOrdem(percorre->dir);
		printf("<%c>", percorre->info);
	}
}

void imprimeSimetrica(no* raiz) {
	no* percorre = raiz;
	if (percorre != NULL) {
		imprimeSimetrica(percorre->esq);
		printf("<%c>", percorre->info);
		imprimeSimetrica(percorre->dir);
	}
}

int max(int x, int y) {
	if (x > y)
		return x;
	else
		return y;
}

int calcAltura(no* raiz) {
	if (raiz != NULL) {
		return max(calcAltura(raiz->esq) + 1, calcAltura(raiz->dir) + 1);
	}
	return 0;
}

int calcBalanco(no* raiz) {
	if (raiz != NULL) {
		return (calcAltura(raiz->esq) - calcAltura(raiz->dir));
	}
	return 0;
}

void verificaAVL(no* raiz, int* avl) {
	if (raiz != NULL) {
		verificaAVL(raiz->esq, avl);
		if (abs(calcBalanco(raiz)) > 1)
			(*avl) = 0;
		verificaAVL(raiz->dir, avl);
	}
}

int calcQuantElem(no* raiz2, char valor) {
	if (raiz2 != NULL) {
		if (raiz2->info == valor)
			return (calcQuantElem(raiz2->esq, valor) + calcQuantElem(raiz2->dir, valor) + 1);
		return (calcQuantElem(raiz2->esq, valor) + calcQuantElem(raiz2->dir, valor));
	}
	return 0;
}

void imprimeElmQuat(no* raiz1, no* raiz2) {
	if (raiz1 != NULL) {
		imprimeElmQuat(raiz1->esq, raiz2);
		printf("<%c/%d>", raiz1->info, calcQuantElem(raiz2, raiz1->info));
		imprimeElmQuat(raiz1->dir, raiz2);
	}
}

void imprimeEmVetor(no* raiz, char* v, int* i) {
	if (raiz != NULL) {
		v[*i] = '<';
		(*i)++;
		v[*i] = 'x';
		(*i)++;
		v[*i] = '>';
		(*i)++;
		v[*i] = '<';
		(*i)++;
		imprimeEmVetor(raiz->esq, v, i);
		v[*i] = '>';
		(*i)++;;
		v[*i] = '<';
		(*i)++;
		imprimeEmVetor(raiz->dir, v, i);
		v[*i] = '>';
		(*i)++;
	}
}

int main() {
	int x = 0, opcao = 0, avl = 1, arvore = 0;
	char valor;
	no* raiz = NULL, *no, *raiz1 = NULL, *raiz2 = NULL;
	do {
		system(COMANDO_LIMPAR_CONSOLE);
		printf("|||||||||| ARVORE DE CARACTERES - MENU |||||||||| \n");
		printf("(1) Criar Arvore\n");
		printf("(2) Inserir em Arvore\n");
		printf("(3) Remover de Arvore\n");
		printf("(4) Buscar elemento em Arvore\n");
		printf("(5) Imprimir (Pre-Ordem)\n");
		printf("(6) Imprimir (Pos-Ordem)\n");
		printf("(7) Imprimir (Ordem Simetrica)\n");
		printf("(8) Verifica se arvore eh AVL\n");
		printf("(9) Imprime quantidade de cada elemento de 1 em 2\n");
		printf("(10) Verifica se 1 e 2 sao isomorficas\n");
		printf("(11) Encerrar\n");
		printf("Opcao: ");
		scanf("%d", &opcao);
		getchar();
		switch (opcao) {
		case 1: {
			printf("Arvore (1 ou 2): ");
			scanf("%d", &arvore);
			getchar();
			switch (arvore) {
			case 1: {
				raiz1 = criaArv();
				break;
			}
			case 2: {
				raiz2 = criaArv();
				break;
			}
			default: {
				raiz = NULL;
				printf(" * Arvore Invalida!\n");
				break;
			}
			}
			printf("Tecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 2: {
			printf("Arvore (1 ou 2): ");
			scanf("%d", &arvore);
			getchar();
			switch (arvore) {
			case 1: {
				if (raiz1 != NULL) {
					printf("Valor a ser incluso: ");
					scanf("%c", &valor);
					getchar();
					no = insereArv1(raiz1, valor);
				} else
					printf(" * Arvore %d nao foi criada!\n", arvore);
				break;
			}
			case 2: {
				if (raiz2 != NULL) {
					printf("Valor a ser incluso: ");
					scanf("%c", &valor);
					getchar();
					no = insereArv2(raiz2, valor);
				} else
					printf(" * Arvore %d nao foi criada!\n", arvore);
				break;
			}
			default: {
				raiz = NULL;
				printf(" * Arvore Invalida!\n");
				break;
			}
			}
			printf("Tecle ENTER para continuar\n");
			getchar();
			raiz = NULL;
			break;
		}
		case 3: {
			printf("Arvore (1 ou 2): ");
			scanf("%d", &arvore);
			getchar();
			switch (arvore) {
			case 1: {
				if (raiz1 != NULL) {
					printf("Valor a ser removido: ");
					scanf("%c", &valor);
					getchar();
					raiz1 = removeArv(raiz1, valor);
				} else
					printf(" * Arvore %d nao foi criada!\n", arvore);
				break;
			}
			case 2: {
				if (raiz2 != NULL) {
					printf("Valor a ser removido: ");
					scanf("%c", &valor);
					getchar();
					raiz2 = removeArv(raiz2, valor);
				} else
					printf(" * Arvore %d nao foi criada!\n", arvore);
				break;
			}
			default: {
				printf(" * Arvore Invalida!\n");
				break;
			}
			}
			printf("Tecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 4: {
			printf("Arvore (1 ou 2): ");
			scanf("%d", &arvore);
			getchar();
			switch (arvore) {
			case 1: {
				raiz = raiz1;
				break;
			}
			case 2: {
				raiz = raiz2;
				break;
			}
			default: {
				raiz = NULL;
				printf(" * Arvore Invalida!\n");
				break;
			}
			}
			if (raiz != NULL) {
				printf("Valor a ser buscado: ");
				scanf("%c", &valor);
				getchar();
				if (buscaArv(raiz, valor) != NULL)
					printf(" *** Valor presente na arvore!\n");
				else
					printf(" *** Valor ausente na arvore!\n");
			} else
				printf(" * Arvore %d nao foi criada!\n", arvore);
			printf("Tecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 5: {
			printf("Arvore (1 ou 2): ");
			scanf("%d", &arvore);
			getchar();
			switch (arvore) {
			case 1: {
				raiz = raiz1;
				break;
			}
			case 2: {
				raiz = raiz2;
				break;
			}
			default: {
				raiz = NULL;
				printf(" * Arvore Invalida!\n");
				break;
			}
			}
			if ((raiz != NULL) && (raiz->vazia != 1)) {
				printf("\n -> Impressao em Pre-Ordem\n");
				imprimePreOrdem(raiz);
			} else
				printf(" * Arvore Vazia\n");
			printf("\n\nTecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 6: {
			printf("Arvore (1 ou 2): ");
			scanf("%d", &arvore);
			getchar();
			switch (arvore) {
			case 1: {
				raiz = raiz1;
				break;
			}
			case 2: {
				raiz = raiz2;
				break;
			}
			default: {
				raiz = NULL;
				printf(" * Arvore Invalida!\n");
				break;
			}
			}
			if ((raiz != NULL) && (raiz->vazia != 1)) {
				printf("\n -> Impressao em Pos-Ordem\n");
				imprimePosOrdem(raiz);
			} else
				printf(" * Arvore Vazia\n");
			printf("\n\nTecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 7: {
			printf("Arvore (1 ou 2): ");
			scanf("%d", &arvore);
			getchar();
			switch (arvore) {
			case 1: {
				raiz = raiz1;
				break;
			}
			case 2: {
				raiz = raiz2;
				break;
			}
			default: {
				raiz = NULL;
				printf(" * Arvore Invalida!\n");
				break;
			}
			}
			if ((raiz != NULL) && (raiz->vazia != 1)) {
				printf("\n -> Impressao em Ordem Simetrica\n");
				imprimeSimetrica(raiz);
			} else
				printf(" * Arvore Vazia\n");
			printf("\n\nTecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 8: {
			printf("Arvore (1 ou 2): ");
			scanf("%d", &arvore);
			getchar();
			switch (arvore) {
			case 1: {
				raiz = raiz1;
				break;
			}
			case 2: {
				raiz = raiz2;
				break;
			}
			default: {
				raiz = NULL;
				printf(" * Arvore Invalida!\n");
				break;
			}
			}
			if (raiz != NULL) {
				if (raiz->vazia != 1) {
					avl = 1;
					verificaAVL(raiz, &avl);
					if (avl == 1)
						printf("A Arvore %d eh AVL\n", arvore);
					else
						printf("A Arvore %d nao eh AVL\n", arvore);
				} else
					printf(" * Arvore Vazia\n");
			} else
				printf(" * Arvore %d nao foi criada!\n", arvore);
			printf("\nTecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 9: {
			if ((raiz1 != NULL) && (raiz2 != NULL) && (raiz1->vazia != 1) && (raiz2->vazia != 1))
				imprimeElmQuat(raiz1, raiz2);
			else
				printf(" * Nao eh possivel fazer a analise! Existe pelo menos uma arvore nao criada ou vazia.\n");
			printf("\nTecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 10: {
			char * vetor1 = (char*) calloc(500, sizeof(char));
			char * vetor2 = (char*) calloc(500, sizeof(char));
			if ((raiz1 != NULL) && (raiz2 != NULL) && (raiz1->vazia != 1) && (raiz2->vazia != 1)) {
				x = 0;
				imprimeEmVetor(raiz1, vetor1, &x);
				x = 0;
				imprimeEmVetor(raiz2, vetor2, &x);
				printf("\n * Impressao Generica de 1:\n");
				printf("%s\n", vetor1);
				printf(" * Impressao Generica de 2:\n");
				printf("%s\n", vetor2);
				if (strcmp(vetor1, vetor2) == 0)
					printf(" *** As arvores sao isomorficas!\n");
				else
					printf(" *** As arvores nao sao isomorficas!\n");
			} else
				printf(" * Nao eh possivel fazer a analise! Existe pelo menos uma arvore nao criada ou vazia.\n");
			printf("\nTecle ENTER para continuar\n");
			getchar();
			free(vetor1);
			free(vetor2);
			break;
		}
		default: {
			printf("Opcao invalida!!\n");
			break;
		}
		}
	} while (opcao != 11);
	return 0;
}
