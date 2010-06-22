/*
 ============================================================================
 Arquivo     : Programação - Lista 02 - Questao 03
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AUTORES 5
#define MAX_PALAVRAS_CHAVE 3
#define TAM_STRING_GRANDE 255
#define TAM_STRING_MEDIA 100
#define TAM_ISBN 13

//DEFINE O TIPO Livro:
typedef struct {
	char titulo[TAM_STRING_GRANDE];
	char autores[MAX_AUTORES][TAM_STRING_MEDIA];
	int num_autores;
	char editora[TAM_STRING_MEDIA];
	char isbn[TAM_ISBN];
	int paginas;
	int edicao;
	char palavras_chave[MAX_PALAVRAS_CHAVE][TAM_STRING_MEDIA];
	int num_palavras_chave;
	int ano;
	char area[TAM_STRING_MEDIA];
	int total_exemplares;
	int total_disponiveis;
} Livro;


//Esta linha define que o Tipo da Lista Dinamica eh Livro.
typedef Livro LinkedListType;

/**Estrutura principal da lista dinamica.
 * A partir dela obtemos o inicio e o fim da lista para itererar pelos seus elementos.
 */
typedef struct LinkedList {
	struct LinkedListNode *primeiro; //Ponteiro para o primeiro elemento da lista.
	struct LinkedListNode *ultimo; //Ponteiro para o ultimo elemento da lista.
    long tamanho; //Quantidade de elementos presentes na lista.
} LinkedList;

//No de um elemento da lista:
typedef struct LinkedListNode {
	LinkedListType *valor; //Ponteiro para o valor do no.
    struct LinkedListNode *prox; //Ponteiro para o proximo no da lista.
} LinkedListNode;


//Funcoes relacionados a Lista dinamica de livros:
LinkedList* LinkedList_Criar();
short LinkedList_Inserir(LinkedList* linkedList, LinkedListType *valor);
short LinkedList_Remover(LinkedList* linkedList, LinkedListType *valor_remover);

//Funcoes da biblioteca:
void cadastrarLivro(LinkedList* livros);
void removerLivro(LinkedList* livros, char isbn_remover[]);
void atualizarLivro(LinkedList* livros, char isbn_atualizar[]);
void procurarLivro(LinkedList* livros);
void listarLivros(LinkedList* livros);
Livro* procurarLivroPorISBN(LinkedList* livros, char isbn_procurado[]);
char* gerarStringAutores(Livro* livro);
char* gerarStringPalavrasChave(Livro* livro);
void lerNomesAutores(Livro *livro);
void lerPalavrasChave(Livro *livro);


int main(void) {
	LinkedList* livros = LinkedList_Criar();
	int opcao;

	//Exibe o MENU enquanto o usuario nao escolher a opcao SAIR:
	do {
		printf("\n--- CONTROLE DE LIVROS ---\n");
		printf("\t1 - Cadastrar\n");
		printf("\t2 - Remover\n");
		printf("\t3 - Atualizar\n");
		printf("\t4 - Procurar\n");
		printf("\t0 - Sair\n");
		printf("--- STATUS: %ld livros cadastrados ---\n", livros->tamanho);
		//Le a opcao escolhida pelo usuario
		printf("OPCAO: ");
		scanf("%d", &opcao);
		getchar();
		printf("\n");

		switch (opcao) {
			case 0://Sair
				printf("Programa finalizado!\n");
				break;
			case 1://Cadastrar
				printf("\n[FORMULARIO DE CADASTRO]\n");
				cadastrarLivro(livros);
				break;
			case 2://Remover
				if (livros->tamanho > 0) {
					printf("\n[REMOVER LIVRO]\n");
					//Exibe os livros, solicita o ISBN e remove:
					listarLivros(livros);
					char isbn_remover[TAM_ISBN];
					printf("\nDigite o ISBN do livro a ser removido: ");
					gets(isbn_remover);
					removerLivro(livros, isbn_remover);
				} else {
					printf("[ALERTA] NENHUM LIVRO NA BIBLIOTECA.\n");
				}
				break;
			case 3://Atualizar
				if (livros->tamanho > 0) {
					printf("\n[ATUALIZAR LIVRO]\n");
					//Exibe os livros, solicita o ISBN e inicia o formulario de atualizacao:
					listarLivros(livros);
					char isbn_atualizar[TAM_ISBN];
					printf("\nDigite o ISBN do livro a ser atualizado: ");
					gets(isbn_atualizar);
					atualizarLivro(livros, isbn_atualizar);
				} else {
					printf("[ALERTA] NENHUM LIVRO NA BIBLIOTECA.\n");
				}
				break;
			case 4://Procurar
				if (livros->tamanho > 0) {
					printf("\n[PROCURAR LIVRO]\n");
					procurarLivro(livros);
				} else {
					printf("[ALERTA] NENHUM LIVRO NA BIBLIOTECA.\n");
				}
				break;
			default:
				printf("Opcao invalida!\n");
		}

	} while (opcao != 0);

	return 0;
}

