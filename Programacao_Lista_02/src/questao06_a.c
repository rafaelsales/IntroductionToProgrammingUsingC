/*
 ============================================================================
 Arquivo     : Programação - Lista 02 - Questao 06 (LISTA ESTATICA)
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
	list->vetor[list->tamanho] = &valor;
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
	printf("List {");
	long i;
	for (i = 0; i < list->tamanho; i++) {
		printf("%lf", (double)*list->vetor[i]);
		if (i + 1 != list->tamanho) {
			printf(", ");
		}
	}
	printf("}\n");
}


int main(void) {
	List *list = List_Criar(10);
	List_Imprimir(list);

	printf("1, 3, 5 e 8 inseridos.\n");
	List_Inserir(list, 1);
	List_Inserir(list, 3);
	List_Inserir(list, 5);
	List_Inserir(list, 8);
	List_Imprimir(list);

	long indiceValor1 = List_Buscar(list, 1);
	long indiceValor2 = List_Buscar(list, 5);
	long indiceValor3 = List_Buscar(list, 10);
	if (indiceValor1 != -1) {
		printf("Numero 1 esta no indice: %ld \n", indiceValor1);
	} else {
		printf("Numero 1 nao encontrado.\n");
	}
	if (indiceValor2 != -1) {
		printf("Numero 5 esta no indice: %ld \n", indiceValor2);
	} else {
		printf("Numero 5 nao encontrado.\n");
	}
	if (indiceValor3 != -1) {
		printf("Numero 10 esta no indice: %ld \n", indiceValor3);
	} else {
		printf("Numero 10 nao encontrado.\n");
	}

	printf("5 removido.\n");
	List_Remover(list, 5);
	List_Imprimir(list);
	printf("3 removido.\n");
	List_Remover(list, 3);
	List_Imprimir(list);

	printf("3 e 5 inseridos.\n");
	List_Inserir(list, 3);
	List_Inserir(list, 5);
	List_Imprimir(list);

	printf("1, 3, 5 e 8 removidos.\n");
	List_Remover(list, 1);
	List_Remover(list, 3);
	List_Remover(list, 5);
	List_Remover(list, 8);
	List_Imprimir(list);

	getchar();
	return 0;
}
