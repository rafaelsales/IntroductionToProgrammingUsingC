#include<stdio.h>
#include <stdlib.h>

//typedef struct celula_str *Apontador;

typedef struct celula_str {
	struct celula_str* Direita, *Abaixo;
	int Linha, Coluna;
	int Valor;
} celula;

void imprimir(celula* matriz);

void insere_linha(celula* inicio, celula *novo, int x) {
	celula *atual;
	atual = inicio;
	while ((atual->Direita != inicio) && (x > atual->Direita->Coluna)) {
		atual = atual->Direita;
	}
	novo->Direita = atual->Direita;
	atual->Direita = novo;
}

void insere_coluna(celula* inicio, celula *novo, int x) {
	celula *atual;
	atual = inicio;
	while ((atual->Abaixo != inicio) && (x > atual->Abaixo->Linha)) {
		atual = atual->Abaixo;
	}
	novo->Abaixo = atual->Abaixo;
	atual->Abaixo = novo;
}

celula* definir_matriz(int i, int j) {
	int cont;
	celula* matriz = (celula*) malloc(sizeof(celula));
	celula* celulaPercorre;
	celula* novo;
	matriz->Direita = matriz;
	matriz->Abaixo = matriz;
	matriz->Valor = -1;
	matriz->Linha = i;
	matriz->Coluna = j;

	celulaPercorre = matriz;
	//Cabecas das linhas:
	for (cont = 1; cont <= i; cont++) {
		novo = (celula*) malloc(sizeof(celula));
		celulaPercorre->Abaixo = novo;
		novo->Abaixo = matriz;
		novo->Direita = novo;
		novo->Linha = cont;
		novo->Coluna = 0;
		novo->Valor = -1;
		celulaPercorre = celulaPercorre->Abaixo;
		printf("\nL");
	}

	celulaPercorre = matriz;
	//Cabecas das colunas:
	for (cont = 1; cont <= j; cont++) {
		novo = (celula*) malloc(sizeof(celula));
		celulaPercorre->Direita = novo;
		novo->Direita = matriz;
		novo->Abaixo = novo;
		novo->Linha = 0;
		novo->Coluna = cont;
		novo->Valor = -1;
		celulaPercorre = celulaPercorre->Direita;
		printf(" C");
	}

	return matriz;
}

celula* ler_matriz() {
	int valor;
	int i, j, m, n;
	celula* elemento, * linha, * coluna, * aux;
	celula* matriz;

	printf("Digite a ordem da Matriz : \n\n");
	printf("Numero de linhas : ");
	scanf("%d", &m);
	printf("\nNumero de Colunas : ");
	scanf("%d", &n);

	matriz = definir_matriz(m, n);

	celula** vetorColunas = (celula**) calloc(n, sizeof(celula*));

	coluna = matriz->Direita;
	linha = matriz->Abaixo;

	for (j = 0; j < n; j++) {
		vetorColunas[j] = coluna;
		coluna = coluna->Direita;
	}
	coluna = matriz->Direita;

	printf("Digite os elementos da Matriz : \n\n");

	//tudo errado !!!

	for (i = 1; i <= m; i++) {
		aux = linha;
		for (j = 1; j <= n; j++) {
			printf("Elemento (%d,%d) : ", i, j);
			scanf("%d", &valor);
			if (valor != 0) {
				elemento = (celula*) malloc(sizeof(celula));
				elemento->Valor = valor;
				elemento->Linha = i;
				elemento->Coluna = j;
				elemento->Abaixo = coluna;
				elemento->Direita = linha;
				aux->Direita = elemento;
				aux = aux->Direita;
				vetorColunas[j - 1]->Abaixo = elemento;
				vetorColunas[j - 1] = elemento;
			}
			coluna = coluna->Direita;
		}
		linha = linha->Abaixo;
	}

	for (j = 0; j < n; j++) {
		vetorColunas[j] = vetorColunas[j]->Abaixo;
	}

	for (j = 0; j < n; j++) {
		coluna = vetorColunas[j];
		coluna = coluna->Direita;
	}

	coluna = coluna->Direita;
	linha = linha->Abaixo;

	matriz->Direita = coluna;
	matriz->Abaixo = linha;
	imprimir(matriz);
	return matriz;
}

void imprimir(celula* matriz) {
	celula* linha = matriz->Abaixo;
	celula* coluna;
	int i, j;
	for (i = 1; i <= matriz->Linha; i++) {
		coluna = linha->Direita;
		for (j = 1; j <= matriz->Coluna; j++) {
			if (coluna->Coluna == j) {
				printf("\t%d", coluna->Valor);
				coluna = coluna->Direita;
			} else if (coluna->Coluna != j) {
				printf("\t0");
			}
		}
		printf("\n");
		linha = linha->Abaixo;
	}
}

int maina() {
	int opcao;
	float valor;
	celula* matriz = NULL;
	do {
		printf("\t\t\tMENU\n\n");
		printf("1 - Ler Matriz\n");
		printf("2 - Imprimir Matriz\n");
		printf("3 - \n");
		printf("4 - \n");
		printf("5 - \n");
		printf("6 - \n");
		printf("0 - Sair\n\n");
		printf("Digite sua opcao : ");
		scanf("%d", &opcao);
		getchar();

		switch (opcao) {
		case 0:
			return 0; //Sai do programa.
		case 1:
			system("cls");
			matriz = ler_matriz();
			system("pause");
			system("cls");
			break;

		case 2:
			system("cls");
			imprimir(matriz);
			//printf("-> %d Linhas\n\n", matriz->Linha);
			//printf("-> %d Colunas", matriz->Coluna);
			system("pause");
			system("cls");
			break;

		case 3:

		case 4:

		case 5:

		case 6:

		case 7:

		case 8:

		case 9:

		case 10:

		case 11:

		case 12:

		case 13:

		default:
			printf("Opcao invalida\n");
			system("pause");
			system("cls");
			break;
		}
	} while (opcao != 0);
	return 0;
}
