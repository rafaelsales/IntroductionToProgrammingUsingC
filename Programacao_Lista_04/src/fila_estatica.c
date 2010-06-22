/*
 ============================================================================
 Arquivo     : Programação - Lista 04 - FILA ESTÁTICA
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

//Esta linha define que o tipo da Fila eh int:
typedef int FilaType;

//Estrutura principal da Fila:
typedef struct {
	FilaType** vetor; //Vetor que armazena os elementos da fila.
	int tamanho_maximo; //Tamanho maximo da fila.
	int tamanho; //Quantidade de elementos ocupando a fila. Inicialmente igual a 0.
	int indice_primeiro; //Indice inclusivo do primeiro elemento.
	int indice_ultimo; //Indice exclusivo do ultimo elemento.
} Fila;


Fila* Fila_Criar(int tamanho_maximo);
short Fila_Enfileirar(Fila* fila, FilaType valor_enfileirar);
FilaType* Fila_Desenfileirar(Fila* fila);
FilaType* Fila_Consultar_Proximo(Fila* fila);
short Fila_Verifica_Cheia(Fila* fila);
void Fila_Imprimir(Fila* fila);

/**Cria uma nova Fila.
 * Retorna um ponteiro para a estrutura da fila
 * ou NULL caso tenha ocorrido erro na criacao.
 */
Fila* Fila_Criar(int tamanho_maximo) {
	Fila* fila = (Fila*)malloc(sizeof(Fila));
	fila->vetor = (FilaType**)calloc(tamanho_maximo, sizeof(FilaType*));
	fila->tamanho_maximo = tamanho_maximo;
	fila->tamanho = 0;
	fila->indice_primeiro = 0;
	fila->indice_ultimo = 0;

	return fila;
}

/**Insere um valor no topo da fila.
 * Retorna 1 caso tenha sido inserido com sucesso
 * ou 0 caso a fila esteja cheia.
 */
short Fila_Enfileirar(Fila* fila, FilaType valor_enfileirar) {
	//Verifica se a fila esta cheia:
	if (fila->tamanho == fila->tamanho_maximo) {
		return 0;
	}

	FilaType *novo_valor = (FilaType*)malloc(sizeof(FilaType));
	*novo_valor = valor_enfileirar;
	fila->vetor[fila->indice_ultimo] = novo_valor;
	fila->indice_ultimo = (fila->indice_ultimo + 1) % fila->tamanho_maximo;
	fila->tamanho++;

	return 1;
}

/**Remove o elemento do topo da fila.
 * Retorna um ponteiro para o elemento do topo da
 * fila ou NULL caso a fila esteja vazia.
 */
FilaType* Fila_Desenfileirar(Fila* fila) {
	if (fila->tamanho == 0) {
		return NULL;
	}
	FilaType *elemento_topo = fila->vetor[fila->indice_primeiro];
	fila->vetor[fila->indice_primeiro] = NULL;
	fila->indice_primeiro = (fila->indice_primeiro + 1) % fila->tamanho_maximo;
	fila->tamanho--;

	return elemento_topo;
}

/**Retorna um ponteiro para o proximo elemento da fila a
 * ser desenfileirado ou NULL caso a fila esteja vazia.
 */
FilaType* Fila_Consultar_Proximo(Fila* fila) {
	if (fila->tamanho == 0) {
		return NULL;
	}
	return fila->vetor[fila->indice_primeiro];
}

/**Retorna 1 caso a fila esteja cheia ou 0 caso
 * haja espaco disponivel para enfileirar.
 */
short Fila_Verifica_Cheia(Fila* fila) {
	return fila->tamanho == fila->tamanho_maximo;
}

/**Exibe todos os elementos da fila em forma de string na tela.
 */
void Fila_Imprimir(Fila* fila) {
	printf("Fila {");

	int i = fila->indice_primeiro;
	int cont;
	for (cont = 1; cont <= fila->tamanho; cont++) {
		printf("[%d]=%d", i, (int)*fila->vetor[i]);
		if (cont < fila->tamanho) {
			printf(", ");
		}
		i = (i + 1) % fila->tamanho_maximo;
	}
	printf("}\n");
}


/**
 * FUNCAO PARA TESTE NO MAIN:
 */
int verificaFilaCriada(Fila* fila) {
	if (fila == NULL) {
		printf("Crie a fila antes de utilizar!\n");
	}
	return fila != NULL;
}

int main(void) {
	Fila *fila = NULL;
	int opcao;
	do {
		printf("\n---Fila Estatica---\n");
		printf("\t1-Criar\n");
		printf("\t2-Enfileirar\n");
		printf("\t3-Desenfileirar\n");
		printf("\t4-Consultar proximo da fila\n");
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
				printf("Digite o tamanho maximo da fila: ");
				scanf("%d", &tamanho);
				fila = Fila_Criar(tamanho);
				if (fila != NULL) {
					printf("Fila criada com sucesso.\n");
				}
				break;
			case 2:
				if (!verificaFilaCriada(fila)) {
					break;
				} else if (Fila_Verifica_Cheia(fila)) {
					printf("A fila esta cheia.\n");
					break;
				}
				int numero_enfileirar;
				printf("Digite o numero a ser enfileirado: ");
				scanf("%d", &numero_enfileirar);
				if (Fila_Enfileirar(fila, numero_enfileirar) == 0) {
					printf("Erro ao enfileirar elemento.\n");
				} else {
					printf("Numero enfileirado com sucesso.\n");
				}
				break;
			case 3:
				if (!verificaFilaCriada(fila)) {
					break;
				}
				int* valor_desenfileirado = Fila_Desenfileirar(fila);
				if (valor_desenfileirado == NULL) {
					printf("Fila vazia.\n");
				} else {
					printf("Valor desenfileirado: %d.\n", *valor_desenfileirado);
				}
				break;
			case 4:
				if (!verificaFilaCriada(fila)) {
					break;
				}
				int* valor_proximo = Fila_Consultar_Proximo(fila);
				if (valor_proximo == NULL) {
					printf("Fila vazia.\n");
				} else {
					printf("Proximo da fila: %d.\n", *valor_proximo);
				}
				break;
			case 5:
				if (!verificaFilaCriada(fila)) {
					break;
				}
				Fila_Imprimir(fila);
				break;
			default:
				printf("Opcao invalida!\n");
		}
	} while (opcao != 0);

	return 0;
}
