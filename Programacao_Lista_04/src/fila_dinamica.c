/*
 ============================================================================
 Arquivo     : Programação - Lista 04 - FILA DINÂMICA
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct fila_circular {
	int info;
	struct fila_circular* prox;
};

typedef struct fila_circular No;

// cria lista
No* criaFila() {
	return NULL;
}

// insere sempre no fim
No* insereFila(No* fim, int valor) {
	No* novo = (No*) malloc(sizeof(No));
	novo->info = valor;
	if (novo != NULL) {
		if (fim == NULL) {
			novo->prox = novo;
			return novo;
		}//else
		novo->prox = fim->prox; //novo se transforma no fim e aponta para o inicio
		fim->prox = novo;
		return novo;
	} else {
		printf("Erro da insercao!\n");
		return fim;
	}
}

// revmove sempre do inicio
No* desenfileira(No* fim, int* desenfileirado) {
	No* inicio;
	if (fim != NULL) {
        *desenfileirado=fim->prox->info;    
		if (fim->prox == fim) {                      
			free(fim);
			return NULL;
		} else {
			inicio = fim->prox;
			fim->prox = inicio->prox; //fim passa a apontar para o seguinte ao inicial
			free(inicio);
			return fim;
		}
	} else {
		printf("Fila vazia!\n");
		return NULL;
	}
}

// consulta
No* consultaFila(No* fim, int valor) {
	No* percorre = fim;
	if (fim != NULL) {
		while ((percorre->info != valor) && (percorre->prox != fim))
			percorre = percorre->prox;
		if (percorre->info == valor)
			return percorre;
	}
	return NULL; // se o fim for NULL ou o valor nao for encontrado
}

// imprime fila do começo para o fim
void imprimeFila(No* fim) {
	No* percorre;
	if (fim != NULL) {
		printf("%d\n", fim->prox->info); //imprime o primeiro da fila
		percorre = fim->prox->prox; // percorre recebe o seguinte ao inicial
		while (percorre != fim->prox) {
			printf("%d\n", percorre->info);
			percorre = percorre->prox;
		}
	} else
		printf("Lista vazia!!");
}
// main usado para fazer testes
int main(void) {
    int* desenfileirado=(int*)malloc(sizeof(int));
	No* fim = criaFila(),*fim_controle;
	;
	No* buscado;
	int controle = 1, opcao, valor;
	printf("     ===== Fila Circular ====");
	while (controle == 1) {
		printf("\n -> Para inserir elemento, digite 1\n");
		printf(" -> Para remover elemento, digite 2\n");
		printf(" -> Para buscar um elemento, digite 3\n");
		printf(" -> Para imprimir a fila, digite 4\n");
		printf(" => ");
		scanf("%d", &opcao);
		switch (opcao) {
		case 1: {
			printf("\nQual o valor a ser incluso? ");
			scanf("%d", &valor);
			fim = insereFila(fim, valor);
			break;
		}
		case 2: {
            fim_controle=fim; // guarda o fim antes de ser atualizado (para o if após o desenfileira)
			fim = desenfileira(fim,desenfileirado);
			if(fim_controle!=NULL) printf("Valor desenfileirado: %d\n", *desenfileirado);
			break;
		}
		case 3: {
			printf("\nQual o valor a ser buscado? ");
			scanf("%d", &valor);
			buscado = consultaFila(fim, valor);
			if (buscado == NULL)
				printf("\n *** Valor inexistente na fila\n");
			else
				printf("\n *** Valor existente na fila\n");
			break;
		}
		case 4:
			imprimeFila(fim);
			break;
		default:
			printf("\n *** Operacao invalida!\n");
		}
		printf(" \n** Deseja continuar? (Sim-1/Nao-0) ");
		scanf("%d", &controle);
	}
	return 0;
}