/**
 * Solicita os dados do livro ao usuario para cadastramento.
 */
void cadastrarLivro(LinkedList* livros){
	Livro* livro = (Livro*)malloc(sizeof(Livro));
	//Solicita o preenchimento dos campos ao usuario:
	printf("TITULO: ");
	gets(livro->titulo);

	lerNomesAutores(livro);

	printf("EDITORA: ");
	gets(livro->editora);

	printf("ISBN: ");
	gets(livro->isbn);

	printf("NUMERO DE PAGINAS: ");
	scanf("%d", &livro->paginas);

	printf("EDICAO: ");
	scanf("%d", &livro->edicao);

	lerPalavrasChave(livro);

	printf("ANO: ");
	scanf("%d", &livro->ano);
	getchar();

	printf("AREA (HUMANAS, EXATAS OU CIENCIAS): ");
	gets(livro->area);

	printf("TOTAL DE EXEMPLARES: ");
	scanf("%d", &livro->total_exemplares);

	printf("TOTAL DE EXEMPLARES DISPONIVEIS: ");
	scanf("%d", &livro->total_disponiveis);
	getchar();

	LinkedList_Inserir(livros, livro);
	printf("[INFO] LIVRO CADASTRADO COM SUCESSO.\n");
}

/**
 * Remove um livro dado seu ISBN.
 */
void removerLivro(LinkedList* livros, char isbn_remover[]) {
	Livro* livro = procurarLivroPorISBN(livros, isbn_remover);

	if (livro == NULL) {
		printf("[INFO] LIVRO NAO ENCONTRADO.\n");
		return;
	}

	LinkedList_Remover(livros, livro);
	printf("[INFO] LIVRO REMOVIDO COM SUCESSO.\n");
}

/**
 * Atualiza um livro dado seus ISBN.
 */
