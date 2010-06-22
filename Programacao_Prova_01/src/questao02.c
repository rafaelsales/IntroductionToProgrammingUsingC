/*
 ============================================================================
 Arquivo     : Programação - Prova 01 - Questao 02
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**Estrutura principal da lista dinamica.
*  A partir dela obtemos o inicio da lista para itererar pelos seus elementos.
*/
typedef struct Lista_Encadeada {
	struct Lista_Encadeada_Node* primeiro;
} Lista_Encadeada;

//No de um elemento da lista:
typedef struct Lista_Encadeada_Node {
	char info[255];
	struct Lista_Encadeada_Node* prox;
} Lista_Encadeada_Node;

void descobrirSoldado(Lista_Encadeada* lista, char* nome_soldado_inicio, int numero_contagens);

//Operacoes da lista:
Lista_Encadeada* ListaEncadeada_Criar();
short ListaEncadeada_Inserir(Lista_Encadeada* listaEncadeada, char* valor_inserir);
short ListaEncadeada_Remover(Lista_Encadeada* listaEncadeada, char* valor_remover);
Lista_Encadeada_Node* ListaEncadeada_Buscar(Lista_Encadeada* listaEncadeada, char* valor_procurado);
void ListaEncadeada_Imprimir(Lista_Encadeada* listaEncadeada);


/**Cria uma nova lista dinamica.
 * @Retorno: a estrutura da lista ou NULL caso tenha ocorrido erro na criacao.
 */
Lista_Encadeada* ListaEncadeada_Criar() {
	Lista_Encadeada* ListaEncadeada = (Lista_Encadeada*)malloc(sizeof(Lista_Encadeada));
	ListaEncadeada->primeiro = NULL;
    return ListaEncadeada;
}

/**Insere um valor na lista dinamica.
 * @Retorno: 1 caso tenha sido inserido com sucesso ou 0 caso contrario.
 */
short ListaEncadeada_Inserir(Lista_Encadeada* listaEncadeada, char* valor_inserir) {
	Lista_Encadeada_Node* novoNo = (Lista_Encadeada_Node*)malloc(sizeof(Lista_Encadeada_Node));
	Lista_Encadeada_Node* ultimoNo;

	if (novoNo != NULL) {
		strcpy(novoNo->info, valor_inserir);
		novoNo->prox = NULL;

		//Se a lista for vazia, o noh inserido passa a ser o novo noh:
		if (listaEncadeada->primeiro == NULL) {
			listaEncadeada->primeiro = novoNo;
		} else {
			//Se a lista nao eh vazia, percorre ate o ultimo elemento da lista:
			ultimoNo = listaEncadeada->primeiro;
			while (ultimoNo->prox != NULL) {
				ultimoNo = ultimoNo->prox;
			}
			//O novo noh passa a ser o ultimo da lista:
			ultimoNo->prox = novoNo;
		}

	}
	return (novoNo != NULL);
}

/**Remove um valor da lista dinamica.
 * @Retorno: 1 caso tenha sido removido com sucesso ou 0 caso contrario.
 */
short ListaEncadeada_Remover(Lista_Encadeada* listaEncadeada, char* valor_remover) {
	if (listaEncadeada->primeiro == NULL) {
		return 0;
	}
	Lista_Encadeada_Node* node = listaEncadeada->primeiro;
	Lista_Encadeada_Node* nodeAnterior = listaEncadeada->primeiro;

	short encontrado = 0;
	while (node != NULL && !encontrado) {
		//Verifica se encontrou o noh:
		if (strcmp(node->info, valor_remover) == 0) {
			encontrado = 1;
		} else {
			nodeAnterior = node;
			node = node->prox;
		}
	}

	if (encontrado) {
		if (node == listaEncadeada->primeiro) {
			listaEncadeada->primeiro = node->prox;
		} else {
			nodeAnterior->prox = node->prox;
		}
		free(node);
	}
    return encontrado;
}

/**Busca por um valor na lista dinamica e retorna o noh encontrado ou NULL caso nao tenha sido enconrado.
*/
Lista_Encadeada_Node* ListaEncadeada_Buscar(Lista_Encadeada* listaEncadeada, char* valor_procurado) {
	Lista_Encadeada_Node* node = listaEncadeada->primeiro;
	while (node != NULL) {
		//Verifica se encontrou o no:
		if (strcmp(node->info, valor_procurado) == 0) {
			return node;
		}
		node = node->prox;
	}
	return NULL;
}

/**Exibe todos os elementos da lista dinamica em forma de string na tela.
 */
