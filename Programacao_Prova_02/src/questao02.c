/*
 ============================================================================
 Arquivo     : Programação - Prova 02 - Questao 02 (Árvore Genealógica)
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_STRING 100
#define COMANDO_LIMPAR_CONSOLE "cls" //Para Windows: "cls" ; Para Linux: "clear"

typedef struct Arvore {
	char nome[TAMANHO_STRING];
	char nomeConjuge[TAMANHO_STRING];
	struct Arvore** filhos; //Lista contendo os filhos do noh.
	int quantidadeFilhos; //Quantidade de filhos
} Arvore;

void lerDadosArvore(Arvore* raiz, int nivel);
void carregarArvoreArquivo(FILE* arquivo, Arvore* raiz, int nivel);
void salvarArvoreArquivo(FILE* arquivo, Arvore* raiz, int nivel);
void imprimirArvore(Arvore* raiz, int nivel);
short exibirPais(Arvore* raiz, char* nome);
short exibirFilhos(Arvore* raiz, char* nome);
short exibirAvos(Arvore* raiz, char* nome);
short exibirNetos(Arvore* raiz, char* nome);
short exibirTios(Arvore* raiz, char* nome);
short exibirPrimos(Arvore* raiz, char* nome);
char* solicitarNome();
void solicitarPausa();

/**Solicita a entrada de dados do usuario para criacao da Arvore Genealogica.
 * @Parametro: raiz - Ponteiro para a raiz de uma Arvore.
 * @Parametro: nivel - Nivel do noh raiz. Para chamada inicial, passar o valor 1.
 */
void lerDadosArvore(Arvore* raiz, int nivel) {
	char identacao[nivel - 1];
	strcpy(identacao, "");
	int i;
	//Constroi a string de identacao:
	for (i = 0; i < nivel; i++) {
		strcat(identacao, "|");
	}
	printf("%s-Geracao %d \n", identacao, nivel);

	do {
		printf("%s Nome da pessoa: ", identacao);
		gets(raiz->nome);
	} while (strlen(raiz->nome) == 0);

	printf("%s Nome do conjuge (deixe em branco caso nao tenha): ", identacao);
	gets(raiz->nomeConjuge);

	raiz->filhos = NULL;
	raiz->quantidadeFilhos = 0;
	//Caso seja um casal, faz a leitura dos filhos:
	if (strlen(raiz->nomeConjuge) > 0) {
		int contador = 0;
		char lerFilho;
		do {
			do {//Pergunta se o casal quer registrar filho:
				printf("%s Deseja registrar filho? ('s' ou 'n'): ", identacao);
				scanf("%c", &lerFilho);
				getchar();
			} while (lerFilho != 's' && lerFilho != 'S' && lerFilho != 'n' && lerFilho != 'N');

			if (lerFilho == 's' || lerFilho == 'S') {
				//Chamar recursivo para a geração dos filhos:
				Arvore* filho = malloc(sizeof(Arvore));
				lerDadosArvore(filho, nivel + 1);

				//Adiciona o filho no vetor:
				if (raiz->filhos == NULL) {
					raiz->filhos = (Arvore**) calloc(1, sizeof(Arvore*));
				} else {
					raiz->filhos = (Arvore**) realloc(raiz->filhos, sizeof(raiz->filhos) + sizeof(Arvore*));
				}
				raiz->filhos[contador] = filho;
				contador++;
			}
		} while (lerFilho == 's' || lerFilho == 'S');

		raiz->quantidadeFilhos = contador;
	}
}

/**Carrega uma Arvore Genealogica a partir de um arquivo.
 * @Parametro: arquivo - Ponteiro para o arquivo.
 * @Parametro: raiz - Ponteiro para a raiz de uma Arvore.
 * @Parametro: nivel - Nivel do noh raiz. Para chamada inicial, passar o valor 1.
 */
