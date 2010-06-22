/*
 ============================================================================
 Arquivo     : Programa��o - Lista 05 - Questao 02 (Arvore com n�mero vari�vel de filhos)
 Equipe      : Lucas Assun��o e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int ORDEM_ARVORE;

typedef struct ArvoreNode {
	int info; //Valor do elemento OU n�mero de elementos do n�.
	struct ArvoreNode* prox; //Ponteiro para o proximo elemento do n� da arvore.
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

	//Verifica se o n� chegou ao limite:
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
	} else {//Caso haja espa�o no n�:
		ArvoreNode* novoElemento = ArvoreMultipla_Criar(ORDEM_ARVORE);

		novoElemento->info = valor;
		novoElemento->cabeca = 0;

		nodePai->prox = novoElemento;
		raiz->info++; //Incrementa o tamanho do n�.
	}
}

/**Remove um elemento da �rvore
 * @Parametro: raiz - Ra�z da �rvore
 * @Parametro: valor - Valor a ser exclu�do da �rvore
 * @Retorno: 1 caso o valor tenha sido removido; 0 caso o valor n�o esteja presente na �rvore
 */
short ArvoreMultipla_Remover(ArvoreNode* raiz, int valor) {
	short status_remocao = ArvoreMultipla_Remover(raiz, valor);
	//Verifica se o n� filho ficou vazio:
	if (status_remocao == 2) {
		free(raiz->filho);
		raiz->filho = NULL;
		//Coloca status como n� removido com sucesso:
		status_remocao = 1;
	}
	return status_remocao;
}

/**Fun��o utilizada internamente chamada a partir da fun��o ArvoreMultipla_Remover(ArvoreNode* raiz, int valor);
 * @Parametro: raiz - Ra�z da �rvore
 * @Parametro: valor - Valor a ser exclu�do da �rvore
 * @Retorno: 2 caso o valor tenha sido removido e o n� que possuia o valor ficou vazio
 * sendo ent�o necess�rio sua remo��o da �rvore; 1 caso o valor tenha sido removido;
 * 0 caso o valor n�o esteja presente na �rvore
 */
short ArvoreMultipla_Remover_Interno(ArvoreNode* raiz, int valor) {
	ArvoreNode* node = raiz;
	ArvoreNode* nodeAnterior = NULL;

	/* Procura pelo n� anterior ao n� a ser exclu�do ou pelo n�
	 * pai da sub-�rvore que possivelmente possui o n� a ser exclu�do.
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
		//Ajusta os ponteiros retirando o n� exclu�do:
		nodeAnterior->prox = node->prox;
		free(node);
		//Decrementa o tamanho do n�:
		raiz->info--;
		//Verifica se o n� ficou vazio:
		if (raiz->info == 0) {
			return 2; //Retorno 2 significa que quem chamou deve remover o n� vazio.
		}
		return 1;
	}
	if (node->filho != NULL) {
		short status_remocao = ArvoreMultipla_Remover(node->filho, valor);
		//Verifica se o n� filho ficou vazio:
		if (status_remocao == 2) {
			free(node->filho);
			raiz->filho = NULL;
			//Coloca status como n� removido com sucesso:
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
		//Imprime os n�s filhos do n� cabe�a:
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
		//Imprime os n�s filhos do n� cabe�a:
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
