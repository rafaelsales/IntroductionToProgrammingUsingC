/*
 ============================================================================
 Arquivo     : Programação - Prova 01 - Questao 01
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

//Define o comando utilizado para limpar o console (no Windows: "cls", no Linux "clear")
#define COMANDO_LIMPAR_CONSOLE "cls"

/**Estrutura principal da lista encadeada.
*  A partir dela obtemos o inicio da lista para itererar pelos seus elementos.
*/
typedef struct Lista_Encadeada {
	struct Lista_Encadeada_Node* primeiro;
} Lista_Encadeada;

//No de um elemento da lista:
typedef struct Lista_Encadeada_Node {
	int info;
	struct Lista_Encadeada_Node* prox;
} Lista_Encadeada_Node;

/**Struct contendo duas listas encadeadas, onde 'lista_menores'
 * possui todos os elementos menores que um certo numero 'n' e
 * 'lista_maiores' contem todos os elementos maiores que 'n':
 */
typedef struct Lista_Dividida {
	Lista_Encadeada* lista_menores;
	Lista_Encadeada* lista_maiores;
} ListaDividida;

//Operacoes da lista:
Lista_Encadeada* ListaEncadeada_Criar();
short ListaEncadeada_Inserir(Lista_Encadeada* listaEncadeada, int valor_inserir);
short ListaEncadeada_Remover(Lista_Encadeada* listaEncadeada, int valor_remover);
void ListaEncadeada_Imprimir(Lista_Encadeada* listaEncadeada);

int ListaEncadeada_CalcularComprimento(Lista_Encadeada* listaEncadeada);
int ListaEncadeada_ProcurarOcorrencias(Lista_Encadeada* listaEncadeada, int n_procurado);
int ListaEncadeada_Procurar_E_Substituir(Lista_Encadeada* listaEncadeada, int n_original, int n_novo);
ListaDividida* ListaEncadeada_DividirLista(Lista_Encadeada* listaEncadeada, int n_meio);
Lista_Encadeada* ListaEncadeada_ObterIntersecao(Lista_Encadeada* listaEncadeada_a, Lista_Encadeada* listaEncadeada_b);

/**Cria uma nova lista encadeada.
 * @Retorno: a estrutura da lista ou NULL caso tenha ocorrido erro na criacao.
 */
Lista_Encadeada* ListaEncadeada_Criar() {
	Lista_Encadeada* ListaEncadeada = (Lista_Encadeada*)malloc(sizeof(Lista_Encadeada));
	ListaEncadeada->primeiro = NULL;
    return ListaEncadeada;
}

/**Insere um valor na lista encadeada.
 * @Retorno: 1 caso tenha sido inserido com sucesso ou 0 caso contrario.
 */
short ListaEncadeada_Inserir(Lista_Encadeada* listaEncadeada, int valor_inserir) {
	Lista_Encadeada_Node* novoNo = (Lista_Encadeada_Node*)malloc(sizeof(Lista_Encadeada_Node));

	if (novoNo != NULL) {
		novoNo->info = valor_inserir;
		novoNo->prox = NULL;

		//Associa o primeiro no como o proximo do novo no.
		if (listaEncadeada->primeiro != NULL) {
			novoNo->prox = listaEncadeada->primeiro;
		}
		//O primeiro da lista passa a ser o novo no inserido:
		listaEncadeada->primeiro = novoNo;
	}
	return (novoNo != NULL);
}

/**Remove um valor da lista encadeada.
 * @Retorno: 1 caso tenha sido removido com sucesso ou 0 caso contrario.
 */
short ListaEncadeada_Remover(Lista_Encadeada* listaEncadeada, int valor_remover) {
	if (listaEncadeada->primeiro == NULL) {
		return 0;
	}
	Lista_Encadeada_Node* node = listaEncadeada->primeiro;
	Lista_Encadeada_Node* nodeAnterior = listaEncadeada->primeiro;

	short encontrado = 0;
	while (node != NULL && !encontrado) {
		//Verifica se encontrou o noh:
		if (node->info == valor_remover) {
			encontrado = 1;
		} else {
			nodeAnterior = node;
			node = node->prox;
		}
	}

	if (encontrado) {
		if (node == listaEncadeada->primeiro) {
			listaEncadeada->primeiro = node->prox;
		} else {
			nodeAnterior->prox = node->prox;
		}
		free(node);
	}
    return encontrado;
}

/**Exibe todos os elementos da lista encadeada em forma de string na tela.
 */
