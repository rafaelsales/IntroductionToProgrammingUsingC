/*
 ============================================================================
 Arquivo     : Programação - Prova 01 - Questao 03
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exibir_expressoes_validas(int resultado_correto_expressao, int operandos[], int quantidade_operandos);

/*
 * Procura por expressoes validas e exibe se existirem.
 * @Parametro: resultado_correto_expressao - Valor no qual a expressao deve resultar.
 * @Parametro: operandos - Vetor de inteiros contendo os operandos da expressao.
 * @Parametro: quantidade_operandos - Quantidade de operandos do vetor "operandos".
 */
void exibir_expressoes_validas(int resultado_correto_expressao, int operandos[], int quantidade_operandos) {
	if (quantidade_operandos < 2) {
		printf("Uma expressao valida deve conter no minimo 2 operandos.\n");
		return;
	}
	int indice; //Indice para iterar pelos vetores.
	int quantidade_operadores = quantidade_operandos - 1; //Numero de operadores da expressao.
	int resultado_teste_expressao; //Utilizado para armazenar o valor de uma expressao testada.
	short fim_testes; //boolean para identificar quando todos as combinacoes ja foram feitas.
	char operador = ' '; //Armazena a representacao do operador (+, - ou *) para exibicao.

	//Aloca uma string que armazenara a expressao completa com os operandos e os operadores entre eles:
	char* string_expressao = (char*) calloc(quantidade_operandos * sizeof(int) + quantidade_operadores, sizeof(char));

	/* Vetor contendo os indices dos operadores que devem ser testados entre dois operandos.
	 * Existem 3 indices possiveis: 0, 1 e 2. O indice 0 significa o operador '+', o 2 significa
	 * o operador '-' e o 2 significa o operador '*'.
	 */
	short int operadores[quantidade_operadores];

	//Inicializa o indice que identifica os operadores com 0 - o operador '+':
	for (indice = 0; indice < quantidade_operadores; indice++) {
		operadores[indice] = 0;
	}

	printf("\n=> EXPRESSOES ENCONTRADAS:\n");
	do {
		resultado_teste_expressao = operandos[0];
		sprintf(string_expressao, "%d", operandos[0]);
		//Aplica a sequencia de operadores entre os operandos para verificar o resultado.
		for (indice = 1; indice < quantidade_operandos; indice++) {
			switch (operadores[indice - 1]) {
			case 0:
				resultado_teste_expressao += operandos[indice];
				operador = '+';
				break;
			case 1:
				resultado_teste_expressao -= operandos[indice];
				operador = '-';
				break;
			case 2:
				resultado_teste_expressao *= operandos[indice];
				operador = '*';
				break;
			}
			sprintf(string_expressao, "%s %c %d", string_expressao, operador, operandos[indice]);
		}

		//Compara com o resultado da expressao correto com o resultado esperado:
		if (resultado_correto_expressao == resultado_teste_expressao) {
			printf("Expressao valida encontrada: %d = %s \n", resultado_correto_expressao, string_expressao);
		}

		fim_testes = 1;
		//Verifica se ja foi testado ate o ultimo operador, o operador '*' com todos os operandos:
		for (indice = 0; indice < quantidade_operadores; indice++) {
			if (operadores[indice] < 2) {
				fim_testes = 0;
				break;
			}
		}

		//Se os testes ainda devem continuam, passa para a proxima combinacao de operadores:
		if (fim_testes == 0) {
			//O numero de combinacoes entre os operadores eh 3^(n-1) onde n eh o numero de operandos.
			for (indice = 0; indice < quantidade_operadores; indice++) {
				if (operadores[indice] == 2) {
					operadores[indice] = 0;
				} else {
					operadores[indice]++;
					break;
				}
			}
		}
	} while (fim_testes == 0);

	free(operadores);
	free(string_expressao);
}


//Teste de leitura de uma expressao:
int main(void) {
	printf("--- BUSCADOR DE EXPRESSOES VALIDAS ---\n");
	int resultado_expressao;
	//O vetor eh realocado dinamicamente a cada novo operando digitado pelo usuario:
	int* operandos = NULL;
	int quantidade_operandos = 0;
	char continuar = 's';

	//Le o valor no qual a expressao deve resultar:
	printf("Digite o resultado da expressao: ");
	scanf("%d", &resultado_expressao);

	//Le os operandos (obriga que no minimo dois operandos devem ser lidos):
	do {
		//Realoca o vetor para conter mais um operando:
		operandos = (int*) realloc(operandos, (quantidade_operandos + 1)* sizeof(int));
		printf("Digite um operando da expressao: ");
		scanf("%d", &operandos[quantidade_operandos]);
		getchar();
		quantidade_operandos++;

		//Se pelo menos dois operadores ja foram digitados, pergunta se o usuario quer ler mais operandos:
		if (quantidade_operandos >= 2) {
			printf("Deseja ler mais um operando (s ou n)? ");
			scanf("%c", &continuar);
		}
	} while (continuar == 's' || continuar == 'S');
	//Procura por expressoes validas:
	exibir_expressoes_validas(resultado_expressao, operandos, quantidade_operandos);

	free(operandos);

	printf("\nPressione [ENTER] para sair.\n");
	getchar();
	getchar();
	return 0;
}

/*
 * Questão 03. Papiros misteriosos. Durante escavações no deserto do Saara foram
 * encontrados papiros com símbolos misteriosos provenientes de uma antiga civilização.
 * Depois de longas investigações, os cientistas descobriram que estes símbolos faziam parte
 * de expressões matemáticas, embora os únicos símbolos encontrados fossem dígitos e sinais
 * de igualdade. Sabe-se, no entanto, que eles só conheciam as operações de adição,
 * multiplicação e subtração, e não usavam precedência de operadores, avaliando as
 * expressões da esquerda para a direita. Assim uma equação como 3 + 3 * 5 seria igual a 30 e
 * não 18. A hipótese colocada pelos cientistas é de que os operadores desapareceram dos
 * papiros ao longo do tempo, deixando apenas os dígitos e o sinal de igualdade. Para testar
 * esta hipótese desenvolva uma aplicação que verifique se uma determinada expressão num
 * papiro é válida ou não, ou seja, se colocando os operadores +, -, * nos espaços entre os
 * operandos o resultado é correto. Por exemplo, se num papiro existisse 18 = 7 5 3 2, poderia
 * corresponder à expressão 18 = 7 + 5 – 3 * 2. No entanto a expressão 5 = 3 3 não
 * corresponde a nenhuma operação válida.
 * Implemente um programa em C que receba uma expressão como entrada e diga se a
 * expressão é válida ou não. Em caso positivo apresente no mínimo uma expressão válida
 * correspondente.
 */
