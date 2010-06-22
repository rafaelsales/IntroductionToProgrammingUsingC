/*
 ============================================================================
 Arquivo     : Programação - Lista 03 - Questao 03
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

//Esta linha define que o tipo da Lista encadeada eh long.
typedef long LinkedListType;

/**Estrutura principal da lista encadeada.
 * A partir dela obtemos o inicio e o fim da lista para itererar pelos seus elementos.
 */
typedef struct LinkedList {
	struct LinkedListNode *primeiro;
	struct LinkedListNode *ultimo;
    long tamanho;
} LinkedList;

//No de um elemento da lista:
typedef struct LinkedListNode {
	LinkedListType *valor;
	struct LinkedListNode *ant; //ponteiro para o elemento anterior.
	struct LinkedListNode *prox; //ponteiro para o proximo elemento.
} LinkedListNode;

//Operacoes:
LinkedList* LinkedList_Criar();
short LinkedList_Inserir(LinkedList *linkedList, LinkedListType *valor);
short LinkedList_Remover(LinkedList *linkedList, LinkedListType valorRemover);
LinkedListNode* LinkedList_Buscar(LinkedList *linkedList, LinkedListType valorProcurado);
void LinkedList_Imprimir(LinkedList *linkedList);


/**Cria uma nova lista encadeada.
 * Retorna a estrutura da lista ou NULL caso tenha ocorrido erro na criacao.
 */
LinkedList* LinkedList_Criar() {
	LinkedList *linkedList = (LinkedList*)malloc(sizeof(LinkedList));
	linkedList->tamanho = 0;
	linkedList->primeiro = NULL;
	linkedList->ultimo = NULL;
    return linkedList;
}

/**Insere um valor na lista encadeada.
 * Retorna 1 caso tenha sido inserido com sucesso ou 0 caso contrario.
 */
short LinkedList_Inserir(LinkedList *linkedList, LinkedListType *valor) {
	LinkedListNode *novoNo = (LinkedListNode*)malloc(sizeof(LinkedListNode));

	if (novoNo != NULL) {
		novoNo->valor = valor;
		novoNo->prox = NULL;
		novoNo->ant = linkedList->ultimo;

		/* Se for o primeiro no adicionado na lista, associa ao primeiro.
		 * Senao, associa como proximo do ultimo elemento antes da insercao.
		 */
		if (linkedList->tamanho == 0) {
			linkedList->primeiro = novoNo;
		} else {
			linkedList->ultimo->prox = novoNo;
		}
		linkedList->ultimo = novoNo;

		linkedList->tamanho++;
	}
	return (novoNo != NULL);
}

/**Remove um valor da lista encadeada.
 * Retorna 1 caso tenha sido removido com sucesso ou 0 caso contrario.
 */
short LinkedList_Remover(LinkedList *linkedList, LinkedListType valorRemover) {
	if (linkedList->tamanho == 0) {
		return 0;
	}
	LinkedListNode *node = linkedList->primeiro;

	short encontrado = 0; //0 = nao encontrado; 1 = encontrado
	while (node != NULL && !encontrado) {
		//Verifica se encontrou o no:
		if (*(node->valor) == valorRemover) {
			encontrado = 1;
		} else {
			node = node->prox;
		}
	}
	//Se o elemento foi encontrado, remove o no da lista fazendo os ajustes necessarios:
	if (encontrado) {
		if (node == linkedList->primeiro) {
			linkedList->primeiro = node->prox;
		} else {
			node->ant->prox = node->prox;
		}
		if (node == linkedList->ultimo) {
			linkedList->ultimo = node->ant;
		} else {
			node->prox->ant = node->ant;
		}

		linkedList->tamanho--;

		free(node);
	}
    return encontrado;
}

/**Busca por um valor na lista encadeada e retorna o valor encontrado ou NULL caso nao tenha sido enconrado.
 */
LinkedListNode* LinkedList_Buscar(LinkedList *linkedList, LinkedListType valorProcurado) {
	LinkedListNode *node = linkedList->primeiro;
	while (node != NULL) {
		//Verifica se encontrou o no:
		if (*(node->valor) == valorProcurado) {
			return node;
		}
		node = node->prox;
	}
	return NULL;
}

/**Exibe todos os elementos da lista encadeada em forma de string na tela.
 * Usar somente se o tipo da Lista for numerico: short, int, float, ...
 */
void LinkedList_Imprimir(LinkedList *linkedList) {
	LinkedListNode *node = linkedList->primeiro;
	printf("LinkedList {");
	while (node != NULL) {
		printf("%ld", (long)*node->valor);
		if (node != linkedList->ultimo) {
			printf(", ");
		}
		node = node->prox;
	}
	printf("}\n");
}

/**
 * FUNCOES PARA TESTE NO MAIN:
 */
int verificaListaCriada(LinkedList* lista) {
	if (lista == NULL) {
		printf("Crie a lista antes de utilizar!\n");
	}
	return lista != NULL;
}

int verificaListaVazia(LinkedList* lista) {
	if (lista == NULL){
		return 0;
	}
	if (lista->tamanho == 0) {
		printf("Lista vazia!\n");
	}
	return lista->tamanho == 0;
}

//TESTE DA LISTA:
int main(void) {

	LinkedList *listaEncadeada = NULL;
	int opcao;
	do {
		printf("\n---Lista Dinamica Ordenada---\n");
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

		long *numero = (long*)malloc(sizeof(int));
		switch (opcao) {
			case 0:
				printf("Programa finalizado!\n");
				break;
			case 1:;
				listaEncadeada = LinkedList_Criar();
				if (listaEncadeada != NULL) {
					printf("Lista criada com sucesso.\n");
				}
				break;
			case 2:
				if (!verificaListaCriada(listaEncadeada)) {
					break;
				}
				printf("Digite o numero a ser inserido: ");
				scanf("%ld", numero);
				if (LinkedList_Inserir(listaEncadeada, numero) == 0) {
					printf("Erro ao inserir numero.\n");
				} else {
					printf("Numero inserido com sucesso.\n");
				}
				break;
			case 3:
				if (!verificaListaCriada(listaEncadeada) || verificaListaVazia(listaEncadeada)) {
					break;
				}
				printf("Digite o numero a ser removido: ");
				scanf("%ld", numero);
				if (LinkedList_Remover(listaEncadeada, *numero) == 0) {
					printf("Numero nao encontrado.\n");
				} else {
					printf("Numero removido com sucesso.\n");
				}
				break;
			case 4:
				if (!verificaListaCriada(listaEncadeada) || verificaListaVazia(listaEncadeada)) {
					break;
				}
				printf("Digite o numero a ser procurado: ");
				scanf("%ld", numero);
				if (LinkedList_Buscar(listaEncadeada, *numero) == NULL) {
					printf("Numero nao encontrado.\n");
				} else {
					printf("Numero encontrado.\n");
				}
				break;
			case 5:
				if (!verificaListaCriada(listaEncadeada)) {
					break;
				}
				LinkedList_Imprimir(listaEncadeada);
				break;
			default:
				printf("Opcao invalida!\n");
		}
	} while (opcao != 0);

	return 0;
}
