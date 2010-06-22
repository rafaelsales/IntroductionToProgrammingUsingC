/*
 ============================================================================
 Arquivo     : Programação - Prova 02 - Questao 03 (Matriz Esparsa)
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define COMANDO_LIMPAR_CONSOLE "cls" //Para Windows: "cls" ; Para Linux: "clear"

typedef struct CelulaMatriz {
	float valor; //Valor armazenado na celula
	int linha; //Numero da linha da celula
	int coluna; //Numero da coluna da celula
	struct CelulaMatriz* direita; //Ponteiro para a celula que esta a direita da celula. No caso da ultima celula, aponta para a primeira celula da linha
	struct CelulaMatriz* abaixo; //Ponteiro para a celula que esta abaixo da celula. No caso da ultima celula, aponta para a primeira celula da coluna
} CelulaMatriz;

CelulaMatriz* criarCelula(int linha, int coluna, float valor, CelulaMatriz* direita, CelulaMatriz* abaixo);
CelulaMatriz* criarCelulaVazia(CelulaMatriz* direita, CelulaMatriz* abaixo);
CelulaMatriz* lerMatriz();
void imprimirMatriz(CelulaMatriz* matriz);
void imprimirMatrizFormatada(CelulaMatriz* matriz);
void apagarMatriz(CelulaMatriz* matriz);
CelulaMatriz* somarMatrizes(CelulaMatriz* matrizA, CelulaMatriz* matrizB);
CelulaMatriz* multiplicarMatrizes(CelulaMatriz* matrizA, CelulaMatriz* matrizB);
int maximo(int x, int y);
CelulaMatriz* solicitarEscolhaMatriz(CelulaMatriz* matriz1, CelulaMatriz* matriz2);
short verificarMatrizCriada(CelulaMatriz* matriz);
void solicitarPausa();

/**Aloca e inicializa uma nova celula na memoria com os dados passados por parametro.
 * @Parametro: linha - Numero da linha da celula na matriz
 * @Parametro: coluna - Numero da coluna da celula na matriz
 * @Parametro: valor - Valor da celula
 * @Parametro: direita - Ponteiro para a celula que ficara a direita da celula criado
 * @Parametro: abaixo - Ponteiro para a celula que ficara abaixo da celula criado
 * @Retorno: Retorna um ponteiro para a celula
 */
CelulaMatriz* criarCelula(int linha, int coluna, float valor, CelulaMatriz* direita, CelulaMatriz* abaixo) {
	CelulaMatriz* celula = malloc(sizeof(CelulaMatriz));
	celula->linha = linha;
	celula->coluna = coluna;
	celula->valor = valor;

	if (direita == NULL) {
		celula->direita = celula;
	} else {
		celula->direita = direita;
	}
	if (abaixo == NULL) {
		celula->abaixo = celula;
	} else {
		celula->abaixo = abaixo;
	}
	return celula;
}

/**Aloca e inicializa uma nova celula vazia na memoria.
 * @Parametro: direita - Ponteiro para a celula que ficara a direita da celula criado
 * @Parametro: abaixo - Ponteiro para a celula que ficara abaixo da celula criado
 * @Retorno: Retorna um ponteiro para a celula
 */
CelulaMatriz* criarCelulaVazia(CelulaMatriz* direita, CelulaMatriz* abaixo) {
	return criarCelula(-1, -1, -1, direita, abaixo);
}

/**Solicita a leitura da matriz ao usuario.
 * @Retorno: Ponteiro para o noh cabeca da matriz preenchida
 */
