/*
 ============================================================================
 Arquivo     : Programação - Lista 02 - Questao 04
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// Declaracao de novos tipo (para implentacao da lista)
struct palavra {
	char port[20];
	char ing[20];
};

typedef struct palavra Palavra;

struct lista {
	Palavra info;
	struct lista* prox;
};
typedef struct lista Lista;

// Declaracao de funcoes (inclusive implementacao da lista)

Lista* criaLista();
void inserePalavra(Lista* inicio);
void removePalavra(Lista* inicio);
int diferente(char x[20], char y[20]);
Lista* buscaPalavra(Lista* inicio, char word[20]);
void consultaPalavra(Lista* inicio);

// Funcao que cria lista
Lista* criaLista() {
	Lista* inicio = (Lista *) malloc(sizeof(Lista));
	inicio->prox = NULL;
	return inicio;
}

// Funcao que compara strings (retorna 0 se iguais e 1 se diferentes)
int diferente(char x[20], char y[20]) {
	int i = 0;
	while ((x[i] == y[i]) && (x[i] != '\0') && (y[i] != '\0')) {
		i++;
	}
	if (x[i] == y[i])
		return 0;
	else
		return 1;
}

// Funcao que busca uma dada palavra na lista
// Funcao retorna o ponteiro para o elemento anterior ao buscado
Lista* buscaPalavra(Lista* inicio, char word[20]) {
	Lista* ant_buscada;
	if (inicio->prox == NULL)
		return NULL;
	else {
		ant_buscada = inicio;
		while ((diferente(ant_buscada->prox->info.port, word)) &&
				(ant_buscada->prox->prox != NULL)) {
			ant_buscada = ant_buscada->prox;
		}
		if (diferente(ant_buscada->prox->info.port, word))
			return NULL;
		else
			return ant_buscada;
	}
}

// Funcao que encontra e imprime a traducao de uma dada palavra, caso ela esteja cadastrada no dicionario
void consultaPalavra(Lista* inicio) {
	char word[20];
	Lista* ant_buscada;
	printf("Digite a palavra a ser traduzida para ingles: ");
	scanf("%s", word);
	ant_buscada = buscaPalavra(inicio, word);
	if (ant_buscada != NULL) {
		printf("=> Traducao: %s\n", ant_buscada->prox->info.ing);
	} else
		printf(" ** Palavra nao cadastrada **\n");
}

// Implementacao da inclusao na lista
void inserePalavra(Lista* inicio) {
	Lista* novo = (Lista *) malloc(sizeof(Lista));
	if (novo != NULL) {
		printf(" ** Palavra em portugues: ");
		scanf("%s", novo->info.port);
		printf(" ** Palavra em ingles: ");
		scanf("%s", novo->info.ing);
		novo->prox = inicio->prox;
		inicio->prox = novo;
	} else
		printf("Erro na insercao");
}

// Implementacao da remocao da lista
void removePalavra(Lista* inicio) {
	char word[20];
	Lista* buscada;
	Lista* ant_buscada;
	if (inicio->prox == NULL)
		printf("Nao ha palavras a serem removidas\n");
	else {
		printf("Digite a palavra a ser removida(Portugues): ");
		scanf("%s", word);
		ant_buscada = buscaPalavra(inicio, word);
		if (ant_buscada == NULL)
			printf("Palavra nao cadastrada");
		else {
			buscada = ant_buscada->prox;
			ant_buscada->prox = buscada->prox;
			free(buscada);
		}
	}
}

// Main do Programa
int main(void) {
	Lista* inicio = criaLista();
	int opcao, controle;
	do {
		printf(" -> Para inserir nova palavra, digite 1\n -> Para remover palavra, digite 2\n -> Para fazer consulta, digite 3\n");
		scanf("%d", &opcao);
		switch (opcao) {
			case 1:
				inserePalavra(inicio);
				break;
			case 2:
				removePalavra(inicio);
				break;
			case 3:
				consultaPalavra(inicio);
				break;
			default:
				printf(" ** Opcao invalida!\n\n");
		}
		printf("\n -> Digite 1 para continuar e 0 para sair: ");
		scanf("%d", &controle);
		printf("\n");
	} while (controle == 1);
	return 0;
}