void ListaEncadeada_Imprimir(Lista_Encadeada* listaEncadeada) {
	Lista_Encadeada_Node* node = listaEncadeada->primeiro;
	printf("Lista {");
	while (node != NULL) {
		printf("%d", node->info);
		if (node->prox != NULL) {
			printf(", ");
		}
		node = node->prox;
	}
	printf("}\n");
}

/**Calcula o comprimento da lista encadeada.
 * @Parametro: listaEncadeada - Lista encadeada.
 * @Retorno: Comprimento da lista.
 */
int ListaEncadeada_CalcularComprimento(Lista_Encadeada* listaEncadeada) {
	int comprimento = 0;
	Lista_Encadeada_Node* node = listaEncadeada->primeiro;
	while (node != NULL) {
		comprimento++;
		node = node->prox;
	}
	return comprimento;
}

/**Conta quantas ocorrencias do numero 'n_procurado' ha na lista.
 * @Parametro: listaEncadeada - Lista encadeada.
 * @Parametro: n_procurado - Numero a ser procurado na lista.
 * @Retorno: Numero de ocorrencias de 'n_procurado' na lista.
 */
int ListaEncadeada_ProcurarOcorrencias(Lista_Encadeada* listaEncadeada, int n_procurado) {
	Lista_Encadeada_Node* node = listaEncadeada->primeiro;
	int numero_ocorrencias = 0;
	while (node != NULL) {
		//Verifica se encontrou o noh:
		if (node->info == n_procurado) {
			numero_ocorrencias++;
		}
		node = node->prox;
	}
	return numero_ocorrencias;
}

/**Procura todas as ocorrencias de 'n_original' na lista e as substitui por 'n_novo'.
 * @Parametro: listaEncadeada - Lista encadeada.
 * @Parametro: n_original - Numero original a ser procurado e substituido.
 * @Parametro: n_novo - Numero novo que substituira todos os 'n_original' da lista.
 * @Retorno: Numero de substituicoes efetudas.
 */
int ListaEncadeada_Procurar_E_Substituir(Lista_Encadeada* listaEncadeada, int n_original, int n_novo) {
	Lista_Encadeada_Node* node = listaEncadeada->primeiro;
	int contador_ocorrencias = 0;
	while (node != NULL) {
		//Verifica se encontrou o noh:
		if (node->info == n_original) {
			contador_ocorrencias++;
			node->info = n_novo;
		}
		node = node->prox;
	}
	return contador_ocorrencias;
}

/**Procura por um numero na lista 'listaEncadeada' e constroi duas listas:
 * uma com os elementos de 'listaEncadeada' que sao menores que 'n_meio' e
 * outra com os elementos de 'listaEncadeada' que sao maiores que 'n_meio'.
 * @Parametro: listaEncadeada - Lista encadeada.
 * @Parametro: n_meio - Numero que determina a divisao da lista.
 * @Retorno: Struct ListaDividida contendo as duas listas: menores e maiores.
 */
ListaDividida* ListaEncadeada_DividirLista(Lista_Encadeada* listaEncadeada, int n_meio) {
	Lista_Encadeada* listaMenores = ListaEncadeada_Criar();
	Lista_Encadeada* listaMaiores = ListaEncadeada_Criar();

	Lista_Encadeada_Node* node = listaEncadeada->primeiro;
	while (node != NULL) {
		//Verifica se encontrou o no:
		if (node->info < n_meio) {
			ListaEncadeada_Inserir(listaMenores, node->info);
		} else if (node->info > n_meio) {
			ListaEncadeada_Inserir(listaMaiores, node->info);
		}
		node = node->prox;
	}
	ListaDividida* listaDividida = (ListaDividida*) malloc(sizeof(ListaDividida));
	listaDividida->lista_menores = listaMenores;
	listaDividida->lista_maiores = listaMaiores;

	return listaDividida;
}

/**Obtem a intersecao de duas listas encadeadas.
 * @Parametro: listaEncadeada_a - Lista encadeada.
 * @Parametro: listaEncadeada_b - Lista encadeada.
 * @Retorno: Retorna uma lista encadeada condendo todos os elementos que fazem
 * parte da intersecao das listas 'listaEncadeada_a' e 'listaEncadeada_b'.
 */