void carregarArvoreArquivo(FILE* arquivo, Arvore* raiz, int nivel) {
	if (feof(arquivo)) {
		return;
	}
	int i;

	strcpy(raiz->nome, ""); //Limpa o nome.
	strcpy(raiz->nomeConjuge, ""); //Limpa o nome do conjuge.
	raiz->quantidadeFilhos = 0;
	raiz->filhos = NULL;

	/* Le um noh:
	 * Detalhes da formatacao:
	 * 	- "%*[|]" => Le a identacao de '|' do arquivo e descarta.
	 * 	- "%[ a-zA-Z]" => Le o nome da pessoa
	 * 	- "_&_" => Le o separador entre o nome da pessoa e o nome do conjuge (se houver)
	 *  - "%[ a-zA-Z]" => Le o nome do conjuge da pessoa (se houver)
	 *  - ";%d" => Le o separador ';' apos o nome do conjuge e o numero de filhos do casal (se houverem)
	 */
	fscanf(arquivo, "%*[|]%[ a-zA-Z]_&_%[ a-zA-Z];%d", raiz->nome, raiz->nomeConjuge, &raiz->quantidadeFilhos);
	fscanf(arquivo, "\n"); //Passa pra proxima linha do arquivo

	if (raiz->quantidadeFilhos > 0) {
		//Aloca o vetor de filhos:
		raiz->filhos = (Arvore**) calloc(raiz->quantidadeFilhos, sizeof(Arvore*));
	}

	//Se tiver filhos, le os filhos:
	for (i = 0; i < raiz->quantidadeFilhos; i++) {
		//Aloca o filho:
		raiz->filhos[i] = malloc(sizeof(Arvore));
		carregarArvoreArquivo(arquivo, raiz->filhos[i], nivel + 1);
	}
}

/**Salva uma Arvore Genealogica a partir em um arquivo.
 * @Parametro: arquivo - Ponteiro para o arquivo.
 * @Parametro: raiz - Ponteiro para a raiz de uma Arvore.
 * @Parametro: nivel - Nivel do noh raiz. Para chamada inicial, passar o valor 1.
 */
void salvarArvoreArquivo(FILE* arquivo, Arvore* raiz, int nivel) {
	if (raiz == NULL) {
		return;
	}
	char identacao[nivel - 1];
	strcpy(identacao, "");
	int i;
	//Constroi a string de identacao:
	for (i = 0; i < nivel; i++) {
		strcat(identacao, "|");
	}

	fprintf(arquivo, "%s%s", identacao, raiz->nome);
	if (strlen(raiz->nomeConjuge) > 0) {
		fprintf(arquivo, "_&_%s", raiz->nomeConjuge);
		if (raiz->quantidadeFilhos > 0) {
			fprintf(arquivo, ";%d", raiz->quantidadeFilhos);
		}
	}
	fprintf(arquivo, "\n");

	for (i = 0; i < raiz->quantidadeFilhos; i++) {
		salvarArvoreArquivo(arquivo, raiz->filhos[i], nivel + 1);
	}
}

/**Imprime uma Arvore Genealogica:
 * @Parametro: raiz - Ponteiro para a raiz de uma Arvore.
 * @Parametro: nivel - Nivel do noh raiz. Para chamada inicial, passar o valor 1.
 */
void imprimirArvore(Arvore* raiz, int nivel) {
	if (raiz == NULL) {
		return;
	}
	char identacao[nivel - 1];
	strcpy(identacao, "");
	int i;
	for (i = 1; i < nivel; i++) {
		strcat(identacao, "|");
	}
	if (strlen(raiz->nomeConjuge) == 0) {
		printf("%s+%s \n", identacao, raiz->nome);
	} else {
		printf("%s-%s & %s \n", identacao, raiz->nome, raiz->nomeConjuge);
	}

	if (raiz->filhos != NULL) {
		int i;
		for (i = 0; i < raiz->quantidadeFilhos; i++) {
			imprimirArvore(raiz->filhos[i], nivel + 1);
		}
	}
}

/**Exibe os pais de uma pessoa, se estivere na Arvore.
 * @Parametro: raiz - Raiz da Arvore.
 * @Parametro: nome - Nome da pessoa que tem os pais procurados na Arvore.
 * @Retorno: 1 - caso tenha encontrado a pessoa. 0 - caso nao tenha encontrado.
 */
short exibirPais(Arvore* raiz, char* nome) {
	int i;
	//Procura nos filhos do noh 'raiz' pela pessoa. Se achar, entao os pais sao noh 'raiz'
	for (i = 0; i < raiz->quantidadeFilhos; i++) {
		if (strcmp(raiz->filhos[i]->nome, nome) == 0) {
			printf(" => Os pais de %s sao %s e %s \n", nome, raiz->nome, raiz->nomeConjuge);
			return 1;
		}
	}
	//Chama recursivamente para procurar a pessoa nos niveis abaixo da Arvore:
	for (i = 0; i < raiz->quantidadeFilhos; i++) {
		//Verifica se encontrou na chamada recursiva para nao continuar a busca:
		short resultadoRecursivo = exibirPais(raiz->filhos[i], nome);
		if (resultadoRecursivo == 1) {
			return 1; //Retorna 1 indicando que ja encontrou a pessoa.
		}
	}
	//Nao encontrou:
	return 0;
}

