/*
 ============================================================================
 Arquivo     : Programação - Lista 02 - Questao 02
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>

#define MAX_ALUNOS 5
#define TAM_STRING 255

typedef struct {
	char nome[TAM_STRING];
	int matricula;
	float media;
} Aluno;

//Le os dados dos alunos:
void lerDados(Aluno alunos[]);
//Procura por um aluno dado sua matricula:
void procurarAluno(Aluno alunos[], int matriculaProcurada);
//Exibe os alunos com media maior ou igual que 5:
void exibirAlunosComMediaMaiorIgualCinco(Aluno alunos[]);

int main(void) {
	Aluno alunos[MAX_ALUNOS];
	int matriculaProcurada;
	int opcao;

	printf("--- LEITURA DE DADOS DOS ALUNOS ---\n");
	lerDados(alunos);

	do {
		printf("\n--- MENU DE OPERACOES ---\n");
		printf("\t1 - Procurar um aluno.\n");
		printf("\t2 - Exibir alunos com media maior ou igual a 5.\n");
		printf("\t0 - Sair.\n");
		printf("\tOPCAO: ");
		scanf("%d", &opcao);
		getchar();
		printf("\n");

		switch (opcao) {
			case 0:
				printf("Programa finalizado!\n");
				break;
			case 1:
				printf("Digite uma matricula para procurar o aluno: ");
				scanf("%d", &matriculaProcurada);
				getchar();
				procurarAluno(alunos, matriculaProcurada);
				break;
			case 2:
				exibirAlunosComMediaMaiorIgualCinco(alunos);
				break;
			default:
				printf("Opcao invalida!\n");
		}
	} while (opcao != 0);

	return 0;
}

void lerDados(Aluno alunos[]) {
	int i;
	for (i = 0; i < MAX_ALUNOS; i++) {
		printf("=> CADASTRO DO ALUNO %d:\n", i + 1);

		printf("\tDigite a matricula do aluno %d: ", i + 1);
		scanf("%d", &alunos[i].matricula);
		getchar();

		printf("\tDigite o nome do aluno %d: ", i + 1);
		gets(alunos[i].nome);

		printf("\tDigite a media do aluno %d: ", i + 1);
		scanf("%f", &alunos[i].media);
		getchar();
	}
}

void procurarAluno(Aluno alunos[], int matriculaProcurada) {
	int i = 0;
	int alunoEncontrado = 0;//"booleano"
	while (i < MAX_ALUNOS && alunoEncontrado == 0) {
		if (matriculaProcurada == alunos[i].matricula) {
			alunoEncontrado = 1;
		} else {
			i++;
		}
	}

	if (alunoEncontrado) {
		printf("ALUNO ENCONTRADO:\n");
		printf("\tMATRICULA: %d\n", alunos[i].matricula);
		printf("\tNOME: %s\n", alunos[i].nome);
		printf("\tMEDIA: %.2f\n", alunos[i].media);
	} else {
		printf("ALUNO NAO ENCONTRADO!\n");
	}
}

void exibirAlunosComMediaMaiorIgualCinco(Aluno alunos[]) {
	int i;
	printf("--- ALUNOS COM MEDIA MAIOR OU IGUAL A 5.00 ---\n");
	printf("NOME DO ALUNO - MEDIA\n");
	for (i = 0; i < MAX_ALUNOS; i++) {
		if (alunos[i].media >= 5) {
			printf("%s - %.2f \n", alunos[i].nome, alunos[i].media);
		}
	}
}