Lista_Encadeada* ListaEncadeada_ObterIntersecao(Lista_Encadeada* listaEncadeada_a, Lista_Encadeada* listaEncadeada_b) {
	Lista_Encadeada* lista_intersecao = ListaEncadeada_Criar();
	Lista_Encadeada_Node* node_lista_a = listaEncadeada_a->primeiro;
	Lista_Encadeada_Node* node_lista_b;
	Lista_Encadeada_Node* node_lista_intersecao;
	short numero_ja_inserido; //boolean

	//Itera pelos elementos da lista 'a:'
	while (node_lista_a != NULL) {
		numero_ja_inserido = 0;
		node_lista_intersecao = lista_intersecao->primeiro;
		//Verifica se o elemento ja existe na lista de intersecao:
		while (node_lista_intersecao != NULL) {
			if (node_lista_a->info == node_lista_intersecao->info) {
				numero_ja_inserido = 1;
				break;
			}
			node_lista_intersecao = node_lista_intersecao->prox;
		}

		if (numero_ja_inserido == 0) {
			//Para cada elemento da lista 'a', percorre por todos os elementos da lista 'b':
			node_lista_b = listaEncadeada_b->primeiro;
			while (node_lista_b != NULL) {
				if (node_lista_a->info == node_lista_b->info) {
					ListaEncadeada_Inserir(lista_intersecao, node_lista_a->info);
					break; //Para o while que itera a lista 'b' e passa pro proximo da lista 'a'.
				}
				node_lista_b = node_lista_b->prox; //Passa para o proximo elemento da  lista 'b'.
			}
		}
		node_lista_a = node_lista_a->prox; //Passa para o proximo elemento da  lista 'a'.
	}

	return lista_intersecao;
}

/**Pergunta ao usuário qual das duas listas deve ser utilizada para uma operação.
 * @Parametro: lista1 - Lista encadeada 1.
 * @Parametro: lista1 - Lista encadeada 2.
 * @Retorno: Retorna a lista encadeada escolhida pelo usuario.
 */
Lista_Encadeada* perguntarQualListaUtilizar(Lista_Encadeada* lista1, Lista_Encadeada* lista2) {
	int num_lista;
	Lista_Encadeada* lista_escolhida;
	do {
		printf("Informe qual lista deseja utilizar (1 ou 2): ");
		scanf("%d", &num_lista);
		getchar();
	} while (num_lista != 1 && num_lista != 2);

	if (num_lista == 1) {
		lista_escolhida = lista1;
	} else {
		lista_escolhida = lista2;
	}
	return lista_escolhida;
}