CelulaMatriz* lerMatriz() {
	CelulaMatriz* matriz = criarCelulaVazia(NULL, NULL);
	CelulaMatriz* celula = NULL;
	CelulaMatriz* celulaColuna, * celulaLinha;
	CelulaMatriz** ultimasCelulasColunas = NULL; //Vetor contendo as ultimas celulas das colunas

	int maxLinhas, maxColunas, i, j;
	float valor;

	//Le a ordem da matriz:
	do {
		printf("Digite o numero de LINHAS da matriz: ");
		scanf("%d", &maxLinhas);
	} while (maxLinhas < 1);
	do {
		printf("Digite o numero de COLUNAS da matriz: ");
		scanf("%d", &maxColunas);
	} while (maxColunas < 1);

	//Armazena no noh cabeca da matriz o numero maximo de linhas e colunas:
	matriz->linha = maxLinhas;
	matriz->coluna = maxColunas;

	//Inicializa o vetor das ultimas celulas das colunas (as que estao mais abaixo):
	ultimasCelulasColunas = (CelulaMatriz**) calloc(maxColunas, sizeof(CelulaMatriz*));

	//Inicializa as linhas cabecas da matriz esparsa:
	celulaLinha = matriz;
	for (i = 0; i < maxLinhas; i++) {
		celulaLinha->abaixo = criarCelula(i, -1, -1, NULL, matriz);
		celulaLinha = celulaLinha->abaixo;
	}

	//Inicializa as colunas cabecas da matriz esparsa:
	celulaColuna = matriz;
	for (j = 0; j < maxColunas; j++) {
		celulaColuna->direita = criarCelula(-1, j, -1, matriz, NULL);
		celulaColuna = celulaColuna->direita;
		ultimasCelulasColunas[j] = celulaColuna;
	}

	printf(" => Preencha os elementos da matriz. Os elementos com valor 0 nao serao armazenados. \n");
	celulaLinha = matriz;
	for (i = 0; i < maxLinhas; i++) {
		celulaLinha = celulaLinha->abaixo; //Atribui a linha que sera percorrida
		celulaColuna = celulaLinha; //Atribui o inicio da coluna que sera percorrida
		for (j = 0; j < maxColunas; j++) {
			printf("Digite o elemento [%d][%d]: ", i + 1, j + 1);
			scanf("%f", &valor);
			if (valor != 0) {
				/* Cria a celula fazendo com que o proximo da direita seja o inicio da
				 * linha (cabeca) e o proximo abaixo seja o proximo abaixo da celula acima.
				 */
				celula = criarCelula(i, j, valor, celulaLinha, ultimasCelulasColunas[j]);
				celulaColuna->direita = celula;
				celulaColuna = celula;
				ultimasCelulasColunas[j]->abaixo = celula;
				ultimasCelulasColunas[j] = celula;
			}
		}
	}
	getchar();
	return matriz;
}

/**Imprime somente os elementos da matriz armazenados na memoria - os que nao sao 0.
 * Parametro: matriz - Matriz a ser exibida
 */
void imprimirMatriz(CelulaMatriz* matriz) {
	CelulaMatriz* linha = matriz->abaixo;
	CelulaMatriz* celula;
	int i = 1, j;

	while (linha != matriz) {
		j = 1;
		celula = linha->direita;
		while (celula != linha) {
			printf("Elemento [%d][%d]: %.2f \n", i, j, celula->valor);
			celula = celula->direita;
			j++;
		}
		linha = linha->abaixo;
		i++;
	}
}

/**Imprime os elementos da matriz armazenados na memoria incluindo os 0's nas posicoes onde devem estar.
 * Parametro: matriz - Matriz a ser exibida
 */
void imprimirMatrizFormatada(CelulaMatriz* matriz) {
	CelulaMatriz* linha = matriz->abaixo;
	CelulaMatriz* celula;
	int i = 1, j = 1;

	for (i = 0; i < matriz->linha; i++) {
		celula = linha->direita;
		for (j = 0; j < matriz->coluna; j++) {
			if (celula->coluna == j) {
				printf("\t%.2f", celula->valor);
				celula = celula->direita;
			} else {
				printf("\t 0");
			}
		}
		linha = linha->abaixo;
		printf("\n");
	}
}

/**Apaga a matriz esparsa devolvendo para a memoria o espaco ocupado por todos os elementos.
 * @Parametro: matriz - Matriz a ser apagada
 */
void apagarMatriz(CelulaMatriz* matriz) {
	CelulaMatriz* linha = matriz->abaixo;
	CelulaMatriz* coluna;
	CelulaMatriz* celulaAux;

	while (linha != matriz) {
		printf("\nl< ");
		coluna = linha->direita;
		//Apaga as colunas da linha:
		while (coluna != linha) {
			printf("%.2f ", coluna->valor);
			celulaAux = coluna->direita;
			free(coluna);
			coluna = celulaAux;
		}
		printf(">");
		//Apaga a cabeca da linha:
		celulaAux = linha->abaixo;
		free(linha);
		linha = celulaAux;
	}
	//Apaga as cabecas das colunas:
	coluna = matriz->direita;
	printf("\n  ");
	while (coluna != matriz) {
		printf("c ");
		celulaAux = coluna->direita;
		free(coluna);
		coluna = celulaAux;
	}
	//Apaga o noh cabeca da matriz:
	free(matriz);
}

