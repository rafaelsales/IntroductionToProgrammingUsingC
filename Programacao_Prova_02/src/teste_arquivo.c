/*
 ============================================================================
 Arquivo     : Programação - Prova 02 - Questao
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct teste {
	struct teste* prox;
	int valor;
} teste;

void gravar(teste* t) {
	printf("Granvando dados...\n");
	FILE* file = fopen("dados.dat", "wb");
	if (file == NULL) {
		printf("\tErro ao ler arquivo.\n");
		return;
	}
	fwrite(t, sizeof(teste), sizeof(t), file);
	fclose(file);
	printf("Dados gravados com sucesso!\n");
}

teste* ler() {
	printf("Lendo dados...\n");
	FILE* file = fopen("dados.dat", "rb");
	if (file == NULL) {
		printf("\tErro ao ler arquivo.\n");
		return NULL;
	}
	//Posiciona no final do arquivo para calcular o tamanho:
	fseek(file, 0, SEEK_END);
	long tamanhoArquivo = ftell(file);
	//Reposiciona o arquivo no inicio para leitura:
	rewind(file);
	printf("Tamanho do arquivo: %ld; Tamanho da estrutura: %d \n", tamanhoArquivo, (int)sizeof(teste));
	teste* t = calloc(tamanhoArquivo, sizeof(teste));
	fread(t, sizeof(teste), tamanhoArquivo, file);

	fclose(file);
	printf("Dados lidos com sucesso!\n");
	return t;
}

void imprimir(teste* t) {
	teste* percorre = t;
	while (percorre != NULL) {
		printf("%d ", percorre->valor);
		percorre = percorre->prox;
	}
	printf("\n");
}

int main(void) {
	teste* t = malloc(sizeof(teste));
	t->valor = 1;
	t->prox = malloc(sizeof(teste));
	t->prox->valor = 2;
	t->prox->prox = malloc(sizeof(teste));
	t->prox->prox->valor = 3;
	t->prox->prox->prox = malloc(sizeof(teste));
	t->prox->prox->prox->valor = 4;
	t->prox->prox->prox->prox = malloc(sizeof(teste));
	t->prox->prox->prox->prox->valor = 5;
	t->prox->prox->prox->prox->prox = NULL;

	imprimir(t);

	gravar(t);

	while (t != NULL) {
		teste* ta = t->prox;
		free(t);
		t = ta;
	}

	teste* tLeitura;
	tLeitura = ler();
	imprimir(tLeitura);

	getchar();
	getchar();
	return EXIT_SUCCESS;
}