void atualizarLivro(LinkedList* livros, char isbn_atualizar[]){
	Livro* livro = procurarLivroPorISBN(livros, isbn_atualizar);

	if (livro == NULL) {
		printf("[INFO] LIVRO NAO ENCONTRADO.\n");
		return;
	}

	int opcao;
	do {
		printf("\n--- ATRIBUTOS DO LIVRO PARA ATUALIZACAO ---\n");
		printf("\t1 - TITULO (%s)\n", livro->titulo);
		printf("\t2 - AUTOR(ES) (%s)\n", gerarStringAutores(livro));
		printf("\t3 - EDITORA (%s)\n", livro->editora);
		printf("\t4 - ISBN (%s)\n", livro->isbn);
		printf("\t5 - NUMERO DE PAGINAS (%d)\n", livro->paginas);
		printf("\t6 - EDICAO (%d)\n", livro->edicao);
		printf("\t7 - PALAVRA(S)-CHAVE (%s)\n", gerarStringPalavrasChave(livro));
		printf("\t8 - ANO (%d)\n", livro->ano);
		printf("\t9 - AREA (%s)\n", livro->area);
		printf("\t10 - TOTAL DE EXEMPLARES (%d)\n", livro->total_exemplares);
		printf("\t11 - TOTAL DE EXEMPLARES DISPONIVEIS (%d)\n", livro->total_disponiveis);
		printf("\t0 - FINALIZAR ATUALIZACAO\n");

		//Le a opcao escolhida pelo usuario
		printf("\tOPCAO: ");
		scanf("%d", &opcao);
		getchar();
		printf("\n");

		switch (opcao) {
			case 1:
				printf("\tTITULO: ");
				gets(livro->titulo);
				break;
			case 2:
				lerNomesAutores(livro);
				break;
			case 3:
				printf("\tEDITORA: ");
				gets(livro->editora);
				break;
			case 4:
				printf("\tISBN: ");
				gets(livro->isbn);
				break;
			case 5:
				printf("\tNUMERO DE PAGINAS: ");
				scanf("%d", &livro->paginas);
				getchar();
				break;
			case 6:
				printf("\tEDICAO: ");
				scanf("%d", &livro->edicao);
				getchar();
				break;
			case 7:
				lerPalavrasChave(livro);
				break;
			case 8:
				printf("\tANO: ");
				scanf("%d", &livro->ano);
				getchar();
				break;
			case 9:
				printf("\tAREA (HUMANAS, EXATAS OU CIENCIAS): ");
				gets(livro->area);
				break;
			case 10:
				printf("\tTOTAL DE EXEMPLARES: ");
				scanf("%d", &livro->total_exemplares);
				getchar();
				break;
			case 11:
				printf("\tTOTAL DE EXEMPLARES DISPONIVEIS: ");
				scanf("%d", &livro->total_disponiveis);
				getchar();
				break;
			case 0:
				break;
		}
	} while (opcao != 0);
	printf("[INFO] LIVRO ATUALIZADO COM SUCESSO.\n");
}

/**
 * Procura um livro pelos filtros preenchidos pelo usuario:
 * Titulo, Autor e Palavra-chave.
 */
void procurarLivro(LinkedList* livros){
	char titulo[TAM_STRING_GRANDE];
	char autor[TAM_STRING_MEDIA];
	char palavra_chave[TAM_STRING_MEDIA];

	printf("[INFO] PREENCHA OS CAMPOS PARA FILTRAR A PESQUISA (NAO E NECESSARIO PREENCHER TODOS).\n");
	printf("TITULO: ");
	gets(titulo);
	printf("AUTOR: ");
	gets(autor);
	printf("PALAVRA-CHAVE: ");
	gets(palavra_chave);

	printf("LIVROS ENCONTRADOS:\n");

	LinkedListNode* node = livros->primeiro;
	long i;
	int j;
	int num_livros_encontrados = 0;
	//Variaveis booleanas para verificar se a busca encontrou por titulo, autor e palavra-chave:
	short titulo_encontrado;
	short autor_encontrado;
	short palavra_chave_encontrada;

	for (i = 1; i <= livros->tamanho; i++) {
		Livro* livro = node->valor;

		titulo_encontrado = 0;
		autor_encontrado = 0;
		palavra_chave_encontrada = 0;

		//Verifica se o livro como titulo, o procurado:
		if (strlen(titulo) == 0 || strcmp(livro->titulo, titulo) == 0) {
			titulo_encontrado = 1;
		}
		//Verifica se o livro como autor, o procurado:
		if (strlen(autor) == 0) {
			autor_encontrado = 1;
		} else {
			for (j = 0; j < livro->num_autores; j++) {
				if (strcmp(autor, livro->autores[j]) == 0) {
					autor_encontrado = 1;
					break;
				}
			}
		}
		//Verifica se o livro como palavra-chave, a procurada:
		if (strlen(palavra_chave) == 0) {
			palavra_chave_encontrada = 1;
		} else {
			for (j = 0; j < livro->num_palavras_chave; j++) {
				if (strcmp(palavra_chave, livro->palavras_chave[j]) == 0) {
					palavra_chave_encontrada = 1;
					break;
				}
			}
		}

		//Se encontrou o livro com os dados do filtro, exibe ISBN, Titulo e Autores:
		if (titulo_encontrado == 1 && autor_encontrado == 1 && palavra_chave_encontrada == 1) {
			printf("\tTITULO: %s\n", livro->titulo);
			printf("\tAUTOR(ES): %s\n", gerarStringAutores(livro));
			printf("\tEDITORA: %s\n", livro->editora);
			printf("\tISBN: %s\t", livro->isbn);
			printf("\tNUMERO DE PAGINAS: %d\t", livro->paginas);
			printf("\tEDICAO: %d\n", livro->edicao);
			printf("\tPALAVRA(S)-CHAVE: %s\n", gerarStringPalavrasChave(livro));
			printf("\tANO: %d\t", livro->ano);
			printf("\tAREA: %s\n", livro->area);
			printf("\tTOTAL DE EXEMPLARES: %d\t", livro->total_exemplares);
			printf("\tTOTAL DE EXEMPLARES DISPONIVEIS: %d\n\n", livro->total_disponiveis);
			num_livros_encontrados++;
		}
		//Passa para o proximo Livro da lista:
		node = node->prox;
	}
	if (num_livros_encontrados == 0) {
		printf("[INFO] NENHUM LIVRO ENCONTRADO!");
	} else {
		printf("[INFO] NUMERO DE LIVROS ENCONTRADOS: %d\n", num_livros_encontrados);
	}
}