/**Soma duas matrizes A e B retornando a matriz resultante da soma.
 * @Parametro: matrizA - Matriz A
 * @Parametro: matrizB - Matriz B
 * @Retorno: Matriz resultante da soma Matriz A + Matriz B
 */
CelulaMatriz* somarMatrizes(CelulaMatriz* matrizA, CelulaMatriz* matrizB) {
	CelulaMatriz* celulaMatrizA = matrizA;
	CelulaMatriz* celulaMatrizB = matrizB;
	CelulaMatriz* matrizC = criarCelulaVazia(NULL, NULL);
	CelulaMatriz* celula = NULL;
	CelulaMatriz* celulaColuna, * celulaLinha;
	CelulaMatriz** ultimasCelulasColunas = NULL; //Vetor contendo as ultimas celulas das colunas

	int i, j;
	float valor;

	//Armazena no noh cabeca da matriz o numero de linhas e colunas:
	matrizC->linha = maximo(matrizA->linha, matrizB->linha);
	matrizC->coluna = maximo(matrizA->coluna, matrizB->coluna);

	//Inicializa o vetor das ultimas celulas das linhas:
	ultimasCelulasColunas = (CelulaMatriz**) calloc(matrizC->coluna, sizeof(CelulaMatriz*));

	//Inicializa as linhas cabecas da matriz esparsa:
	celulaLinha = matrizC;
	for (i = 0; i < matrizC->linha; i++) {
		celulaLinha->abaixo = criarCelula(i, -1, -1, NULL, matrizC);
		celulaLinha = celulaLinha->abaixo;
	}

	//Inicializa as colunas cabecas da matriz esparsa:
	celulaColuna = matrizC;
	for (j = 0; j < matrizC->coluna; j++) {
		celulaColuna->direita = criarCelula(-1, j, -1, matrizC, NULL);
		celulaColuna = celulaColuna->direita;
		ultimasCelulasColunas[j] = celulaColuna;
	}

	celulaLinha = matrizC;
	for (i = 0; i < matrizC->linha; i++) {
		celulaLinha = celulaLinha->abaixo; //Atribui a linha que sera percorrida
		celulaColuna = celulaLinha; //Atribui o inicio da coluna que sera percorrida
		//Verifica se a matriz ja terminou de ser lida:
		if (celulaMatrizA->abaixo != matrizA) {
			celulaMatrizA = celulaMatrizA->abaixo->direita;
		}
		if (celulaMatrizB->abaixo != matrizB) {
			celulaMatrizB = celulaMatrizB->abaixo->direita;
		}

		for (j = 0; j < matrizC->coluna; j++) {
			valor = 0;
			if (celulaMatrizA->coluna == j) {
				valor += celulaMatrizA->valor;
				celulaMatrizA = celulaMatrizA->direita;
			}
			if (celulaMatrizB->coluna == j) {
				valor += celulaMatrizB->valor;
				celulaMatrizB = celulaMatrizB->direita;
			}
			if (valor != 0) {
				/* Cria a celula fazendo com que o proximo da direita seja o inicio da
				 * linha (cabeca) e o proximo abaixo seja o proximo abaixo da celula acima.
				 */
				celula = criarCelula(i, j, valor, celulaLinha, ultimasCelulasColunas[j]);
				celulaColuna->direita = celula;
				celulaColuna = celula;
				ultimasCelulasColunas[j]->abaixo = celula;
				ultimasCelulasColunas[j] = celula;
			}
		}
	}
	return matrizC;
}

/**Multiplicacao de duas matrizes A e B retornando a matriz resultante da multiplicacao.
 * @Parametro: matrizA - Matriz A
 * @Parametro: matrizB - Matriz B
 * @Retorno: Matriz resultante da multiplicacao Matriz A x Matriz B
 */