void ListaEncadeada_Imprimir(Lista_Encadeada* listaEncadeada) {
	Lista_Encadeada_Node* node = listaEncadeada->primeiro;
	printf("Lista {");
	while (node != NULL) {
		printf("%s", node->info);
		if (node->prox != NULL) {
			printf(", ");
		}
		node = node->prox;
	}
	printf("}\n");
}

/**Procura o soldado que escapara segundo o problema de Josephus.
 * @Parametro: lista - Lista com os soldados. Para resolver o problema, considera-se que o
 * primeiro soldado da lista estah do lado do ultimo soldado da lista, representando um circulo.
 * @Parametro: nome_soldado_inicio - Nome do soldado que estah na lista e que sera usado
 * para iniciar a primeira contagem.
 * @Parametro: numero_contagens - Numero que soldados que serao contados para decidir
 * qual o proximo soldado sera removido do circulo.
 */
void descobrirSoldado(Lista_Encadeada* lista, char* nome_soldado_inicio, int numero_contagens) {
	Lista_Encadeada_Node* node;
	Lista_Encadeada_Node* nodeAtual;
	int contador;

	node = ListaEncadeada_Buscar(lista, nome_soldado_inicio);
	//Verifica se o soldado de inicio encontra-se na lista:
	if (node == NULL) {
		printf("\nSoldado inicial nao encontrado no circulo.\n");
		getchar();
		return;
	}

	printf("\n=> 'Para descobrir qual soldado sera removido, serao contados %d soldados a cada exclusao de um soldado.\'\n\n", numero_contagens);

	//Exibe o circulo antes de iniciar as exclusoes:
	ListaEncadeada_Imprimir(lista);

	printf("=> Soldado a partir do qual sera iniciada a contagem: %s\n", nome_soldado_inicio);

	//Percorre o circulo enquanto houver mais de 1 soldado:
	while (lista->primeiro->prox != NULL) {
		for (contador = 1; contador <= numero_contagens; contador++) {
			nodeAtual = node;
			if (node->prox == NULL) {
				node = lista->primeiro;
			} else {
				node = node->prox;
			}
			//Verifica se chegou no soldado que deve ser removido do circulo:
			if (contador == numero_contagens) {
				printf("\nSoldado de nome %s removido do circulo.\n", nodeAtual->info);
				ListaEncadeada_Remover(lista, nodeAtual->info);
				break;
			}
		}
		//Exibe os soldados que estao no circulo apos um soldado sair:
		ListaEncadeada_Imprimir(lista);
	}

	printf("\n!!! O nome do soldado que escapara eh %s !!!\n", lista->primeiro->info);
}

//Teste do programa:
int main(void) {
	Lista_Encadeada* lista = ListaEncadeada_Criar();
	int numero_contagens = 0;
	char nome_soldado[255];
	char nome_soldado_inicio[255];
	while (numero_contagens <= 0) {
		printf("Digite o No. de contagens que serao feitas para cada exclusao de soldado: ");
		scanf("%d", &numero_contagens);
		getchar();
	}

	printf("\n=>Preencha abaixo os soldados que irao compor o circulo.\n");
	do {
		printf("Nome do soldado (deixe em branco para parar a leitura): ");
		gets(nome_soldado);
		if (strlen(nome_soldado) != 0) {
			ListaEncadeada_Inserir(lista, nome_soldado);
		}
	} while (strlen(nome_soldado) != 0);

	printf("\nDigite o nome do soldado de inicio da contagem (deve estar no circulo): ");
	gets(nome_soldado_inicio);

	descobrirSoldado(lista, nome_soldado_inicio, numero_contagens);

	getchar();
	return 0;
}
/**
 * Questão 02. Problema de Josephus. Considere que um grupo de soldados está cercado
 * por forças inimigas. Não há esperanças de vitória sem a chegada de reforços, mas existe
 * somente um cavalo disponível para escapar. Os soldados entram em acordo para decidir
 * quem será. Eles formam um círculo e um número n é sorteado. Um nome também é
 * sorteado. Começando pelo nome sorteado, eles começam a contar ao longo do círculo em
 * sentido horário. Quando chega n, esse soldado é retirado do círculo e o processo se repete
 * até que reste somente um soldado. Esse será o soldado que devera escapar.
 * Faça um programa em C tal que dado um conjunto de soldados, um número n, a ordem em
 * que os soldados são colocados em círculo, e o soldado a partir do qual começará a
 * contagem, determine a ordem em que os soldados são eliminados do círculo e o soldado
 * que escapará.
 */
