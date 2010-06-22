/*
 ============================================================================
 Arquivo     : Programação - Lista 03 - Questao 01 (LISTA ESTATICA ORDENADA)
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

//Esta linha define que o tipo da Lista Estatica eh int.
typedef int ListType;

/**Estrutura principal da lista estatica.
 */
typedef struct List {
	ListType** vetor;
	long tamanho;
	long tamanho_maximo;
} List;

//Operacoes:
List* List_Criar(long tamanho_maximo);
short List_Inserir(List* list, ListType valor);
short List_Remover(List* list, ListType valor_remover);
long List_Buscar(List* list, ListType valor_procurado);
void List_Imprimir(List* list);


/**Cria uma nova lista estatica.
 * Retorna a estrutura da lista ou NULL caso tenha ocorrido erro na criacao.
 */
List* List_Criar(long tamanho_maximo) {
	//Aloca a estrutura:
	List *list = (List*)malloc(sizeof(List));
	//Aloca o vetor que armazenara os elementos da lista:
	list->vetor = (ListType**)calloc(tamanho_maximo, sizeof(ListType*));
	list->tamanho = 0;
	list->tamanho_maximo = tamanho_maximo;
    return list;
}

/**Insere um valor na lista estatica.
 * Retorna 1 caso tenha sido inserido com sucesso ou 0 caso contrario.
 */
short List_Inserir(List* list, ListType valor) {
	if (list->tamanho == list->tamanho_maximo) {
		return 0;
	}
	//Procura pela posicao onde deve ser adicionada o elemento:
	long i = 0;
	while (i < list->tamanho && *list->vetor[i] < valor) {
		i++;
	}

	//Desloca os elementos do vetor para liberar espaco para o novo elemento:
	long j;
	for (j = list->tamanho; j > i; j--) {
		list->vetor[j] = list->vetor[j-1];
	}
	int *novo_valor = (int*)malloc(sizeof(int));
	*novo_valor = valor;
	list->vetor[i] = novo_valor;

	list->tamanho++;
	return 1;
}

/**Remove um valor da lista estatica.
 * Retorna 1 caso tenha sido removido com sucesso ou 0 caso contrario.
 */
short List_Remover(List* list, ListType valor_remover) {
	long i;
	long indice_remover = -1;
	for (i = 0; i < list->tamanho; i++) {
		if (*(list->vetor[i]) == valor_remover) {
			indice_remover = i;
			break;
		}
	}

	/**Verifica se o elemento foi encontrado. Se tiver sido encontrado,
	 * desloca os elementos do vetor para preencher o espaco vazio:
	 */
	if (indice_remover != -1) {
		//Desloca os elementos do vetor para preencher o espaco vazio:
		for (i = indice_remover; i < list->tamanho - 1; i++) {
			list->vetor[i] = list->vetor[i+1];
		}
		list->vetor[list->tamanho] = NULL;
		list->tamanho--;
		return 1;
	}
	return 0;
}

/**Busca por um valor na lista estatica. Caso tenha sido encontrado,
 * retorna o indice dele no vetor. Caso contrario, retorna -1;
 */
long List_Buscar(List* list, ListType valor_procurado) {
	long i;
	for (i = 0; i < list->tamanho; i++) {
		if (*(list->vetor[i]) == valor_procurado) {
			return i;
		}
	}
	return -1;
}

/**Exibe todos os elementos da lista estatica em forma de string na tela.
 * Usar somente se o tipo da Lista for numerico: short, int, float, ...
 */
void List_Imprimir(List* list) {
	printf("Lista {");
	long i;
	for (i = 0; i < list->tamanho; i++) {
		printf("%ld", (long)*list->vetor[i]);
		if (i + 1 != list->tamanho) {
			printf(", ");
		}
	}
	printf("}\n");
}

/**
 * FUNCOES PARA TESTE NO MAIN:
 */
int verificaListaCriada(List* lista) {
	if (lista == NULL) {
		printf("Crie a lista antes de utilizar!\n");
	}
	return lista != NULL;
}
int verificaListaCheia(List* lista) {
	if (lista == NULL){
		return 0;
	}
	if (lista->tamanho == lista->tamanho_maximo) {
		printf("Lista cheia!\n");
	}
	return lista->tamanho == lista->tamanho_maximo;
}
int verificaListaVazia(List* lista) {
	if (lista == NULL){
		return 0;
	}
	if (lista->tamanho == 0) {
		printf("Lista vazia!\n");
	}
	return lista->tamanho == 0;
}

int main(void) {
	List *lista = NULL;
	int opcao;
	do {
		printf("\n---Lista Estatica Ordenada---\n");
		printf("\t1-Criar\n");
		printf("\t2-Inserir\n");
		printf("\t3-Remover\n");
		printf("\t4-Buscar\n");
		printf("\t5-Imprimir\n");
		printf("\t0-Sair\n");
		printf("\tDigite a opcao: ");
		scanf("%d", &opcao);
		getchar();
		printf("\n");

		long numero;
		switch (opcao) {
			case 0:
				printf("Programa finalizado!\n");
				break;
			case 1:;
				int tamanho;
				printf("Digite o tamanho da lista a ser criada: ");
				scanf("%d", &tamanho);
				lista = List_Criar(tamanho);
				if (lista != NULL) {
					printf("Lista criada com sucesso.\n");
				}
				break;
			case 2:
				if (!verificaListaCriada(lista) || verificaListaCheia(lista)) {
					break;
				}
				numero = 0;
				printf("Digite o numero a ser inserido: ");
				scanf("%ld", &numero);
				if (List_Inserir(lista, numero) == 0) {
					printf("Erro ao inserir numero.\n");
				} else {
					printf("Numero inserido com sucesso.\n");
				}
				break;
			case 3:
				if (!verificaListaCriada(lista) || verificaListaVazia(lista)) {
					break;
				}
				printf("Digite o numero a ser removido: ");
				scanf("%ld", &numero);
				if (List_Remover(lista, numero) == 0) {
					printf("Numero nao encontrado.\n");
				} else {
					printf("Numero removido com sucesso.\n");
				}
				break;
			case 4:
				if (!verificaListaCriada(lista) || verificaListaVazia(lista)) {
					break;
				}
				printf("Digite o numero a ser procurado: ");
				scanf("%ld", &numero);
				int indice_numero = List_Buscar(lista, numero);
				if (indice_numero == -1) {
					printf("Numero nao encontrado.\n");
				} else {
					printf("Numero encontrado no indice %d do vetor.\n", indice_numero);
				}
				break;
			case 5:
				if (!verificaListaCriada(lista)) {
					break;
				}
				List_Imprimir(lista);
				break;
			default:
				printf("Opcao invalida!\n");
		}
	} while (opcao != 0);

	return 0;
}
