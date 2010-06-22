/*
 ============================================================================
 Nome        : Programacao_Lista_01_12-08-2008/Questao_03.c
 Equipe      : Rafael de Castro, Lucas Assuncao
 ============================================================================
 */

#include <stdio.h>

int main(void) {
	int numero_secreto = -1, numero_teste = -1, tentativas = 0, i;

	while (numero_secreto < 1 || numero_secreto > 100) {
		printf("Digite um numero inteiro no intervalo fechado de 1 a 100: ");
		scanf("%d", &numero_secreto);
	}
	//Preenche a tela com 100 linhas em branco para ocultar o numero secreto:
	for (i = 0; i < 100; i++) {
		printf("\n");
	}

	printf("---ACERTE UM NUMERO---\n");
	//Le as tentativas do usuario e verifica o status da jogada:
	while (numero_teste != 0 && numero_teste != numero_secreto) {
		printf("Digite um numero inteiro no intervalo fechado de 1 a 100 (0 para desistir): ");
		scanf("%d", &numero_teste);

		//Se o usuario nao desistiu, verifica o status da tentativa:
		if (numero_teste != 0) {
			if (numero_teste < numero_secreto) {
				printf("Voce digitou um numero inferior ao numero secreto.\n");
			} else if (numero_teste > numero_secreto) {
				printf("Voce digitou um numero superior ao numero secreto.\n");
			}
			tentativas++;
		}
	}

	//Verifica se o usuario acertou:
	if (numero_teste == numero_secreto) {
		printf("\nParabens! Voce acertou o numero secreto em %d tentativas.", tentativas);
	}

	printf("\n\nPressione ENTER para sair");
	getchar();
	getchar();
	return 0;
}