/**Exibe os filhos de uma pessoa, se estivere na Arvore.
 * @Parametro: raiz - Raiz da Arvore.
 * @Parametro: nome - Nome da pessoa que tem os filhos procurados na Arvore.
 * @Retorno: 1 - caso tenha encontrado a pessoa. 0 - caso nao tenha encontrado.
 */
short exibirFilhos(Arvore* raiz, char* nome) {
	int i;
	//Verifica se o nome da pessoa procurada esta no noh raiz atual.
	if (strcmp(raiz->nome, nome) == 0 || strcmp(raiz->nomeConjuge, nome) == 0) {
		//Verifica se a pessoa eh casada:
		if (strlen(raiz->nomeConjuge) == 0) {
			printf(" => %s nao eh casado(a).\n", raiz->nome);
		} else if (raiz->quantidadeFilhos == 0) { //Verifica se a pessoa possui filhos:
			printf(" => %s e %s nao possuem filhos.\n", raiz->nome, raiz->nomeConjuge);
		} else {
			//Itera pelos filhos exibindo-os:
			printf(" => Os filhos de %s e %s sao: \n", raiz->nome, raiz->nomeConjuge);
			for (i = 0; i < raiz->quantidadeFilhos; i++) {
				printf("     - %s \n", raiz->filhos[i]->nome);
			}
		}
		return 1; //Retorna 1 indicando que ja encontrou a pessoa.
	} else if (raiz->quantidadeFilhos > 0) {
		for (i = 0; i < raiz->quantidadeFilhos; i++) {
			//Verifica se encontrou na chamada recursiva para nao continuar a busca:
			short resultadoRecursivo = exibirFilhos(raiz->filhos[i], nome);
			if (resultadoRecursivo == 1) {
				return 1;
			} //Caso nao tenha encontrado continua a busca.
		}
	}
	//Nao encontrou:
	return 0;
}

/**Exibe os avos de uma pessoa, se estivere na Arvore.
 * @Parametro: raiz - Raiz da Arvore.
 * @Parametro: nome - Nome da pessoa que tem os avos procurados na Arvore.
 * @Retorno: 1 - caso tenha encontrado a pessoa. 0 - caso nao tenha encontrado.
 */
short exibirAvos(Arvore* raiz, char* nome) {
	int i, j;
	Arvore* filho;
	//Procura nos netos do noh 'raiz' pela pessoa. Se achar, entao os avos sao noh 'raiz'
	for (i = 0; i < raiz->quantidadeFilhos; i++) {
		filho = raiz->filhos[i];
		for (j = 0; j < filho->quantidadeFilhos; j++) {
			if (strcmp(filho->filhos[j]->nome, nome) == 0) {
				printf(" => Os avos de %s sao %s e %s \n", nome, raiz->nome, raiz->nomeConjuge);
				return 1;
			}
		}
	}
	//Chama recursivamente para procurar a pessoa nos niveis abaixo da Arvore:
	for (i = 0; i < raiz->quantidadeFilhos; i++) {
		//Verifica se encontrou na chamada recursiva para nao continuar a busca:
		short resultadoRecursivo = exibirAvos(raiz->filhos[i], nome);
		if (resultadoRecursivo == 1) {
			return 1; //Retorna 1 indicando que ja encontrou a pessoa.
		}
	}
	//Nao encontrou:
	return 0;
}

/**Exibe os netos de uma pessoa, se estivere na Arvore.
 * @Parametro: raiz - Raiz da Arvore.
 * @Parametro: nome - Nome da pessoa que tem os netos procurados na Arvore.
 * @Retorno: 1 - caso tenha encontrado a pessoa. 0 - caso nao tenha encontrado.
 */