CelulaMatriz* multiplicarMatrizes(CelulaMatriz* matrizA, CelulaMatriz* matrizB) {
	CelulaMatriz* celulaMatrizA = matrizA;
	CelulaMatriz* celulaMatrizB = matrizB;
	CelulaMatriz* matrizC = criarCelulaVazia(NULL, NULL);
	CelulaMatriz* celula = NULL;
	CelulaMatriz* celulaColuna, * celulaLinha;
	CelulaMatriz** ultimasCelulasColunas = NULL; //Vetor contendo as ultimas celulas das colunas

	int i, j;
	float valor;

	//Armazena no noh cabeca da matriz o numero de linhas e colunas:
	matrizC->linha = maximo(matrizA->linha, matrizB->linha);
	matrizC->coluna = maximo(matrizA->coluna, matrizB->coluna);

	//Inicializa o vetor das ultimas celulas das linhas:
	ultimasCelulasColunas = (CelulaMatriz**) calloc(matrizC->coluna, sizeof(CelulaMatriz*));

	//Inicializa as linhas cabecas da matriz esparsa:
	celulaLinha = matrizC;
	for (i = 0; i < matrizC->linha; i++) {
		celulaLinha->abaixo = criarCelula(i, -1, -1, NULL, matrizC);
		celulaLinha = celulaLinha->abaixo;
	}

	//Inicializa as colunas cabecas da matriz esparsa:
	celulaColuna = matrizC;
	for (j = 0; j < matrizC->coluna; j++) {
		celulaColuna->direita = criarCelula(-1, j, -1, matrizC, NULL);
		celulaColuna = celulaColuna->direita;
		ultimasCelulasColunas[j] = celulaColuna;
	}

	celulaLinha = matrizC;
	for (i = 0; i < matrizC->linha; i++) {
		celulaLinha = celulaLinha->abaixo; //Atribui a linha que sera percorrida
		celulaColuna = celulaLinha; //Atribui o inicio da coluna que sera percorrida
		//Verifica se a matriz ja terminou de ser lida:
		if (celulaMatrizA->abaixo != matrizA) {
			celulaMatrizA = celulaMatrizA->abaixo->direita;
		}
		if (celulaMatrizB->abaixo != matrizB) {
			celulaMatrizB = celulaMatrizB->abaixo->direita;
		}

		for (j = 0; j < matrizC->coluna; j++) {
			valor = 0;
			if (celulaMatrizA->coluna == j) {
				valor += celulaMatrizA->valor;
				celulaMatrizA = celulaMatrizA->direita;
			}
			if (celulaMatrizB->coluna == j) {
				valor += celulaMatrizB->valor;
				celulaMatrizB = celulaMatrizB->direita;
			}
			if (valor != 0) {
				/* Cria a celula fazendo com que o proximo da direita seja o inicio da
				 * linha (cabeca) e o proximo abaixo seja o proximo abaixo da celula acima.
				 */
				celula = criarCelula(i, j, valor, celulaLinha, ultimasCelulasColunas[j]);
				celulaColuna->direita = celula;
				celulaColuna = celula;
				ultimasCelulasColunas[j]->abaixo = celula;
				ultimasCelulasColunas[j] = celula;
			}
		}
	}
	return matrizC;
}

/**Retorna o maior valor de dois inteiros.
 * @Parametro: x - Valor x
 * @Parametro: y - Valor y
 * @Retorno: Retorna o maior dos valores x e y.
 */
int maximo(int x, int y) {
	if (x > y) {
		return x;
	} else {
		return y;
	}
}

/**Pergunta ao usuario qual das duas matrizes sera utilizada para uma determinada operacao.
 * @Parametro: matriz1 - Matriz 1
 * @Parametro: matriz2 - Matriz 2
 * @Retorno: Matriz escolhida pelo usuario
 */
CelulaMatriz* solicitarEscolhaMatriz(CelulaMatriz* matriz1, CelulaMatriz* matriz2) {
	int numeroMatriz;
	do {
		printf("Informe qual matriz deseja utilizar (1 ou 2): ");
		scanf("%d", &numeroMatriz);
		getchar();
	} while (numeroMatriz != 1 && numeroMatriz != 2);

	if (numeroMatriz == 1) {
		return matriz1;
	} else {
		return matriz2;
	}
}

/**Verifica se uma matriz esta criada e exibe uma mensagem caso nao tenha sido criada.
 * @Parametro: matriz - Matriz a ser verificada
 * @Retorno: Retorna 1 caso a matriz foi criada ou 0 caso nao foi criada
 */
short verificarMatrizCriada(CelulaMatriz* matriz) {
	if (matriz == NULL) {
		printf(" => Voce deve preencher a matriz antes de utiliza-la!\n");
		return 0;
	}
	return 1;
}

/**Exibe uma pausa na tela.
 */
void solicitarPausa() {
	printf("\nPressione [ENTER] para continuar.\n");
	getchar();
}

