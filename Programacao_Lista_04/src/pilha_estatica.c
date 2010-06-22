/*
 ============================================================================
 Arquivo     : Programação - Lista 04 - PILHA ESTÁTICA
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

//Esta linha define que o tipo da Pilha eh int:
typedef int PilhaType;

//Estrutura principal da Pilha:
typedef struct {
	PilhaType** vetor; //Vetor que armazena os elementos da pilha.
	int tamanho_maximo; //Tamanho maximo da pilha.
	int indice_topo; //Indice do topo da pilha. Caso vazia, o indice eh -1.
} Pilha;


Pilha* Pilha_Criar(int tamanho_maximo);
short Pilha_Empilhar(Pilha* pilha, PilhaType valor_empilhar);
PilhaType* Pilha_Desempilhar(Pilha* pilha);
PilhaType* Pilha_Consultar_Topo(Pilha* pilha);
short Pilha_Verifica_Cheia(Pilha* pilha);
void Pilha_Imprimir(Pilha* pilha);

/**Cria uma nova Pilha.
 * Retorna um ponteiro para a estrutura da pilha ou NULL caso tenha ocorrido erro na criacao.
 */
Pilha* Pilha_Criar(int tamanho_maximo) {
	Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
	pilha->tamanho_maximo = tamanho_maximo;
	pilha->vetor = (PilhaType**)calloc(tamanho_maximo, sizeof(PilhaType*));
	pilha->indice_topo = -1;

	return pilha;
}

/**Insere um valor no topo da pilha.
 * Retorna 1 caso tenha sido inserido com sucesso ou 0 caso a pilha esteja cheia.
 */
short Pilha_Empilhar(Pilha* pilha, PilhaType valor_empilhar) {
	//Verifica se a pilha esta cheia:
	if (pilha->indice_topo + 1 == pilha->tamanho_maximo) {
		return 0;
	}
	pilha->indice_topo++;

	PilhaType *novo_valor = (PilhaType*)malloc(sizeof(PilhaType));
	*novo_valor = valor_empilhar;
	pilha->vetor[pilha->indice_topo] = novo_valor;

	return 1;
}

/**Remove o elemento do topo da pilha.
 * Retorna um ponteiro para o elemento do topo da pilha ou NULL caso a pilha esteja vazia.
 */
PilhaType* Pilha_Desempilhar(Pilha* pilha) {
	if (pilha->indice_topo == -1) {
		return NULL;
	}
	PilhaType *elemento_topo = pilha->vetor[pilha->indice_topo];
	pilha->vetor[pilha->indice_topo] = NULL;
	pilha->indice_topo--;

	return elemento_topo;
}

/**Retorna um ponteiro para o elemento do topo da pilha ou NULL caso a pilha esteja vazia.
 */
PilhaType* Pilha_Consultar_Topo(Pilha* pilha) {
	if (pilha->indice_topo == -1) {
		return NULL;
	}
	return pilha->vetor[pilha->indice_topo];
}

/**Retorna 1 caso a pilha esteja cheia ou 0 caso haja espaco disponivel para empilhar.
 */
short Pilha_Verifica_Cheia(Pilha* pilha) {
	return pilha->indice_topo + 1 == pilha->tamanho_maximo;
}

/**Exibe todos os elementos da pilha em forma de string na tela.
 */
void Pilha_Imprimir(Pilha* pilha) {
	printf("Pilha {");
	int i;
	for (i = 0; i <= pilha->indice_topo; i++) {
		printf("%d", (int)*pilha->vetor[i]);
		if (i != pilha->indice_topo) {
			printf(", ");
		}
	}
	printf("}\n");
}


/**
 * FUNCAO PARA TESTE NO MAIN:
 */
int verificaPilhaCriada(Pilha* pilha) {
	if (pilha == NULL) {
		printf("Crie a pilha antes de utilizar!\n");
	}
	return pilha != NULL;
}

int main(void) {
	Pilha *pilha = NULL;
	int opcao;
	do {
		printf("\n---Pilha Estatica---\n");
		printf("\t1-Criar\n");
		printf("\t2-Empilhar\n");
		printf("\t3-Desempilhar\n");
		printf("\t4-Consultar topo\n");
		printf("\t5-Imprimir\n");
		printf("\t0-Sair\n");
		printf("\tDigite a opcao: ");
		scanf("%d", &opcao);
		getchar();
		printf("\n");
		switch (opcao) {
			case 0:
				printf("Programa finalizado!\n");
				break;
			case 1:;
				int tamanho;
				printf("Digite o tamanho maximo da pilha: ");
				scanf("%d", &tamanho);
				pilha = Pilha_Criar(tamanho);
				if (pilha != NULL) {
					printf("Pilha criada com sucesso.\n");
				}
				break;
			case 2:
				if (!verificaPilhaCriada(pilha)) {
					break;
				} else if (Pilha_Verifica_Cheia(pilha)) {
					printf("A pilha esta cheia.\n");
					break;
				}
				int numero_empilhar;
				printf("Digite o numero a ser empilhado: ");
				scanf("%d", &numero_empilhar);
				if (Pilha_Empilhar(pilha, numero_empilhar) == 0) {
					printf("Erro ao empilhar elemento.\n");
				} else {
					printf("Numero empilhado com sucesso.\n");
				}
				break;
			case 3:
				if (!verificaPilhaCriada(pilha)) {
					break;
				}
				int* valor_desempilhado = Pilha_Desempilhar(pilha);
				if (valor_desempilhado == NULL) {
					printf("Pilha vazia.\n");
				} else {
					printf("Valor desempilhado: %d.\n", *valor_desempilhado);
				}
				break;
			case 4:
				if (!verificaPilhaCriada(pilha)) {
					break;
				}
				int* valor_topo = Pilha_Consultar_Topo(pilha);
				if (valor_topo == NULL) {
					printf("Pilha vazia.\n");
				} else {
					printf("Valor do topo da pilha: %d.\n", *valor_topo);
				}
				break;
			case 5:
				if (!verificaPilhaCriada(pilha)) {
					break;
				}
				Pilha_Imprimir(pilha);
				break;
			default:
				printf("Opcao invalida!\n");
		}
	} while (opcao != 0);

	return 0;
}