short exibirNetos(Arvore* raiz, char* nome) {
	int i, j;
	Arvore* filho;
	int possuiNetos = 0;
	//Verifica se o nome da pessoa procurada esta no noh raiz atual.
	if (strcmp(raiz->nome, nome) == 0 || strcmp(raiz->nomeConjuge, nome) == 0) {
		//Verifica se a pessoa eh casada:
		if (strlen(raiz->nomeConjuge) == 0) {
			printf(" => %s nao eh casado(a).\n", raiz->nome);
		} else {
			//Verifica se a pessoa possui netos:
			for (i = 0; i < raiz->quantidadeFilhos; i++) {
				if (raiz->filhos[i]->quantidadeFilhos > 0) {
					possuiNetos = 1;
					break;
				}
			}
			if (possuiNetos == 0) {
				printf(" => %s e %s nao possuem netos.\n", raiz->nome, raiz->nomeConjuge);
			} else {
				//Itera pelos netos exibindo-os:
				printf(" => Os netos de %s e %s sao: \n", raiz->nome, raiz->nomeConjuge);
				for (i = 0; i < raiz->quantidadeFilhos; i++) {
					filho = raiz->filhos[i];
					for (j = 0; j < filho->quantidadeFilhos; j++) {
						printf("     - %s \n", filho->filhos[j]->nome);
					}
				}
			}
		}
		return 1; //Retorna 1 indicando que ja encontrou a pessoa.
	} else if (raiz->quantidadeFilhos > 0) {
		for (i = 0; i < raiz->quantidadeFilhos; i++) {
			//Verifica se encontrou na chamada recursiva para nao continuar a busca:
			short resultadoRecursivo = exibirNetos(raiz->filhos[i], nome);
			if (resultadoRecursivo == 1) {
				return 1;
			} //Caso nao tenha encontrado continua a busca.
		}
	}
	//Nao encontrou:
	return 0;
}

/**Exibe os tios de uma pessoa, se estivere na Arvore.
 * @Parametro: raiz - Raiz da Arvore.
 * @Parametro: nome - Nome da pessoa que tem os tios procurados na Arvore.
 * @Retorno: 1 - caso tenha encontrado a pessoa. 0 - caso nao tenha encontrado.
 */
short exibirTios(Arvore* raiz, char* nome) {
	int i, j;
	int encontrouPessoa = 0;
	Arvore* paiPessoa;
	Arvore* tio;

	/* Procura nos netos do noh 'raiz' pela pessoa. Se achar, entao os tios
	 * sao os filhos de 'raiz' exceto os pais da pessoa procurada.
	 */
	for (i = 0; i < raiz->quantidadeFilhos; i++) {
		paiPessoa = raiz->filhos[i];
		for (j = 0; j < paiPessoa->quantidadeFilhos; j++) {
			//Verifica se encontrou a pessoa:
			if (strcmp(paiPessoa->filhos[j]->nome, nome) == 0) {
				encontrouPessoa = 1;
				break;
			}
		}
		if (encontrouPessoa) {//Para a iteracao se tiver encontrado a pessoa.
			break;
		}
	}

	//Se encontrou a pessoa, exibe os tios dela, se houverem:
	if (encontrouPessoa) {
		if (raiz->quantidadeFilhos == 1) {
			printf(" => %s nao possui tios.\n", nome);
		} else {
			printf(" => Os tios de %s sao: \n", nome);
			//Itera pelos tios da pessoa (filhos do avo, exceto os pais da pessoa):
			for (i = 0; i < raiz->quantidadeFilhos; i++) {
				tio = raiz->filhos[i];
				if (tio == paiPessoa) {//Se eh o pai da pessoa, pula.
					continue;
				}
				printf("     - %s \n", tio->nome);
				if (strlen(tio->nomeConjuge) > 0) {
					printf("     - %s \n", tio->nomeConjuge);
				}
			}
		}
		return 1;
	}

	//Chama recursivamente para procurar a pessoa nos niveis abaixo da Arvore:
	for (i = 0; i < raiz->quantidadeFilhos; i++) {
		//Verifica se encontrou na chamada recursiva para nao continuar a busca:
		short resultadoRecursivo = exibirTios(raiz->filhos[i], nome);
		if (resultadoRecursivo == 1) {
			return 1; //Retorna 1 indicando que ja encontrou a pessoa.
		}
	}
	//Nao encontrou:
	return 0;
}

/**Exibe os primos de primeiro grau de uma pessoa, se estivere na Arvore.
 * @Parametro: raiz - Raiz da Arvore.
 * @Parametro: nome - Nome da pessoa que tem os primos procurados na Arvore.
 * @Retorno: 1 - caso tenha encontrado a pessoa. 0 - caso nao tenha encontrado.
 */