int main(void) {
	int opcao, numeroAux;
	CelulaMatriz* matriz1 = NULL;
	CelulaMatriz* matriz2 = NULL;
	CelulaMatriz* matrizA;
	CelulaMatriz* matrizB;

	do {
		system(COMANDO_LIMPAR_CONSOLE);
		printf(" * Existem duas matrizes criadas na memoria.\n Para algumas operacoes eh "
			"necessario informar a matriz que sera utilizada.\n Outras operacoes "
			"utilizarao as duas matrizes simultaneamente.\n\n");
		printf("=== MATRIZES ESPARSAS === \n");
		printf(" 1 - Ler Matriz (Matriz 1 ou Matriz 2) \n");
		printf(" 2 - Imprimir Matriz (Matriz 1 ou Matriz 2) \n");
		printf(" 3 - Imprimir Matriz Formatada (Matriz 1 ou Matriz 2) \n");
		printf(" 4 - Apagar Matriz (Matriz 1 ou Matriz 2) \n");
		printf(" 5 - Somar Matrizes \n");
		printf(" 6 - Multiplicar Matrizes \n");
		printf(" 0 - Finalizar \n");
		printf(" => Digite a opcao: ");
		scanf("%d", &opcao);
		getchar();
		printf("\n");

		//Verifica se digitou uma opcao invalida:
		if (opcao < 0 || opcao > 6) {
			printf(" => Opcao invalida!\n");
			solicitarPausa();
			continue;
		}

		switch (opcao) {
		case 1:
			do {
				printf("Informe qual matriz deseja preencher (1 ou 2): ");
				scanf("%d", &numeroAux);
				getchar();
			} while (numeroAux != 1 && numeroAux != 2);
			printf("=> Leitura da Matriz Esparsa %d \n", numeroAux);
			if (numeroAux == 1) {
				matriz1 = lerMatriz();
			} else {
				matriz2 = lerMatriz();
			}

			break;
		case 2:
			matrizA = solicitarEscolhaMatriz(matriz1, matriz2);
			if (verificarMatrizCriada(matrizA) == 1) {
				printf(" => Exibicao da Matriz (somente elementos armazenados - nao 0): \n");
				imprimirMatriz(matrizA);
			}

			break;
		case 3:
			matrizA = solicitarEscolhaMatriz(matriz1, matriz2);
			if (verificarMatrizCriada(matrizA) == 1) {
				printf(" => Exibicao da Matriz (todos os elementos): \n");
				imprimirMatrizFormatada(matrizA);
			}

			break;
		case 4:
			matrizA = solicitarEscolhaMatriz(matriz1, matriz2);
			if (verificarMatrizCriada(matrizA) == 1) {
				if (matriz1 == matrizA) {
					apagarMatriz(matriz1);
					matriz1 = NULL;
				} else {
					apagarMatriz(matriz2);
					matriz2 = NULL;
				}
				free(matrizA);
				printf(" => Matriz apagada com sucesso!\n");
			}

			break;
		case 5:
			printf(" => Defina as matrizes A e B utilizadas na soma A + B: \n");
			printf("Matriz A: ");
			matrizA = solicitarEscolhaMatriz(matriz1, matriz2);
			printf("Matriz B: ");
			matrizB = solicitarEscolhaMatriz(matriz1, matriz2);

			//Verifica se as duas matrizes estao criadas:
			if (verificarMatrizCriada(matrizA) == 1 && verificarMatrizCriada(matrizB) == 1) {
				printf("\n => Matriz A: \n");
				imprimirMatrizFormatada(matrizA);
				printf("\n => Matriz B: \n");
				imprimirMatrizFormatada(matrizB);
				printf("\n => Soma A + B: \n");
				//Soma as matriz e imprime a matriz resultante:
				imprimirMatrizFormatada(somarMatrizes(matrizA, matrizB));
			}

			break;
		case 6:
			printf(" => Defina as matrizes A e B utilizadas na multiplicacao A * B: \n");
			printf("Matriz A: ");
			matrizA = solicitarEscolhaMatriz(matriz1, matriz2);
			printf("Matriz B: ");
			matrizB = solicitarEscolhaMatriz(matriz1, matriz2);

			//Verifica se as duas matrizes estao criadas:
			if (verificarMatrizCriada(matrizA) == 1 && verificarMatrizCriada(matrizB) == 1) {
				printf("\n => Matriz A: \n");
				imprimirMatrizFormatada(matrizA);
				printf("\n => Matriz B: \n");
				imprimirMatrizFormatada(matrizB);
				printf("\n => Multiplicacao A * B: \n");
				//Soma as matriz e imprime a matriz resultante:
				imprimirMatrizFormatada(multiplicarMatrizes(matrizA, matrizB));
			}

			break;
		}

		if (opcao != 0) {
			solicitarPausa();
		}
	} while (opcao != 0);

	return EXIT_SUCCESS;
}