/**
 * Lista todos os livros
 */
void listarLivros(LinkedList* livros) {
	printf("\t[LISTANDO TODOS OS LIVROS]\n");
	printf("\tISBN - TITULO - AUTORES\n");

	LinkedListNode* node = livros->primeiro;
	long i;
	for (i = 1; i <= livros->tamanho; i++) {
		char *nomes_autores = gerarStringAutores(node->valor);
		//Exibe ISBN, Titulo e Autores:
		printf("\t%s - %s - %s \n", node->valor->isbn , node->valor->titulo, nomes_autores);
		//Passa para o proximo Livro da lista:
		node = node->prox;
	}
}

/**
 * Procura um livro dado seu ISBN.
 * Caso o livro seja encontrado retorna um ponteiro para o Livro.
 * Caso contrario, retorna NULL.
 */
Livro* procurarLivroPorISBN(LinkedList* livros, char isbn_procurado[]) {
	LinkedListNode* node = livros->primeiro;
	long i;
	for (i = 1; i <= livros->tamanho; i++) {
		//Verifica se o ISBN eh o procurado:
		if (strcmp(node->valor->isbn, isbn_procurado) == 0) {
			//Retorna o livro:
			return node->valor;
		}
		//Passa para o proximo Livro da lista:
		node = node->prox;
	}

	return NULL;
}


/**
 * Gera uma string contendo o nome dos autores do
 * livro separados por virgula.
 */
char* gerarStringAutores(Livro* livro) {
	//Aloca espaco para String contendo o nome dos autores separados por ,:
	char *nomes_autores = (char*)calloc(livro->num_autores, TAM_STRING_MEDIA + 8);
	int j;
	for (j = 0; j < livro->num_autores; j++) {
		//Concatena o nome do autor:
		strcat(nomes_autores, livro->autores[j]);
		//Se nao for o ultimo autor, adiciona a virgula:
		if (j < livro->num_autores - 1) {
			strcat(nomes_autores, ", ");
		}
	}
	return nomes_autores;
}

/**
 * Gera uma string contendo o nome das palavras-chave do
 * livro separadas por virgula.
 */