short exibirPrimos(Arvore* raiz, char* nome) {
	int i, j;
	int encontrouPessoa = 0;
	int possuiNetos = 0;
	Arvore* paiPessoa = NULL;
	Arvore* tio;

	/* Procura nos netos do noh 'raiz' pela pessoa. Se achar, entao os primos
	 * sao os filhos dos filhos de 'raiz' exceto os irmaos da pessoa.
	 */
	for (i = 0; i < raiz->quantidadeFilhos; i++) {
		paiPessoa = raiz->filhos[i];
		for (j = 0; j < paiPessoa->quantidadeFilhos; j++) {
			//Verifica se encontrou a pessoa:
			if (strcmp(paiPessoa->filhos[j]->nome, nome) == 0) {
				encontrouPessoa = 1;
				break;
			}
		}
		if (encontrouPessoa) {//Para a iteracao se tiver encontrado a pessoa.
			break;
		}
	}

	//Se encontrou a pessoa, exibe os primos dela, se houverem:
	if (encontrouPessoa) {
		for (i = 0; i < raiz->quantidadeFilhos; i++) {
			if (raiz->filhos[i]->quantidadeFilhos > 0) {
				possuiNetos = 1;
			}
		}
		if (possuiNetos == 0) {
			printf(" => %s nao possui primos.\n", nome);
		} else {
			printf(" => Os primos de %s sao: \n", nome);
			//Itera pelos tios da pessoa (filhos do avo, exceto os pais da pessoa):
			for (i = 0; i < raiz->quantidadeFilhos; i++) {
				tio = raiz->filhos[i];
				if (tio == paiPessoa) {//Se eh o pai da pessoa, pula.
					continue;
				}
				for (j = 0; j < tio->quantidadeFilhos; j++) {
					printf("     - %s \n", tio->filhos[j]->nome);
				}
			}
		}

		return 1;
	}

	//Chama recursivamente para procurar a pessoa nos niveis abaixo da Arvore:
	for (i = 0; i < raiz->quantidadeFilhos; i++) {
		//Verifica se encontrou na chamada recursiva para nao continuar a busca:
		short resultadoRecursivo = exibirPrimos(raiz->filhos[i], nome);
		if (resultadoRecursivo == 1) {
			return 1; //Retorna 1 indicando que ja encontrou a pessoa.
		}
	}
	//Nao encontrou:
	return 0;
}

/**Solicita a digitacao do nome de uma pessoa.
 * @Retorno: Nome da pessoa digitada.
 */
char* solicitarNome() {
	char* nome = calloc(TAMANHO_STRING, sizeof(char));
	do {
		printf("Digite o nome da pessoa: ");
		gets(nome);
	} while (strlen(nome) == 0);
	printf("\n");
	return nome;
}

/**Exibe uma pausa na tela.
 */
void solicitarPausa() {
	printf("\nPressione [ENTER] para continuar.\n");
	getchar();
}