//TESTE DAS FUNCIONALIDADES:
int main(void) {
	Lista_Encadeada* lista1 = ListaEncadeada_Criar();
	Lista_Encadeada* lista2 = ListaEncadeada_Criar();
	Lista_Encadeada* lista_auxiliar;

	int opcao_menu, numero_aux1, numero_aux2, resposta;
	printf("*Existem duas listas criadas na memoria. Para algumas operacoes eh necessario informar qual lista devera ser utilizada. Outras operacoes utilizarao as duas listas simultaneamente.\n\n");
	do {
		printf("--------------- TESTE DE OPERACOES COM LISTAS ---------------\n");
		printf(" 1 - Inserir em lista (Lista 1 ou Lista 2)\n");
		printf(" 2 - Remover da lista (Lista 1 ou Lista 2)\n");
		printf(" 3 - Imprimir as listas\n");
		printf(" 4 - Calcular comprimento das listas\n");
		printf(" 5 - Contar ocorrencias de um numero em uma lista (Lista 1 ou Lista 2)\n");
		printf(" 6 - Substituicao de ocorrencias de um numero em uma lista (Lista 1 ou Lista 2)\n");
		printf(" 7 - Dividir uma lista em duas (Lista 1 ou Lista 2)\n");
		printf(" 8 - Intersecao das listas\n");
		printf(" 0 - Sair\n");
		printf("Opcao: ");
		scanf("%d", &opcao_menu);
		getchar();
		printf("\n");

		switch (opcao_menu) {
			case 0:
				printf("Programa finalizado. Pressione [ENTER] para fechar.");
				break;
			case 1:
				lista_auxiliar = perguntarQualListaUtilizar(lista1, lista2);
				printf("Digite o valor para inserir: ");
				scanf("%d", &numero_aux1);
				getchar();
				ListaEncadeada_Inserir(lista_auxiliar, numero_aux1);
				printf("\tNumero inserido com sucesso.\n");

				getchar();
				system(COMANDO_LIMPAR_CONSOLE);
				break;
			case 2:
				lista_auxiliar = perguntarQualListaUtilizar(lista1, lista2);
				ListaEncadeada_Imprimir(lista_auxiliar);
				printf("Digite o valor para remover: ");
				scanf("%d", &numero_aux1);
				getchar();
				resposta = ListaEncadeada_Remover(lista_auxiliar, numero_aux1);
				if (resposta) {
					printf("\tNumero removido com sucesso.\n");
				} else {
					printf("\tNumero nao encontrado.\n");
				}

				getchar();
				system(COMANDO_LIMPAR_CONSOLE);
				break;
			case 3:
				ListaEncadeada_Imprimir(lista1);
				ListaEncadeada_Imprimir(lista2);

				getchar();
				system(COMANDO_LIMPAR_CONSOLE);
				break;
			case 4:
				printf("Comprimento das listas:\n");
				printf("\tLista 1: %d\n", ListaEncadeada_CalcularComprimento(lista1));
				printf("\tLista 2: %d\n", ListaEncadeada_CalcularComprimento(lista2));

				getchar();
				system(COMANDO_LIMPAR_CONSOLE);
				break;
			case 5:
				lista_auxiliar = perguntarQualListaUtilizar(lista1, lista2);
				printf("Digite o valor a procurar ocorrencias na lista: ");
				scanf("%d", &numero_aux1);
				getchar();
				resposta = ListaEncadeada_ProcurarOcorrencias(lista_auxiliar, numero_aux1);
				printf("\tQuantidade de ocorrencias na lista: %d \n", ListaEncadeada_ProcurarOcorrencias(lista_auxiliar, numero_aux1));

				getchar();
				system(COMANDO_LIMPAR_CONSOLE);
				break;
			case 6:
				lista_auxiliar = perguntarQualListaUtilizar(lista1, lista2);
				printf("Digite o valor a ser substituido na lista: ");
				scanf("%d", &numero_aux1);
				getchar();
				printf("Digite o novo valor que substituira o valor procurado: ");
				scanf("%d", &numero_aux2);
				getchar();
				resposta = ListaEncadeada_Procurar_E_Substituir(lista_auxiliar, numero_aux1, numero_aux2);
				if (resposta == 0) {
					printf("\tNenhuma ocorrencia do valor a ser substituido foi encontrada.\n");
				} else {
					printf("\tForam feitas %d substituicoes de '%d' por '%d'.\n", resposta, numero_aux1, numero_aux2);
				}

				getchar();
				system(COMANDO_LIMPAR_CONSOLE);
				break;
			case 7:
				lista_auxiliar = perguntarQualListaUtilizar(lista1, lista2);
				printf("Digite o valor do meio da lista: ");
				scanf("%d", &numero_aux1);
				getchar();
				resposta = ListaEncadeada_ProcurarOcorrencias(lista_auxiliar, numero_aux1);
				if (resposta == 0) {
					printf("Valor nao encontrado na lista.\n");
				} else {
					ListaDividida* subListas = ListaEncadeada_DividirLista(lista_auxiliar, numero_aux1);
					printf("\tLista com os elementos menores que %d: \n\t", numero_aux1);
					ListaEncadeada_Imprimir(subListas->lista_menores);
					printf("\tLista com os elementos maiores que %d: \n\t", numero_aux1);
					ListaEncadeada_Imprimir(subListas->lista_maiores);
				}
				getchar();
				system(COMANDO_LIMPAR_CONSOLE);
				break;
			case 8:
				lista_auxiliar = ListaEncadeada_ObterIntersecao(lista1, lista2);
				printf("Intersecao das listas: ");
				ListaEncadeada_Imprimir(lista_auxiliar);

				getchar();
				system(COMANDO_LIMPAR_CONSOLE);
				break;
			default:
				printf("Opcao invalida.\n");
		}
	} while (opcao_menu != 0);

	getchar();
	return 0;
}
/**
 * Questão 01. Suponha uma lista dinâmica de números inteiros. Implemente as seguintes
 * rotinas em C. (1,0 ponto)
 * a) Uma função que tenha como valor de retorno o comprimento da lista encadeada.
 * b) Uma função que receba como parâmetros uma lista encadeada e um número inteiro n
 * e retorne o número de nós da lista que possuem um campo info com valores iguais a n.
 * c) Uma função que receba como parâmetros uma lista encadeada e dois números
 * (original e novo) e troque todas as ocorrências do número original pelo número novo.
 * d) Uma função que receba como parâmetro uma lista encadeada e um valor inteiro n, e
 * retorne duas listas, de tal forma que a primeira lista possua todos os elementos que
 * são maiores que n e a segunda lista possua todos os elementos que são menores do
 * que n. Considere uma lista qualquer não ordenada.
 * e) Uma função que construa uma nova lista a partir dos números que fazem parte das
 * duas listas. Essa função deve receber como parâmetro as duas listas a serem
 * comparadas e retornar a lista resultante com os elementos que fazem parte da
 * interseção. Considere duas listas quaisquer não ordenadas.
 */

