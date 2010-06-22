/*
 ============================================================================
 Nome        : Programacao_Lista_01_12-08-2008/Questao_05.c
 Equipe      : Rafael de Castro, Lucas Assuncao
  ============================================================================
 */

#include <stdio.h>

int main(void) {
	float h, peso, h_min = 0.0, peso_max = 0.0;
	char sexo;
	int i, numero_mulheres = 0;

	/* Entrada de Valores */
	for (i = 1; i <= 4; i++) {
		printf("Pessoa Numero %d:\n", i);
		printf("\tDigite a altura (Em metros): ");
		scanf("%f", &h);
		printf("\tDigite o peso (Em quilos): ");
		scanf("%f", &peso);
		printf("\tDigite o sexo (M=Masculino / F=Feminino): ");
		getchar();
		scanf("%c", &sexo);

		/* Peso maximo / Altura minima */

		if (i == 1) { /* h_min e peso_max sao inicializados com os dados da 1a pessoa */
			h_min = h;
			peso_max = peso;
		} else {
			if (h < h_min)
				h_min = h;
			if (peso > peso_max)
				peso_max = peso;
		}

		/* Contador de mulheres / Calculo Peso ideal */
		/* Caso seja digitado sexo invalido, o programa nao imprime peso ideal */
		if ((sexo == 'F') || (sexo == 'f')) {
			numero_mulheres++;
			printf("\t*** Peso Ideal: %6.3fkg ***\n", (62.1 * h) - 44.7);
		}
		if ((sexo == 'M') || (sexo == 'm'))
			printf("\t*** Peso Ideal: %6.3fkg ***\n", (72.7 * h) - 58);
	}

	printf("\nA pessoa de maior peso tem %6.3fkg", peso_max);
	printf("\nA pessoa de menor altura tem %6.2fm", h_min);
	printf("\nNumero de pessoas do sexo feminino: %d", numero_mulheres);

	printf("\n\nPressione ENTER para sair");
	getchar();
	getchar();
	return 0;
}