int main(void) {
	int opcao, retornoAux;
	Arvore* raiz = NULL;
	char* nomeAux = NULL;
	FILE* arquivo;
	do {
		system(COMANDO_LIMPAR_CONSOLE);
		printf("=== ARVORE GENEALOGICA === \n");
		printf(" 1 - Criar nova Arvore Genealogica \n");
		printf(" 2 - Ler Arvore Genealogica de um arquivo \n");
		printf(" 3 - Salvar Arvore Genealogica em um arquivo \n");
		printf(" 4 - Imprimir Arvore Genealogica \n");
		printf(" 5 - Exibir pais de uma pessoa \n");
		printf(" 6 - Exibir filhos de uma pessoa \n");
		printf(" 7 - Exibir avos de uma pessoa \n");
		printf(" 8 - Exibir netos de uma pessoa \n");
		printf(" 9 - Exibir tios de uma pessoa \n");
		printf(" 10 - Exibir primos de primeiro grau de uma pessoa \n");
		printf(" 0 - Finalizar \n");
		printf(" => Digite a opcao: ");
		scanf("%d", &opcao);
		getchar();
		printf("\n");

		//Verifica se digitou uma opcao invalida:
		if (opcao < 0 || opcao > 10) {
			printf("Opcao invalida!\n");
			solicitarPausa();
			continue;
		} else if (raiz == NULL && opcao >= 3 && opcao <= 10) {
			printf(" => Voce deve criar ou ler de um arquivo uma Arvore Genealogica "
				"antes de utilizar as operacoes de 3 a 9!\n");
			solicitarPausa();
			continue;
		}

		switch (opcao) {
		case 1:
			printf(" => Preencha a Arvore Genealogica: \n");
			raiz = malloc(sizeof(Arvore));
			lerDadosArvore(raiz, 1);

			printf(" => Fim da leitura.\n");

			break;
		case 2:
			printf("Nome do arquivo (Deixe em branco para usar 'arvore.txt'): ");
			nomeAux = calloc(TAMANHO_STRING, sizeof(char));
			gets(nomeAux);
			if (strlen(nomeAux) == 0) {
				nomeAux = "arvore.txt";
			}

			raiz = malloc(sizeof(Arvore));
			arquivo = fopen(nomeAux, "r");
			if (arquivo == NULL) {
				printf(" => Ocorreu um erro ao gravar o arquivo! O arquivo pode estar em uso ou nao existe.\n");
			} else {
				carregarArvoreArquivo(arquivo, raiz, 1);
				fclose(arquivo);
				//Verifica se a arvore esta vazia:
				if (strlen(raiz->nome) == 0) {
					printf(" => O arquivo esta corrompido ou vazio.\n");
					raiz = NULL;
				} else {
					printf(" => Arquivo '%s' carregado com sucesso!\n", nomeAux);
				}
			}
			break;
		case 3:
			printf("Nome do arquivo (Deixe em branco para usar 'arvore.txt'): ");
			nomeAux = calloc(TAMANHO_STRING, sizeof(char));
			gets(nomeAux);
			if (strlen(nomeAux) == 0) {
				nomeAux = "arvore.txt";
			}
			arquivo = fopen(nomeAux, "w");
			if (arquivo == NULL) {
				printf(" => Ocorreu um erro ao gravar o arquivo! O arquivo pode estar em uso.\n");
			} else {
				salvarArvoreArquivo(arquivo, raiz, 1);
				fclose(arquivo);
				printf(" => Arquivo '%s' salvo com sucesso!\n", nomeAux);
			}
			break;
		case 4:
			printf(" => Exibicao da Arvore Genealogica: \n");
			imprimirArvore(raiz, 1);
			break;
		case 5:
			nomeAux = solicitarNome();
			retornoAux = exibirPais(raiz, nomeAux);
			if (retornoAux == 0) {
				printf(" => %s nao esta na Arvore ou seus pais nao estao na Arvore.\n", nomeAux);
			}
			break;
		case 6:
			nomeAux = solicitarNome();
			retornoAux = exibirFilhos(raiz, nomeAux);
			if (retornoAux == 0) {
				printf(" => %s nao foi encontrado na Arvore.\n", nomeAux);
			}
			break;
		case 7:
			nomeAux = solicitarNome();
			retornoAux = exibirAvos(raiz, nomeAux);
			if (retornoAux == 0) {
				printf(" => %s nao esta na Arvore ou seus avos nao estao na Arvore.\n", nomeAux);
			}
			break;
		case 8:
			nomeAux = solicitarNome();
			retornoAux = exibirNetos(raiz, nomeAux);
			if (retornoAux == 0) {
				printf(" => %s nao foi encontrado na Arvore.\n", nomeAux);
			}
			break;
		case 9:
			nomeAux = solicitarNome();
			retornoAux = exibirTios(raiz, nomeAux);
			if (retornoAux == 0) {
				printf(" => %s nao foi encontrado na Arvore ou seus tios nao estao na Arvore.\n", nomeAux);
			}
			break;
		case 10:
			nomeAux = solicitarNome();
			retornoAux = exibirPrimos(raiz, nomeAux);
			if (retornoAux == 0) {
				printf(" => %s nao foi encontrado na Arvore ou seus primos nao estao na Arvore.\n", nomeAux);
			}
			break;
		}

		if (opcao != 0) {
			solicitarPausa();
		}
	} while (opcao != 0);

	return EXIT_SUCCESS;
}

/*
 * Questão 02. Construa um programa em linguagem C que permita definir uma árvore
 * genealógica e verificar relações de parentesco entre pessoas. O programa deverá
 * permitir que a árvore genealógica seja lida de um arquivo de texto ou montada pelo
 * usuário dinamicamente. Uma vez construída uma árvore genealógica, o programa
 * deverá permitir fazer as seguintes consultas, relativas a uma determinada pessoa:
 * (3,0 pontos)
 * 1. Quem são os pais da pessoa?
 * 2. Quem são os filhos da pessoa?
 * 3. Quem são os avós da pessoa?
 * 4. Quem são os netos da pessoa?
 * 5. Quem são os tios da pessoa?
 * 6. Quem são os primos de primeiro grau da pessoa?
 */
