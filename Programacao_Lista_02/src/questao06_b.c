/*
 ============================================================================
 Arquivo     : Programação - Lista 02 - Questao 06 (LISTA DINAMICA)
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

//Esta linha define que o tipo da Lista Dinamica eh int.
typedef int LinkedListType;

/**Estrutura principal da lista dinamica.
*  A partir dela obtemos o inicio da lista para itererar pelos seus elementos.
*/
typedef struct LinkedList {
	struct LinkedListNode* primeiro;
    long tamanho;
} LinkedList;

//No de um elemento da lista:
typedef struct LinkedListNode {
	LinkedListType* valor;
	struct LinkedListNode* prox;
} LinkedListNode;

//Operacoes:
LinkedList* LinkedList_Criar();
short LinkedList_Inserir(LinkedList* linkedList, LinkedListType* valor);
short LinkedList_Remover(LinkedList* linkedList, LinkedListType valorRemover);
LinkedListNode* LinkedList_Buscar(LinkedList* linkedList, LinkedListType valorProcurado);
void LinkedList_Imprimir(LinkedList* linkedList);


/**Cria uma nova lista dinamica.
*  Retorna a estrutura da lista ou NULL caso tenha ocorrido erro na criacao.
*/
LinkedList* LinkedList_Criar() {
	LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
	linkedList->tamanho = 0;
	linkedList->primeiro = NULL;
    return linkedList;
}

/**Insere um valor na lista dinamica.
*  Retorna 1 caso tenha sido inserido com sucesso ou 0 caso contrario.
*/
short LinkedList_Inserir(LinkedList* linkedList, LinkedListType* valor) {
	LinkedListNode* novoNo = (LinkedListNode*)malloc(sizeof(LinkedListNode));

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
*  Retorna 1 caso tenha sido removido com sucesso ou 0 caso contrario.
*/
short LinkedList_Remover(LinkedList* linkedList, LinkedListType valorRemover) {
	if (linkedList->tamanho == 0) {
		return 0;
	}
	LinkedListNode* node = linkedList->primeiro;
	LinkedListNode* nodeAnterior = linkedList->primeiro;

	short encontrado = 0;
	while (node != NULL && !encontrado) {
		//Verifica se encontrou o no:
		if (*(node->valor) == valorRemover) {
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

/**Busca por um valor na lista dinamica e retorna o valor encontrado ou NULL caso nao tenha sido enconrado.
*/
LinkedListNode* LinkedList_Buscar(LinkedList* linkedList, LinkedListType valorProcurado) {
	LinkedListNode* node = linkedList->primeiro;
	while (node != NULL) {
		//Verifica se encontrou o no:
		if (*(node->valor) == valorProcurado) {
			return node;
		}
		node = node->prox;
	}
	return NULL;
}

/**Exibe todos os elementos da lista dinamica em forma de string na tela.
*  Usar somente se o tipo da Lista for numerico: short, int, float, ...
*/
void LinkedList_Imprimir(LinkedList* linkedList) {
	LinkedListNode* node = linkedList->primeiro;
	printf("LinkedList {");
	while (node != NULL) {
		printf("%lf", (double)*node->valor);
		if (node->prox != NULL) {
			printf(", ");
		}
		node = node->prox;
	}
	printf("}\n");
}

//TESTE DA LISTA:
int main(void) {
	LinkedList* linkedList = LinkedList_Criar();
	int valor1 = 1, valor2 = 3, valor3 = 5, valor4 = 8;
	LinkedList_Inserir(linkedList, &valor1);
	LinkedList_Imprimir(linkedList);
	LinkedList_Inserir(linkedList, &valor2);
	LinkedList_Imprimir(linkedList);
	LinkedList_Inserir(linkedList, &valor3);
	LinkedList_Imprimir(linkedList);
	LinkedList_Inserir(linkedList, &valor4);
	LinkedList_Imprimir(linkedList);

	//Teste de busca:
	LinkedListNode* noValor1 = LinkedList_Buscar(linkedList, 1);
	LinkedListNode* noValor2 = LinkedList_Buscar(linkedList, 8);
	LinkedListNode* noValor3 = LinkedList_Buscar(linkedList, 10);
	if (noValor1 != NULL) {
		printf("Valor 1: %lf \n", (double)*noValor1->valor);
	} else {
		printf("Valor 1 nao encontrado.\n");
	}
	if (noValor2 != NULL) {
		printf("Valor 2: %lf \n", (double)*noValor2->valor);
	} else {
		printf("Valor 2 nao encontrado.\n");
	}
	if (noValor3 != NULL) {
		printf("Valor 3: %lf \n", (double)*noValor3->valor);
	} else {
		printf("Valor 3 nao encontrado.\n");
	}

	//Testes de remocao e insercao aleatorios:
	LinkedList_Remover(linkedList, 5);
	LinkedList_Imprimir(linkedList);
	LinkedList_Remover(linkedList, 3);
	LinkedList_Imprimir(linkedList);

	LinkedList_Inserir(linkedList, &valor2);
	LinkedList_Inserir(linkedList, &valor3);
	LinkedList_Imprimir(linkedList);

	LinkedList_Remover(linkedList, 5);
	LinkedList_Imprimir(linkedList);
	LinkedList_Remover(linkedList, 3);
	LinkedList_Imprimir(linkedList);
	LinkedList_Remover(linkedList, 8);
	LinkedList_Imprimir(linkedList);
	LinkedList_Inserir(linkedList, &valor3);
	LinkedList_Imprimir(linkedList);
	LinkedList_Remover(linkedList, 1);
	LinkedList_Imprimir(linkedList);
	LinkedList_Remover(linkedList, 5);
	LinkedList_Imprimir(linkedList);

	getchar();
	return 0;
}
