/*
 ============================================================================
 Nome        : Programacao_Lista_01_12-08-2008/Questao_01.c
 Equipe      : Rafael de Castro, Lucas Assuncao
 ============================================================================
 */

#include <stdio.h>

int main(void) {
	float peso, altura, imc;

	/* Entrada de Dados */

	printf("Digite o peso da pessoa (em kg): ");
	scanf("%f", &peso);
	printf("Digite a altura da pessoa (em metros): ");
	scanf("%f", &altura);

	/* Calculo do IMC */

	altura = altura * altura;
	imc = peso / altura;

	/* Calculo da situacao da pessoa */

	if (imc < 30) {
		if (imc < 25) {
			if (imc < 20) {
				printf("\n ** Abaixo do peso ideal");
			} else {
				printf("\n ** Peso normal");
			}
		} else {
			printf("\n ** Acima do peso ideal");
		}
	} else {
		printf("\n ** Obeso");
	}

	printf("\n\nPressione ENTER para sair");
	getchar();
	getchar();
	return 0;
}

