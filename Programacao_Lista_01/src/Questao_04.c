/*
 ============================================================================
 Nome        : Programacao_Lista_01_12-08-2008/Questao_04.c
 Equipe      : Rafael de Castro, Lucas Assuncao
 ============================================================================
 */

#include <stdio.h>

int main(void) {
	float num, num_anterior, soma;
	int controle = 2;

	/* Entrada do primeiro valor */
	printf("Digite o 1o numero: ");
	scanf("%f", &num_anterior);
	soma = num_anterior;

	/* Entrada dos demais valores */
	while (controle <= 8) {
		printf("Digite o %do numero: ", controle);
		scanf("%f", &num);

		//Compara com o anterior para saber se e valido:
		if (num != num_anterior) {
			num_anterior = num;
			controle++;
			soma = soma + num;
		} else {
			printf("* O numero deve ser diferente do numero anterior (%.3f)\n", num_anterior);
		}
	}

	/* Mostra o resultado */
	printf("O somatorio dos numeros e: %.3f", soma);

	printf("\n\nPressione ENTER para sair");
	getchar();
	getchar();
	return 0;
}
/* OBS.: O programa mostra os numeros com a precisao de 3 casas decimais. */
/*  Entretando, na soma, as demais fracoes sao preservadas. */
