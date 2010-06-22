/*
 ============================================================================
 Arquivo     : Programação - Lista 02 - Questao 01
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>

#define MAX_ALUNOS 15
#define NUM_NOTAS 4
#define TAM_STRING 255

int main(void) {
	float matrizNotas[MAX_ALUNOS][NUM_NOTAS];
	char vetorNomes[MAX_ALUNOS][TAM_STRING];

	int i, j;
	//Le os dados:
	for (i = 0; i < MAX_ALUNOS; i++) {
		printf("Digite o nome do aluno %d: ", i + 1);
		gets(vetorNomes[i]);

		for (j = 0; j < NUM_NOTAS; j++) {
			printf("\tDigite a nota da prova %d: ", j + 1);
			scanf("%f", &matrizNotas[i][j]);
		}
		getchar();
	}

	float mediaClasse = 0;
	//Exibe os dados:
	printf("\n---REULSTADO---\n");
	for (i = 0; i < MAX_ALUNOS; i++) {
		printf("\nAluno: %s", vetorNomes[i]);
		float mediaAluno = 0;
		for (j = 0; j < NUM_NOTAS; j++) {
			mediaAluno += matrizNotas[i][j];
		}
		mediaAluno /= NUM_NOTAS;
		mediaClasse += mediaAluno;

		printf("\n\tMedia: %.2f", mediaAluno);
		if (mediaAluno >= 7) {
			printf("\tSituacao: APROVADO");
		} else {
			printf("\tSituacao: REPROVADO");
		}
	}
	mediaClasse /= MAX_ALUNOS;
	printf("\n\nMedia da classe: %.2f", mediaClasse);

	getchar();
	getchar();
	return 0;
}