char* gerarStringPalavrasChave(Livro* livro) {
	//Aloca espaco para String contendo o nome das palavras-chave separados por ,:
	char *palavras_chaves = (char*)calloc(livro->num_palavras_chave, TAM_STRING_MEDIA + 6);
	int j;
	for (j = 0; j < livro->num_palavras_chave; j++) {
		//Concatena o nome da palavra-chave:
		strcat(palavras_chaves, livro->palavras_chave[j]);
		//Se nao for a ultima palavra-chave, adiciona a virgula:
		if (j < livro->num_palavras_chave - 1) {
			strcat(palavras_chaves, ", ");
		}
	}
	return palavras_chaves;
}

/**
 * Le ate 5 autores e os adiciona ao livro.
 */
void lerNomesAutores(Livro* livro) {
	int i = 0;
	do {
		printf("\tDigite a quantidade de autores a ser lida (maximo %d): ", MAX_AUTORES);
		scanf("%d", &livro->num_autores);
	} while (livro->num_autores > MAX_AUTORES);
	getchar();

	for (i = 0; i < livro->num_autores; i++) {
		printf("\tDigite o nome do autor No. %d: ", i+1);
		gets(livro->autores[i]);
	}
}

/**
 * Le ate 3 palavras-chave e as adiciona ao livro.
 */
void lerPalavrasChave(Livro *livro) {
	int i = 0;
	do {
		printf("\tDigite a quantidade de palavras-chave a ser lida (maximo %d): ", MAX_PALAVRAS_CHAVE);
		scanf("%d", &livro->num_palavras_chave);
	} while (livro->num_palavras_chave > MAX_PALAVRAS_CHAVE);
	getchar();

	for (i = 0; i < livro->num_palavras_chave; i++) {
		printf("\tDigite a palavras-chave No. %d: ", i+1);
		gets(livro->palavras_chave[i]);
	}
}


/**
 * FUNCOES DA LISTA DINAMICA:
 */

/**Cria uma nova lista dinamica.
 * Retorna a estrutura da lista ou NULL caso tenha ocorrido erro na criacao.
 */
LinkedList* LinkedList_Criar() {
	LinkedList *linkedList = (LinkedList*)malloc(sizeof(LinkedList));
	linkedList->tamanho = 0;
	linkedList->primeiro = NULL;
    return linkedList;
}

/**Insere um valor na lista dinamica.
 * Retorna 1 caso tenha sido inserido com sucesso ou 0 caso contrario.
 */
short LinkedList_Inserir(LinkedList *linkedList, LinkedListType *valor) {
	LinkedListNode *novoNo = (LinkedListNode*)malloc(sizeof(LinkedListNode));

	if (novoNo != NULL) {
		novoNo->valor = valor;
		novoNo->prox = NULL;

		//Associa o primeiro no como o proximo do novo no.
		if (linkedList->tamanho > 0) {
			novoNo->prox = linkedList->primeiro;
		}
		//O primeiro da lista passa a ser o novo no inserido:
		linkedList->primeiro = novoNo;

		linkedList->tamanho++;
	}
	return (novoNo != NULL);
}

/**Remove um valor da lista dinamica.
 * Retorna 1 caso tenha sido removido com sucesso ou 0 caso contrario.
 */
short LinkedList_Remover(LinkedList* linkedList, LinkedListType* valorRemover) {
	if (linkedList->tamanho == 0) {
		return 0;
	}
	LinkedListNode *node = linkedList->primeiro;
	LinkedListNode *nodeAnterior = linkedList->primeiro;

	short encontrado = 0;
	while (node != NULL && !encontrado) {
		//Verifica se encontrou o no:
		if (node->valor == valorRemover) {
			encontrado = 1;
		} else {
			nodeAnterior = node;
			node = node->prox;
		}
	}

	if (encontrado) {
		if (node == linkedList->primeiro) {
			linkedList->primeiro = node->prox;
		} else {
			nodeAnterior->prox = node->prox;
		}
		linkedList->tamanho--;
		free(node);
	}
    return encontrado;
}
