/*
 ============================================================================
 Arquivo     : Programação - Prova 02 - Questao 05
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMANDO_LIMPAR_CONSOLE "cls" //Para Windows: "cls" ; Para Linux: "clear"

// Implementacao da arvore de inteiros
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
	no* buscado = buscaArv(raiz, valor), *ant_buscado = buscaAntArv(raiz, valor);
	if (buscado != NULL) {
		if (buscado->esq != NULL) {
			balancoMaior(buscado);
		} else {
			if (buscado->dir != NULL) {
				balancoMenor(buscado);
			} else {
				if (ant_buscado == NULL) {
					printf("Remocao do valor %d realizada com sucesso!\n", valor);
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

// Implementacao da arvore de palavras

struct arv_busca_txt {
	char info[100];
	int vazia;
	int qtd;
	struct arv_busca_txt* esq;
	struct arv_busca_txt* dir;
};
typedef struct arv_busca_txt noh;

noh* criaArvTxt(void) {
	noh* raiz = (noh*) malloc(sizeof(noh));
	raiz->vazia = 1;
	return raiz;
}

noh* buscaArvTxt(noh* raiz, char * valor) {
	noh* percorre = raiz, *ant_percorre = raiz;
	if (raiz->vazia != 1) {
		while ((percorre != NULL) && (strcmp(percorre->info, valor) != 0)) { // fator de ordenacao eh o strcomp
			ant_percorre = percorre;
			if (strcmp(percorre->info, valor) < 0)
				percorre = percorre->dir;
			else {
				if (strcmp(percorre->info, valor) > 0)
					percorre = percorre->esq;
			}
		}
		return percorre;
	}
	return NULL;
}

noh* insereArvTxt(noh* raiz, char * valor) {
	noh* retorno = NULL;
	noh* buscado = buscaArvTxt(raiz, valor);
	if (raiz != NULL) {
		if (buscado == NULL) {
			if (raiz->vazia == 1) {
				strcpy(raiz->info, valor);
				raiz->vazia = 0;
				raiz->qtd = 1;
				raiz->esq = NULL;
				raiz->dir = NULL;
				retorno = raiz;
			} else {
				noh* percorre, * ant_percorre;
				noh* novo = (noh*) malloc(sizeof(noh));
				strcpy(novo->info, valor);
				novo->vazia = 0;
				novo->qtd = 1;
				novo->esq = NULL;
				novo->dir = NULL;
				if (strcmp(raiz->info, valor) < 0)
					percorre = raiz->dir;
				else {
					percorre = raiz->esq;
				}
				ant_percorre = raiz;
				while (percorre != NULL) {
					ant_percorre = percorre;
					if (strcmp(percorre->info, valor) < 0)
						percorre = percorre->dir;
					else {
						if (strcmp(percorre->info, valor) > 0)
							percorre = percorre->esq;
					}
				}
				if (strcmp(ant_percorre->info, valor) < 0)
					ant_percorre->dir = novo;
				else {
					if (strcmp(ant_percorre->info, valor) > 0)
						ant_percorre->esq = novo;
				}
				retorno = novo;
			}
			printf("Valor incluso com sucesso!\n");
		} else
			buscado->qtd = (buscado->qtd) + 1; //incrementa quantidade de vezes que aparece no texto!
	}
	return retorno;
}

void imprimeGenericaTxt(noh* raiz) {
	noh* percorre = raiz;
	if (percorre != NULL) {
		printf("<%s/%d>", percorre->info, percorre->qtd);
		printf("<");
		imprimeGenericaTxt(percorre->esq);
		printf(">");
		printf("<");
		imprimeGenericaTxt(percorre->dir);
		printf(">");
	}
}

// Funcao que retorna quantidade de nos de uma arvore
int contaNos(no* raiz) {
	if (raiz != NULL) {
		return (contaNos(raiz->esq) + contaNos(raiz->dir) + 1);
	}
	return 0;
}

// Funcao que retorna quantidade de folhas de uma arvore
void contaFolhas(no* raiz, int* qtd) {
	if (raiz != NULL) {
		contaFolhas(raiz->esq, qtd);
		if ((raiz->dir == NULL) && (raiz->esq == NULL))
			(*qtd)++;
		contaFolhas(raiz->dir, qtd);
	}
}

// Funcao que espelha um arvore
void espelhaArv(no* raiz, no*aux) {
	if (raiz != NULL) {
		aux = raiz->esq;
		raiz->esq = raiz->dir; // troca de lugares
		raiz->dir = aux;
		espelhaArv(raiz->esq, NULL);
		espelhaArv(raiz->dir, NULL);
	}
}

//////////////// Funcoes usadas para transformar um texto em uma arvore ///////////////////

char* carregaPalavra(char* textoSemEspaco, int i, int f) {
	int controle = 0;
	char* palavra = (char*) calloc(100, sizeof(char));
	while (i < f) {
		palavra[controle] = textoSemEspaco[i];
		i++;
		controle++;
	}
	if (controle == 0) {
		free(palavra); //desaloca palavra
		return NULL; //caso nao seja criada substring
	}
	return palavra;
}

void retiraEspacosExtra(char* t, char* textoSemEspaco) {
	int i = 0, j = 0, copia = 0;
	while (t[i] != '\0') {
		if (copia == 0) { //inapto a copiar
			if (t[i] != ' ') {
				textoSemEspaco[j] = t[i];
				j++;
				copia = 1; // torna apto a copiar
			}
		} else {
			if (t[i] == ' ')
				copia = 0; // copia o espaco e torna inapto ate achar um caractere valido
			textoSemEspaco[j] = t[i];
			j++;
		}
		i++;
	}
	t[i] = '\0';
}

noh* converteStrArv(char* texto) { // retorna raiz da arvore de palavras
	int cont = 0, inicio = 0, fim = 0;
	char* palavra;
	noh* raiz = criaArvTxt();
	char* textoSemEspaco = (char*) calloc(500, sizeof(char));
	retiraEspacosExtra(texto, textoSemEspaco);
	while (textoSemEspaco[cont] != '\0') {
		if (textoSemEspaco[cont] == ' ') {
			fim = cont;
			//inclui em arvore (substring de inicio a fim-1)
			palavra = carregaPalavra(textoSemEspaco, inicio, fim);
			if (palavra != NULL)
				insereArvTxt(raiz, palavra);
			inicio = fim + 1;
		}
		cont++;
	}
	fim = cont;
	// carrega ultima palavra caso haja espaco apos ela.
	palavra = carregaPalavra(textoSemEspaco, inicio, fim);
	if (palavra != NULL)
		insereArvTxt(raiz, palavra);
	return raiz;
}

// Main (Com Menu)
int main() {
	int opcao = 0, valor, qtd;
	no* raiz = NULL, *no;
	do {
		system(COMANDO_LIMPAR_CONSOLE);
		printf("|||||||||| MENU |||||||||| \n");
		printf("(1) Criar Arvore\n");
		printf("(2) Inserir em Arvore\n");
		printf("(3) Remover de Arvore\n");
		printf("(4) Buscar elemento em Arvore\n");
		printf("(5) Imprimir (Pre-Ordem)\n");
		printf("(6) Imprimir (Pos-Ordem)\n");
		printf("(7) Imprimir (Ordem Simetrica)\n");
		printf("(8) Calcular numero de nos\n");
		printf("(9) Calcular numero de folhas\n");
		printf("(10) Espelhar arvore\n");
		printf("(11) Transformar texto em arvore binaria de pesquisa\n");
		printf("(12) Encerrar\n");
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
		case 8: {
			if ((raiz != NULL) && (raiz->vazia != 1)) {
				qtd = contaNos(raiz);
				printf(" * Quantidade de nos: %d", qtd);
			} else
				printf("Arvore Vazia \n");
			printf("\n\nTecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 9: {
			if ((raiz != NULL) && (raiz->vazia != 1)) {
				qtd = 0;
				contaFolhas(raiz, &qtd);
				printf(" * Quantidade de folhas: %d", qtd);
			} else
				printf("Arvore Vazia \n");
			printf("\n\nTecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 10: {
			if ((raiz != NULL) && (raiz->vazia != 1)) {
				espelhaArv(raiz, NULL);
				printf(" * Arvore espelhada!");
			} else
				printf("Arvore Vazia \n");
			printf("\n\nTecle ENTER para continuar\n");
			getchar();
			break;
		}
		case 11: {
			char* texto = (char*) calloc(500, sizeof(char));
			noh* raiz;
			printf("Digite o texto a ser transformado em arvore: ");
			gets(texto);
			raiz = converteStrArv(texto);
			if (raiz->vazia != 1) {
				printf("\nImpressao em Ordem Simetrica:\n\n");
				imprimeGenericaTxt(raiz);
			} else
				printf("Arvore Vazia!\n");
			printf("\n\nTecle ENTER para continuar\n");
			getchar();
			free(texto);
			break;
		}
		}
	} while (opcao != 12);
	return 0;
}
