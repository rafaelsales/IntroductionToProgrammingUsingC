/*
 ============================================================================
 Arquivo     : Programação - Lista 05 - Questao 02 (Arvore com número variável de filhos)
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int ORDEM_ARVORE;

typedef struct ArvoreNode {
	int info; //Valor do elemento OU número de elementos do nó.
	struct ArvoreNode* prox; //Ponteiro para o proximo elemento do nó da arvore.
	struct ArvoreNode* filho; //Ponteiro para sub-arvore
	short cabeca; //0 se nao eh o cabeca. 1 se eh o cabeca.
} ArvoreNode;

ArvoreNode* ArvoreMultipla_Criar(int ordemArvore);
void ArvoreMultipla_Inserir(ArvoreNode* raiz, int valor);
short ArvoreMultipla_Remover(ArvoreNode* raiz, int valor);
short ArvoreMultipla_RemoverAuxiliar(ArvoreNode* raiz, int valor);
void ArvoreMultipla_ImprimirPosOrdem(ArvoreNode* raiz);
void ArvoreMultipla_ImprimirOrdemSimetrica(ArvoreNode* raiz);

ArvoreNode* ArvoreMultipla_Criar(int ordemArvore) {
	ArvoreNode* raiz = (ArvoreNode*) malloc(sizeof(ArvoreNode));
	raiz->info = 0;
	raiz->filho = NULL;
	raiz->prox = NULL;
	raiz->cabeca = 1;
	ORDEM_ARVORE = ordemArvore;
	return raiz;
}

void ArvoreMultipla_Inserir(ArvoreNode* raiz, int valor) {
	ArvoreNode* nodePai = raiz;

	while (nodePai->prox != NULL) {
		if (valor > nodePai->info) {
			nodePai = nodePai->prox;
		} else {
			break;
		}
	}

	//Verifica se o nó chegou ao limite:
	if (raiz->info == ORDEM_ARVORE) {
		//Se nao possui sub-arvore, cria uma nova sub-arvore:
		if (raiz->filho == NULL) {
			ArvoreNode* novoElemento = ArvoreMultipla_Criar(ORDEM_ARVORE);
			ArvoreNode* novoCabeca = ArvoreMultipla_Criar(ORDEM_ARVORE); //Elemento cabeca do novo noh.

			novoElemento->info = valor;
			novoElemento->cabeca = 0;

			novoCabeca->info = 1;
			novoCabeca->prox = novoElemento;
			novoCabeca->cabeca = 1;

			nodePai->filho = novoCabeca;
			return;
		} else {//Senao, chama recursivamente para incluir na subarvore de baixo:
			ArvoreMultipla_Inserir(nodePai->filho, valor);
			return;
		}
	} else {//Caso haja espaço no nó:
		ArvoreNode* novoElemento = ArvoreMultipla_Criar(ORDEM_ARVORE);

		novoElemento->info = valor;
		novoElemento->cabeca = 0;

		nodePai->prox = novoElemento;
		raiz->info++; //Incrementa o tamanho do nó.
	}
}

/**Remove um elemento da árvore
 * @Parametro: raiz - Raíz da árvore
 * @Parametro: valor - Valor a ser excluído da árvore
 * @Retorno: 1 caso o valor tenha sido removido; 0 caso o valor não esteja presente na árvore
 */
short ArvoreMultipla_Remover(ArvoreNode* raiz, int valor) {
	short status_remocao = ArvoreMultipla_Remover(raiz, valor);
	//Verifica se o nó filho ficou vazio:
	if (status_remocao == 2) {
		free(raiz->filho);
		raiz->filho = NULL;
		//Coloca status como nó removido com sucesso:
		status_remocao = 1;
	}
	return status_remocao;
}

/**Função utilizada internamente chamada a partir da função ArvoreMultipla_Remover(ArvoreNode* raiz, int valor);
 * @Parametro: raiz - Raíz da árvore
 * @Parametro: valor - Valor a ser excluído da árvore
 * @Retorno: 2 caso o valor tenha sido removido e o nó que possuia o valor ficou vazio
 * sendo então necessário sua remoção da árvore; 1 caso o valor tenha sido removido;
 * 0 caso o valor não esteja presente na árvore
 */
short ArvoreMultipla_Remover_Interno(ArvoreNode* raiz, int valor) {
	ArvoreNode* node = raiz;
	ArvoreNode* nodeAnterior = NULL;

	/* Procura pelo nó anterior ao nó a ser excluído ou pelo nó
	 * pai da sub-árvore que possivelmente possui o nó a ser excluído.
	 */
	while (node->prox != NULL) {
		if (valor > node->info || node->cabeca == 1) {
			nodeAnterior = node;
			node = node->prox;
		} else {
			break;
		}
	}

	//Verifica se encontrou o valor a ser excluido:
	if (node->info == valor) {
		//Ajusta os ponteiros retirando o nó excluído:
		nodeAnterior->prox = node->prox;
		free(node);
		//Decrementa o tamanho do nó:
		raiz->info--;
		//Verifica se o nó ficou vazio:
		if (raiz->info == 0) {
			return 2; //Retorno 2 significa que quem chamou deve remover o nó vazio.
		}
		return 1;
	}
	if (node->filho != NULL) {
		short status_remocao = ArvoreMultipla_Remover(node->filho, valor);
		//Verifica se o nó filho ficou vazio:
		if (status_remocao == 2) {
			free(node->filho);
			raiz->filho = NULL;
			//Coloca status como nó removido com sucesso:
			status_remocao = 1;
		}
		return status_remocao;
	}
	return 0;
}

void ArvoreMultipla_ImprimirPosOrdem(ArvoreNode* raiz) {
	ArvoreNode* node = raiz;
	if (node != NULL) {
		printf("< ");
		//Imprime os nós filhos do nó cabeça:
		ArvoreMultipla_ImprimirPosOrdem(node->filho);
		node = node->prox;
		while (node != NULL) {
			ArvoreMultipla_ImprimirPosOrdem(node->filho);
			printf("%d ", node->info);
		}
		printf(">");
	}
}

void ArvoreMultipla_ImprimirOrdemSimetrica(ArvoreNode* raiz) {
	ArvoreNode* node = raiz;
	if (node != NULL) {
		printf("< ");
		//Imprime os nós filhos do nó cabeça:
		ArvoreMultipla_ImprimirOrdemSimetrica(node->filho);
		node = node->prox;
		while (node != NULL) {
			printf("%d ", node->info);
			ArvoreMultipla_ImprimirOrdemSimetrica(node->filho);
		}
		printf(">");
	}
}

int main(void) {

	return 0;
}
